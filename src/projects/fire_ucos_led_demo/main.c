///******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
// * �ļ���       ��main.c
// * ����         �����Ǹ��û�ģ�棬�Ѿ���Ӻ����еĿ⣬�û��Լ����ÿ��ﺯ������
// *          
// * ʵ��ƽ̨     ��Ұ��kinetis������
// * ��汾       ��
// * Ƕ��ϵͳ     ��
// *
// * ����         ��Ұ��Ƕ��ʽ���������� 
// * �Ա���       ��http://firestm32.taobao.com
// * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008   
//**********************************************************************************/	
//
//
//#include "common.h"
//#include "include.h"
//
//
//
///*************************************************************************
//*                             Ұ��Ƕ��ʽ����������
//*                               LEDʵ���ۺϲ���
//*  ʵ��˵����Ұ�� ucos LED ʵ��
//*            Task_Start ���治����˸ LED0
//*
//*  ʵ��������� 
//*
//*  ʵ��Ч����LED0 ��˸
//*
//*  ʵ��Ŀ�ģ����� ucos ϵͳ�Ƿ���������
//*
//*  �޸�ʱ�䣺2012-2-29     �Ѳ���
//*
//*  ��    ע��Ұ��Kinetis������� LED0~3 ���ֱ��PTD15~PTD12 ���͵�ƽ����
//*************************************************************************/
//OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		    //��������Task_Start��ջ
//OS_STK app_task_stk[STARTUP_TASK_STK_SIZE];
//OS_STK app_task1_stk[STARTUP_TASK_STK_SIZE];
//OS_STK app_task2_stk[STARTUP_TASK_STK_SIZE];
//
//void main()
//{
//    
//    OSInit();                                               //��ʼ��uC/OS
//    OSTaskCreate(Task_Start,(void *)0,
//                 &startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);    //��������
//    OSTaskCreate(app_task,(void *)0,
//                 &app_task_stk[STARTUP_TASK_STK_SIZE-1], APP_TASK_PRIO);
//    OSTaskCreate(app_task1,(void *)0,
//                 &app_task1_stk[STARTUP_TASK_STK_SIZE-1], APP_TASK1_PRIO);
//    OSTaskCreate(app_task2,(void *)0,
//                 &app_task2_stk[STARTUP_TASK_STK_SIZE-1], APP_TASK2_PRIO);
//    OSStart();                                              //�������������
//}
//
