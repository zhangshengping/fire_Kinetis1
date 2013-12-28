
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


unsigned int i = 0;



/*********************************�����ջ��*****************************/
OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		    //��������Task_Start��ջ

OS_STK app_task_stk[STARTUP_TASK_STK_SIZE];

OS_STK app_task1_stk[STARTUP_TASK_STK_SIZE];

OS_STK app_task2_stk[STARTUP_TASK_STK_SIZE];

OS_STK State_Get_stk[STARTUP_TASK_STK_SIZE];



/********************************ϵͳ�������������**********************/
OS_EVENT * sem_LED;
OS_EVENT * sem_I;





/******************************������������*************************
*******************************������������**************************
*******************************������������*************************
*******************************������������*************************
*******************************������������*************************/



/*******************************ϵͳ��ʼ������************************
* ���ܣ�ϵͳ��ʼ�������������������������д���
*
*
*
*
*********************************************************************/
void Task_Start(void *p_arg)
{
    /**************** ��ʼ�� ϵͳ�δ�ʱ�� �����ڶ�ʱ�������****************/
    u32  cnts;                                                                     
    cnts         = core_clk_mhz *( (u32)1000000u / (u32)OS_TICKS_PER_SEC );        /* Determine nbr SysTick increments.                    */
    OS_CPU_SysTickInit(cnts);                                                     /* Init uC/OS periodic time src (SysTick).              */

   
#if (OS_TASK_STAT_EN > 0)
     /*       ����ͳ������           */
    OSStatInit();                                               
#endif
    
    
    (void)p_arg;                				// 'p_arg' ��û���õ�����ֹ��������ʾ����    
    
    BSP_Init();                                                 //��ʼ��������
//   CInt = OSSemCreate(0);                                      //�����ź���
    
    /******************* �û������� ************************/
    OSTaskCreate(app_task1,(void *)0,
                 &app_task1_stk[STARTUP_TASK_STK_SIZE-1], APP_TASK1_PRIO);
    OSTaskCreate(State_Get,(void *)0,
                 &State_Get_stk[STARTUP_TASK_STK_SIZE-1], State_Get_PRIO);
    OSTaskCreate(app_task2, (void *)0,
                 &app_task2_stk[STARTUP_TASK_STK_SIZE-1], APP_TASK2_PRIO);
    
    while (1)
    {
        LED_turn(LED0);                                         //LED0��˸
	OSTimeDlyHMSM(0, 0,0,500); 
    }
}




/*******************************�ź������Ͳ���************************
* ���ܣ��ź�������
*
*
*
*
*********************************************************************/
void State_Get(void *p_arg)
{
  uint8_t state;
  (void) p_arg;
  sem_LED = OSSemCreate(0);
  while(1)
  {
    state = PTC2_IN;
    if(state)
    {
      OSSemPost(sem_LED);
    }
    OSTimeDlyHMSM(0,0,6,0);
  }
}



/*******************************�ź����ȴ�************************
* ���ܣ��ź����ȴ�
*
*
*
*
*********************************************************************/
void app_task1(void *p_arg)
{
  INT8U ERR;
  uint8_t num = 0;
  (void) p_arg;
  while(1)
  {
    OSSemPend(sem_LED, 0, &ERR);
    num++;
    LCD_write_num(0,0, num);
    Light3_on;
    OSTimeDlyHMSM(0,0,0,600);
    Light3_off;
  }
}



/*******************************�ź����ȴ�************************
* ���ܣ��ź����ȴ�
*
*
*
*
*********************************************************************/
void app_task(void *p_arg)
{
  (void) p_arg;
  while(1)
  {
    Light2_on;
    OSTimeDlyHMSM(0,0,0,500);
    Light2_off;
    OSTimeDlyHMSM(0,0,0,500);
  }
}



/*******************************�ź����ȴ�************************
* ���ܣ��ź����ȴ�
*
*
*
*
*********************************************************************/
void app_task2(void *p_arg)
{
  INT8U err;
  (void) p_arg;
  sem_I = OSSemCreate(0);
  while(1)
  {
    OSSemPend(sem_I,0, &err);
    LCD_write_num(0, 1, i);
    OSTimeDly(20);
    enable_irq(91);
//    Light4_on;
//    OSTimeDlyHMSM(0,0,3,0);
//    Light4_off;
//    OSTimeDlyHMSM(0,0,3,0);
  }
}





/*******************************main************************
* ���ܣ�main����
*
*
*
*
*********************************************************************/
void main()
{
    
    OSInit();                                               //��ʼ��uC/OS
    OSTaskCreate(Task_Start,(void *)0,
                 &startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);    //��������
    OSStart();                                              //�������������
}


