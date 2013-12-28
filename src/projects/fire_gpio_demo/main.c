//-----------------------------------------------------------------------
// �� �� ��: SDHC                           
// Ӳ������: ��K60���İ������С��                                       
// ��������: ���ڲ���SDHC����
// Ŀ    ��: ��������SDHCģ��ı�̷���       
// ˵    ��: ������Ϊ115200,ʹ��UART3��
// ��Ȩ����: ���ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
// �汾����:    ʱ��                         �汾                             �޸�
//           2011-12-14     V1.0      SDHC������ʼ�汾
//---------------���ݴ�ѧ��˼����Ƕ��ʽϵͳʵ����2011��--------------------

//ͷ�ļ�
#include "includes.h"

//ȫ�ֱ�������
extern int periph_clk_khz;
uint8 InitSD(uint8 verbose);

//SD���������ܷ��ؽ��
enum
{
	SD_OK,
	NO_SD_CARD,
	INIT_SD_FAILS
};

//������
void main(void)
{
    //1 ������ʹ�õı�������
    uint32 runcount,i;		//���м�����
    uint8  SDHCReceiveBuff[512];
    //2 ���ж�
    DisableInterrupts;      //��ֹ���ж�

    //3 ģ���ʼ��
    light_init(Light_Run_PORT,Light_Run1,Light_OFF); //ָʾ�Ƴ�ʼ��
    hw_uart_init (UART4,periph_clk_khz,115200);			 //���ڳ�ʼ��

    InitSD(VERBOSE_ON);
    //4 ���ж�
    //enable_uart_re_int(UART4,UART5irq);		//������3�����ж�
    EnableInterrupts;			        //�����ж�

    hw_uart_send_string(UART4,(uint8*)"\r\n");
    
    if(disk_read (0,SDHCReceiveBuff,0,1) == RES_OK)
    {
    	for(i = 0;i < 512;i++)
    	{
    		hw_uart_send_hex_number(UART4,(uint32)SDHCReceiveBuff[i]);
    		hw_uart_send_string(UART4,(uint8*)" ");
    	}
		hw_uart_send_string(UART4,(uint8*)"\r\n");
    }
    else
    {
    	hw_uart_send_string(UART4,(uint8*)"Read disk failed!\r\n");
    }
    
    for(i = 0;i < 512;i++)
    {
    	SDHCReceiveBuff[i]++;
    }
    if(disk_write (0,SDHCReceiveBuff,0,1) == RES_OK)
    {
    	hw_uart_send_string(UART4,(uint8*)"Write disk successed!\r\n");
    }
    else
    {
    	hw_uart_send_string(UART4,(uint8*)"Write disk failed!\r\n");
    }
    for(i = 0;i < 512;i++)
    {
    	SDHCReceiveBuff[i] = 0;
    }
    if(disk_read (0,SDHCReceiveBuff,0,1) == RES_OK)
    {
    	for(i = 0;i < 512;i++)
    	{
    		hw_uart_send_hex_number(UART4,(uint32)SDHCReceiveBuff[i]);
    		hw_uart_send_string(UART4,(uint8*)" ");
    	}
		hw_uart_send_string(UART4,(uint8*)"\r\n");
    }
    else
    {
    	hw_uart_send_string(UART4,(uint8*)"Read disk failed!\r\n");
    }

    //��ѭ��
    while(1)
    {
        //1 ��ѭ��������һ����ֵ��ʹС�Ƶ�������״̬�л�
        runcount++;
        if(runcount>=5000000)
        {
            light_change(Light_Run_PORT,Light_Run1);//ָʾ�Ƶ�������״̬�л�
            runcount=0;
        }
    }
}


uint8 InitSD(uint8 verbose)
{ 
  uint8  status;
  uint32 i;

  #define TF_PWR_PORT PORT_E
  #define TF_PWR      6
  hw_gpio_init(TF_PWR_PORT, TF_PWR, 1, 1);
  
  //�ȴ��ź��ȶ�
  for(i = 0;i < 200000;i++)
  {
  }
  
  //�ж�SD�Ƿ��Ѿ���
  if ((disk_status(0) & STA_NOINIT) != STA_NOINIT)
  {
		if (verbose == VERBOSE_ON)
		{
			hw_uart_send_string(UART4,(uint8 *)"\n\rSD card is already mounted!\n\r");
		}
		return SD_OK;
  }
  
  if (SDCARD_GPIO_DETECT == 0)
  {
		//�ȴ�SD����ʼ�����
		for(i = 0;i < 1000000;i++)
		{
		}
		
		//��ʼ������0
		status = disk_initialize(0);
		if (status == RES_OK)
		{
			if (SDHC_Info.CARD == ESDHC_CARD_SD)
			{
				if (verbose == VERBOSE_ON)
				{
					hw_uart_send_string(UART4,(uint8 *)"\n\rSD card has been successfully initialized !!!\n\r");
				}
			}
			if (SDHC_Info.CARD == ESDHC_CARD_SDHC)
			{
				if (verbose == VERBOSE_ON)
				{
					hw_uart_send_string(UART4,(uint8 *)"\n\rSDHC card has been successfully initialized !!!\n\r");
				}
			}			
		}else
		{
			if (verbose == VERBOSE_ON)
			{
				hw_uart_send_string(UART4,(uint8 *)"\n\rSD card failure !!!\n\r");
			}
			return INIT_SD_FAILS;
		}
	}else
	{
		if (verbose == VERBOSE_ON)
		{
			hw_uart_send_string(UART4,(uint8 *)"\n\rNo SD card detected !!!\n\r");		
		}	
		return NO_SD_CARD;
	}
	return SD_OK;
}
