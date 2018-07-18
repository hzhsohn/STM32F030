#ifndef __OUTPUT_H
#define __OUTPUT_H

#include "stm32f0xx.h"

#define	OUTPUT_AHBP 	RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB


#define OUTP1		GPIOA
#define OUTP1_PIN		GPIO_Pin_5
#define OUTP1_SET(x)            			x?GPIO_ResetBits(OUTP1,OUTP1_PIN):GPIO_SetBits(OUTP1,OUTP1_PIN)  //�͵�ƽ����
         

#define OUTP2		GPIOB
#define OUTP2_PIN		GPIO_Pin_1
#define OUTP2_SET(x)            		  !x?GPIO_ResetBits(OUTP2,OUTP2_PIN):GPIO_SetBits(OUTP2,OUTP2_PIN)  //�ߵ�ƽ����


void OUTPUT_Init(void);

#endif
