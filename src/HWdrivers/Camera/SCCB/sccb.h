/******************** (C) COPYRIGHT 2012-2013 �Ĭ�Ƽ� DEMOK*********
 * �ļ���         �� sccb.h
 * ����           �� OV����ͷSCCB����ͷ�ļ�
 *
 * ʵ��ƽ̨       �� �Ĭ�Ƽ�DEMOK Kinetis������
 * ����           �� �Ĭ�Ƽ�DEMOK Kinetis����С��

 * �Ա�����       �� http://shop60443799.taobao.com/
 * ������������   �� 1030923155@qq.com 
 * ��������QQȺ   �� 103360642

 * ����޶�ʱ��    ��2012-11-12
 * �޶�����        ����
**********************************************************************************/
#ifndef __SCCB_H__
#define __SCCB_H__

#include "common.h"
#include "gpio.h"

//--- Ĭ��SCL��PA10   SDA��PA11------//
void sccb_init(void);                           //��ʼ��SCCB�˿�ΪGPIO
void sccb_wait(void);                           //SCCBʱ����ʱ
void sccb_start(void);                          //��ʼ��־
void sccb_stop(void);                           //ֹͣ��־
u8 sccb_sendByte(u8 data);
void sccb_regWrite(u8 device,u8 address,u8 data);

//--GPIO_DDR_1bit(PORTx,n,ddr)--//
#define SCL_OUT   GPIO_DDR_1bit(PORTA,10,1)      //SCL-PA0����Ϊ����˿�
#define SDA_OUT   GPIO_DDR_1bit(PORTA,11,1)      //SDA-PA1����Ϊ����˿�
#define SDA_IN    GPIO_DDR_1bit(PORTA,11,0)      //SDA-PA1����Ϊ����˿�

//--GPIO_SET_1bit(PORTx,n,data)--//
#define SCL_HIGH  GPIO_SET_1bit(PORTA,10,1)
#define SCL_LOW   GPIO_SET_1bit(PORTA,10,0)
#define SDA_HIGH  GPIO_SET_1bit(PORTA,11,1)
#define SDA_LOW   GPIO_SET_1bit(PORTA,11,0)
#define SDA_DATA  GPIO_GET_1bit(PORTA,11) 



#endif