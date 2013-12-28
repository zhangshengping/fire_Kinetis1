/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��lptmr.c 
 * ����         ��lptmr�����Ķ�ʱ����Ŀǰֻ��һ����ʱ����ʱ����
 * ��ע         ���ٷ�����
 *          
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 * 
 * ����         ����˼������˾
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008   
**********************************************************************************/	

#include "common.h"
#include "lptmr.h"

/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*  
*  �������ƣ�time_delay_ms
*  ����˵������ʱ������ʹ�ö����Ķ�ʱ����ʱ��׼ȷ
*  ����˵����ms   ��ʱʱ�䣬��λΪms
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע���ٷ������Դ�
*************************************************************************/
void time_delay_ms(uint32 ms)
{
    /* Make sure the clock to the LPTMR is enabled */
    SIM_SCGC5|=SIM_SCGC5_LPTIMER_MASK; 
    
    /* Set the compare value to the number of ms to delay */
    LPTMR0_CMR = ms; 
    
    /* Set up LPTMR to use 1kHz LPO with no prescaler as its clock source */
    LPTMR0_PSR = LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK; 
    
    /* Start the timer */
    LPTMR0_CSR |= LPTMR_CSR_TEN_MASK; 
    
    /* Wait for counter to reach compare value */
    while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK));
    
    /* Clear Timer Compare Flag */
    LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;
    
    return;
}