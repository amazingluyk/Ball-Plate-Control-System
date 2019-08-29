#include "hongwai.h" 
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
void hongwai_Init(void)
{
GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //输入
 	GPIO_Init(GPIOF, &GPIO_InitStructure);	  //初始化GPIOD3,6
 	GPIO_SetBits(GPIOF,GPIO_Pin_13|GPIO_Pin_15);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //输入
 	GPIO_Init(GPIOG, &GPIO_InitStructure);	  //初始化GPIOD3,6
 	GPIO_SetBits(GPIOG,GPIO_Pin_1);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);	  //初始化GPIOD3,6
 	GPIO_SetBits(GPIOE,GPIO_Pin_1);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);	  //初始化GPIOD3,6
	
}
