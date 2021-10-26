/**
 * @file: p_wifi_connections.h
 * @author: Anonyman637
 * @date: 10/27/2021; 4:35 AM
 */

#ifndef ESP32WSS_P_WIFI_CONNECTIONS_H
#define ESP32WSS_P_WIFI_CONNECTIONS_H

#include <wifi_connection.h>

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <esp_wifi.h>
#include <esp_wifi_default.h>

static const char *TAG = "wss:wifi";

#define WSS_WIFI_STA_SSID CONFIG_WIFI_SSID
#define WSS_WIFI_STA_PASSWORD CONFIG_WIFI_PASSWORD
#define WSS_WIFI_MAXIMUM_RETRY CONFIG_WIFI_MAXIMUM_RETRY

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries
 */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

static void
wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

#endif //ESP32WSS_P_WIFI_CONNECTIONS_H
