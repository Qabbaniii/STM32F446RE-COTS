/********************************************************************************
 *	FILE DESCRIPTION
 *********************************************************************************
 * Filename              :   GPIO_Program.c
 * Author                :   Abdullah Qabbani
 * Origin Date           :   29/02/2024
 * Version               :   1.0.0
 * Compiler              :   GCC ARM Embedded Toolchain
 * Target                :
 * Notes                 :
 *
 *********************************************************************************/
/************************ SOURCE REVISION LOG *************************************
 *
 *  Date 	    	 Version   Author             Description
 *  29/02/2024       1.0.0     Abdullah Qabbani   Initial Release.
 *
 **********************************************************************************/

/**********************************************************************************
 * 	INCLUDES
 **********************************************************************************/
#include "stdint.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/STM32f44xx.h"
#include "GPIO_Interface.h"


/* static array of 8 pointers (the GPIO Ports) to avoid using "switch case" */

static GPIO_RegDef_t *GPIO_PORT[8] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};

/*********************************************************************************
 *	GLOBAL FUNCTIONS
 *********************************************************************************/

/*
 * Prototype        : uint8_t GPIO_u8PinInit(const PinConfig_t * PinConfig);
 * Description      : initializes the GPIO pin according to the input paramters
 * Parameters (in)  : PinConfig  :  A struct of paramters to config the pin like :
									PortName,pinNum,Mode,Speed,OutputType,PullType,ALtFunc
 * Parameters (out) : None                          
 * return           : ErrorStatus               
 */                                                 
                                                    
uint8 GPIO_u8PinInit(const PinConfig_t * PinConfig) 
{
	uint8 Local_u8ErrorStatus = OK;

	if((PinConfig->portName <= PORTH) && (PinConfig->pinNum <= PIN15) )
	{
		/*select GPIO mode: INPUT , OUTPUT , ANALOG , ALT FUNC */
		(GPIO_PORT[PinConfig->portName]->MODER) &= ~(TWO_BIT_MASK << ((PinConfig->pinNum) * TWO_PIN_ACCESS));
		(GPIO_PORT[PinConfig->portName]->MODER) |= ((PinConfig->mode) << ((PinConfig->pinNum) * TWO_PIN_ACCESS));

		/*Select GPIO Pull state : PU , PD , NO PULL*/
		(GPIO_PORT[PinConfig->portName]->PUPDR) &= ~(TWO_BIT_MASK << ((PinConfig->pinNum) * TWO_PIN_ACCESS));
		(GPIO_PORT[PinConfig->portName]->PUPDR) |= ((PinConfig->pullType) << ((PinConfig->pinNum) * TWO_PIN_ACCESS));

		/*Select Output type & output speed in case of general purpose output or alternate function */
		if ((PinConfig->mode) == OUTPUT || (PinConfig->mode) == ALTERNATE_FUNCTION)
		{
			(GPIO_PORT[PinConfig->portName]->OTYPER) &= ~(ONE_BIT_MASK << (PinConfig->pinNum));
			(GPIO_PORT[PinConfig->portName]->OTYPER) |= ((PinConfig->pullType) << (PinConfig->pinNum));

			(GPIO_PORT[PinConfig->portName]->OSPEEDR) &= ~(TWO_BIT_MASK << (PinConfig->pinNum) * TWO_PIN_ACCESS);
			(GPIO_PORT[PinConfig->portName]->OSPEEDR) |= ((PinConfig->pullType) << (PinConfig->pinNum) * TWO_PIN_ACCESS);
			if ((PinConfig->mode) == ALTERNATE_FUNCTION)
			{
				if ((PinConfig->pinNum) <= PIN7)
				{
					(GPIO_PORT[PinConfig->portName]->AFRL[0]) &= ~(FOUR_BIT_MASK << (PinConfig->pinNum) * FOUR_PIN_ACCESS);
					(GPIO_PORT[PinConfig->portName]->AFRL[0]) |= ((PinConfig->altFunc) << (PinConfig->pinNum) * FOUR_PIN_ACCESS);
				}
				else if ((PinConfig->pinNum) > PIN7)
				{
					(GPIO_PORT[PinConfig->portName]->AFRL[1]) &= ~(FOUR_BIT_MASK << (PinConfig->pinNum) * FOUR_PIN_ACCESS);
					(GPIO_PORT[PinConfig->portName]->AFRL[1]) |= ((PinConfig->altFunc) << (PinConfig->pinNum) * FOUR_PIN_ACCESS);
				}
			}
		}
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}

/*
 * Prototype        : uint8 GPIO_u8SetPinValue(Port_t PortName ,Pin_t pinNum,PinVal_t PinVal)
 * Description      : set a certain value on an output pin
 * Parameters (in)  : PortName [PORTA - PORTH] 
					  pinNum   [PIN0 - PIN15]
					  PinVal   PIN_LOW,PIN_HIGH            
 * Parameters (out) : None    
 * return           : ErrorStatus
 */
 
uint8 GPIO_u8SetPinValue(Port_t portName ,Pin_t pinNum,PinVal_t PinVal)
{
	uint8_t Local_u8ErrorStatus = OK;
if ((portName <= PORTH) && (pinNum <= PIN15))
{
	switch(PinVal)
	{
	case PIN_LOW : GPIO_PORT[portName]->ODR &= ~(ONE_BIT_MASK << pinNum);break;
	case PIN_HIGH: GPIO_PORT[portName]->ODR |= (ONE_BIT_MASK << pinNum);break;
	}
}
else
{
	Local_u8ErrorStatus = NOK;
}
return Local_u8ErrorStatus;
}
/*
 * Prototype        : uint8 GPIO_u8TogglePinValue(Port_t PortName ,Pin_t pinNum);
 * Description      : toggles the value of a certain pin
 * Parameters (in)  : PortName [PORTA - PORTH] 
					  pinNum   [PIN0 - PIN15]
 * Parameters (out) : None    
 * return           : ErrorStatus
 */

uint8 GPIO_u8TogglePinValue(Port_t portName ,Pin_t pinNum)
{
	uint8_t Local_u8ErrorStatus = OK;
if ((portName <= PORTH) && (pinNum <= PIN15))
{
	GPIO_PORT[portName]->ODR ^= (ONE_BIT_MASK << pinNum);
}
else
{
	Local_u8ErrorStatus = NOK;
}
return Local_u8ErrorStatus;
}

/*
 * Prototype        : uint8 GPIO_vReadPinValue(PORT_t Port ,Pin_t pinNum,PinVal_t* PinVal);
 * Description      : reads the value of a certain pin
 * Parameters (in)  : PortName [PORTA - PORTH]
					  pinNum   [PIN0 - PIN15]
 * Parameters (out) : PinVal   0,1   
 * return           : ErrorStatus
 */
 uint8 GPIO_u8ReadPinValue(Port_t portName ,Pin_t pinNum,PinVal_t* PinVal)
 {
	 uint8_t Local_u8ErrorStatus = OK;
	 	if ((portName <= PORTH) && (pinNum <= PIN15))
	 	{
	 		*PinVal = ((GPIO_PORT[portName]->IDR) >> pinNum & (ONE_BIT_MASK));
	 	}
	 	else
	 	{
	 		Local_u8ErrorStatus = NOK;
	 	}
	 return Local_u8ErrorStatus;
 }


/**************************************************************************************
 *  END OF FILE: GPIO_Program.c
 **************************************************************************************/
