#include <stdio.h>
#include "mqtt_client.h"
#include "mqtt.h"

#define TAG "MQTT"

void mqtt_service_start() {
    // Start the MQTT service
    const esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address {
            .uri = MQTT_BROKER_ADDRESS_URI,
            .port = MQTT_BRORKER_PORT
        }
    };
    if(MQTT_USER_AUTHENTICATION) {
        mqtt_cfg.username = MQTT_USERNAME;
        mqtt_cfg.password = MQTT_PASSWORD;
    }
    ESP_ERROR_CHECK(esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg));
    ESP_ERROR_CHECK(esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, null));
    ESP_ERROR_CHECK(esp_mqtt_client_start(client));
    ESP_LOGI(TAG, "MQTT service started");
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id) {
         case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;
        default:
            break;
    }
}
