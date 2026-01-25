/*
 * MPU6050.h
 *
 *      Author: ADMIN
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

void MPU6050_Init(I2C_HandleTypeDef*HI2C, TIM_HandleTypeDef *HTIM);
void MPU6050_GetAccel();
void MPU6050_GetGyro();
void MPU6050_Calibrate(uint16_t duration);
void MPU6050_GetFullReadings();
void MPU6050_GetFilteredData(float filterGyroCoef);

#endif /* INC_MPU6050_H_ */
