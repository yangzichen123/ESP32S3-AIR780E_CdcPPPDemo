#ifndef __USER_USBPPP_H__
#define __USER_USBPPP_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "led_indicator.h"
#include "led_indicator_blink_default.h"

    extern led_indicator_handle_t s_led_system_handle;
    extern led_indicator_handle_t s_led_wifi_handle;
    extern led_indicator_handle_t s_led_4g_handle;
    esp_err_t SL_UsbModemPPPInit(void);
    void SL_LedIndicatorInit(void);

#ifdef __cplusplus
}
#endif

#endif