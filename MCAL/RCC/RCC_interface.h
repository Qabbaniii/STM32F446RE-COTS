
/**********************************************************************************
 *	FILE DESCRIPTION
 **********************************************************************************
 * Filename              :   RCC_interface.h
 * Author                :   Abdullah Qabbani
 * Origin Date           :   19/2/2024
 * Version               :   1.0.0
 * Compiler              :   GCC ARM Embedded Toolchain
 * Target                :
 * Notes                 :
 *
 **********************************************************************************/

/************************ SOURCE REVISION LOG *************************************
 *
 *  Date 	    Version   Author             Description
 *  23/2/2024   1.0.0     Abdullah Qabbani   Initial Release.
 *
 **********************************************************************************/
#ifndef MCAL_RCC_INTERFACE_H_
#define MCAL_RCC_INTERFACE_H_

/***********************************************************************************
 * 	INCLUDES
 **********************************************************************************/
#include "../../Services/STD_TYPES.h"
#include "RCC_config.h"

/***********************************************************************************
 *	CONSTANT MACROS & ENUMS
 ***********************************************************************************/


/*System Clock*/
enum {
	HSI,
	HSE,
	PLL,
	LSI,
	LSE,
	RTC
};

/*PLL Source Mux*/
enum {
	HSE_CLK_divided_by_1,
	HSE_CLK_divided_by_2,
	HSI_CLK_divided_by_2,
};

/*PLL Multiplication*/
enum {
	PLl_CLK_x2,
	PLl_CLK_x3,
	PLl_CLK_x4,
	PLl_CLK_x5,
	PLl_CLK_x6,
	PLl_CLK_x7,
	PLl_CLK_x8,
	PLl_CLK_x9,
	PLl_CLK_x10,
	PLl_CLK_x11,
	PLl_CLK_x12,
	PLl_CLK_x13,
	PLl_CLK_x14,
	PLl_CLK_x15,
	PLl_CLK_x16};

/*AHB Prescaler*/
enum {
	SYS_CLK,
	SYS_CLK_divided_by_2=8,
	SYS_CLK_divided_by_4,
	SYS_CLK_divided_by_8,
	SYS_CLK_divided_by_16,
	SYS_CLK_divided_by_64,
	SYS_CLK_divided_by_128,
	SYS_CLK_divided_by_256,
	SYS_CLK_divided_by_512,
};

/*APB1 & APB2 Prescaler*/
enum {
	HCLK,
	HCLK_divided_by_2=4,
	HCLK_divided_by_4,
	HCLK_divided_by_8,
	HCLK_divided_by_16
};



/*ADC Prescaler*/
enum {
	PCLK2_divided_by_2,
	PCLK_divided_by_4,
	PCLK_divided_by_6,
	PCLK_divided_by_8
};

#define CLK_ON       1
#define CLK_OFF      0

#define BYPASS_ON   1
#define BYPASS_OFF  0

#define TimeoutMax configTIME_OUT_MAX


/***********************************************************************************
 *	FUNCTION PROTOTYPES
 **********************************************************************************/

uint8 RCC_u8SetClkStatus (uint8 copy_u8SysClk ,uint8 copy_u8Status);
void RCC_vSetSysClk(uint8 copy_u8ClkType);
void RCC_vHSEBypassStatus(uint8 copy_u8HSEBypassStatus);
void RCC_vHSEHSEToPLLPrescaler(uint8 copy_u8HSEToPLLPrescaler);
void RCC_vPLLConfig(uint8 copy_PLLMull,uint8 copy_PLLSrc);

void RCC_vAHBEnableClk(uint8 copy_u8prephiral);
void RCC_vAHBDisableCLK(uint8 copy_u8prephiral);

void RCC_vAPB2EnableClk(uint8 copy_u8prephiral);
void RCC_vAPB2DisableClk(uint8 copy_u8prephiral);

void RCC_vAPB1EnableClk(uint8 copy_u8prephiral);
void RCC_vAPB1DisableCLK(uint8 copy_u8prephiral);


void RCC_vAHBPrescaler(uint8 copy_u8prescaler);
void RCC_vAPB1Prescaler(uint8 copy_u8prescaler);
void RCC_vAPB2Prescaler(uint8 copy_u8prescaler);
void RCC_vADCPrescaler(uint8 copy_u8prescaler);
/**********************************************************************************
 *	END OF FILE: RCC_interface.h
 **********************************************************************************/

#endif /* MCAL_RCC_INTERFACE_H_ */
