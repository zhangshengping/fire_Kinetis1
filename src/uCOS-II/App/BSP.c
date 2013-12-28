/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��BSP.c
 * ����         ���뿪������صĺ���
 *          
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��uC/OS-II V2.92
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008   
**********************************************************************************/	

#include <BSP.h>
#include <LED.h>
#include "exti.h"
#include "nokia_5110.h"
#include "LED_CORE.h"


/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*  
*  �������ƣ�BSP_Init
*  ����˵�����������ʼ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-10
*  ��    ע����ý����еĳ�ʼ�������������ʵ��
*************************************************************************/
void BSP_Init()
{
  LED_INIT();
  Light_init;
   gpio_init(PORTB,0,GPO,1);
  input_init();
  LCD_init();
//  LCD_write_english_string(0, 0, "LCD Inited!");
  Light1_on;
  Light2_on;
  Light3_on;
  Light4_on;
  exti_init(PORTE, 0, rising_down);//ʹ��E���ж�
}

void input_init()
{
  gpio_init(PORTC, 2, GPI, 0);
}

