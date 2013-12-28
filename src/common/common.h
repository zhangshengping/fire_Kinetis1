/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��common.h
 * ����         ��ͨ������ͷ�ļ����ʺ�ȫ���Ĺ���
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/	

#ifndef _COMMON_H_
#define _COMMON_H_

//Ϊʹ�÷���ģʽ����ӵģ�����ģʽӦ�����δ��ڷ��͡���PLL���໷����
//#define   Simulator
#ifdef    Simulator
  #define NO_PLL_INIT   //�������໷
  #define NPRINTF       //����printf
#endif

/********************************************************************/

/*
 * Debug prints ON (#define) or OFF (#undef)
 */
#define DEBUG_PRINT



/*****************************������������*****************************/
typedef 	unsigned 	char		u8;	  //�޷�����
typedef 	unsigned 	short int	u16;
typedef 	unsigned 	long  int	u32;

typedef 			char		s8;	  //�з�����
typedef 			short int	s16;
typedef 			long  int	s32;

////2.2 ���ͱ����궨��
//	#define TRUE (1)
//	#define FALSE (0)
//	#define NULL (0)
//	typedef unsigned char			bool;  /*  8 bits */
//	typedef unsigned char			BOOL;  /*  8 bits */
//	typedef unsigned char			uint8;  /*  8 bits */
//	typedef unsigned short int	    uint16; /* 16 bits */
//	typedef unsigned long int		uint32; /* 32 bits */
//	
//	typedef char			   		int8;   /*  8 bits */
//	typedef short int	       		int16;  /* 16 bits */
//	typedef int		       	        int32;  /* 32 bits */
//	
//	typedef volatile int8			vint8;  /*  8 bits */
//	typedef volatile int16			vint16; /* 16 bits */
//	typedef volatile int32			vint32; /* 32 bits */
//	
//	typedef volatile uint8			vuint8;  /*  8 bits */
//	typedef volatile uint16		vuint16; /* 16 bits */
//	typedef volatile uint32		vuint32; /* 32 bits */

/*
 * Include the generic CPU header file
 */
#include "arm_cm4.h"

/*
 * Include the platform specific header file
 */
#if (defined(TWR_K40X256))
  #include "k40_tower.h"
#elif (defined(TWR_K60N512))
// #include "k60_tower.h"
  #include "k60_fire.h"
#elif (defined(TWR_K53N512))
 #include "k53_tower.h"
#else
  #error "No valid platform defined"
#endif

/*
 * Include the cpu specific header file
 */
#if (defined(CPU_MK40N512VMD100))
//  #include "MK40N512VMD100.h"
  #include "MK40DZ10.h"
#elif (defined(CPU_MK60N512VMD100))
// #include "MK60N512VMD100.h"
  #include "MK60DZ10.h"
#elif (defined(CPU_MK53N512CMD100))
//  #include "MK53N512CMD100.h"
  #include "MK53DZ10.h"
#else
  #error "No valid CPU defined"
#endif


/*
 * Include any toolchain specfic header files
 */
#if (defined(CW))
  #include "cw.h"
#elif (defined(IAR))
  #include "iar.h"
#else
#warning "No toolchain specific header included"
#endif

/*
 * Include common utilities
 */
#include "assert.h"
#include "io.h"
#include "startup.h"
#include "stdlib.h"


#if (defined(IAR))
	#include "intrinsics.h"
#endif


#include  "sysinit.h"           //ϵͳ����
#include "mcg.h"
#include "fire_drivers_cfg.h"   //�ܽŸ�������

#include "lptmr.h"
#define DELAY()  time_delay_ms(500)
#define DELAY_MS(ms) time_delay_ms(ms)
/********************************************************************/

#endif /* _COMMON_H_ */
