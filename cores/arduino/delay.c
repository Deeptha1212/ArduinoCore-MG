/**
 * Project                           : Secure IoT SoC
 * Name of the file                  : delays.c
 * Brief Description of file         : This is the source file for all types of delays from utilites .
 * Name of Author                    : Suneeth Damodharan
 * Email ID                          : suneeth@mindgrovetech.in
 * 
 * @file delays.c
 * @author suneeth@mingrovetech.in 
 * @brief This is the source file for all types of delays
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) Mindgrove Technologies Pvt. Ltd 2024. All rights reserved.
 * 
 */

#include "delay.h"


static inline uint64_t mcycles(void)
{
  uint64_t mcycle_value;
  asm volatile("csrr %0 mcycle":"=r"(mcycle_value));
  return mcycle_value;
}


void delayms(long delay)
{
  for(int i=0;i<(3334*delay*(40000000/40000000));i++){
    asm volatile("NOP");
  }
}


void delayus(long delay)
{
  for(int i=0;i<(4*delay*(40000000/40000000));i++){
    asm volatile("NOP");
  }
}
 

