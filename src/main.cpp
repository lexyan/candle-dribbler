/*
 * candle-dribbler - ESP32 Zigbee light controller
 * Copyright 2023  Simon Arlott
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <esp_err.h>
#include <nvs_flash.h>

#include "nutt/device.h"
#include "nutt/light.h"

using namespace nutt;

#ifndef NUTT_MAX_LIGHTS
static constexpr const size_t MAX_LIGHTS = 4;
#else
static constexpr const size_t MAX_LIGHTS = NUTT_MAX_LIGHTS;
#endif

extern "C" void app_main() {
	esp_err_t err = nvs_flash_init();
	if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		err = nvs_flash_init();
	}
	ESP_ERROR_CHECK(err);

	auto &device = *new Device{};

	if (MAX_LIGHTS >= 1) (new Light{1, GPIO_NUM_3,  GPIO_NUM_18, true})->attach(device);
	if (MAX_LIGHTS >= 2) (new Light{2, GPIO_NUM_2,  GPIO_NUM_19, true})->attach(device);
	if (MAX_LIGHTS >= 3) (new Light{3, GPIO_NUM_11, GPIO_NUM_20, true})->attach(device);
	if (MAX_LIGHTS >= 4) (new Light{4, GPIO_NUM_10, GPIO_NUM_21, true})->attach(device);
	if (MAX_LIGHTS >= 5) (new Light{5, GPIO_NUM_1,  GPIO_NUM_22, true})->attach(device);
	if (MAX_LIGHTS >= 6) (new Light{6, GPIO_NUM_0,  GPIO_NUM_23, true})->attach(device);

	device.start();
}
