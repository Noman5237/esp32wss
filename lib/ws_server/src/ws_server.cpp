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
			// TODO: Handle data
            break;
        case WS_EVT_PONG:
            ESP_LOGI(TAG, "Pong:\n\tClient id:%u\n", client->id());
            break;
        case WS_EVT_ERROR:
            ESP_LOGI(TAG, "Error:\n\tClient id:%u\n", client->id());
            break;
    }
}