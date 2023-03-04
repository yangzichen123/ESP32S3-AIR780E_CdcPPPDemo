// Copyright 2020 Espressif Systems (Shanghai) Co. Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _INTERFACE_DRV_DEF_H_
#define _INTERFACE_DRV_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0))
#define gpio_pad_select_gpio esp_rom_gpio_pad_select_gpio
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif

/**< Define the function of interface instance */
#define LCD_WRITE_COMMAND(data, length) g_lcd_handle.interface_drv->write_command(g_lcd_handle.interface_drv, (data), (length))
#define LCD_WRITE(data, length) g_lcd_handle.interface_drv->write(g_lcd_handle.interface_drv, (data), (length))
#define LCD_READ(data, length)  g_lcd_handle.interface_drv->read(g_lcd_handle.interface_drv, (data), (length))
#define LCD_IFACE_ACQUIRE()     g_lcd_handle.interface_drv->bus_acquire(g_lcd_handle.interface_drv)
#define LCD_IFACE_RELEASE()     g_lcd_handle.interface_drv->bus_release(g_lcd_handle.interface_drv)


static inline esp_err_t LCD_WRITE_CMD(uint8_t cmd)
{
    return LCD_WRITE_COMMAND((uint8_t*)&cmd, 1);
}

static inline esp_err_t LCD_WRITE_CMD_16B(uint16_t cmd)
{
    return LCD_WRITE_COMMAND((uint8_t*)&cmd, 2);
}

static inline esp_err_t LCD_WRITE_DATA(uint8_t data)
{
    return LCD_WRITE((uint8_t*)&data, 1);
}

static inline esp_err_t LCD_WRITE_DATA_16B(uint16_t data)
{
    return LCD_WRITE((uint8_t*)&data, 2);
}

static inline esp_err_t LCD_WRITE_REG(uint8_t cmd, uint8_t data)
{
    esp_err_t ret;
    ret = LCD_WRITE_CMD(cmd);
    ret |= LCD_WRITE_DATA(data);
    if (ESP_OK != ret) {
        return ESP_FAIL;
    }

    return ESP_OK;
}

static inline esp_err_t LCD_WRITE_REG_16B(uint16_t cmd, uint16_t data)
{
    esp_err_t ret;
    ret = LCD_WRITE_CMD_16B(cmd);
    ret |= LCD_WRITE_DATA_16B(data);
    if (ESP_OK != ret) {
        return ESP_FAIL;
    }

    return ESP_OK;
}

#ifdef __cplusplus
}
#endif

#endif
