/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��main.c
 * ����         ��PWMʵ��
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


#if 1    //����ѡ�� 0 �� 1 ���л�����������ͬ��main����

/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*                             PWMʵ��ʾ�����򵥲���
*
*  ʵ��˵����Ұ��PWMʵ�飬��ʾ���������Ƶ�ʡ�
*
*  ʵ������������� FTM1_CH0 ���� PWM ���岨 ���� PTA8 �ܽš�
*            �� PTA8 ����ʾ����
*
*  ʵ��Ч�������Բ��Ƶ��Ϊ 35kHz
*
*  ʵ��Ŀ�ģ����� PWM Ƶ���Ƿ���ȷ
*
*  �޸�ʱ�䣺2012-2-29     �Ѳ���
*
*  ��    ע��FTM.h ���и���FTMͨ������Ӧ�ܽŵı��񣬷���鿴
*            ռ�ձȴ��ݽ���Ĳ�����Ҫ���� FTM_PRECISON �Ķ�����ѡ��
*************************************************************************/
void  main()
{
    FTM_PWM_init(FTM1,CH0,35000,50); //��ʼ��FTM1_CH0���Ƶ��Ϊ35kHZ,ռ�ձ�Ϊ50%��PWM ��FTM1_CH0��ӦPTA8��
    while(1)
    {
    }
}

#else


/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*                               PWMʵ��LED����
*
*  ʵ��˵����Ұ��PWMʵ�飬��LED������ռ�ձȵı仯��
*
*  ʵ������������� FTM1_CH0 ���� PWM ���岨
*            �� FTM.h ����Բ鵽 FTM1_CH0 ��Ӧ�ܽ�Ϊ PTA8
*            �� PTA8 ���� LED0���� PTA8 �� PTD15 �̽�
*
*  ʵ��Ч�������Կ��� LED0 �ɰ���������ͻȻ���������ȥ����
*
*  ʵ��Ŀ�ģ����� PWM Ƶ���Ƿ���ȷ
*
*  �޸�ʱ�䣺2012-2-29     �Ѳ���
*
*  ��    ע��Ұ��Kinetis������� LED0~3 ���ֱ��PTD15~PTD12 ���͵�ƽ����
*            FTM.h ���и���FTMͨ������Ӧ�ܽŵı��񣬷���鿴
*            ռ�ձȴ��ݽ���Ĳ�����Ҫ���� FTM_PRECISON �Ķ�����ѡ��
*************************************************************************/
void  main()
{
    u32 i;
    FTM_PWM_init(FTM1,CH0,35000,100);        //FTM1_CH0��ʼ��PWM ��PA8
    while(1)
    {
        for(i=10;i>1;i--)
        {
            FTM_PWM_Duty(FTM1,CH0,i*10);      //�ı�ռ�ձȣ��𽥱�С ,LED �𽥱��� ���͵�ƽ������
            time_delay_ms(100);               //��ʱ100ms 	
        }
    }
}


#endif