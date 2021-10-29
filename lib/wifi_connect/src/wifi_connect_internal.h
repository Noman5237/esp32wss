/**
 * @file: p_wifi_connect.h
 * @author: Noman5237
 * @date: 27/10/2021; 18:22
 */

#ifndef ESPWSS_WIFI_CONNECT_INTERNAL_H
#define ESPWSS_WIFI_CONNECT_INTERNAL_H

#include <Arduino.h>
#include <IPAddress.h>
#include <WiFi.h>
#include <utils.h>

#include "../include/wifi_connect.h"

#define IPADDR2CSTR(ip) ip.toString().c_str()

static const char* TAG = "wss:wifi";

#define CONFIG_WIFI_SSID "Chaos"
#define CONFIG_WIFI_PASSWORD "Chaos5312"
#define CONFIG_WIFI_MAXIMUM_RETRY 5
#define CONFIG_WIFI_CONNECTION_RETRY_DELAY_MS 5000

IPAddress CONFIG_WIFI_IP(192, 168, 137, 215);
IPAddress CONFIG_WIFI_GATEWAY(192, 168, 137, 1);
IPAddress CONFIG_WIFI_SUBNET(255, 255, 255, 0);

#endif  //ESPWSS_WIFI_CONNECT_INTERNAL_H