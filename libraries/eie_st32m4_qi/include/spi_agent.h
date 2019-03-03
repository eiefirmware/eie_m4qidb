/*******************************************************************************
* File: spi_agent.h
* Description:
* Header file for spi_agent.c
*******************************************************************************/

#ifndef __SPI_AGENT_H
#define __SPI_AGENT_H

/*******************************************************************************
* Typedefs
*******************************************************************************/

typedef enum
{
  NVM_READ = 0,
  NVM_WRITE = 1,
  NVM_ERASE = 2
} NVM_ACCESS_TYPE_ENUM;

/* Message struct used for SPI data */
typedef struct
{
  u16 u16Length;               /* Number of bytes in the message */
  u8* pu8Data;                 /* Address of the first data byte */
  NVM_ACCESS_TYPE_ENUM  eAccessType;  
} SpiQueueMessageType;

// Address where config data is stored: $000000
#define NVM_ADDRESS_L    (0x00)
#define NVM_ADDRESS_M    (0x00)
#define NVM_ADDRESS_H    (0x00)


/*******************************************************************************
* Macros (board-specific: need to be adjusted to target PCB)
*******************************************************************************/


/*******************************************************************************
* Application Values
*******************************************************************************/
/* RTOS settings */
#define SPI_STACK_SIZE              configMINIMAL_STACK_SIZE        /* Size of the LCD stack */
#define SPI_TASK_PRIORITY           mainCOMMUNICATION_TASK_PRIORITY /* Priority of the LCD task */


#define SPI_QUEUE_LENGTH            (u8)5     /* Maximum number of messages allowed in the queue */
#define SPI_QUEUE_ITEM_SIZE         (u8)(sizeof(SpiQueueMessageType)) /* Size of each item in the queue */

#define SPI_RX_BUFFER_SIZE          (u16)128  /* Maximum receive buffer size */

#define SPI_CMD_BUFFER_SIZE         (50)
#define SPI_MAX_CMD_LENGTH          (5)


/*******************************************************************************
* Function prototypes
*******************************************************************************/
/* Public API Functions */

/* Protected Functions */
static portTASK_FUNCTION( vSpiTask, pvParameters );
void vStartSpiTask( unsigned portBASE_TYPE uxPriority );


/* Private  Functions */

#endif /* __SPI_AGENT_H */