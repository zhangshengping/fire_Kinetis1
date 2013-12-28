

#include "nokia_5110.h"
#include "english_6x8_pixel.h"
#include "write_chinese_string_pixel.h"


/*-----------------------------------------------------------------------
LCD_init          : NOKIA5110LCD ��ʼ��

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/

void delay_1us(void)                 //1us��ʱ����
  {
   unsigned int i;
  for(i=0;i<1000;i++);
  }

  void delay_1ms(void)                 //1ms��ʱ����
  {
   unsigned int i;
   for (i=0;i<11400;i++);
  }
  
void delay_nms(unsigned int n)       //N ms��ʱ����
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1ms();
  }

  
void LCD_pin_config()
{
    gpio_init(PortSCLK, SCLK_Pin,GPO,HIGH);
    gpio_init(PortSDIN, SDIN_Pin,GPO,HIGH);
    gpio_init(PortLCD_DC, LCD_DC_Pin,GPO,HIGH);
    gpio_init(PortLCD_CE, LCD_CE_Pin,GPO,HIGH);
    gpio_init(PortLCD_RST, LCD_RST_Pin,GPO,HIGH);
}

void LCD_init(void)
  {
            // ����һ����LCD��λ�ĵ͵�ƽ����
   LCD_pin_config();
   LCD_RST = 0;
   // delay_1us();    

   LCD_RST = 1;
    
		// �ر�LCD
   LCD_CE = 0;
  //  delay_1us();
		// ʹ��LCD
   LCD_CE = 1;
    delay_1us();

    LCD_write_byte(0x21, 0);	// ʹ����չ��������LCDģʽ
    LCD_write_byte(0xc0, 0);	// ����ƫ�õ�ѹ   �����ѹ��ʱ��ֵ��С
    LCD_write_byte(0x07, 0);	// �¶�У��
    LCD_write_byte(0x13, 0);	// 1:48
    LCD_write_byte(0x20, 0);	// ʹ�û�������
    LCD_clear();	        // ����
    LCD_write_byte(0x0c, 0);	// �趨��ʾģʽ��������ʾ
        
           // �ر�LCD
   LCD_CE = 0;
  }

/*-----------------------------------------------------------------------
LCD_clear         : LCD��������,���ҽ�XY��������

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/
void LCD_clear(void)
  {
    unsigned int i;

    LCD_write_byte(0x0c, 0);			
    LCD_write_byte(0x80, 0);			

    for (i=0; i<504; i++)
      LCD_write_byte(0, 1);
	LCD_set_XY(0,0);											//��XY��������
  }

/*-----------------------------------------------------------------------
LCD_set_XY        : ����LCD���꺯��

���������X       ��0��83
          Y       ��0��5

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/
void LCD_set_XY(unsigned char X, unsigned char Y)
  {
    LCD_write_byte(0x40 | Y, 0);								// column
    LCD_write_byte(0x80 | X, 0);          						// row
  }

/*-----------------------------------------------------------------------
LCD_write_char    : ��ʾӢ���ַ�

���������c       ����ʾ���ַ���

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/
void LCD_write_char(unsigned char c)
  {
    unsigned char line;

    c -= 32;

    for (line=0; line<6; line++)
      LCD_write_byte(font6x8[c][line], 1);
  }

/*-----------------------------------------------------------------------
LCD_write_english_String  : Ӣ���ַ�����ʾ����

���������*s      ��Ӣ���ַ���ָ�룻
          X��Y    : ��ʾ�ַ�����λ��,x 0-83 ,y 0-5

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 		
-----------------------------------------------------------------------*/
void LCD_write_english_string(unsigned char X,unsigned char Y,char *s)
  {
    LCD_set_XY(X,Y);
    while (*s) 
      {
	 LCD_write_char(*s);
	 s++;
      }
  }
