

#include "app.h"

/*****************************************************
*                                                    *
*                  ͷ�ļ�������                      *
*                                                    *
******************************************************/
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



/*****************************************************
*                                                    *
*                  �����ջ������                    *
*                                                    *
******************************************************/
OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		    

OS_STK task1_stk[task1_stk_size];

OS_STK task2_stk[task2_stk_size];

OS_STK task3_stk[task3_stk_size];



/*****************************************************
*                                                    *
*                  ϵͳ�����������                  *
*                                                    *
******************************************************/
OS_EVENT * sem_LED;
OS_EVENT * sem_I;





/*****************************************************
*                                                    *
*                  ����������                      *
*                                                    *
******************************************************/
void task1(void * p_arg)
{
  (void) p_arg;
  while(1)
  {
   if(PTC2_IN == 1) OSTaskSuspend(task2_prio);
   else OSTaskResume(task2_prio);
   Light1_turn();
   OSTimeDly(900);
//    Light2_turn();
//    Light3_turn();
//    Light4_turn();
  }
}

void task2(void * p_arg)
{
  (void) p_arg;
  while(1)
  {
    Light2_turn();
    OSTimeDlyHMSM(0,0,0,700);
    
//    Light2_turn();
//    Light3_turn();
//    Light4_turn();
  }
}

void task3(void * p_arg)
{
  (void) p_arg;
  while(1)
  {
    Light3_turn();
    OSTimeDlyHMSM(0,0,0,500);
//    Light2_turn();
//    Light3_turn();
//    Light4_turn();
  }
}
















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
    
    
    (void)p_arg;   // 'p_arg' ��û���õ�����ֹ��������ʾ����                 				
    
    BSP_Init();  //��ʼ��������,�������г�ʼ�����������                                               
    
    /*******************�û����񴴽���************************/
    OSTaskCreate(task1,(void *)0,
                 &task1_stk[task1_stk_size - 1], task1_prio); 
    OSTaskCreate(task2, (void *)0,
                 &task2_stk[task2_stk_size - 1], task2_prio);
    OSTaskCreate(task3, (void *)0,
                 &task3_stk[task3_stk_size - 1], task3_prio);
    while (1)
    {
        Light4_turn();                                         //LED0��˸
	OSTimeDlyHMSM(0, 0,0,500); 
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


