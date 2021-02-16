/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

//#define USE_SEMIHOSTING 1

TaskHandle_t TaskHandle1 = NULL;
TaskHandle_t TaskHandle2 = NULL;
char msg_buffer[512] = "";
typedef enum {
	UNAVAILABLE = 0,
	AVAILABLE = !UNAVAILABLE
} UartAccessState;
uint8_t UART_ACCESS = AVAILABLE;

void uart_printf(char *msg);

static void prvSetupUart(void) {

	//enable UART clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//AF pin config
	GPIO_InitTypeDef gpio_uart_pins;
	memset(&gpio_uart_pins, 0, sizeof(gpio_uart_pins));
	gpio_uart_pins.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio_uart_pins.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart_pins.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio_uart_pins);
	//PA2, PA3 as TX and RX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	//UART init
	USART_InitTypeDef usart2_init;
	memset(&usart2_init, 0, sizeof(usart2_init));
	usart2_init.USART_BaudRate = 115200;
	usart2_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart2_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart2_init.USART_Parity = USART_Parity_No;
	usart2_init.USART_StopBits = USART_StopBits_1;
	usart2_init.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &usart2_init);

	USART_Cmd(USART2, ENABLE);
}

static void prvSetupHardware(void) {

	prvSetupUart();
}

void vTask1_handler(void *params) {

	while(true)
	{
		if(UART_ACCESS == AVAILABLE){
			UART_ACCESS = UNAVAILABLE;
			uart_printf("Task - 1: Hello world.\r\n");
			UART_ACCESS = AVAILABLE;
			taskYIELD();
		}

	}
}

void vTask2_handler(void *params) {

	while(true)
	{
		if(UART_ACCESS == AVAILABLE){
			UART_ACCESS = UNAVAILABLE;
			uart_printf("Task - 2: Hello world.\r\n");
			UART_ACCESS = AVAILABLE;
			taskYIELD();
		}
	}
}

#ifdef USE_SEMIHOSTING
	extern void initialise_monitor_handles();
#endif

void uart_printf(char *msg) {

	for (uint32_t i = 0; i < strlen(msg); i++) {
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) != SET);
		USART_SendData(USART2, msg[i]);
	}

}

int main(void)
{
	DWT->CTRL |= (1 << 0);
	RCC_DeInit();
	SystemCoreClockUpdate();
	prvSetupHardware();
#ifdef USE_SEMIHOSTING
	initialise_monitor_handles();
	printf("Hello World!\n");
#endif

	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();

	sprintf(msg_buffer, "This is Hello World app begin.\r\n");
	uart_printf(msg_buffer);

	xTaskCreate(vTask1_handler, "Task-1",
			configMINIMAL_STACK_SIZE, NULL,
			2, &TaskHandle1);

	xTaskCreate(vTask2_handler, "Task-2",
				configMINIMAL_STACK_SIZE, NULL,
				2, &TaskHandle2);

	vTaskStartScheduler();

	for(;;);
}
