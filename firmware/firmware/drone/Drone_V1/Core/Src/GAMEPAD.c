/*
 * GAMEPAD.c
 *
 *  Created on: Jan 28, 2026
 *      Author: ADMIN
 */

#include "main.h"
#include "GAMEPAD.h"

GAMEPAD gamepad;

void GAMEPAD_Init(UART_HandleTypeDef *huart){
	gamepad.huart = huart;
	HAL_UART_Receive_DMA(gamepad.huart, gamepad.buffer, 6);
}

void GAMEPAD_Update(){

	gamepad.A = gamepad.buffer[0] & (1 << 0);
	gamepad.B = gamepad.buffer[0] & (1 << 1);
	gamepad.X = gamepad.buffer[0] & (1 << 2);
	gamepad.Y = gamepad.buffer[0] & (1 << 3);

	gamepad.UP = gamepad.buffer[0] & (1 << 4);
	gamepad.DOWN = gamepad.buffer[0] & (1 << 5);
	gamepad.LEFT = gamepad.buffer[0] & (1 << 6);
	gamepad.RIGHT = gamepad.buffer[0] & (1 << 7);

	gamepad.L1 = gamepad.buffer[1] & (1 << 3);
	gamepad.R1 = gamepad.buffer[1] & (1 << 2);
	gamepad.L2 = gamepad.buffer[1] & (1 << 1);
	gamepad.R2 = gamepad.buffer[1] & (1 << 0);

	gamepad.LX = gamepad.buffer[2];
	gamepad.LY = gamepad.buffer[3];
	gamepad.RX = gamepad.buffer[4];
	gamepad.RY = gamepad.buffer[5];
}

void GAMEPAD_ReceiveData(){
	HAL_UART_Receive_DMA(gamepad.huart, gamepad.buffer, 6);
}



