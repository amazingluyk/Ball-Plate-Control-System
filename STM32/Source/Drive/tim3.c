#include "tim3.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"
uint16_t	sta = 0;
uint16_t	sta_flag = 0;
void Timer3_init(void)	
{	 
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure1;

RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMx,ENABLE);

TIM_TimeBaseStructure1.TIM_Period = 9999; 
TIM_TimeBaseStructure1.TIM_Prescaler =720-1;   	    
TIM_TimeBaseStructure1.TIM_ClockDivision = 0x0; 				
TIM_TimeBaseStructure1.TIM_CounterMode = TIM_CounterMode_x; 
TIM_DeInit(TIM3);
TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure1); 
TIM_ClearFlag(TIM3,TIM_FLAG_Update);               
TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  
TIM_Cmd(TIM3, ENABLE); 	 //使能定时器2
	
 /*以下定时器3中断初始化*/
TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //向上计数溢出产生中断

}

void Isr_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure1; 
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  NVIC_InitStructure1.NVIC_IRQChannel =TIM3_IRQn;// TIM3_IRQChannel; 
  NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 0; 
  NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init (&NVIC_InitStructure1);
	
}


