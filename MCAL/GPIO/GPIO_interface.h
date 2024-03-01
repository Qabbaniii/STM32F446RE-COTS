/**********************************************************************************
 *	FILE DESCRIPTION
 **********************************************************************************
 * Filename              :   GPIO_interface.h
 * Author                :   Abdullah Qabbani
 * Origin Date           :   29/02/2024
 * Version               :   1.0.0
 * Compiler              :   GCC ARM Embedded Toolchain
 * Target                :
 * Notes                 :	
 *
 **********************************************************************************/
/************************ SOURCE REVISION LOG *************************************
 *
 *  Date 	   		 Version   Author             Description
 *  29/02/2024       1.0.0     Abdullah Qabbani   Initial Release.
 *
 **********************************************************************************/
#ifndef GPIO_GPIO_INTERFACE_H_
#define GPIO_GPIO_INTERFACE_H_

/***********************************************************************************
 * 	INCLUDES
 **********************************************************************************/
#include "../../LIB/STD_TYPES.h"

/***********************************************************************************
 *	CONSTANT MACROS & ENUMS
 ***********************************************************************************/


typedef enum
{
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH
}Port_t;
typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}Pin_t;

typedef enum
{
	INPUT=0,
	OUTPUT,
	ALTERNATE_FUNCTION,
	ANALOG
}Mode_t;

typedef enum
{
	LOW=0,
	MEDIUM,
	FAST,
	HIGH
}OutputSpeed_t;
typedef enum
{
	PUSH_PULL=0,
	OPEN_DRAIN
}OutputType_t;
typedef enum
{
	AF0=0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}AltFunc_t;

typedef enum
{
	NOPULL=0,
	PULLUP,
	PULLDOWN
}PullUpDown_t;

typedef enum
{
	PIN_LOW,
	PIN_HIGH
}PinVal_t;

typedef struct
{
	Port_t 			portName;
	Pin_t 			pinNum;
	Mode_t 			mode;
	OutputSpeed_t 	speed;
	OutputType_t 	outputType;
	PullUpDown_t 	pullType;
	AltFunc_t 		altFunc;
}PinConfig_t;

/***********************************************************************************
 *	FUNCTION PROTOTYPES
 **********************************************************************************/
uint8 GPIO_u8PinInit(const PinConfig_t * PinConfig);
uint8 GPIO_u8SetPinValue(Port_t PortName ,Pin_t PinNum,PinVal_t PinVal);
uint8 GPIO_u8TogglePinValue(Port_t PortName ,Pin_t PinNum);
uint8 GPIO_vReadPinValue(Port_t PortName ,Pin_t PinNum,PinVal_t* PinVal);

/**********************************************************************************
 *	END OF FILE: GPIO_interface.h
 **********************************************************************************/
#endif
