/**
 * @file: wifi_connect.cpp
 * @author: Noman5237
 * @date: 27/10/2021; 18:21
 */

#include "wifi_connect_internal.h"

void wifi_connect_station() {
    ESP_LOGD(TAG, "starting wifi connection");
    ESP_LOGI(TAG, "configured wifi with ip: %s, gateway: %s, subnet: %s", IPADDR2CSTR(CONFIG_WIFI_IP), IPADDR2CSTR(CONFIG_WIFI_GATEWAY), IPADDR2CSTR(CONFIG_WIFI_SUBNET));
    WiFi.config(CONFIG_WIFI_IP, CONFIG_WIFI_GATEWAY, CONFIG_WIFI_SUBNET);

    int wifi_status;
    for (int i = 0; i < CONFIG_WIFI_MAXIMUM_RETRY; i++) {
        ESP_LOGI(TAG, "connecting to SSID: %s with PASS: %s", CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);
        WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);
        delay(CONFIG_WIFI_CONNECTION_RETRY_DELAY_MS);
        wifi_status = WiFi.status();
        if (wifi_status == WL_CONNECTED) {
            break;
        } else {
            ESP_LOGE(TAG, "cannot connect to the wifi; error code %d", wifi_status);
        }
    }

    if (wifi_status == WL_CONNECTED) {
        ESP_LOGI(TAG, "connected to wifi with ip: %s", IPADDR2CSTR(WiFi.localIP()));
    }
}