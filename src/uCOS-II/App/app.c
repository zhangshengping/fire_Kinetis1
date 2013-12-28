

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


//INT8U a[4] = {1,2,3,4};
//INT8U b[4] = {5,6,7,8};




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
OS_EVENT * Queue;

void * Queuel[5];

INT8U a[10]={1,2,3,4,5,6,7,8,9,0};

INT8U b[10]={1+10,2+10,3+10,4+10,5+10,6+10,7+10,8+10,9+10,0+10};




/*****************************************************
*                                                    *
*                  ����������                      *
*                                                    *
******************************************************/
void task1(void *p_arg)
{
  INT8U i;
  (void) p_arg;
  (INT8U *) b;
   while(1)
  {
    for(i = 0; i< 10;i++)
    {
      OSQPost(Queue,b+i);
      OSTimeDlyHMSM(0,0,0,103);
    }
  }
}

void task3(void * p_arg)
{
  INT8U * msg;
  INT8U err;
  while(1)
  {
    msg = (INT8U *)OSQPend(Queue, 0, &err);
    LCD_write_num(0,0,(int)*msg);
    OSTimeDlyHMSM(0,0,0,200);
  }
}

void task2(void * p_arg)
{
  Queue = OSQCreate(Queuel,5);
  INT8U i;
  (INT8U *)a;
  while(1)
  {
    for(i= 0 ;i <10;i++)
    {
      OSQPost(Queue, a+i);
      LCD_write_english_string(0,3,"OSQPosted");
      OSTimeDlyHMSM(0,0,0,158);
    }
    
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
        GPIO_PTOR_REG(PTB_BASE_PTR) |= 1;
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


