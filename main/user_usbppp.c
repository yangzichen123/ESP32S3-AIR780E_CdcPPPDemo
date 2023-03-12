#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_netif.h"
#include "led_indicator.h"
#include "led_indicator_blink_default.h"
#include "usbh_modem_board.h"
#include "usbh_modem_wifi.h"
#include "mqtt_client.h"

static const char *TAG = "user_usbppp";
#define LED_RED_SYSTEM_GPIO CONFIG_EXAMPLE_LED_RED_SYSTEM_GPIO
#define LED_BLUE_WIFI_GPIO CONFIG_EXAMPLE_LED_BLUE_WIFI_GPIO
#define LED_GREEN_4GMODEM_GPIO CONFIG_EXAMPLE_LED_GREEN_4GMODEM_GPIO
#define LED_ACTIVE_LEVEL 1

// static modem_wifi_config_t s_modem_wifi_config = MODEM_WIFI_DEFAULT_CONFIG();
led_indicator_handle_t s_led_system_handle = NULL;
led_indicator_handle_t s_led_wifi_handle = NULL;
led_indicator_handle_t s_led_4g_handle = NULL;

void SL_LedIndicatorInit(void)
{
    led_indicator_gpio_config_t led_indicator_gpio_config = {
        .is_active_level_high = LED_ACTIVE_LEVEL,
    };

    led_indicator_config_t led_config = {
        .led_indicator_gpio_config = &led_indicator_gpio_config,
        .mode = LED_GPIO_MODE,
    };

    if (LED_RED_SYSTEM_GPIO)
    {
        led_indicator_gpio_config.gpio_num = LED_RED_SYSTEM_GPIO;
        s_led_system_handle = led_indicator_create(&led_config);
        assert(s_led_system_handle != NULL);
        led_indicator_stop(s_led_system_handle, BLINK_CONNECTED);
        led_indicator_stop(s_led_system_handle, BLINK_CONNECTING);
        // led_indicator_start(s_led_system_handle, BLINK_CONNECTING);
    }
    if (LED_BLUE_WIFI_GPIO)
    {
        led_indicator_gpio_config.gpio_num = LED_BLUE_WIFI_GPIO;
        s_led_wifi_handle = led_indicator_create(&led_config);
        assert(s_led_wifi_handle != NULL);
        led_indicator_stop(s_led_wifi_handle, BLINK_CONNECTED);
        led_indicator_stop(s_led_wifi_handle, BLINK_CONNECTING);
    }
    if (LED_GREEN_4GMODEM_GPIO)
    {
        led_indicator_gpio_config.gpio_num = LED_GREEN_4GMODEM_GPIO;
        s_led_4g_handle = led_indicator_create(&led_config);
        assert(s_led_4g_handle != NULL);
        led_indicator_stop(s_led_4g_handle, BLINK_CONNECTED);
        led_indicator_stop(s_led_4g_handle, BLINK_CONNECTING);
    }
}

static void on_modem_event(void *arg, esp_event_base_t event_base,
                           int32_t event_id, void *event_data)
{
    if (event_base == MODEM_BOARD_EVENT)
    {
        if (event_id == MODEM_EVENT_SIMCARD_DISCONN)
        {
            ESP_LOGW(TAG, "Modem Board Event: SIM Card disconnected");
            led_indicator_start(s_led_4g_handle, BLINK_CONNECTED);
        }
        else if (event_id == MODEM_EVENT_SIMCARD_CONN)
        {
            ESP_LOGI(TAG, "Modem Board Event: SIM Card Connected");
            led_indicator_stop(s_led_4g_handle, BLINK_CONNECTED);
        }
        else if (event_id == MODEM_EVENT_DTE_DISCONN)
        {
            ESP_LOGW(TAG, "Modem Board Event: USB disconnected");
            led_indicator_stop(s_led_4g_handle, BLINK_CONNECTED);
            led_indicator_start(s_led_4g_handle, BLINK_CONNECTING);
        }
        else if (event_id == MODEM_EVENT_DTE_CONN)
        {
            ESP_LOGI(TAG, "Modem Board Event: USB connected");
            led_indicator_stop(s_led_4g_handle, BLINK_CONNECTED);
            led_indicator_start(s_led_4g_handle, BLINK_CONNECTING);
        }
        else if (event_id == MODEM_EVENT_DTE_RESTART)
        {
            ESP_LOGW(TAG, "Modem Board Event: Hardware restart");
            led_indicator_start(s_led_4g_handle, BLINK_CONNECTED);
        }
        else if (event_id == MODEM_EVENT_DTE_RESTART_DONE)
        {
            ESP_LOGI(TAG, "Modem Board Event: Hardware restart done");
            led_indicator_stop(s_led_4g_handle, BLINK_CONNECTED);
        }
        else if (event_id == MODEM_EVENT_NET_CONN)
        {
            ESP_LOGI(TAG, "Modem Board Event: Network connected");
            led_indicator_start(s_led_4g_handle, BLINK_CONNECTED);
        }
        else if (event_id == MODEM_EVENT_NET_DISCONN)
        {
            ESP_LOGW(TAG, "Modem Board Event: Network disconnected");
            led_indicator_stop(s_led_4g_handle, BLINK_CONNECTED);
        }
        else if (event_id == MODEM_EVENT_WIFI_STA_CONN)
        {
            ESP_LOGI(TAG, "Modem Board Event: Station connected");
            led_indicator_start(s_led_4g_handle, BLINK_CONNECTED);
        }
        else if (event_id == MODEM_EVENT_WIFI_STA_DISCONN)
        {
            ESP_LOGW(TAG, "Modem Board Event: All stations disconnected");
            led_indicator_stop(s_led_4g_handle, BLINK_CONNECTED);
        }
    }
}
esp_err_t SL_UsbModemPPPInit(void)
{
    /* Initialize modem board. Dial-up internet */
    modem_config_t modem_config = MODEM_DEFAULT_CONFIG();
/* Modem init flag, used to control init process */
#ifndef CONFIG_EXAMPLE_ENTER_PPP_DURING_INIT
    /* if Not enter ppp, modem will enter command mode after init */
    modem_config.flags |= MODEM_FLAGS_INIT_NOT_ENTER_PPP;
    /* if Not waiting for modem ready, just return after modem init */
    modem_config.flags |= MODEM_FLAGS_INIT_NOT_BLOCK;
#endif
    modem_config.handler = on_modem_event;
    return modem_board_init(&modem_config);
}
