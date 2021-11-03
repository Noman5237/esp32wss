/**
 * @file: ws_server.cpp
 * @author: Noman5237
 * @date: 28/10/2021; 02:11
 */

#include "ws_server_internal.h"

// Web server running on port 80
AsyncWebServer server(80);
// Web socket
AsyncWebSocket ws("/ws");

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

        JsonObject dt = doc["dt"];
        ws_server_fc_input[THRUST] = dt["t"];  // 40
        ws_server_fc_input[ROLL] = dt["r"];  // 40
        ws_server_fc_input[PITCH] = dt["p"];  // 40
        ws_server_fc_input[YAW] = dt["y"];  // 40
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

void ws_server_fc_input_format() {
    ws_server_fc_input[THRUST] = map(ws_server_fc_input[THRUST], -100, 100, 1000, 2000);
    ws_server_fc_input[ROLL] = map(ws_server_fc_input[ROLL], -100, 100, -10, 10);
    ws_server_fc_input[PITCH] = map(ws_server_fc_input[PITCH], -100, 100, -10, 10);
    ws_server_fc_input[YAW] = map(ws_server_fc_input[YAW], -100, 100, -10, 10);
}