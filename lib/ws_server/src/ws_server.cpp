/**
 * @file: ws_server.cpp
 * @author: Noman5237
 * @date: 28/10/2021; 02:11
 */

#include <ESP32Servo.h>

#include "ws_server_internal.h"

// Web server running on port 80
AsyncWebServer server(80);
// Web socket
AsyncWebSocket ws("/ws");

Servo ESC;

void ws_server_start() {
    ESP_LOGD(TAG, "adding ws event handler");
    ws.onEvent(ws_event_handler);
    ESP_LOGD(TAG, "adding ws event source to server");
    server.addHandler(&ws);

    ESP_LOGD(TAG, "adding default handler for server homepage");
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Welcome to ESP32 Backend Server");
    });

    ESP_LOGI(TAG, "ws server starting");
    server.begin();
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    ESC.setPeriodHertz(50);  // Standard 50hz servo
    ESC.attach(15, 1000, 2000);
}

void handlingIncomingData(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo *)arg;

    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        DynamicJsonDocument doc(96);
        DeserializationError error = deserializeJson(doc, data, len);

        if (error) {
            ESP_LOGE(TAG, "deserializeJson(%s) failed: %s", data, error.c_str());
            return;
        }

        // const char *svc = doc["svc"];  // "control"

        // JsonObject dt = doc["dt"];
        // int dt_t = dt["t"];  // 40
        // int dt_r = dt["r"];  // 40
        // int dt_p = dt["p"];  // 40
        // int dt_y = dt["y"];  // 40
        // ESP_LOGI(TAG, "t:%d;r:%d;p:%d;y:%d", dt_t, dt_r, dt_p, dt_y);

        int dt_t = doc["dt"]["t"];
        ESC.write(dt_t);
    } else {
        ESP_LOGI(TAG, "message split");
    }
}

void ws_event_handler(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            ESP_LOGI(TAG, "Client connected: \n\tClient id:%u\n\tClient IP:%s\n",
                     client->id(), client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            ESP_LOGI(TAG, "Client disconnected:\n\tClient id:%u\n", client->id());
            break;
        case WS_EVT_DATA:
            handlingIncomingData(arg, data, len);
            break;
        case WS_EVT_PONG:
            ESP_LOGI(TAG, "Pong:\n\tClient id:%u\n", client->id());
            break;
        case WS_EVT_ERROR:
            ESP_LOGI(TAG, "Error:\n\tClient id:%u\n", client->id());
            break;
    }
}