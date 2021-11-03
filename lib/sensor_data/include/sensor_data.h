/**
 * @file: sensor_data.h
 * @author: Noman5237
 * @date: 29/10/2021; 10:45
 */

#ifndef ESPWSS_SENSOR_DATA_H
#define ESPWSS_SENSOR_DATA_H
#include <MPU6050_light.h>

#define X 0
#define Y 1
#define Z 2

extern float sensor_data_gyro[3];
extern float sensor_data_acc[3];
extern float sensor_data_temp;

extern float sensor_data_angle[3];

/**
 * Setup sensor_datas for reading data
 */
void sensor_data_setup();

/**
 * calibrate sensor_data input data
 */
void sensor_data_calibrate();

/**
 * read data from sensor_datas
 */
void sensor_data_read();

void sensor_data_format();

/**
 * Calculate the x, y, and z angles
 */
void sensor_data_calculate_angle();

/**
 * update sensor data readings for accurate value in the loop
 */
void sensor_data_update();

#endif  //ESPWSS_SENSOR_DATA_H