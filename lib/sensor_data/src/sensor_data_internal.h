/**
 * @file: sensor_data_input_internal.h
 * @author: Noman5237
 * @date: 29/10/2021; 10:45
 */

#ifndef ESPWSS_SENSOR_DATA_INPUT_INTERNAL_H
#define ESPWSS_SENSOR_DATA_INPUT_INTERNAL_H

#include <Wire.h>
#include <utils.h>

#include "../include/sensor_data.h"

static const char* TAG = "wss:sensor_data";

float sensor_data_gyro_raw[3] = {0, 0, 0};
float sensor_data_gyro_offset[3] = {0, 0, 0};

float sensor_data_acc_raw[3] = {0, 0, 0};
float sensor_data_acc_offset[3] = {0, 0, 0};

float sensor_data_gyro_angle[3] = {0, 0, 0};
float sensor_data_acc_angle[3] = {0, 0, 0};

void sensor_data_setup_mpu6050();

void sensor_data_calibrate_mpu6050();

void sensor_data_read_mpu6050();

void sensor_data_format_mpu6050();

#endif  //ESPWSS_SENSOR_DATA_INTERNAL_H