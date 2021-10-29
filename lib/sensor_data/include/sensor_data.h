/**
 * @file: sensor_data.h
 * @author: Noman5237
 * @date: 29/10/2021; 10:45
 */

#ifndef ESPWSS_SENSOR_DATA_H
#define ESPWSS_SENSOR_DATA_H

#define X 0
#define Y 1
#define Z 2

static float sensor_data_gyro[3] = {0, 0, 0};
static float sensor_data_gyro_offset[3] = {0, 0, 0};
static float sensor_data_acc[3] = {0 ,0 ,0};
static float sensor_data_acc_offset[3] = {0 ,0 ,0};
static float sensor_data_temp = 0;

/**
 * Setup sensor_datas for reading data
 */
void sensor_data_setup();

/**
 * calibrate sensor_data input data
 */
void sensor_data_calibrate();

/**
 * Read data from sensor_datas
 */
void sensor_data_read();

#endif  //ESPWSS_SENSOR_DATA_H