/**
 * @file: sensor_data.cpp
 * @author: Noman5237
 * @date: 29/10/2021; 10:45
 */

#include "sensor_data_internal.h"

Adafruit_MPU6050 sensor_data_mpu;
sensors_event_t _a, _g, _temp;

void sensor_data_setup() {
    ESP_LOGD(TAG, "setting up mpu6050");
    sensor_data_setup_mpu6050();
}

void sensor_data_calibrate() {
    ESP_LOGD("calibrating values from mpu6050");
    sensor_data_calibrate_mpu6050();
}

void sensor_data_read() {
    ESP_LOGD("reading values from mpu6050");
    sensor_data_read_mpu6050();
}

void sensor_data_setup_mpu6050() {
    if (!sensor_data_mpu.begin()) {
        ESP_LOGE(TAG, "failed to find MPU6050 chip");
        utils_suspend();
    }
    sensor_data_mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    ESP_LOGI("mpu6050 accelerometer range: ");
    switch (sensor_data_mpu.getAccelerometerRange()) {
        case MPU6050_RANGE_2_G:
            ESP_LOGI(TAG, "+-2G");
            break;
        case MPU6050_RANGE_4_G:
            ESP_LOGI(TAG, "+-4G");
            break;
        case MPU6050_RANGE_8_G:
            ESP_LOGI(TAG, "+-8G");
            break;
        case MPU6050_RANGE_16_G:
            ESP_LOGI(TAG, "+-16G");
            break;
    }

    sensor_data_mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    ESP_LOGI("mpu6050 gyro range: ");
    switch (sensor_data_mpu.getGyroRange()) {
        case MPU6050_RANGE_250_DEG:
            ESP_LOGI(TAG, "+- 250 deg/s");
            break;
        case MPU6050_RANGE_500_DEG:
            ESP_LOGI(TAG, "+- 500 deg/s");
            break;
        case MPU6050_RANGE_1000_DEG:
            ESP_LOGI(TAG, "+- 1000 deg/s");
            break;
        case MPU6050_RANGE_2000_DEG:
            ESP_LOGI(TAG, "+- 2000 deg/s");
            break;
    }

    ESP_LOGD(TAG, "mpu6050 setup finished");
}

void sensor_data_calibrate_mpu6050() {
    int max_samples = 2000;

    for (int i = 0; i < max_samples; i++) {
        sensor_data_read_mpu6050();

        sensor_data_gyro_offset[X] += sensor_data_gyro[X];
        sensor_data_gyro_offset[Y] += sensor_data_gyro[Y];
        sensor_data_gyro_offset[Z] += sensor_data_gyro[Z];

        // Just wait a bit before next loop
        delay(3);
    }

    // Calculate average offsets
    sensor_data_gyro_offset[X] /= max_samples;
    sensor_data_gyro_offset[Y] /= max_samples;
    sensor_data_gyro_offset[Z] /= max_samples;
}

void sensor_data_read_mpu6050() {
    sensor_data_mpu.getEvent(&_a, &_g, &_temp);
    ESP_LOGI(TAG, "Acceleration: X: %f Y: %f Z: %f", _a.acceleration.x, _a.acceleration.y, _a.acceleration.z);
    ESP_LOGI(TAG, "Rotation X: %f Y: %f Z: %f", _g.gyro.x, _g.gyro.y, _g.gyro.z);
    ESP_LOGI(TAG, "Temperature: %f", _temp.temperature);
}