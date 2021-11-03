/**
 * @file: sensor_data.cpp
 * @author: Noman5237
 * @date: 29/10/2021; 10:45
 */

#include "sensor_data_internal.h"

MPU6050 sensor_data_mpu(Wire);

float sensor_data_gyro[3] = {0, 0, 0};
float sensor_data_acc[3] = {0, 0, 0};
float sensor_data_temp = 0;

float sensor_data_angle[3] = {0, 0, 0};

void sensor_data_setup() {
    ESP_LOGD(TAG, "setting up mpu6050");
    sensor_data_setup_mpu6050();
}

void sensor_data_calibrate() {
    ESP_LOGD(TAG, "calibrating values from mpu6050");
    sensor_data_calibrate_mpu6050();
}

void sensor_data_read() {
    // ESP_LOGD(TAG, "reading values from mpu6050");
    sensor_data_read_mpu6050();
}

void sensor_data_format() {
    // ESP_LOGD(TAG, "formatting sensor data");
    sensor_data_format_mpu6050();
}

void sensor_data_setup_mpu6050() {
    if (!sensor_data_mpu.begin()) {
        ESP_LOGE(TAG, "failed to find MPU6050 chip");
        utils_suspend();
    }

    ESP_LOGD(TAG, "mpu6050 setup finished");
}

void sensor_data_calibrate_mpu6050() {
    sensor_data_mpu.calcOffsets();
    sensor_data_gyro_offset[X] = sensor_data_mpu.getGyroXoffset();
    sensor_data_gyro_offset[Y] = sensor_data_mpu.getGyroYoffset();
    sensor_data_gyro_offset[Z] = sensor_data_mpu.getGyroZoffset();
    ESP_LOGI(TAG, "calibration finished");
    ESP_LOGI(TAG, "gyro data offset: X: %f Y: %f Z: %f", sensor_data_gyro_offset[X], sensor_data_gyro_offset[Y], sensor_data_gyro_offset[Z]);
    ESP_LOGI(TAG, "acc data offset: X: %f Y: %f Z: %f", sensor_data_acc_offset[X], sensor_data_acc_offset[Y], sensor_data_acc_offset[Z]);
}

void sensor_data_read_mpu6050() {
    sensor_data_acc_raw[X] = sensor_data_mpu.getAccX();
    sensor_data_acc_raw[Y] = sensor_data_mpu.getAccY();
    sensor_data_acc_raw[Z] = sensor_data_mpu.getAccZ();
    // ESP_LOGD(TAG, "Raw Acceleration: X: %f Y: %f Z: %f", sensor_data_acc_raw[X], sensor_data_acc_raw[Y], sensor_data_acc_raw[Z]);
    sensor_data_gyro_raw[X] = sensor_data_mpu.getGyroX();
    sensor_data_gyro_raw[Y] = sensor_data_mpu.getGyroY();
    sensor_data_gyro_raw[Z] = sensor_data_mpu.getGyroZ();
    // ESP_LOGD(TAG, "Raw Rotation: X: %f Y: %f Z: %f", sensor_data_gyro_raw[X], sensor_data_gyro_raw[Y], sensor_data_gyro_raw[Z]);
    // ESP_LOGD(TAG, "Temperature: %f", _temp.temperature);
    sensor_data_temp = sensor_data_mpu.getTemp();
}

void sensor_data_format_mpu6050() {
    sensor_data_acc[X] = sensor_data_acc_raw[X] * 9.8;
    sensor_data_acc[Y] = sensor_data_acc_raw[Y] * 9.8;
    sensor_data_acc[Z] = sensor_data_acc_raw[Z] * 9.8;

    ESP_LOGI(TAG, "Acceleration: X: %f Y: %f Z: %f", sensor_data_acc[X], sensor_data_acc[Y], sensor_data_acc[Z]);
    ESP_LOGI(TAG, "Rotation: X: %f Y: %f Z: %f", sensor_data_gyro[X], sensor_data_gyro[Y], sensor_data_gyro[Z]);
}

void sensor_data_calculate_angle() {
    sensor_data_angle[X] = sensor_data_mpu.getAngleX();
    sensor_data_angle[Y] = sensor_data_mpu.getAngleY();
    sensor_data_angle[Z] = sensor_data_mpu.getAngleZ();

    ESP_LOGI(TAG, "Angle: X: %f Y: %f Z: %f", sensor_data_angle[X], sensor_data_angle[Y], sensor_data_angle[Z]);
}

void sensor_data_update() {
    sensor_data_mpu.update();
}