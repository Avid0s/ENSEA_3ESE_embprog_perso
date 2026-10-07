/*
 * menu.c
 *
 *  Created on: 1 Oct 2026
 *      Author: gjvid
 */

#ifndef

typedef struct {
	const char *label;
	bool *led_on;
	uint8_t led_index;
} menu_entry_t;

void menu_entry_toggle(menu_entry_t *e, const bsp_t *bsp) {
	*e->led_on = !*e->led_on;
	bsp->led_set(bsp->ctx, e->led_index, *e->led_on);
}
