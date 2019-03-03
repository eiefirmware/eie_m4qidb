/*******************************************************************************
* File: typedefs.h                                                               
* Description:
* Type definitions for use with the system.
*******************************************************************************/

#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

typedef void(*fnCode_type)(void);

/* CHAR/SHORT/LONG types here for legacy code compatibility */
typedef char CHAR;              /* Signed 8-bits */
typedef unsigned char UCHAR;    /* Unsigned 8-bits */
typedef short SHORT;            /* Signed 16-bits */
typedef unsigned short USHORT;  /* Unsigned 16-bits */
typedef long LONG;              /* Signed 32-bits */
typedef unsigned long ULONG;    /* Unsigned 32-bits */

typedef enum {false = 0, true  = 1} bool;


#define BIT0 (1 << 0) 
#define BIT1 (1 << 1) 
#define BIT2 (1 << 2) 
#define BIT3 (1 << 3) 
#define BIT4 (1 << 4) 
#define BIT5 (1 << 5) 
#define BIT6 (1 << 6) 
#define BIT7 (1 << 7) 
#define BIT8 (1 << 8) 
#define BIT9 (1 << 9) 
#define BIT10 (1 << 10) 
#define BIT11 (1 << 11) 
#define BIT12 (1 << 12) 
#define BIT13 (1 << 13) 
#define BIT14 (1 << 14) 
#define BIT15 (1 << 15) 


#if 0
typedef char s8;              /* Signed 8-bits */
typedef unsigned char u8;    /* Unsigned 8-bits */
typedef short s16;            /* Signed 16-bits */
typedef unsigned short u16;  /* Unsigned 16-bits */
typedef long s32;              /* Signed 32-bits */
typedef unsigned long u32;    /* Unsigned 32-bits */

/* STM32F10x Standard Peripheral Library old types (maintained for legacy purpose) */
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  /*!< Read Only */
typedef __I int16_t vsc16;  /*!< Read Only */
typedef __I int8_t vsc8;   /*!< Read Only */

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /*!< Read Only */
typedef __I uint16_t vuc16;  /*!< Read Only */
typedef __I uint8_t vuc8;   /*!< Read Only */

#ifndef __cplusplus
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#endif

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;
#endif

#endif /* __TYPEDEFS_H */

