/*
 * app.c
 *
 *  Created on: Sep 27, 2026
 *      Author: laurentf
 */

#include "app.h"
#include <stdio.h>
#define STR_SIZE 32

void app_init(app_t *app, bsp_t *bsp) {
	app->last_tick = 0;
	app->led1_on = false;
	app->led2_on = false;
	app->led3_on = false;
	app->bsp = bsp;

}

void app_process(app_t *app) {
	bsp_t * bsp = app->bsp;

	uint32_t tick = bsp->get_tick_ms(bsp);
	if (tick - app->last_tick >= 250) {
		app->last_tick = tick;
		app->led1_on = !app->led1_on;
		bsp->led_set(bsp, 0, app->led1_on);

		int32_t delta = bsp->encoder_get_delta(bsp);
		static int32_t tot_rotation;
		tot_rotation += delta;

		if (bsp->enc_pressed(bsp))
			tot_rotation =0;

		char str[STR_SIZE];

		bsp->oled_clear(bsp);
		snprintf(str, STR_SIZE, "Delta = %ld", delta);
		bsp->oled_draw_string(bsp, 10, 10, str, true);
		snprintf(str, STR_SIZE, "Total = %ld", tot_rotation);
		bsp->oled_draw_string(bsp, 10, 20, str, true);
		bsp->oled_show(bsp);

	}
	if (bsp->sw1_pressed(bsp)) {
		app->led2_on = !app->led2_on;
		bsp->led_set(bsp, 1, app->led2_on);
	}
	if (bsp->sw2_pressed(bsp)) {
		app->led3_on = !app->led3_on;
		bsp->led_set(bsp, 2, app->led3_on);
	}
}
