#ifndef INC_GAMEPAD_H_
#define INC_GAMEPAD_H_

#include "main.h"

typedef struct {
	uint8_t UP;
	uint8_t DOWN;
	uint8_t LEFT;
	uint8_t RIGHT;
	uint8_t TRIANGLE;
	uint8_t CIRCLE;
	uint8_t CROSS;
	uint8_t SQUARE;
	uint8_t L1;
	uint8_t L2;
	uint8_t R1;
	uint8_t R2;
	uint8_t LX;
	uint8_t LY;
	uint8_t RX;
	uint8_t RY;
	uint8_t buffer[6];
	UART_HandleTypeDef *huart;
} GAMEPAD;


void GAMEPAD_Init(UART_HandleTypeDef *huart);
void GAMEPAD_ReceiveData();
void GAMPEPAD_Update();

#endif /* INC_GAMEPAD_H_ */
