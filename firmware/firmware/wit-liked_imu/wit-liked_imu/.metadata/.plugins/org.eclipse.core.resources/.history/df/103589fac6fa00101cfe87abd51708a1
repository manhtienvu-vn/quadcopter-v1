
// * WT61.c
// *
// *  Created on: Dec 2, 2025
// *  Author: manhtienvu-vn
//

#include "WT61.h"
#include "stdbool.h"

// Read Format: [Protocol Header 0x55] [DataFieldID] [Data Packet of 33 Bytes]
// TYPE table (Data content):
/*     TYPE         |      REMARK
 *     0x51         |    Acceleration
 *     0x52	        |  Angular velocity
 *     0x53		    |       Angle
 */

#define PROTOCOL_HEADER 0x55
#define FIELD_ANGLE 0x53

//Write Format (in Hex code): 0xFF 0xAA COMMAND
static const uint8_t BAUDRATE_115200[] = {0xFF, 0xAA, 0x63};
static const uint8_t BAUDRATE_9600[] = {0xFF, 0xAA, 0x64};
static const uint8_t ANGLEZ_ZERO[] = {0xFF, 0xAA, 0x52};


UART_HandleTypeDef *IMU_UART;

volatile float yaw_angle = 0;
volatile float prev_yaw_angle = 0;
volatile float save_yaw_angle = 0;
volatile float pitch_angle = 0;
volatile float roll_angle = 0;

//A data packet contains exactly 33 bytes -> It's always better to define an array with size > 33
uint8_t data_packet[40];
uint8_t check_bit = 0x00;

bool handle = false;

void WT61_Init(UART_HandleTypeDef *huart){
	IMU_UART = huart;
	WT61_ResetAngle();
	WT61_ReceiveDataPacket();
}

void WT61_SetBaudrate(uint16_t MCU_BAUDRATE, uint16_t IMU_BAUDRATE, uint8_t TARGET_BAUDRATE){
	HAL_UART_DMAStop(IMU_UART);

	//NOTE: To send any data from MCU Tx to the IMU Rx, we have to synchronize the communication baudrate
	//Case: Tx Rate != Rx Rate -> Change Tx Rate to Rx Rate before transmitting the data command

	if (MCU_BAUDRATE != IMU_BAUDRATE){

		IMU_UART->Init.BaudRate = IMU_BAUDRATE;

		if (HAL_UART_Init(IMU_UART) != HAL_OK){

			Error_Handler();
		}
		//Now, we have successfully synchronize the Tx Rate and the Rx Rate to initialize the communication
		MCU_BAUDRATE = IMU_BAUDRATE;
	}
	//Waiting for Hardware Configuration
	HAL_Delay(10);

	//Send data command to request the IMU Module Tx to output at the TARGET_BAUDRATE
	HAL_UART_Transmit(IMU_UART, &TARGET_BAUDRATE, 3, 1000);
	//Now, the IMU Module Tx is re-configured to output at TARGET_BAUDRATE
	IMU_BAUDRATE = TARGET_BAUDRATE;

	//Important Final Step: Remember to re-configure MCU-Rx to receive data at the same TARGET_BAUDRATE
	if (MCU_BAUDRATE != TARGET_BAUDRATE){
		IMU_UART->Init.BaudRate = TARGET_BAUDRATE;

		if (HAL_UART_Init(IMU_UART) != HAL_OK){
			Error_Handler();
		}

		MCU_BAUDRATE = TARGET_BAUDRATE;
	}
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
	if (handle == true){
		HAL_UART_DMAStop(IMU_UART);
		HAL_UART_Receive(IMU_UART, &check_bit, 1, 1000);

		if(check_bit != PROTOCOL_HEADER){

			while (check_bit != PROTOCOL_HEADER){

				HAL_UART_Receive(IMU_UART, &check_bit, 1, 1000);

			}
			check_bit = 0x00;
			handle = false;
			WT61_ReceiveDataPacket();
		}
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
	WT61_HandleAngleWrapAround();
	return yaw_angle - save_yaw_angle;
}

void WT61_HandleAngleWrapAround(){
	// 0 -> 360 degree
	if (yaw_angle - prev_yaw_angle > 300.0f){
		save_yaw_angle += 360.0f;
	}

	//360 -> 0 degree
	else if (yaw_angle - prev_yaw_angle < -300.0f){
		save_yaw_angle -= 360.0f;
	}

	prev_yaw_angle = yaw_angle;
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
//		WT61_CalculateFullAngles();

//		angleZ = yaw_angle;
//		angleX = pitch_angle;
//		angleY = roll_angle;

//		WT61_ReceiveDataPacket();
	}
}




