/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��app.c
 * ����         ��uC/OS���û�������ͷ�ļ�
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/	

#ifndef _APP_H_
#define _APP_H_


#include <stdint.h>
#include <app.h>
#include  "ucos_ii.h"  		//uC/OS-IIϵͳ����ͷ�ļ�
#include  "LED.h"
#include  "sysinit.h"          //ϵͳ����
#include <BSP.h>
#include "LED_CORE.h"
#include "common.h"
#include "include.h"
#include "nokia_5110.h"








/**************** �û��������� *******************/
void Task_Start(void *p_arg);

void app_task(void *p_arg);

void app_task1(void *p_arg);

void app_task2(void *p_arg);

void State_Get(void *p_arg);



#endif    //_APP_H_
