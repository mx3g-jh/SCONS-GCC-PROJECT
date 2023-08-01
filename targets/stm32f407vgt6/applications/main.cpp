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

#include "slog.h"
#include "uorb/publication.h"
#include "uorb/publication_multi.h"
#include "uorb/subscription.h"
#include "uorb/subscription_interval.h"
#include "example_string.h"

/* defined the LED0 pin: PD14 */
#define LED1_PIN    GET_PIN(E, 3)

void *thread_publisher(void *arg)
{
	uorb::PublicationData<uorb::msg::example_string> pub_example_string;

	for (int i = 0; i < 1000; i++) {
		snprintf((char *)pub_example_string.get().string,
			 example_string_s::STRING_LENGTH, "%d: %s", i,
			 "pub test.");

		if (!pub_example_string.Publish()) {
			LOGGER_ERROR("Publish error");
		}

		usleep(1 * 1000 * 1000);
	}

	LOGGER_WARN("Publication over.");

	return nullptr;
}

void *thread_subscriber(void *unused)
{
	uorb::SubscriptionData<uorb::msg::example_string> sub_example_string;

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

	int timeout_ms = 2000;

	struct orb_pollfd pollfds[] = {
		{.fd = sub_example_string.handle(), .events = POLLIN}
	};

	while (true) {
		if (0 < orb_poll(pollfds, ARRAY_SIZE(pollfds), timeout_ms)) {
			if (sub_example_string.Update()) {
				LOGGER_INFO("Receive msg: \"%s\"", sub_example_string.get().string);
			}

			usleep(1 * 1000 * 1000);
		}

		//  else {
		//   LOGGER_WARN("Got no data within %d milliseconds", 2000);
		//   break;
		// }
	}

	LOGGER_WARN("subscription over");
	return nullptr;
}

int main(void)
{
//   LOGGER_INFO("uORB version: %s", orb_version());

	// One publishing thread, three subscription threads
	pthread_t pthread_id;
	pthread_create(&pthread_id, nullptr, thread_publisher, nullptr);
	pthread_create(&pthread_id, nullptr, thread_subscriber, nullptr);

	// Wait for all threads to finish
//   pthread_exit(nullptr);

	return RT_EOK;
}