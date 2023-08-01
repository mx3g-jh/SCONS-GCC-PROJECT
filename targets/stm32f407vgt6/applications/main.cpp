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
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define PTS_PASS        0
#define PTS_FAIL        1
#define PTS_UNRESOLVED  2
#define PTS_UNSUPPORTED 4
#define PTS_UNTESTED    5

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

#define PTS_ATTRIBUTE_NORETURN      __attribute__((noreturn))
#define PTS_ATTRIBUTE_UNUSED        __attribute__((unused))
#define PTS_ATTRIBUTE_UNUSED_RESULT __attribute__((warn_unused_result))

/* defined the LED0 pin: PD14 */
#define LED1_PIN    GET_PIN(E, 3)

static void* a_thread_func(void* parameter)
{
    sleep(10);

    /* Shouldn't reach here.  If we do, then the pthread_cancel()
     * function did not succeed. */
    fprintf(stderr, "Could not send cancel request correctly\n");

    return NULL;
}

static int posix_testcase(void)
{
    pthread_t new_th;
    int ret;

    ret = pthread_create(&new_th, NULL, a_thread_func, NULL);
    if (ret) {
        fprintf(stderr, "pthread_create(): %s\n", strerror(ret));
        return PTS_UNRESOLVED;
    }

    /* Try to cancel the newly created thread.  If an error is returned,
     * then the thread wasn't created successfully. */
    ret = pthread_cancel(new_th);
    if (ret) {
        printf("Test FAILED: A new thread wasn't created: %s\n",
               strerror(ret));
        return PTS_FAIL;
    }

    printf("Test PASSED\n");
    return PTS_PASS;
}

int main(void)
{
	/* set LED0 pin mode to output */
	rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
	posix_testcase();
	while (1) {
		rt_thread_mdelay(50);
		rt_pin_write(LED1_PIN, PIN_HIGH);
		rt_thread_mdelay(50);
		rt_pin_write(LED1_PIN, PIN_LOW);
	}

	return RT_EOK;
}