/*-----------------------------------------------------------------------
LCD_write_chinese_string: ��LCD����ʾ����

���������X��Y    ����ʾ���ֵ���ʼX��Y���ꣻ
          ch_with �����ֵ���Ŀ��
          num     ����ʾ���ֵĸ�����  
          line    �����ֵ��������е���ʼ����
          row     ��������ʾ���м��
��д����          ��2004-8-11 
����޸�����      ��2004-8-12 
���ԣ�
	LCD_write_chi(0,0,12,7,0,0);
	LCD_write_chi(0,2,12,7,0,0);
	LCD_write_chi(0,4,12,7,0,0);	
-----------------------------------------------------------------------*/                        
void LCD_write_chinese_string(unsigned char X, unsigned char Y, 
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row)
  {
    unsigned char i,n;
    
    LCD_set_XY(X,Y);                             			//���ó�ʼλ��
    
    for (i=0;i<num;)
      {
      	for (n=0; n<ch_with*2; n++)              			//дһ������
      	  { 
      	    if (n==ch_with)                      			//д���ֵ��°벿��
      	      {
      	        if (i==0) LCD_set_XY(X,Y+1);
      	        else
      	           LCD_set_XY((X+(ch_with+row)*i),Y+1);
              }
      	    LCD_write_byte(write_chinese[line+i][n],1);
      	  }
      	i++;
      	LCD_set_XY((X+(ch_with+row)*i),Y);
      }
  }
  


/*-----------------------------------------------------------------------
LCD_draw_map      : λͼ���ƺ���

���������X��Y    ��λͼ���Ƶ���ʼX��Y���ꣻ
          *map    ��λͼ�������ݣ�
          Pix_x   ��λͼ���أ�����
          Pix_y   ��λͼ���أ���

��д����          ��2004-8-13
����޸�����      ��2004-8-13 
-----------------------------------------------------------------------*/
void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map,
                  unsigned char Pix_x,unsigned char Pix_y)
  {
    unsigned int i,n;
    unsigned char row;
    
    if (Pix_y%8==0) row=Pix_y/8;      					//����λͼ��ռ����
      else
        row=Pix_y/8+1;
    
    for (n=0;n<row;n++)
      {
      	LCD_set_XY(X,Y);
        for(i=0; i<Pix_x; i++)
          {
            LCD_write_byte(map[i+n*Pix_x], 1);
          }
        Y++;                         					//����
      }      
  }

/*-----------------------------------------------------------------------
LCD_write_byte    : ʹ��SPI�ӿ�д���ݵ�LCD

���������data    ��д������ݣ�
          command ��д����/����ѡ��

��д����          ��2004-8-10 
����޸�����      ��2004-8-13 
-----------------------------------------------------------------------*/
void LCD_write_byte(unsigned char dat, unsigned char command)
  {
    unsigned char i;
    //PORTB &= ~LCD_CE ;		        	// ʹ��LCD
    LCD_CE = 0;
    
    if (command == 0)
     // PORTB &= ~LCD_DC ;	        		// ��������
     LCD_DC = 0;
    else
     // PORTB |= LCD_DC ;		        	// ��������
     LCD_DC = 1;
		for(i=0;i<8;i++)
		{
			if(dat&0x80)
				SDIN = 1;
			else
				SDIN = 0;
			SCLK = 0;
			dat = dat << 1;
			SCLK = 1;
		}
   // SPDR = data;							// �������ݵ�SPI�Ĵ���

    //while ((SPSR & 0x80) == 0);         	// �ȴ����ݴ������
	
    //PORTB |= LCD_CE ;						// �ر�LCD
     LCD_CE = 1;
  }
  
 
  
  
  
  
  /*=====================������ͼ����====================
��    �룺map  ͼ��������ַ
��    �ߣ���ʢƽ
�޸�ʱ�䣺2013-3-12
======================================================*/  
  
void LCD_draw_whole(unsigned char * map)
  {
	  int i;
	  
	  LCD_clear();
	  
	  
	  for(i=0;i<504;i++)
	  {
		  LCD_write_byte(*map++,1);
	  }
  }
  
  
  
  
  
  
  
  /*=========��ʱ����ʱ����=============
  ��    �ߣ���ʢƽ
  ====================================*/
  void delay_long_time(void)
 {
 	unsigned int time=2576;
 	while(time--);
 }





