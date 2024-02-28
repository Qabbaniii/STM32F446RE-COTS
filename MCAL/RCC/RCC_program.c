/**********************************************************************************
 *	FILE DESCRIPTION
 **********************************************************************************
 * Filename              :   RCC_Program.c
 * Author                :   Abdullah Qabbani
 * Origin Date           :   18/2/2024
 * Version               :   1.0.0
 * Compiler              :   GCC ARM Embedded Toolchain
 * Target                :
 * Notes                 :
 *
 *******************************************************************************/

/************************ SOURCE REVISION LOG **********************************
 *
 *    Date    Version   Author             Description
 *  23/2/2024   1.0.0   Abdullah Qabbani  Initial Release.
 *
 *******************************************************************************/

/*==============================================================================================================================================
 * Includes
 *==============================================================================================================================================*/
#include "stdint.h"
#include "../../SERVICES/BIT_MATH.h"
#include "../../SERVICES/STD_TYPES.h"
#include "RCC_Config.h"
#include "RCC_Interface.h"
#include "RCC_Register.h"


/*
 * Prototype   : uint8 RCC_u8SetClkStatus (uint8 copy_u8SysClk ,uint8 copy_u8Status)
 * Description : Set clock status
 * Arguments   : copy_u8SysClk : takes only HSI, HSE,PLL
 *               copy_u8Status : CLK_OM , CLK_OFF
 * return      : uint8_t number used for error handling
 *			     (1) means no error,(0) means Timeout for ready flag
 */
uint8 RCC_u8SetClkStatus (uint8 copy_u8SysClk ,uint8 copy_u8Status)
{
	/* variable to store time needed for clk to be ready */
	uint16 LOC_u16Timeout = 0 ;
	/* check clk type and it's status */
	switch (copy_u8SysClk ){
		case HSE:
		{
			switch ( copy_u8Status )
			{
				default:break;
				case CLK_ON:
				{
					/* HSE ON */
					SET_BIT(RCC->RCC_CR,HSEON);
					/* Waiting until Clock is Ready or timeout is reached */
					while( (GET_BIT(RCC->RCC_CR,HSERDY) == 0 ) && (LOC_u16Timeout <= TimeoutMax) )
					{
						LOC_u16Timeout ++ ;
					}
					/* check if timeout is reached */
					if ( LOC_u16Timeout == TimeoutMax )
					{
						return 0;
					}
				}break;
				case CLK_OFF:
				{
					/*  HSE OFF */
					CLR_BIT(RCC -> RCC_CR,HSEON);
				}break;
			}
		}break;
		case HSI:
		{
			switch ( copy_u8Status )
			{
				default:break;
				case CLK_ON:
				{
					/* HSE ON */
					SET_BIT(RCC->RCC_CR,HSION);
					/* Waiting until Clock is Ready or timeout is reached */
					while(GET_BIT(RCC->RCC_CR,HSIRDY == 0 ) && (LOC_u16Timeout <= TimeoutMax) )
					{
						LOC_u16Timeout ++ ;
					}
					/* check if timeout is reached */
					if ( LOC_u16Timeout == TimeoutMax )
					{
						return 0;
					}
				}break;
				case CLK_OFF:
				{
					/*  HSE OFF */
					CLR_BIT(RCC->RCC_CR,HSION);
				}break;
			}
		}break;
		case PLL:
		{
			switch (copy_u8Status)
			{
				default:break;
				case CLK_ON :
				{
				/* PLL ON */
				SET_BIT(RCC -> RCC_CR,PLLON);
				/*  Waiting until Clock is Ready or timeout is reached */
				while( GET_BIT(RCC ->RCC_CR  ,PLLRDY) == 0  && LOC_u16Timeout <= TimeoutMax)
				{
					LOC_u16Timeout ++ ;
				}
				/* check if timeout is reached */
				if ( LOC_u16Timeout < TimeoutMax )
				{
					return 0;
				}
				}break;
				case CLK_OFF :
				{
				/* PLL OFF */
				CLR_BIT(RCC ->RCC_CR,PLLON);
				}break;
			}
		}break;
	}
	return 1;
}


