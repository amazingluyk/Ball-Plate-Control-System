#ifndef _tim3_h
#define _tim3_h

#include "stm32f10x.h"


#define RCC_APB1Periph_TIMx     RCC_APB1Periph_TIM3
#define TIM_CounterMode_x       TIM_CounterMode_Up


void Timer3_init(void);
void Isr_Init(void);

extern uint16_t sta;
extern uint16_t sta_flag;

#endif /*__BSP_TIMER_H*/
