/**
 * @file: ws_server_internal.h
 * @author: Noman5237
 * @date: 28/10/2021; 02:13
 */

#ifndef ESPWSS_WS_SERVER_INTERNAL_H
#define ESPWSS_WS_SERVER_INTERNAL_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <motor_input.h>

#include "../include/ws_server.h"

static const char* TAG = "wss:ws_server";

int ws_server_fc_input[4] = {0, 0, 0, 0};

void ws_event_handler(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len);

#endif  //ESPWSS_WS_SERVER_INTERNAL_H