#include "ti-lib.h"
#include "contiki.h"
#include "sys_ctrl.h"
#include "dev/oscillators.h"
#include "dev/soc-rtc.h"
#include "dev/watchdog.h"
#include "dev/uart1.h"
#include "dev/serial-line.h"
#include "lib/sensors.h"
#include "lpm.h"
//Net Setting
#include "ieee-addr.h"
#include "contiki-net.h"
#include "net/netstack.h"
#include "rf-core/rf-core.h"
#include "flashdata.h"

//**********************************//
#if CONTIKI_CONF_NETSYNCH
#include "netsynch.h"
#include "task-schedule.h"

 // #include "adc.h"

  #if ROOTNODE
    #include "correct_time.h"
  #endif
 
#endif

#include <stdio.h>
#include <string.h>
#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif
/*---------------------------------------------------------------------------*/
/** \brief Board specific iniatialisation */
void board_init(void);


/*---------------------------------------------------------------------------*/
static void
set_rf_params(void)
{
  uint16_t short_addr;
  uint8_t ext_addr[8];
  radio_value_t val = 0;

  ieee_addr_cpy_to(ext_addr, 8);

  short_addr = ext_addr[7];
  short_addr |= ext_addr[6] << 8;

  /* Populate linkaddr_node_addr. Maintain endianness */
  memcpy(&linkaddr_node_addr, &ext_addr[8 - LINKADDR_SIZE], LINKADDR_SIZE);

  NETSTACK_RADIO.set_value(RADIO_PARAM_PAN_ID, IEEE802154_PANID);
  NETSTACK_RADIO.set_value(RADIO_PARAM_16BIT_ADDR, short_addr);
  NETSTACK_RADIO.set_value(RADIO_PARAM_CHANNEL, RF_CORE_CHANNEL);
  NETSTACK_RADIO.set_object(RADIO_PARAM_64BIT_ADDR, ext_addr, 8);

  NETSTACK_RADIO.get_value(RADIO_PARAM_CHANNEL, &val);

}


int
main(void)
{
    
  ti_lib_int_master_disable();
  /* Set the LF XOSC as the LF system clock source */
  oscillators_select_lf_xosc();

  lpm_init();
  
  board_init();

  printf("Starting " CONTIKI_VERSION_STRING "\n");
  printf("supports cc13xx platform\n");
  printf("author HIT-CPSGroup\n");

  ti_lib_int_master_enable(); 

  soc_rtc_init();

  rtimer_init();
  /**********************************************/

   // write_to_flash();
  /*************************************************/

  watchdog_init();
  
  process_init(); 

  random_init(0x1234);

  /*set uart-input function*/
  // uart1_set_input(serial_line_input_byte);
  serial_line_init();

  process_start(&etimer_process, NULL);
  ctimer_init();

  energest_init();
  ENERGEST_ON(ENERGEST_TYPE_CPU);

  printf(" Net: ");
  printf("%s\n", NETSTACK_NETWORK.name);
  printf(" MAC: ");
  printf("%s\n", NETSTACK_MAC.name);
  printf(" RDC: ");
  printf("%s\n", NETSTACK_RDC.name);

  /****************by xiaobing **************/
  #if CONTIKI_CONF_NETSYNCH

   netsynch_init();

   #if  ROOTNODE  
    // netsynch_set_authority_level(0); 
   correct_time_init();
   #endif 

  task_schedule_init();

  #endif
/******************************/

  netstack_init();
  set_rf_params();
#if NETSTACK_CONF_WITH_IPV6
  memcpy(&uip_lladdr.addr, &linkaddr_node_addr, sizeof(uip_lladdr.addr));
  queuebuf_init();
  process_start(&tcpip_process, NULL);
#endif /* NETSTACK_CONF_WITH_IPV6 */

  autostart_start(autostart_processes);

  watchdog_start();

  while(1) {
    
    uint8_t r;
    
    do {
      r = process_run();
      watchdog_periodic();
    } while(r > 0);
    
    // lpm_drop();
   
  }

}