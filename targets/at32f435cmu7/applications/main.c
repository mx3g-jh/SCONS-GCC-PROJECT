/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "drv_gpio.h"

/* defined the led pin: pc13 */
#define LED_PIN    GET_PIN(C, 13)

int main(void)
{
    rt_uint32_t speed = 50;
    /* set led pin mode to output */
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(speed);
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(speed);
    }
}
