#include "moto.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"
#include "misc.h"	 
void moto_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //初始化GPIOD3,6
 	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOD3,6
 	GPIO_SetBits(GPIOB,GPIO_Pin_7);
}
void moto_run(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_1,Bit_SET);
	delay_ms(1);
	GPIO_WriteBit(GPIOA, GPIO_Pin_1,Bit_RESET);
}
void moto_backrun(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_1,Bit_SET);
	delay_ms(1);
	GPIO_WriteBit(GPIOA, GPIO_Pin_1,Bit_RESET);
}
