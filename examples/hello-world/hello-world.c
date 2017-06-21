/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
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
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"
#include "dev/watchdog.h"
#include "node-id.h"
// #include "bat-voltage.h"

#include <stdio.h> /* For printf() */

// void led_toggle(uint32_t i);
// void logic_test(uint32_t i);
// static uint32_t logic=0;
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);

PROCESS_THREAD(hello_world_process, ev, data)
{

  PROCESS_BEGIN();
  // //printf(" %x\n",get_voltage());
  // static struct etimer et;
  // etimer_set(&et,4*CLOCK_SECOND);
  // unsigned long cpu,lpm,transmit,listen,irq;
  // while(1)
  // {
    
  //    PROCESS_YIELD();
  //    if(etimer_expired(&et)&& ev==PROCESS_EVENT_TIMER)
  //    {
      
  //     cpu      = energest_type_time(ENERGEST_TYPE_CPU)      ;
  //     lpm      = energest_type_time(ENERGEST_TYPE_LPM)      ;
  //     listen   = energest_type_time(ENERGEST_TYPE_LISTEN)   ;
  //     //printf("cpu  %lu  , lpm  %lu\n", cpu,lpm);
  //     printf("listen  %lu\n", listen);
  //     energest_type_set(ENERGEST_TYPE_CPU,0);
  //     energest_type_set(ENERGEST_TYPE_LPM,0);
  //     energest_type_set(ENERGEST_TYPE_LISTEN,0);
      printf("hello-world!\n");
  //     //printf("voltage: %d\n",get_voltage());
  //    //  // printf("restart count %d\n",restart_count );
  //    //  restart_count_byte_restore();
  //    //  printf("restart count %d\n",restart_count );
  //    //  restart_count++;
  //    //  restart_count_byte_burn(restart_count);
  //     etimer_set(&et,5*CLOCK_SECOND);
  //    }

  // }
 
 PROCESS_END();

}

