/*
 * UART_DMA_Handler.h
 *
 *  Created on: Jan 3, 2023
 *      Author: karl.yamashita
 */

#ifndef INC_UART_DMA_HANDLER_H_
#define INC_UART_DMA_HANDLER_H_


#define UART_DMA_CHAR_SIZE 192
#define UART_DMA_QUEUE_SIZE 16

typedef struct
{
	uint8_t data[UART_DMA_CHAR_SIZE];
	uint32_t size;
}UART_DMA_Data;

typedef struct
{
	UART_HandleTypeDef *huart;
	UART_DMA_Data queue[UART_DMA_QUEUE_SIZE];

	UART_DMA_Data *msgToParse;
	RING_BUFF_STRUCT ptr;
	bool uart_dma_rxIntErrorFlag;
}UART_DMA_RxQueueStruct;

typedef struct
{
	UART_HandleTypeDef *huart;
	UART_DMA_Data queue[UART_DMA_QUEUE_SIZE];
	RING_BUFF_STRUCT ptr;
}UART_DMA_TxQueueStruct;


void UART_DMA_RxInit(UART_DMA_RxQueueStruct *msg, UART_HandleTypeDef *huart);
void UART_DMA_TxInit(UART_DMA_TxQueueStruct *msg, UART_HandleTypeDef *huart);
void UART_DMA_EnableRxInterrupt(UART_DMA_RxQueueStruct *msg);
void UART_DMA_CheckRxInterruptErrorFlag(UART_DMA_RxQueueStruct *msg);
int UART_DMA_MsgRdy(UART_DMA_RxQueueStruct *msg);
void UART_DMA_NotifyUser(UART_DMA_TxQueueStruct *msg, char *str, bool lineFeed);

void UART_DMA_TX_AddMessageToBuffer(UART_DMA_TxQueueStruct *msg, uint8_t *str, uint32_t size);
void UART_DMA_SendMessage(UART_DMA_TxQueueStruct * msg);


#endif /* INC_UART_DMA_HANDLER_H_ */
