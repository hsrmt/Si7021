#ifndef __SI7021_H
#define __SI7021_H
#include "stm32f4xx.h"
extern I2C_HandleTypeDef hi2c1;
uint8_t data[3];
uint8_t da[1] = {0xFE};
uint8_t read[2]= {0xE3,0xE5};
uint8_t data1[3];
float temp,tempp;
float hu,humid;
uint16_t sum_temp,sum_humid;
void si7021_init()
{
HAL_I2C_Master_Transmit(&hi2c1,0x80,da,1,100);
	HAL_Delay(20);
}
void get_si7021(float *temp,float *humid)
{

		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		HAL_I2C_Master_Transmit(&hi2c1,0x80,&read[0],1,100);
		HAL_I2C_Master_Receive(&hi2c1,0x80,data,3,1000);
		sum_temp = (data[0]<<8) | data[1];
		tempp	= sum_temp;
		*temp = (-46.85 + (175.72*(tempp/65536)));
		HAL_Delay(20);
		HAL_I2C_Master_Transmit(&hi2c1,0x80,&read[1],1,100);
		HAL_I2C_Master_Receive(&hi2c1,0x80,data1,3,1000);
		sum_humid= (data1[0]<<8) | data1[1];
		hu= sum_humid;
		*humid = (-6+(125*(hu/65536)));
		HAL_Delay(20);
	}

#endif
