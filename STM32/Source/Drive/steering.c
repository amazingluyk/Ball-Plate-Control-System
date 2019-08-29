#include "steering.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

void steering_Init()		//��ʱ����ʼ��
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  /*  ����dingshiqiʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); /* ����GPIOʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  /* �����ܽŸ��ù���*/
	
	TIM_TimeBaseInitStructure.TIM_Period = 1999;			  //��ʱ50HZ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 719;			//ϵͳ��Ƶ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, & TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM4, ENABLE);                              //��ʱ��ʹ�� 

	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;	          //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //���ø����������ģʽ��ע��PWM�Ǹ������������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOB,&GPIO_InitStructure);                 /* ��ʼ��GPIO */	

		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;	          //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //���ø����������ģʽ��ע��PWM�Ǹ������������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC3Init(TIM4, & TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);	
	
	
	TIM_OC4Init(TIM4, & TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
}

