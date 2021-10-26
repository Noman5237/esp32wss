/**
 * @file: esp32wss.c
 * @author: Anonyman637
 * @date: 10/27/2021; 4:42 AM
 */

#include <esp_log.h>
#include <nvs_flash.h>
#include <esp_netif.h>
#include <esp_event.h>

#include <wifi_connection.h>

static const char *TAG = "wss:main";

void app_main(void) {
	ESP_LOGD(TAG, "starting main");
	ESP_ERROR_CHECK(nvs_flash_init());
	ESP_ERROR_CHECK(esp_netif_init());
	
	ESP_LOGD(TAG, "starting default event loop");
	ESP_ERROR_CHECK(esp_event_loop_create_default());
	
	ESP_LOGD(TAG, "call to wifi connect to station");
	wifi_connect_station();
	
}
