/**
  ******************************************************************************
  * @file    stm32f4x7_eth_conf_template.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    14-October-2011
  * @brief   Configuration file for the STM32F407xx/417xx Ethernet driver.
  *          This file should be copied to the application folder and renamed to
  *          stm32f4x7_eth_conf.h    
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4x7_ETH_CONF_H
#define __STM32F4x7_ETH_CONF_H


/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx.h"
   
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Uncomment the line below when using time stamping and/or IPv4 checksum offload */
//#define USE_ENHANCED_DMA_DESCRIPTORS

#define _eth_delay_    ETH_Delay /* Default _eth_delay_ function with less precise timing */

/* Redefinition of the Ethernet driver buffers size and count */   
#define ETH_RX_BUF_SIZE    ipconfigNETWORK_MTU /* buffer size for receive */
#define ETH_TX_BUF_SIZE    ipconfigNETWORK_MTU /* buffer size for transmit */
#define ETH_RXBUFNB        10                  /* Rx buffers of size ETH_RX_BUF_SIZE */
#define ETH_TXBUFNB        3                   /* Tx buffers of size ETH_TX_BUF_SIZE */


/* PHY configuration section **************************************************/
/* PHY Reset delay */ 
#define PHY_RESET_DELAY    ((uint32_t)0x000FFFFF) 
/* PHY Configuration delay */ 
#define PHY_CONFIG_DELAY   ((uint32_t)0x00FFFFFF)

/* The PHY status register */
#define PHY_SR                         REG_PORT3_STATUS1

/* The Speed and Duplex mask values */
#define PHY_SPEED_STATUS               BIT2 
#define PHY_DUPLEX_STATUS              BIT1

   
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  


#endif /* __STM32F4x7_ETH_CONF_H */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

