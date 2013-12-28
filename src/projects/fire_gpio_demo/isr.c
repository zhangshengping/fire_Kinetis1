/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��isr.c
 * ����         ���жϴ�������
 *          
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ���������� 
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/	



#include "common.h"
#include "include.h"
#include "nokia_5110.h"

extern u32 i,j;
extern u8 image[40][40];
extern u8 finish_flag;
u8 cow = 0, row = 0, line = 0;
u32 hang,chang;

void image_us()
{
   int i =0;
   int j=0;
   for(i=0;i<25;i++)
   for(j=0;j<22;j++)
       asm("nop");

}




void PORTD_IRQHandler()  //���жϴ�����
{
    u8 dly;
     PORTD_ISFR |= 1<<10;
     image_us();
     if(line < 200)
     {
       if(line%5 == 0)
       {
         dly = 9;
         for(row = 0; row < 40; row++)
          image[cow][row] = GPIOD_PDIR & 0xff;
         while(dly--)
         {
           asm("nop");
         }
         cow++;
       }
       line++;
     }
     else
     {
       disable_irq(90);
       finish_flag = 1;
     }
     Light4_turn();
}

void PORTE_IRQHandler()  //���жϴ�����
{
  PORTE_PCR0 |= PORT_PCR_ISF_MASK;
  disable_irq(91);
  enable_irq(90);
  cow = 0;
  line = 0;
  Light3_turn();
}






void USART1_IRQHandler(void)
{
   
}
    
//void PORTA_IRQHandler()
//  {
//    
//    if(PORTA_ISFR & 1<<9)
//    {
//      PORTA_ISFR |= 1<<9;
//      //���ж��źŴ����ĳ���
//    LCD_write_num(0,0,i);
//    i++;
//      
//      
//    }
//    if(PORTA_ISFR & 1<<27)
//    {
//      PORTA_ISFR |= 1<<27;
//      //���ж��źŴ����ĳ���
//      
//    }
//  }