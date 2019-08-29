/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"

uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
uint8 img[CAMERA_H][CAMERA_W];
unsigned char ssss[2];
unsigned char former[9];
unsigned char send_real[10];
unsigned char send_real1[10];
//函数声明
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void sendimg(void *imgaddr, uint32 imgsize);



/*!
 *  @brief      main函数
 *  @since      v5.0
 *  @note       山外摄像头 LCD 测试实验
 */
void  main(void)
{
  int x_range=0,y_range=0,m=0,n=0;
  int i,j,real_x,real_y;
  int pass;
    uart_init(UART3,115200);
    //Site_t site     = {0, 0};                           //显示图像左上角位置
    //Size_t imgsize  = {CAMERA_W, CAMERA_H};             //图像大小
    //Size_t size;                   //显示区域图像大小

   // LCD_init();
    //LCD_str            (site,"Cam init ing",FCOLOUR,BCOLOUR);

    //size.H = LCD_H;
    //size.W = LCD_W;

    camera_init(imgbuff);
   // uart_putchar (UART3,'F');
    //LCD_str            (site,"Cam init OK!",FCOLOUR,BCOLOUR);
    //site.y = 110;
    //LCD_FSTR_CH(site,vcan_str,FCOLOUR,BCOLOUR);

    //配置中断服务函数
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //设置 PORTA 的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //设置 DMA0 的中断服务函数为 PORTA_IRQHandler

    former[0]='0';
    former[1]='1';
    former[2]=' ';
    former[3]='0';
    former[4]='2';
    former[5]=' ';
    former[6]='0';
    former[7]='3';
    former[8]=' ';
    
    while(1)
    {
        camera_get_img();                                   //摄像头获取图像
                      //黑白摄像头
        //LCD_Img_Binary_Z(site, size, imgbuff, imgsize);

        /******************** 山外多功能调试助手 【黑白模式】 发送图像到上位机 ***********************/
      //  imgbuff[line*center_y+center_x/8]
   //     vcan_sendimg(imgbuff, sizeof(imgbuff));

        /******************** 山外多功能调试助手 【灰度模式】 发送图像到上位机 ***********************/
      // img_extract(img, imgbuff, CAMERA_SIZE);          //解压为灰度图像，方便发送到上位机显
       // vcan_sendimg(img, sizeof(img));

        /******************** 发送图像到上位机 ***********************/

        img_extract(img, imgbuff, CAMERA_SIZE);          //解压为灰度图像，方便发送到上位机显
        //sendimg(img, CAMERA_W * CAMERA_H);                    //发送到上位机
       
        real_y=60;
        real_x=84;
        y_range=0;
        x_range=0;
        i=84;
        j=60;
        pass=0;
        while(1)
        {
          pass=0;
          n=i-y_range;
            for(m=j-x_range;m<(j+x_range+1);m++)
            {
              if(img[m][n])
              {
                if(img[m][n+1])
                {
                   if(img[m][n-1])
                   {
                      if(img[m+1][n])
                      {
                         if(img[m-1][n])
                         {
                          pass=1;
                          real_y=m;
                          real_x=n;
                          break;
                         }
                      }
                   }
                }
              }
            }
            if(pass==1)
            {
              break;
            }
            m=j+x_range;
            for(n=i-x_range;n<(i+x_range+1);n++)
            {
             if(img[m][n])
              {
                if(img[m][n+1])
                   if(img[m][n-1])
                      if(img[m+1][n])
                         if(img[m-1][n])
                         {
                          pass=1;
                          real_y=m;
                          real_x=n;
                          break;
                         }
              }
            }
            if(pass==1)
            {
              break;
            }
            n=i+y_range;
            for(m=j+x_range;m>(j-x_range-1);m--)
            {
            if(img[m][n])
              {
                if(img[m][n+1])
                   if(img[m][n-1])
                      if(img[m+1][n])
                         if(img[m-1][n])
                         {
                          pass=1;
                          real_y=m;
                          real_x=n;
                          break;
                         }
              }
            }
            if(pass==1)
            {
              break;
            }
            m=j-x_range;
            for(n=i+x_range;n>(i-x_range-1);n--)
            {
             if(img[m][n])
              {
                if(img[m][n+1])
                   if(img[m][n-1])
                      if(img[m+1][n])
                         if(img[m-1][n])
                         {
                          pass=1;
                          real_y=m;
                          real_x=n;
                          break;
                         }
              }
            }
            if(pass==1)
            {
              break;
            }
            x_range++;
            y_range++;
             if(x_range>52)
             {
                  break;
             }
        }
         y_range=0;
         x_range=0;
        send_real[0]=real_x;
       send_real1[0]=' ';
        send_real1[1]=real_y;
        ssss[0]='\r';
        ssss[1]='\n';
    uart_putbuff(VCAN_PORT,former,9);
      uart_putbuff(VCAN_PORT,send_real,1);
      
      uart_putbuff(VCAN_PORT,send_real1,2);
         uart_putbuff(VCAN_PORT,ssss,2);
        
         /*
        for(i=0;i<CAMERA_SIZE;i++)
        {
          imgbuff[i]=0XFF;
        }
          imgbuff[20*real_y+real_x/8]&=~(0X80>>(real_x%8));
        vcan_sendimg(imgbuff, sizeof(imgbuff));
        */
    }
    
}



/*!
 *  @brief      PORTA中断服务函数
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //清中断标志位

    n = 29;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //使用行中断
    n = 28;
    if(flag & (1 << n))                                 //PTA28触发中断
    {
        camera_href();
    }
#endif


}

/*!
 *  @brief      DMA0中断服务函数
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}


//发送图像到上位机显示
//不同的上位机，不同的命令，这里使用 yy_摄像头串口调试 软件
//如果使用其他上位机，则需要修改代码
void sendimg(void *imgaddr, uint32 imgsize)
{
    uint8 cmd[4] = {0, 255, 1, 0 };    //yy_摄像头串口调试 使用的命令

    uart_putbuff(VCAN_PORT, (uint8_t *)cmd, sizeof(cmd));    //先发送命令

    uart_putbuff(VCAN_PORT, imgaddr, imgsize); //再发送图像
}