/*==============ͼ����ʾ���������ܳ������ã������һ�ֽ�дnokia5110��8���㣩========
LCD_draw_picture    : ��һ����άͼ�������nokia5110����ʾ

���������start_x     ����ʾͼ��Ŀ�ʼ���кţ�
          start_y    ����ʾͼ��Ŀ�ʼ���кţ�
          map       : ͼ�����飻
          line     : ������
          row      ��������0-5����

��д����          ��2013-6-29 
����޸�����      ��2013-6-29 
��������          ��2013-07-04
================================================================================*/
void LCD_draw_picture(unsigned char start_x, unsigned char start_y, 
                      unsigned char *map, unsigned char line, unsigned row)
  {
        unsigned char *p;
        unsigned i,j;
        p= map;
        for(i=0;i<line;i++)
        {
              LCD_set_XY(start_x,start_y+i);
              for(j=0;j<row;j++)
              {
                    LCD_write_byte(*p++,1);
              }
        }
  }
  
  
  
  
  
  
  
/*=========================================================================
** ��������
          LCD_draw_pixel
          
** �������ܼ�飺
          ��һ����άͼ�������nokia5110����ʾ

** ���������
          image    ��Ҫ��ʾͼ�������׵�ַ(ָ��)������������������
          line     ��ͼ�����������ص㣩��
          row      : ͼ�����������ص㣩��
          threshold: ��ֵ����ֵ������Ƕ�ֵ���Ժ��ͼ�񣬷�ֵΪ0����
          X        ����ʼ��ʾ��X���ꣻ
          Y        ����ʼ��ʾ��Y���꣨0-5����

** ���ز�����
           ��

** ��   �ߣ�
           ��ʢƽ

** ��д���ڣ�
            2013-6-29 

** �޸���ʷ��
            2013-6-29 

** ������ڣ�
            2013-07-04
===========================================================================*/
  void LCD_draw_pixel(void *image, unsigned char line, unsigned char row,
                    unsigned char threshold,unsigned char X, unsigned char Y)
   {
      unsigned char *p_image, i, j, k, temp,n;
      p_image = image;
//      if(line > 0)
        n=line/8;
      for(i=0;i<n;i++)
      {
            LCD_set_XY(0+X,i+Y);
            for(j=0;j<row;j++)
            {
                  for(k=0;k<8;k++)
                  {
                       ((*(p_image+(i*8+k)*row+j))>threshold) ? 
                                     (temp &= ~(1<<k)):(temp |= 1<<k) ;
                  }
                  LCD_write_byte(temp,1);
            }
      }
      if(line%8)
            {
                  for(j=0;j<row;j++)
                        {
                              for(k=0;k<line%8;k++)
                              {
                                    ((*(p_image+(i*8+k)*row+j))>threshold) ? 
                                    (temp &= ~(1<<k)) : (temp |= 1<<k);
                              }
                              LCD_write_byte(temp,1);
                        }
            }
    }


/*=========================================================================
** ��������
          LCD_write_num
          
** �������ܼ�飺
          ��ʾһ��ʮ������

** ���������
            X ��ʼ��д���к�
            Y ��ʼ��д���к�
            num Ҫ��ʾ������
          

** ���ز�����
           ��

** ��   �ߣ�
           ��ʢƽ

** ��д���ڣ�
            2013-9-17

** �޸���ʷ��
            2013-9-17

** ������ڣ�
            2013-9-17
===========================================================================*/

void LCD_write_num(u8 X, u8 Y, int num)
{
  u8 b[6], i;
  LCD_set_XY(X,Y);
  
  for(i = 0; i < 6; i++)
  {
    b[5-i] = (num % 10) + '0';
    num = num / 10;
  }
  
  for(i = 0; i < 6; i++)
  {
    LCD_write_char(b[i]);
  } 
}
