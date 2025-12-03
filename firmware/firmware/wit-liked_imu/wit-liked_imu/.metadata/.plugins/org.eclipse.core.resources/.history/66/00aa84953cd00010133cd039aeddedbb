
// * WT61.c
// *
// *  Created on: Dec 2, 2025
// *  Author: manhtienvu-vn
//

#include "WT61.h"
#include "stdbool.h"

UART_HandleTypeDef *IMU_UART;
//
volatile double yaw_angle = 0;
volatile double pitch_angle = 0;
volatile double roll_angle = 0;
//
//A data packet contains exactly 33 bytes -> It's always better to define an array with size > 33
uint8_t data_packet[40];
uint8_t check_bit = 0x00;

bool handle = false;

void WT61_Init(UART_HandleTypeDef *huart){
	IMU_UART = huart;
	WT61_ResetAngle();
	WT61_CheckProtocolHeader();
}

void WT61_ResetAngle(){
	HAL_UART_DMAStop(IMU_UART);
	HAL_UART_Transmit(IMU_UART, ANGLEZ_ZERO, sizeof(ANGLEZ_ZERO), 1000);
	HAL_Delay(5);
}

void WT61_ReceiveDataPacket(){
	HAL_UART_Receive_DMA(IMU_UART, data_packet, 33);
}

void WT61_CheckProtocolHeader(){
	HAL_UART_Receive(IMU_UART, &check_bit, 1, 1000);
	if(check_bit != PROTOCOL_HEADER){
		while (check_bit != PROTOCOL_HEADER){
			HAL_UART_Receive(IMU_UART, &check_bit, 1, 1000);
		}
		check_bit = 0x00;
		WT61_ReceiveDataPacket();
	}
}

bool WT61_CheckDataField(){
	if (data_packet[0] != FIELD_ANGLE){
		return false;
	}
	else {
		return true;
	}
}

double WT61_GetPitchAngle(){
	return pitch_angle;
}

double WT61_GetRollAngle(){
	return roll_angle;
}

double WT61_GetYawAngle(){
	return yaw_angle;
}

void WT61_CalculateFullAngles(){
	if (!WT61_CheckDataField()){
		handle = true;
		return;
	};

	pitch_angle = ( ((data_packet[4] << 8) | (data_packet[3])) / 32768.0f ) * 180.0f;
	roll_angle = ( ((data_packet[2] << 8) | (data_packet[1])) / 32768.0f ) * 180.0f;
	yaw_angle = ( ((data_packet[6] << 8) | (data_packet[5])) / 32768.0f) * 180.0f;

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == IMU_UART->Instance){
		WT61_CalculateFullAngles();
		WT61_ReceiveDataPacket();
	}
}




