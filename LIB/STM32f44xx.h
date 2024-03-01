
/********************************************************************************
 *	FILE DESCRIPTION
 ********************************************************************************
 * Filename              :   STM32f44xx.h
 * Author                :   Abdullah Qabbani
 * Origin Date           :   27/03/2024
 * Version               :   1.0.0
 * Compiler              :   GCC ARM Embedded Toolchain
 * Target                :
 * Notes                 :	
 *
 *********************************************************************************/
/************************ SOURCE REVISION LOG *************************************
 *
 *  Date 	 	     Version   Author             Description
 *  27/03/2024       1.0.0     Abdullah Qabbani   Initial Release.
 *
 **********************************************************************************/
#ifndef STM32F44xx_H_ 
#define STM32F44xx_H_

/********************************************************************************
 *	Various Memories Base Address
 ********************************************************************************/

#define FLASH_BASE_ADDRESS		0x08000000UL
#define SRAM_BADE_ADDRESS		0x20000000UL


/********************************************************************************
 *	AHB1 Peripheral Base Address 
 ********************************************************************************/
 
 /**************************   GPIOx Base Address     ***************************/
 #define GPIOA_BASE_ADDRESS		0x40020000UL
 #define GPIOB_BASE_ADDRESS		0x40020400UL
 #define GPIOC_BASE_ADDRESS		0x40020800UL
 #define GPIOD_BASE_ADDRESS		0x40020C00UL
 #define GPIOE_BASE_ADDRESS		0x40021000UL
 #define GPIOF_BASE_ADDRESS		0x40021400UL
 #define GPIOG_BASE_ADDRESS		0x40021800UL
 #define GPIOH_BASE_ADDRESS		0x40021C00UL

 /***************************   RCC Base Address     ***************************/
 #define RCC_BASE_ADDRESS		0x40023800UL
 
/********************************************************************************
 *	AHB2 Peripheral Base Address 
 ********************************************************************************/
 
 /********************************************************************************
 *	AHB3 Peripheral Base Address 
 ********************************************************************************/
 
/********************************************************************************
 *	APB1 Peripheral Base Address 
 ********************************************************************************/
  
/********************************************************************************
 *  APB2 Peripheral Base Address 
 ********************************************************************************/
  

/********************************************************************************
 *	Various Registers Definition
 ********************************************************************************/

/********************   GPIO Register Definition Structure    ********************/

typedef struct
{
  volatile uint32_t MODER;   /*GPIO PORT MODE REGISTER */
  volatile uint32_t OTYPER;  /*GPIO PORT OUTPUT TYPE REGISTER*/
  volatile uint32_t OSPEEDR; /*GPIO PORT OUTPUT SPEED REGISTER*/
  volatile uint32_t PUPDR;   /*GPIO PORT PULL UP / DOWN REGISTER */
  volatile uint32_t IDR;     /*GPIO PORT INPUT DAATA REGISTER */
  volatile uint32_t ODR;     /*GPIO PORT OUTPUT DATA REGISTER */
  volatile uint32_t BSRR;    /*GPIO PORT BIT SET / RESET REGISTER  */
  volatile uint32_t LCKR;    /*GPIO PORT LOCK REGISTER  */
  volatile uint32_t AFR[2]; /*GPIO PORT ALTERNATE FUNCTION REGISTER  */
} GPIO_RegDef_t;

/********************   RCC Register Definition Structure    ********************/

