/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��main.c
 * ����         ��SD�����ļ�ϵͳʵ��
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
#include "ff.h"



#define BUFF_SIZE   100


void main(void)
{
    FIL fdst,fdst2;  //�ļ�
    FATFS fs;  //�ļ�ϵͳ
    FRESULT res;
   
    uint32 size, sizetmp;
    char *str = "������ʢƽ\n";
    printf(str);
    f_mount(&fs,0,1);
    res = f_open(&fdst,"0:/data1.txt",FA_OPEN_ALWAYS|FA_WRITE);
    f_printf(&fdst,"succed\n����");
    f_close(&fdst);
    while(1)
      printf("end\n");


}




//    Light_init;
//    printf("����ͨ������");
//
//    for(size = 0; size < BUFF_SIZE; size++)buff[size] = 0;
//
//    f_mount(0, &fs);		                                                       //SD��ϵͳ��ʼ��
//
//    res = f_open(&fdst, "0:/FireDemod.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);  //���ļ������û�оʹ���������д��
//
//    if( res == FR_DISK_ERR)
//    {
//        printf( "\nû����SD������\n" );
//        return;
//    }
//    else if ( res == FR_OK )
//    {
//        printf( "\n�ļ��򿪳ɹ� \n" );
//        Light1_on;
//    }
//    else
//    {
//        printf("\n����ֵ�쳣");
//    }
//
//
//    f_puts(str, &fdst);                     //���ļ���д���ַ���
//    f_puts("hello,\nI am ok",&fdst);
//
//    size = f_size(&fdst);                   //��ȡ�ļ��Ĵ�С
//   
//
//    printf( "\n�ļ���СΪ��%d \n" , size);  //���ڴ�ӡ�ļ��Ĵ�С
//
//    if(size > BUFF_SIZE)size = BUFF_SIZE;   //��ֹ���
//
//    f_lseek(&fdst, 0);                      //��ָ��ָ���ļ�����
//    f_read (&fdst, buff, size, (UINT *)&sizetmp);   //��ȡ
//
//
//    printf("�ļ�����Ϊ��%s", (char const *)buff);
//
//    f_close(&fdst);                         //�ر��ļ�
//    f_open(&fdst2, "0:/size.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
//    f_printf(&fdst2,"%d",size);
//    f_close(&fdst2);

