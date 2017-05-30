/*
 * Copyright (c) 2014, Texas Instruments Incorporated - http://www.ti.com/
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*---------------------------------------------------------------------------*/
/**
 * \addtogroup cc13xx-cc26xx-rtc
 * @{
 *
 * \file
 * Implementation of the CC13xx/CC26xx AON RTC driver
 */
/*---------------------------------------------------------------------------*/
#include "contiki.h"
#include "sys/energest.h"
#include "rtimer.h"
#include "lpm.h"

#include "ti-lib.h"
#include "netconfig.h"
#include <stdint.h>
#include <stdbool.h>
/*---------------------------------------------------------------------------*/
#if CONTIKI_CONF_NETSYNCH
#include "netsynch.h"
#include "task-schedule.h"
#endif

/*---------------------------define hit platform softclock-------------------------------------*/


static uint8_t  active_flag_one_second_before = 0;

/*define our time interval.such as active period or inactive period*/
#define RTC_TIME (RTIMER_SECOND)   //10 minutes
/*---------------------------------------------------------------------------*/
#define soc_rtc_isr(...) AONRTCIntHandler(__VA_ARGS__)
/*---------------------------------------------------------------------------*/
/* Prototype of a function in clock.c. Called every time the handler fires */
void clock_update(void);

static rtimer_clock_t last_isr_time;
/*---------------------------------------------------------------------------*/
#define COMPARE_INCREMENT (RTIMER_SECOND / CLOCK_SECOND)
// #define COMPARE_INCREMENT (RTIMER_SECOND /128 )
#define MULTIPLE_512_MASK 0xFFFFFE00
/*---------------------------------------------------------------------------*/
/*
 * Used to test timer wraparounds.
 *
 * Set to 0xFFFFFFFA to test AON RTC second counter wraparound
 * Set to 0xFFFA to test AON RTC 16.16 format wraparound
 */
#ifdef SOC_RTC_CONF_START_TICK_COUNT
#define SOC_RTC_START_TICK_COUNT SOC_RTC_CONF_START_TICK_COUNT
#else
#define SOC_RTC_START_TICK_COUNT 0
#endif


/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
void
soc_rtc_init(void)
{
  bool interrupts_disabled;
  uint32_t next;

  /* Disable and clear interrupts */
  interrupts_disabled = ti_lib_int_master_disable();

  ti_lib_aon_rtc_disable();

  ti_lib_aon_rtc_event_clear(AON_RTC_CH0);
  ti_lib_aon_rtc_event_clear(AON_RTC_CH1);
  ti_lib_aon_rtc_event_clear(AON_RTC_CH2);//add by hit


  /* Setup the wakeup event */
  ti_lib_aon_event_mcu_wake_up_set(AON_EVENT_MCU_WU0, AON_EVENT_RTC_CH0);
  ti_lib_aon_event_mcu_wake_up_set(AON_EVENT_MCU_WU1, AON_EVENT_RTC_CH1);
  ti_lib_aon_event_mcu_wake_up_set(AON_EVENT_MCU_WU2, AON_EVENT_RTC_CH2);//add by hit


  ti_lib_aon_rtc_combined_event_config(AON_RTC_CH0 | AON_RTC_CH1 | AON_RTC_CH2);//change by hit

  HWREG(AON_RTC_BASE + AON_RTC_O_SEC) = SOC_RTC_START_TICK_COUNT;

  next = ti_lib_aon_rtc_current_compare_value_get() + COMPARE_INCREMENT;

  /* Configure channel 1 to start generating clock ticks. First tick at 512 */
  ti_lib_aon_rtc_compare_value_set(AON_RTC_CH1, next);

  
  next = ti_lib_aon_rtc_current_compare_value_get() + RTC_TIME;

  /* Configure channel 1 to start generating clock ticks. First tick at 512 */
  ti_lib_aon_rtc_compare_value_set(AON_RTC_CH2, next);



  /* Enable channel 1 and the RTC */
  ti_lib_aon_rtc_channel_enable(AON_RTC_CH1);
  ti_lib_aon_rtc_channel_enable(AON_RTC_CH2);// add by hit

  ti_lib_aon_rtc_enable();

  ti_lib_int_enable(INT_AON_RTC);

  /* Re-enable interrupts */
  if(!interrupts_disabled) {
    ti_lib_int_master_enable();
  }
}
/*---------------------------------------------------------------------------*/
rtimer_clock_t
soc_rtc_get_next_trigger()
{
  rtimer_clock_t ch1 = ti_lib_aon_rtc_compare_value_get(AON_RTC_CH1);

  if(HWREG(AON_RTC_BASE + AON_RTC_O_CHCTL) & AON_RTC_CHCTL_CH0_EN) {
    rtimer_clock_t ch0 = ti_lib_aon_rtc_compare_value_get(AON_RTC_CH0);

    return RTIMER_CLOCK_LT(ch0, ch1) ? ch0 : ch1;
  }

  return ch1;
}
/*---------------------------------------------------------------------------*/
void
soc_rtc_schedule_one_shot(uint32_t channel, uint32_t ticks)
{
  if((channel != AON_RTC_CH0) && (channel != AON_RTC_CH1)) {
    return;
  }

  /* Set the channel to fire a one-shot compare event at time==ticks */
  ti_lib_aon_rtc_compare_value_set(channel, ticks);
  ti_lib_aon_rtc_channel_enable(channel);

}