/*
 * Prototype   : void RCC_vSetSysClk(uint8 copy_u8ClkType)
 * Description : Set System Clock
 * Arguments   : copy_u8ClkType : takes only HSI, HSE,PLL
 *
 * return      : void
 */
void RCC_vSetSysClk(uint8 copy_u8ClkType)
{
	/* bit masking */
		RCC->RCC_CFGR &= ~( 0b11 << SW0 );
	/* Check SYSCLK */
	switch (copy_u8ClkType )
	{
	default:break;
	case HSE:
		{
			/* SET HSE AS SYSCLK */
			SET_BIT(RCC -> RCC_CFGR,SW0);
			CLR_BIT(RCC -> RCC_CFGR,SW1);
		}break;
	case HSI:
		{
			/* SET HSI AS SYSCLK */
			CLR_BIT(RCC -> RCC_CFGR,SW0);
			CLR_BIT(RCC -> RCC_CFGR,SW1);
		}break;
	case PLL:
		{
			/* SET PLL AS SYSCLK */
			CLR_BIT(RCC -> RCC_CFGR,SW0);
			SET_BIT(RCC -> RCC_CFGR,SW1);
		}break;
	}
}
/*
 * Prototype   : void RCC_vHSEConfig(uint8 copy_u8HSEBypassStatus,uint8 copy_u8HSEToPLLPrescaler)
 * Description : Set HSE Configuration
 * Arguments   : uint8 : 1- copy_u8HSEBypassStatus :  BYPASS_ON , BYPASS_OFF
 *                       2- copy_u8HSEToPLLPrescaler : Takes HSE_CLK , HSE_CLK_divided_by_2
 * return      : void
 */
void RCC_vHSEBypassStatus(uint8 copy_u8HSEBypassStatus)
{
	/* Check bypass is on or not */
	if ( copy_u8HSEBypassStatus == BYPASS_ON  )
	{
		SET_BIT(RCC ->RCC_CR,HSEBYP);
	}
	else if ( copy_u8HSEBypassStatus == BYPASS_OFF  )
	{
		CLR_BIT(RCC ->RCC_CR,HSEBYP);
	}

}
/*
 * Prototype   : void RCC_vHSEHSEToPLLPrescaler(uint8 copy_u8HSEToPLLPrescaler)
 * Description : Set HSE Configuration
 * Arguments   : copy_u8HSEToPLLPrescaler :Takes HSE_CLK_divided_by_1 , HSE_CLK_divided_by_2
 * return      : void
 */
void RCC_vHSEHSEToPLLPrescaler(uint8 copy_u8HSEToPLLPrescaler)
{
	/* HSE to PLL divider config */
	if ( copy_u8HSEToPLLPrescaler == HSE_CLK_divided_by_2 )
	{
		SET_BIT(RCC ->RCC_CR,PLLXTPRE);
	}
	else if ( copy_u8HSEToPLLPrescaler == HSE_CLK_divided_by_1  )
	{
		CLR_BIT(RCC ->RCC_CR,PLLXTPRE);
	}
}
/*
 * Prototype   : void RCC_vPLLConfig(uint8 copy_PLLMull,uint8 copy_PLLSrc)
 * Description : Set PLL Configuration
 * Arguments   : PLL_CONFIG : 1- copy_PLLMull  : Takes PLl_CLK_xi , i is from 2 to 16
 *                            2- copy_PLLSrc   : Takes HSE , HSI
 * return      : void
 */
