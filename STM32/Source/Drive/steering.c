#include "steering.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

void steering_Init()		//定时器初始化
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  /*  开启dingshiqi时间*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); /* 开启GPIO时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  /* 开启管脚复用功能*/
	
	TIM_TimeBaseInitStructure.TIM_Period = 1999;			  //定时50HZ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 719;			//系统分频
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, & TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM4, ENABLE);                              //定时器使能 

	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;	          //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //设置复用推挽输出模式（注意PWM是复用推挽输出）
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOB,&GPIO_InitStructure);                 /* 初始化GPIO */	

		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;	          //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //设置复用推挽输出模式（注意PWM是复用推挽输出）
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC3Init(TIM4, & TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);	
	
	
	TIM_OC4Init(TIM4, & TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
}

