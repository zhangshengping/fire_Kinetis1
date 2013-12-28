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
#include "isr.h"

extern unsigned int i;
extern OS_EVENT * sem_I;
//extern OS_EVENT  * CInt;

/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�USART1_IRQHandler
*  ����˵��������1 �ж� ���� ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*  ��    ע��
*************************************************************************/
void USART1_IRQHandler(void)
{
    uint8 ch;

    DisableInterrupts;		    //�����ж�

    //����һ���ֽ����ݲ��ط�
    ch=uart_getchar (UART1);        //���յ�һ������
    uart_sendStr  (UART1,"\n�㷢�͵�����Ϊ��");
    uart_putchar (UART1,ch);        //�ͷ��ͳ�ȥ

    EnableInterrupts;		    //�����ж�
}




/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�SysTick_Handler
*  ����˵����ϵͳ�δ�ʱ���жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-18    �Ѳ���
*  ��    ע��ucos���õõ�
*************************************************************************/
void SysTick_Handler(void)
{
        OSIntEnter();
        OSTimeTick();
        OSIntExit();
}


//void PORTD_IRQHandler()  //���жϴ�����
//{
//     OSIntEnter();
//     OSIntExit();
//}
//
void PORTE_IRQHandler()  //���жϴ�����
{
  PORTE_PCR0 |= PORT_PCR_ISF_MASK;
  OSIntEnter();
  i++;
  disable_irq(91);
  OSSemPost(sem_I);
  OSIntExit();
}





