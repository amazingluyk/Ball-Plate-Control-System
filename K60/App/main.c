/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"

uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
uint8 img[CAMERA_H][CAMERA_W];
unsigned char ssss[2];
unsigned char former[9];
unsigned char send_real[10];
unsigned char send_real1[10];
//��������
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void sendimg(void *imgaddr, uint32 imgsize);



/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ������ͷ LCD ����ʵ��
 */
void  main(void)
{
  int x_range=0,y_range=0,m=0,n=0;
  int i,j,real_x,real_y;
  int pass;
    uart_init(UART3,115200);
    //Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��
    //Size_t imgsize  = {CAMERA_W, CAMERA_H};             //ͼ���С
    //Size_t size;                   //��ʾ����ͼ���С

   // LCD_init();
    //LCD_str            (site,"Cam init ing",FCOLOUR,BCOLOUR);

    //size.H = LCD_H;
    //size.W = LCD_W;

    camera_init(imgbuff);
   // uart_putchar (UART3,'F');
    //LCD_str            (site,"Cam init OK!",FCOLOUR,BCOLOUR);
    //site.y = 110;
    //LCD_FSTR_CH(site,vcan_str,FCOLOUR,BCOLOUR);

    //�����жϷ�����
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //���� PORTA ���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //���� DMA0 ���жϷ�����Ϊ PORTA_IRQHandler

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
        camera_get_img();                                   //����ͷ��ȡͼ��
                      //�ڰ�����ͷ
        //LCD_Img_Binary_Z(site, size, imgbuff, imgsize);

        /******************** ɽ��๦�ܵ������� ���ڰ�ģʽ�� ����ͼ����λ�� ***********************/
      //  imgbuff[line*center_y+center_x/8]
   //     vcan_sendimg(imgbuff, sizeof(imgbuff));

        /******************** ɽ��๦�ܵ������� ���Ҷ�ģʽ�� ����ͼ����λ�� ***********************/
      // img_extract(img, imgbuff, CAMERA_SIZE);          //��ѹΪ�Ҷ�ͼ�񣬷��㷢�͵���λ����
       // vcan_sendimg(img, sizeof(img));

        /******************** ����ͼ����λ�� ***********************/

        img_extract(img, imgbuff, CAMERA_SIZE);          //��ѹΪ�Ҷ�ͼ�񣬷��㷢�͵���λ����
        //sendimg(img, CAMERA_W * CAMERA_H);                    //���͵���λ��
       
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
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 29;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //ʹ�����ж�
    n = 28;
    if(flag & (1 << n))                                 //PTA28�����ж�
    {
        camera_href();
    }
#endif


}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}


//����ͼ����λ����ʾ
//��ͬ����λ������ͬ���������ʹ�� yy_����ͷ���ڵ��� ���
//���ʹ��������λ��������Ҫ�޸Ĵ���
void sendimg(void *imgaddr, uint32 imgsize)
{
    uint8 cmd[4] = {0, 255, 1, 0 };    //yy_����ͷ���ڵ��� ʹ�õ�����

    uart_putbuff(VCAN_PORT, (uint8_t *)cmd, sizeof(cmd));    //�ȷ�������

    uart_putbuff(VCAN_PORT, imgaddr, imgsize); //�ٷ���ͼ��
}

