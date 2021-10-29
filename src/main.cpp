/**
 * @file: main.cpp
 * @author: Noman5237
 * @date: 27/10/2021; 18:12
 */

#include <Arduino.h>
#include <wifi_connect.h>
#include <ws_server.h>

#include "main_internal.h"

void setup() {
    ESP_LOGD(TAG, "setup started");

    ESP_LOGD(TAG, "wifi connect station called");
    wifi_connect_station();

	ESP_LOGD(TAG, "ws server start called");
	ws_server_start();

    ESP_LOGD(TAG, "setting up sensors");
    sensor_data_setup();
    ESP_LOGD(TAG, "calibrating sensor input");
    sensor_data_calibrate();
}

void loop() {
    // put your main code here, to run repeatedly:
}