/*
 * WT61.h
 *
 *  Created on: Dec 2, 2025
 *  Author: manhtienvu-vn
 */
#include <main.h>
#include <stdbool.h>
#ifndef WT61_H_
#define WT61_H_

void WT61_Init(UART_HandleTypeDef *huart);
void WT61_SetBaudrate(uint16_t MCU_BAUDRATE, uint16_t IMU_OUTPUT_BAUDRATE, uint8_t TARGET_BAUDRATE);
double WT61_GetYawAngle();
double WT61_GetRollAngle();
double WT61_GetPitchAngle();
void WT61_CheckProtocolHeader(); //START_BIT
bool WT61_CheckDataField();	//a bit represents Data content
void WT61_ReceiveDataPacket(); //a data packet of 33 bytes
void WT61_CalculateFullAngles();
void WT61_HandleAngleWrapAround();
void WT61_ResetAngle();


#endif /* INC_WT61_H_ */
