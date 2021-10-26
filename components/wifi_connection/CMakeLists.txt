idf_component_register(SRCS "wifi_connection.c"
                       INCLUDE_DIRS "include"
                       PRIV_INCLUDE_DIRS "private"
                       PRIV_REQUIRES log esp_wifi freertos)
