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
 * Re-ARM with RAMPS v1.6+ pin assignments
 *
 * Applies to the following boards:
 *
 *  RAMPS_14_EEF (Hotend0, Hotend1, Fan)
 */

// Numbers in parentheses () are the corresponding mega2560 pin numbers

#ifndef TARGET_LPC1768
  #error "Oops! Make sure you have the LPC1768 environment selected in your IDE."
#endif

#define RAMPS_D8_PIN       P1_20   // D11 Servo pin 11 to drive the SSR

//
// Steppers
//
#ifndef X_CS_PIN
  #define X_CS_PIN         P1_01   // ETH
#endif

#ifndef Y_CS_PIN
  #define Y_CS_PIN         P1_04   // ETH
#endif

#ifndef Z_CS_PIN
  #define Z_CS_PIN         P1_10   // ETH
#endif

#ifndef E0_CS_PIN
  #define E0_CS_PIN        P1_14   // ETH
#endif

#ifndef E1_CS_PIN
  #define E1_CS_PIN        -1
#endif

#include "pins_RAMPS_RE_ARM.h"
//
// Servos
//

//
// Limit Switches
//

//
// Software SPI pins for TMC2130 stepper drivers
//
#if ENABLED(TMC_USE_SW_SPI)
   #undef  TMC_SW_MOSI
   #undef  TMC_SW_MISO
   #undef  TMC_SW_SCK

   #define TMC_SW_MOSI      P1_00   // ETH   
   #define TMC_SW_MISO      P1_08   // ETH
   #define TMC_SW_SCK       P1_09   // ETH
#endif

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
//  3.3V max when defined as an analog input
//
#define TEMP_0_PIN          P0_27   // (A3)  Analog Input PT100
#define TEMP_1_PIN          P0_28   // (A4)  Analog Input PT100
#define TEMP_BED_PIN        1       // A1 (T1) - (68) - TEMP_BED_PIN - (A14) Analog Input

//
// Heaters
//
#ifndef MOSFET_D_PIN
  #define MOSFET_D_PIN     -1
#endif
#ifndef RAMPS_D8_PIN
  #define RAMPS_D8_PIN     P1_20   // D11 Servo pin 11 to drive the SSR
#endif
#ifndef RAMPS_D9_PIN
  #define RAMPS_D9_PIN     P2_04   // (9)
#endif
#ifndef RAMPS_D10_PIN
  #define RAMPS_D10_PIN    P2_05   // (10)
#endif
#define HEATER_0_PIN       RAMPS_D10_PIN
#define HEATER_1_PIN       RAMPS_D9_PIN
#define HEATER_BED_PIN     RAMPS_D8_PIN

//
// Fans
// cooling parts fans
#define FAN_PIN            8   // D8

/* Fan Expansion board pins
* * Hotends Fans
**use same pin
**********************************/
#define E0_AUTO_FAN_PIN P1_18   // (4) IO pin. Buffer needed - D6 Servo pin 6 for Hotend Fan0
#define E1_AUTO_FAN_PIN P1_18   // (4) IO pin. Buffer needed - D5 Servo pin 5 for Hotend Fan1

//
// Misc. Functions
//
#ifdef FIL_RUNOUT_PIN
    #undef FIL_RUNOUT_PIN
    #define FIL_RUNOUT_PIN -1
#endif

//
// SD Support
//
#ifdef USB_SD_DISABLED
    #undef USB_SD_DISABLED
#endif
#ifdef USB_SD_ONBOARD
    #undef USB_SD_ONBOARD
#endif
//#define USB_SD_DISABLED
#define USB_SD_ONBOARD        // Provide the onboard SD card to the host as a USB mass storage device

#ifdef LPC_SD_LCD
    #undef LPC_SD_LCD
#endif
#ifdef LPC_SD_ONBOARD
    #undef LPC_SD_ONBOARD
#endif
//#define LPC_SD_LCD          // Marlin uses the SD drive attached to the LCD
#define LPC_SD_ONBOARD        // Marlin uses the SD drive on the control board

#if ENABLED(LPC_SD_LCD)
    #define SCK_PIN          P0_15
    #define MISO_PIN         P0_17
    #define MOSI_PIN         P0_18
    #define SS_PIN           P1_23   // Chip select for SD card used by Marlin
    #define ONBOARD_SD_CS    P0_06   // Chip select for "System" SD card

#elif ENABLED(LPC_SD_ONBOARD)
    #if ENABLED(USB_SD_ONBOARD)
        // When sharing the SD card with a PC we want the menu options to
        // mount/unmount the card and refresh it. So we disable card detect.
        #define SHARED_SD_CARD
        #undef SD_DETECT_PIN // there is also no detect pin for the onboard card
    #endif

    #define SCK_PIN          P0_07
    #define MISO_PIN         P0_08
    #define MOSI_PIN         P0_09
    #define SS_PIN           P0_06   // Chip select for SD card used by Marlin
    #define ONBOARD_SD_CS    P0_06   // Chip select for "System" SD card
#endif


/**
 *  Fast PWMs
 *
 *  The LPC1768's hardware PWM controller has 6 channels. Each channel
 *  can be setup to either control a dedicated pin directly or to generate
 *  an interrupt. The direct method's duty cycle is accurate to within a
 *  a microsecond. The interrupt method's average duty cycle has the
 *  the same accuracy but the individual cycles can vary because of higher
 *  priority interrupts.
 *
 *  All Fast PWMs have a 50Hz rate.
 *
 *  The following pins/signals use the direct method. All other pins use the
 *  the interrupt method. Note that SERVO2_PIN and RAMPS_D8_PIN use the
 *  interrupt method.
 *
 *     P1_20 (11)   SERVO0_PIN
 *     P1_21 ( 6)   SERVO1_PIN       J5-1
 *     P0_18 ( 4)   SERVO3_PIN       5V output
 *    *P2_04 ( 9)   RAMPS_D9_PIN
 *    *P2_05 (10)   RAMPS_D10_PIN
 *
 *    * - If used as a heater driver then a Fast PWM is NOT assigned. If used as
 *        a fan driver then enabling FAST_PWM_FAN assigns a Fast PWM to it.
 */

 /**
  * Special pins
  *   P1_30  (37) (NOT 5V tolerant)
  *   P1_31  (49) (NOT 5V tolerant)
  *   P0_27  (57) (Open collector)
  *   P0_28  (58) (Open collector)
  */

/**
 *  The following mega2560 pins are NOT available in a Re-ARM system:
 *
 *  7, 17, 22, 23, 25, 27, 29, 32, 39, 40, 42, 43, 44, 45, 47, 64, 65, 66
 */
