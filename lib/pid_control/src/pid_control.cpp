/**
 * @file: pid_control.cpp
 * @author: Noman5237
 * @date: 29/10/2021; 12:41
 */

#ifndef ESPWSS_PID_CONTROL_H
#define ESPWSS_PID_CONTROL_H

#include "pid_control_internal.h"

void pid_control_calculate_motor_speed() {
    sensor_data_update();
    // sensor_data_read();
    // sensor_data_format();
    sensor_data_calculate_angle();
    // ws_server_fc_input_format();
    // ESP_LOGI(TAG, "A: X: %f Y: %f Z: %f", sensor_data_acc[X], sensor_data_acc[Y], sensor_data_acc[Z]);
    ESP_LOGI(TAG, "R: X: %f Y: %f Z: %f", sensor_data_angle[X], sensor_data_angle[Y], sensor_data_angle[Z]);
    ESP_LOGI(TAG, "t:%d;r:%d;p:%d;y:%d", ws_server_fc_input[THRUST], ws_server_fc_input[ROLL], ws_server_fc_input[PITCH], ws_server_fc_input[YAW]);
}

#endif  //ESPWSS_PID_CONTROL_H