void RCC_vPLLConfig(uint8 copy_PLLMull,uint8 copy_PLLSrc)
{
	/* bit masking */
	RCC ->RCC_CFGR &= ~( 0b1111 << PLLMUL0 );
	/* Set PLL Multiplication Factor */
	RCC ->RCC_CFGR |= ( copy_PLLMull  << PLLMUL0 );

	/* check PLL CLK Source*/
	if ( copy_PLLSrc == HSE )
	{
		SET_BIT(RCC->RCC_CFGR, PLLSRC);
	}
	else if ( copy_PLLSrc == HSI)
	{
		CLR_BIT(RCC->RCC_CFGR, PLLSRC);
	}
}
/*
 * Prototype   : void RCC_vAHBPrescaler(uint8 copy_u8prescaler)
 * Description : Set AHB Prescaler
 * Arguments   : copy_u8prescaler : Takes SYS_CLK,SYS_CLK_divided_by_2,SYS_CLK_divided_by_4,SYS_CLK_divided_by_8,
 * 										  SYS_CLK_divided_by_16,SYS_CLK_divided_by_64,SYS_CLK_divided_by_128,
										  SYS_CLK_divided_by_256,SYS_CLK_divided_by_512,
 * return      : void
 */
void RCC_vAHBPrescaler(uint8 copy_u8prescaler)
{
	/* bit masking */
	RCC->RCC_CFGR &= ~(0b1111<< HPRE0);
	/* set AHB Prescaler */
	RCC->RCC_CFGR |=  (copy_u8prescaler << HPRE0);


}
/*
 * Prototype   : void RCC_vAPB1Prescaler(uint8 copy_u8prescaler)
 * Description : Set APB1 Prescaler
 * Arguments   : copy_u8prescaler : Takes HCLK,HCLK_divided_by_2=4,HCLK_divided_by_4,
										  HCLK_divided_by_8,
										  HCLK_divided_by_16
 * return      : void
 */
void RCC_vAPB1Prescaler(uint8 copy_u8prescaler)
{
	/* bit masking */
	RCC->RCC_CFGR &= ~(0b111<< PPRE10);
	/* set APB1 Prescaler */
	RCC->RCC_CFGR |=  (copy_u8prescaler << PPRE10);
}
/*
 * Prototype   : void RCC_vAPB2Prescaler(uint8 copy_u8prescaler)
 * Description : Set APB2 Prescaler
 * Arguments   : copy_u8prescaler : Takes HCLK,HCLK_divided_by_2=4,HCLK_divided_by_4,
										  HCLK_divided_by_8,
										  HCLK_divided_by_16
 * return      : void
 */
void RCC_vAPB2Prescaler(uint8 copy_u8prescaler)
{
	/* bit masking */
	RCC->RCC_CFGR &= ~(0b111<< PPRE20);
	/* set APB2 Prescaler */
	RCC->RCC_CFGR |=  (copy_u8prescaler << PPRE20);
}

/*
 * Prototype   : void RCC_vADCPrescaler(uint8 copy_u8prescaler)
 * Description : Set ADC Prescaler
 * Arguments   : copy_u8prescaler : Takes   PCLK2_divided_by_2,PCLK_divided_by_4,
											PCLK_divided_by_6,
											PCLK_divided_by_8
 * return      : void
 */
void RCC_vADCPrescaler(uint8 copy_u8prescaler)
{
	/* bit masking */
	RCC->RCC_CFGR &= ~(0b11<< ADCPRE0);
	/* set ADC Prescaler */
	RCC->RCC_CFGR |=  (copy_u8prescaler << ADCPRE0);
}

/*
 * Prototype   : void RCC_vAHBEnableClk(uint8 copy_u8prephiral)
 * Description : Enable Required AHB Peripheral
 * Arguments   : copy_u8prephiral : Takes DMA1EN,DMA2EN,SRAMEN,FLITFEN,CRCEN,FSMCEN,SDIOEN
 * return      : void
 */
