/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��main.c
 * ����         ��UART���ڷ���ʵ��
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


void main()
{
	u32	i;
	FTM_PWM_init(FTM1,CH0,35000,100);
	while(1)
	{
		for(i=10;i>1;i--)
		{
			FTM_PWM_Duty(FTM1,CH0,i*10);
			time_delay_ms(100);
		}
	}
}