#include "contiki.h"
#include "net/netstack.h"
#include "bat-voltage.h"

#include <stdio.h>
#include <string.h>
#define PERIOD 3
#define SEND_INTERVAL (PERIOD*CLOCK_SECOND)
static int i=0;
PROCESS(radio_sender_process,"radio sender process");
AUTOSTART_PROCESSES(&radio_sender_process);
PROCESS_THREAD(radio_sender_process,ev,data)
{
	
	static struct etimer periodic;
	PROCESS_BEGIN();
    printf("%s\n","Startting sender");
	etimer_set(&periodic,SEND_INTERVAL);
    char buf[25]="Hello World!";
    char *sender=buf;
   
	while(1){
		PROCESS_YIELD_UNTIL(ev==PROCESS_EVENT_TIMER);
		if(etimer_expired(&periodic)){
			i = get_voltage();
			// i ++;
			sprintf(buf, " Hello %d,", i);
			etimer_reset(&periodic);
		    NETSTACK_RADIO.send(buf,sizeof(buf));
			printf("send %s\n",sender);
		}
	}
	
	PROCESS_END();
}