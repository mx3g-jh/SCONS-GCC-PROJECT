/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     misonyo   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED0 pin: PD14 */
#define LED1_PIN    GET_PIN(E, 3)

int main(void)
{
    /* set LED0 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_thread_mdelay(100);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(100);
        rt_pin_write(LED1_PIN, PIN_LOW);
    }

    return RT_EOK;
}
