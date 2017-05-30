#include "contiki.h"
#include "contiki-conf.h"
#include "dev/netconfig.h"
#include "stdio.h"
#include "node-id.h"
#if CONTIKI_CONF_NETSYNCH
#include "netsynch.h"
#include "task-schedule.h"
#endif

// void led_toggle(uint32_t i);
void logic_test(uint32_t i);
static uint32_t logic=0;
// static uint32_t add_time=0;

#if CC1310_CONF_LOWPOWER


static volatile uint8_t  active_flag_one_second_before = 0;
static volatile uint16_t  init_net_flag = 1;

#if WAKEUP_NODE_DEV
static volatile uint8_t  active_flag = 1;
#else
static volatile uint8_t  active_flag = 0;
#endif

static uint8_t schedule_bit[18]; 

static soft_time  timenow;
static int cal_offest = 0;            
static uint32_t cal_interval = 0;
static uint32_t cal_count = 0;

static uint16_t days=0;
static uint8_t  ledon_flag =0;

#if !WAKEUP_NODE_DEV
//static void update_soft_time();
#endif

void update_soft_time()

{
  // logic=logic^1;
  // led_toggle(logic);
  // add_time++;
  // // printf("time %d\n",add_time);

  timenow.sec+=1;
  if( timenow.sec/60){ 
      ++timenow.minute;
      timenow.sec=0;
  }

  if( timenow.minute/60 ){
      ++timenow.hour; 
      timenow.minute=0;
  }
  if( timenow.hour/24 ){
      timenow.hour=0;
      ++days;
  }

}

void set_init_flag(uint16_t flag){
    init_net_flag =flag;
}

void set_ledon_flag(uint8_t flag){
  ledon_flag = flag;
}

uint16_t get_init_flag(){
  return init_net_flag ;
}

#if !WAKEUP_NODE_DEV
// void set_active_flag(int hour,int minute,int second_s)
void set_active_flag()
{
//   calendar_time  cal_time_now;
  int index=0;
  // read_calendar(&cal_time_now);
  // int hour   = BCD_to_dec(cal_time_now.hour);
  // int minute = BCD_to_dec(cal_time_now.min);
  // index=hour*6+minute/10;         //6 ,10
  index=timenow.hour*6+timenow.minute/10;         //6   ,10
  schedule_bitmap_get(schedule_bit);

#if 0  
  int index2=0;
  for(;index2<18;index2++){
    printf("schedule_bit [%d] = %d\n",index2,schedule_bit[index2] );
  }
#endif
  active_flag= init_net_flag&((schedule_bit[index/8]) >> (7-(index%8)));

  #if !ROOTNODE
     //printf("active flag:%u\n",active_flag);
  #endif
 //  active_flag = 1;

  // if(timenow.sec%30==0){
     
  //   active_flag =active_flag^1;
  //   logic =logic^1;
  //   logic_test(logic);
  // }

  //  active_flag = 1;

}
#endif


void syn_update_timenow(soft_time syntime)
{
   timenow.minute=syntime.minute;
   timenow.hour  =syntime.hour;
   timenow.sec   =syntime.sec;
}

void get_timenow(soft_time *times)
{
   times->hour   =timenow.hour;
   times->minute =timenow.minute;
   times->sec    =timenow.sec;
}

clock_time_t get_idle_time(void)  //return 0 means not in active mode .
{
  uint8_t counter=0;
  int index=0;
  int i=0;

  // get_timenow(&timenow);
  if(active_flag){
    index=timenow.hour*6 +timenow.minute/10 +1;
      // printf("index :%d\n",index);
    for(;i<144;i++){
      if((((schedule_bit[index/8]) >> (7-(index%8)) ) & 0x01)){
             index=(index+1)%144;
             ++counter;
    }else 
      break;
    }
    // printf("%d %d\n",counter,index);
    return ((10*counter+9-timenow.minute%10)*60+(60-timenow.sec)); 
  }
  return 0x0;
}

uint8_t get_active_flag(void)
{
  return active_flag;
}

uint16_t 
get_nowdays()
{
  return days;
}
/*----------------------------------------------------------------*/

void 
set_autocal_info(int autocal_offest,uint32_t autocal_interval){
  cal_count = 0;
  cal_offest = autocal_offest;
  cal_interval = autocal_interval;
}


/********************************************************/
uint32_t get_cal_count(){
  return cal_count;
}

void set_cal_countaddone(){
  cal_count++;
  // printf
}

int get_cal_offest(){
  // cal_offest=0;
  return cal_offest;
}
int get_cal_interval(){

  return cal_interval;
}
void set_cal_countzero(){
  cal_count=0;
}

#endif