typedef struct
{
  volatile uint32 CR;         /*!< RCC clock control register,                                   */
  volatile uint32 PLLCFGR;    /*!< RCC PLL configuration register,                               */
  volatile uint32 CFGR;       /*!< RCC clock configuration register,                             */
  volatile uint32 CIR;        /*!< RCC clock interrupt register,                                 */
  volatile uint32 AHB1RSTR;   /*!< RCC AHB1 peripheral reset register,                           */
  volatile uint32 AHB2RSTR;   /*!< RCC AHB2 peripheral reset register,                           */
  volatile uint32 AHB3RSTR;   /*!< RCC AHB3 peripheral reset register,                           */
  uint32 RESERVED0;           /*!< Reserved, 0x1C                                                */
  volatile uint32 APB1RSTR;   /*!< RCC APB1 peripheral reset register,                           */
  volatile uint32 APB2RSTR;   /*!< RCC APB2 peripheral reset register,                           */
  uint32 RESERVED1[2];        /*!< Reserved, 0x28-0x2C                                           */
  volatile uint32 AHB1ENR;    /*!< RCC AHB1 peripheral clock register,                           */
  volatile uint32 AHB2ENR;    /*!< RCC AHB2 peripheral clock register,                           */
  volatile uint32 AHB3ENR;    /*!< RCC AHB3 peripheral clock register,                           */
  uint32 RESERVED2;           /*!< Reserved, 0x3C                                                */
  volatile uint32 APB1ENR;    /*!< RCC APB1 peripheral clock enable register,                    */
  volatile uint32 APB2ENR;    /*!< RCC APB2 peripheral clock enable register,                    */
  uint32 RESERVED3[2];        /*!< Reserved, 0x48-0x4C                                           */
  volatile uint32 AHB1LPENR;  /*!< RCC AHB1 peripheral clock enable in low power mode register,  */
  volatile uint32 AHB2LPENR;  /*!< RCC AHB2 peripheral clock enable in low power mode register,  */
  volatile uint32 AHB3LPENR;  /*!< RCC AHB3 peripheral clock enable in low power mode register,  */
  uint32 RESERVED4;           /*!< Reserved, 0x5C                                                */
  volatile uint32 APB1LPENR;  /*!< RCC APB1 peripheral clock enable in low power mode register,  */
  volatile uint32 APB2LPENR;  /*!< RCC APB2 peripheral clock enable in low power mode register,  */
  uint32 RESERVED5[2];        /*!< Reserved, 0x68-0x6C                                           */
  volatile uint32 BDCR;       /*!< RCC Backup domain control register,                           */
  volatile uint32 CSR;        /*!< RCC clock control & status register,                          */
  uint32 RESERVED6[2];        /*!< Reserved, 0x78-0x7C                                           */
  volatile uint32 SSCGR;      /*!< RCC spread spectrum clock generation register,                */
  volatile uint32 PLLI2SCFGR; /*!< RCC PLLI2S configuration register,                            */
  volatile uint32 PLLSAICFGR; /*!< RCC PLLSAI configuration register,                            */
  volatile uint32 DCKCFGR;    /*!< RCC Dedicated Clocks configuration register,                  */
  volatile uint32 CKGATENR;   /*!< RCC Clocks Gated ENable Register,                             */
  volatile uint32 DCKCFGR2;   /*!< RCC Dedicated Clocks configuration register 2,                */
} RCC_RegDef_t;


/********************************************************************************
 *	Various PREPHIRAL DEFINITION
 ********************************************************************************/

/********************   GPIO peripheral Definitions     ********************/

#define GPIOA ((GPIO_RegDef_t *)GPIOA_BASE_ADDRESS)
#define GPIOB ((GPIO_RegDef_t *)GPIOB_BASE_ADDRESS)
#define GPIOC ((GPIO_RegDef_t *)GPIOC_BASE_ADDRESS)
#define GPIOD ((GPIO_RegDef_t *)GPIOD_BASE_ADDRESS)
#define GPIOE ((GPIO_RegDef_t *)GPIOE_BASE_ADDRESS)
#define GPIOF ((GPIO_RegDef_t *)GPIOF_BASE_ADDRESS)
#define GPIOG ((GPIO_RegDef_t *)GPIOG_BASE_ADDRESS)
#define GPIOH ((GPIO_RegDef_t *)GPIOH_BASE_ADDRESS)

/********************   RCC peripheral Definitions     ********************/
#define RCC  ((RCC_RegDef_t*)RCC_BASE_ADDRESS)

 

/*********************************************************************************
 *	END OF FILE: STM32F44xx.h
 *********************************************************************************/
 #endif