void RCC_vAHBEnableClk(uint8 copy_u8prephiral)
{
	/* Enable Required AHB Peripheral */
	SET_BIT(RCC ->RCC_AHBENR,copy_u8prephiral);

}
/*
 * Prototype   : void RCC_vAHBDisableCLK(uint8 copy_u8prephiral)
 * Description : Disable Required AHB Peripheral
 * Arguments   : copy_u8prephiral : Takes DMA1EN,DMA2EN,SRAMEN,FLITFEN,CRCEN,FSMCEN,SDIOEN
 * return      : void
 */
void RCC_vAHBDisableCLK(uint8 copy_u8prephiral)
{
	/* Disable Required AHB Peripheral */
	CLR_BIT(RCC ->RCC_AHBENR,copy_u8prephiral);

}
/*
 * Prototype   : void RCC_vAPB2EnableClk(uint8 copy_u8prephiral)
 * Description : Enable Required APB2 Peripheral
 * Arguments   : copy_u8prephiral : Takes AFIOEN,IOPAEN,IOPBEN,IOPCEN,IOPDEN,IOPEEN,IOPFEN,IOPGEN,
										  ADC1EN,ADC2EN,TIM1EN,SPI1EN,TIM8EN,USART1EN,ADC3EN,
										  TIM9EN,TIM10EN,TIM11EN
 * return      : void
 */

void RCC_vAPB2EnableClk(uint8 copy_u8prephiral)
{
	/* Enable Required APB2 Peripheral */
	SET_BIT(RCC ->RCC_APB2ENR,copy_u8prephiral);
}
/*
 * Prototype   : void RCC_vAPB2DisableClk(uint8 copy_u8prephiral)
 * Description : Disable Required APB2 Peripheral
 * Arguments   : copy_u8prephiral : Takes AFIOEN,IOPAEN,IOPBEN,IOPCEN,IOPDEN,IOPEEN,IOPFEN,IOPGEN,
										  ADC1EN,ADC2EN,TIM1EN,SPI1EN,TIM8EN,USART1EN,ADC3EN,
										  TIM9EN,TIM10EN,TIM11EN
 *
 * return      : void
 */
void RCC_vAPB2DisableClk(uint8 copy_u8prephiral)
{
	/* Disable Required APB2 Peripheral */
	CLR_BIT(RCC ->RCC_APB2ENR,copy_u8prephiral);
}
/*
 * Prototype   : void RCC_vAPB1EnableCLK(uint8 copy_u8prephiral)
 * Description : Enable Required APB1 Peripheral
 * Arguments   : copy_u8prephiral : Takes TIM2EN,TIM3EN,TIM4EN,TM5EN,TM6EN,TM7EN,TIM12EN,TIM13EN,TIM14EN
											,WWDGEN,SPI2EN,SPI3EN,USART2EN,USART3EN,UART4EN,UART5EN
											,I2C1EN,I2C2EN,USBEN,CANEN,BKPEN,PWREN,DACEN
 * return      : void
 */
void RCC_vAPB1EnableClk(uint8 copy_u8prephiral)
{
	/* Enable Required APB1 Peripheral */
	SET_BIT(RCC ->RCC_APB1ENR,copy_u8prephiral);
}
/*
 * Prototype   : void RCC_vAPB1DisableCLK(uint8 copy_u8prephiral)
 * Description : Disable Required APB1 Peripheral
 * Arguments   : copy_u8prephiral : Takes   TIM2EN,TIM3EN,TIM4EN,TM5EN,TM6EN,TM7EN,TIM12EN,TIM13EN,TIM14EN
											,WWDGEN,SPI2EN,SPI3EN,USART2EN,USART3EN,UART4EN,UART5EN
											,I2C1EN,I2C2EN,USBEN,CANEN,BKPEN,PWREN,DACEN
 * return      : void
 */
void RCC_vAPB1DisableCLK(uint8 copy_u8prephiral)
{
	/* Disable Required APB1 Peripheral */
	CLR_BIT(RCC ->RCC_APB1ENR,copy_u8prephiral);
}
















