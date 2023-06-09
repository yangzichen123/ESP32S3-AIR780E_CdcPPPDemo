// Copyright 2015-2019 Espressif Systems (Shanghai) PTE LTD
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

#include "hal/i2c_hal.h"

void i2c_hal_master_handle_tx_event(i2c_hal_context_t *hal, i2c_intr_event_t *event)
{
    if (i2c_ll_get_intsts_mask(hal->dev) != 0) {
        // If intr status is 0, no need to handle it.
        i2c_ll_master_get_event(hal->dev, event);
        if ((*event < I2C_INTR_EVENT_END_DET) ||
            (*event == I2C_INTR_EVENT_TRANS_DONE)) {
            i2c_ll_master_disable_tx_it(hal->dev);
            i2c_ll_master_clr_tx_it(hal->dev);
        } else if (*event == I2C_INTR_EVENT_END_DET) {
            i2c_ll_master_clr_tx_it(hal->dev);
        }
    }
}

void i2c_hal_master_handle_rx_event(i2c_hal_context_t *hal, i2c_intr_event_t *event)
{
    if (i2c_ll_get_intsts_mask(hal->dev) != 0) {
        i2c_ll_master_get_event(hal->dev, event);
        if ((*event < I2C_INTR_EVENT_END_DET) ||
            (*event == I2C_INTR_EVENT_TRANS_DONE)) {
            i2c_ll_master_disable_rx_it(hal->dev);
            i2c_ll_master_clr_rx_it(hal->dev);
        } else if (*event == I2C_INTR_EVENT_END_DET) {
            i2c_ll_master_clr_rx_it(hal->dev);
        }
    }
}

void i2c_hal_slave_handle_event(i2c_hal_context_t *hal, i2c_intr_event_t *event)
{
    i2c_ll_slave_get_event(hal->dev, event);
}

void i2c_hal_disable_slave_tx_it(i2c_hal_context_t *hal)
{
    i2c_ll_slave_disable_tx_it(hal->dev);
}

void i2c_hal_update_config(i2c_hal_context_t *hal)
{
    i2c_ll_update(hal->dev);
}

void i2c_hal_get_rxfifo_cnt(i2c_hal_context_t *hal, uint32_t *len)
{
    *len =  i2c_ll_get_rxfifo_cnt(hal->dev);
}

void i2c_hal_get_txfifo_cnt(i2c_hal_context_t *hal, uint32_t *len)
{
    *len =  i2c_ll_get_txfifo_len(hal->dev);
}

void i2c_hal_get_intsts_mask(i2c_hal_context_t *hal, uint32_t *mask)
{
    *mask = i2c_ll_get_intsts_mask(hal->dev);
}