void enable_etimer(){
  
  uint32_t next;
  next = ti_lib_aon_rtc_current_compare_value_get() + COMPARE_INCREMENT;

  // /* Configure channel 1 to start generating clock ticks. First tick at 512 */
  ti_lib_aon_rtc_compare_value_set(AON_RTC_CH1, next);
  ti_lib_aon_rtc_channel_enable(AON_RTC_CH1);
  
 

}

void disable_etimer(){

  ti_lib_aon_rtc_channel_disable(AON_RTC_CH1);
}
/*---------------------------------------------------------------------------*/
rtimer_clock_t
soc_rtc_last_isr_time(void)
{
  return last_isr_time;
}
/*---------------------------------------------------------------------------*/
/* The AON RTC interrupt handler */
void
soc_rtc_isr(void)
{
  uint32_t now, next;

  // ENERGEST_ON(ENERGEST_TYPE_IRQ);

  last_isr_time = RTIMER_NOW();

  now = ti_lib_aon_rtc_current_compare_value_get();

  if(ti_lib_aon_rtc_event_get(AON_RTC_CH2)){// add by hit cps

    HWREG(AON_RTC_BASE + AON_RTC_O_EVFLAGS) = AON_RTC_EVFLAGS_CH2;

   
    /*********************************************/

#if !WAKEUP_NODE_DEV  

#if ROOTNODE
    update_soft_time();
#else      
    /*if(ledon_flag){
      leds_off(LEDS_ALL);
      ledon_flag =0;
    }*/

    /*++cal_count;
    if(cal_offest != 0 && cal_count >= cal_interval){
      cal_count = 0;
      if(cal_offest < 0){
        update_soft_time();
        update_soft_time();
      }
    }else{
      update_soft_time();
    }*/
    set_cal_countaddone();
    if(get_cal_offest()!= 0&&get_cal_count()>=get_cal_interval()){
        set_cal_countzero();
        if(get_cal_offest()<0){
          update_soft_time();
          update_soft_time();
        }

    }else{
        update_soft_time();

    }

#endif

       active_flag_one_second_before=get_active_flag();
       set_active_flag();
       // set_active_flag(timenow.hour,timenow.minute,timenow.sec);

      if(get_active_flag()!=active_flag_one_second_before){
        
         if(get_active_flag() ==1){
           enable_etimer();
           task_schedule_change();
           
         }
      }   
#endif
// if node is root node keep working in active state forever.
  
#if  (!ROOTNODE) & (!WAKEUP_NODE_DEV)
    if(get_active_flag() ==1){ 
          
      ;;//because of multiple shutdown that lead to etimer err time sequence
  
    }else {         

      disable_etimer();    //etimer  off
  
   }
#endif
    

    /***********************************************/
    next = (now + RTC_TIME);
    
    ti_lib_aon_rtc_compare_value_set(AON_RTC_CH2, next);
  }

  if(ti_lib_aon_rtc_event_get(AON_RTC_CH1)) {
    HWREG(AON_RTC_BASE + AON_RTC_O_EVFLAGS) = AON_RTC_EVFLAGS_CH1;
     
     /* Adjust the s/w tick counter irrespective of which event trigger this */
      clock_update();
       // logic =logic^1;
       // led_toggle(logic);   
    /*
     * We need to keep ticking while we are awake, so we schedule the next
     * event on the next 512 tick boundary. If we drop to deep sleep before it
     * happens, lpm_drop() will reschedule us in the 'distant' future
     */

      next = (now + COMPARE_INCREMENT) & MULTIPLE_512_MASK;

      ti_lib_aon_rtc_compare_value_set(AON_RTC_CH1, next);

  }

  if(ti_lib_aon_rtc_event_get(AON_RTC_CH0)) {
    ti_lib_aon_rtc_channel_disable(AON_RTC_CH0);
    HWREG(AON_RTC_BASE + AON_RTC_O_EVFLAGS) = AON_RTC_EVFLAGS_CH0;
    rtimer_run_next();
    
  }

  // ENERGEST_OFF(ENERGEST_TYPE_IRQ);
  
}
/*---------------------------------------------------------------------------*/
/** @} */
