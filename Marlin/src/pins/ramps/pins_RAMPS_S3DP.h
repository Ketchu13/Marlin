/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
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
 *
 */

/**
 * Arduino Mega with RAMPS v1.4 (or v1.3) pin assignments
 *
 * Applies to the following boards:
 *
 *  RAMPS_14_EEF (Hotend0, Hotend1, Fan)
 */


#define RAMPS_D8_PIN       11   // D11 Servo pin 11 to drive the SSR

#include "pins_RAMPS.h"

#undef TEMP_0_PIN
#undef TEMP_1_PIN
#undef TEMP_BED_PIN
#undef HEATER_0_PIN
#undef HEATER_1_PIN
#undef HEATER_BED_PIN

#undef FAN_PIN

#undef E0_AUTO_FAN_PIN
#undef E1_AUTO_FAN_PIN


//
// Temperature Sensors
//
#define TEMP_0_PIN         14    // (A3)  Analog Input PT100
#define TEMP_1_PIN         4    // (A4)  Analog Input PT100
#define TEMP_BED_PIN       15   // (A14) Analog Input

//
// Heaters
//
#define HEATER_0_PIN       RAMPS_D10_PIN
#define HEATER_1_PIN       RAMPS_D9_PIN
#define HEATER_BED_PIN     RAMPS_D8_PIN

//
//*********Fans***********
// cooling parts fans
#define FAN_PIN            8   // D8
/* Fan Expansion board pins
* * Hotends Fans
**********************************/
#define E0_AUTO_FAN_PIN 6 // D6 Servo pin 6 for Hotend Fan0
#define E1_AUTO_FAN_PIN 5 // D5 Servo pin 5 for Hotend Fan1