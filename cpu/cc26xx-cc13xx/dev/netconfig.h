#ifndef NETCONFIG_H_
#define NETCONFIG_H_

/************************define hit softtime*************************************/


#if CC1310_CONF_LOWPOWER

void update_soft_time();

void set_active_flag();//get active flag from 
// void set_active_flag(int hour,int minute,int second_s);//get active flag from 

void syn_update_timenow(soft_time syntime);

void get_timenow(soft_time *times);

uint8_t get_active_flag(void);

clock_time_t get_idle_time(void);

void set_init_flag(uint16_t  flag);
     
uint16_t get_init_flag();    

void set_autocal_info(int autocal_offest,uint32_t autocal_interval);
uint16_t get_nowdays();

void set_ledon_flag(uint8_t flag);

uint32_t get_cal_count();
void set_cal_countaddone();

int get_cal_offest();

void set_cal_countzero();

int get_cal_interval();

#endif


#endif/*NETCONFIG*/