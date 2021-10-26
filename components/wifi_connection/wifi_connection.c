/**
 * @file: wifi_connection.c
 * @author: Anonyman637
 * @date: 10/27/2021; 4:42 AM
 */

#include "p_wifi_connections.h"

static EventGroupHandle_t s_wifi_event_group;

static int s_retry_num = 0;

static void
wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
	if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
		esp_wifi_connect();
	} else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
		if (s_retry_num < WSS_WIFI_MAXIMUM_RETRY) {
			ESP_LOGI(TAG, "retrying to connect to wifi");
			esp_wifi_connect();
			s_retry_num++;
		} else {
			xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
		}
	} else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
		ip_event_got_ip_t *event = event_data;
		ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
		s_retry_num = 0;
		xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
	}
	
}

void
wifi_connect_station(void) {
	s_wifi_event_group = xEventGroupCreate();
	
	ESP_LOGD(TAG, "initializing wifi setups");
	esp_netif_create_default_wifi_sta();
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	
	ESP_LOGD(TAG, "configuring wifi and event handlers");
	
	esp_event_handler_instance_t instance_any_id;
	esp_event_handler_instance_t instance_got_ip;
	
	ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
	                                                    ESP_EVENT_ANY_ID,
	                                                    &wifi_event_handler,
	                                                    NULL,
	                                                    &instance_any_id));
	
	ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
	                                                    IP_EVENT_STA_GOT_IP,
	                                                    &wifi_event_handler,
	                                                    NULL,
	                                                    &instance_got_ip));
	
	wifi_config_t wifi_config = {
			.sta = {
					.ssid = WSS_WIFI_STA_SSID,
					.password = WSS_WIFI_STA_PASSWORD,
					
					/* Setting a password implies station will connect to all security modes including WEP/WPA.
					 * However, these modes are deprecated and not advisable to be used. In case your Access point
					 * doesn't support WPA2, these modes can be enabled by commenting below line */
					.threshold.authmode = WIFI_AUTH_WPA2_PSK,
					
					.pmf_cfg = {
							.capable = true,
							.required = false
					},
			},
	};
	
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
	ESP_ERROR_CHECK(esp_wifi_start());
	
	ESP_LOGD(TAG, "finished initializing and configuring wifi");
	
	ESP_LOGD(TAG, "waiting for wifi to connect");
	EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
	                                       WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
	                                       pdFALSE,
	                                       pdFALSE,
	                                       portMAX_DELAY);
	
	if (bits & WIFI_CONNECTED_BIT) {
		ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
		         WSS_WIFI_STA_SSID, WSS_WIFI_STA_PASSWORD);
	} else if (bits & WIFI_FAIL_BIT) {
		ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
		         WSS_WIFI_STA_SSID, WSS_WIFI_STA_PASSWORD);
	} else {
		ESP_LOGE(TAG, "UNEXPECTED EVENT");
	}
	
	ESP_LOGD(TAG, "cleaning up resources");
	ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
	ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
	vEventGroupDelete(s_wifi_event_group);
}
