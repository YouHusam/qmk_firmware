/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#include QMK_KEYBOARD_H
#include "pong.h"

uint16_t pong_enabled = false;

void start_pong(void) {
    pong_enabled = true;
    pong_init();
}

enum layers {
    _NUMPAD,
    _LAYER1,
    _LAYER2,
    _LAYER3,
};

enum custom_keycodes {
    PONG_START = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMPAD] = LAYOUT(
        LT(1, KC_NUM_LOCK),   LT(2, KC_MUTE),
        KC_KP_SLASH,   KC_KP_ASTERISK,   KC_KP_MINUS,   KC_KP_PLUS,
        KC_KP_7,   KC_KP_8,   KC_KP_9,   KC_KP_0,
        KC_KP_4,   KC_KP_5,   KC_KP_6,   KC_KP_ENTER,
        KC_KP_1,   KC_KP_2,   KC_KP_3,   KC_KP_DOT
    ),
    [_LAYER1] = LAYOUT(
      _______,   MO(_LAYER3),
      QK_BOOT,   PONG_START,   _______,   _______,
      _______,   _______,   _______,   _______,
      _______,   _______,   _______,   _______,
      QK_CLEAR_EEPROM,   _______,   _______,   _______
    ),
    [_LAYER2] = LAYOUT(
      MO(_LAYER3),   _______,
      _______,   _______,   _______,   _______,
      _______,   _______,   _______,   _______,
      _______,   _______,   _______,   _______,
      QK_CLEAR_EEPROM ,   _______,   _______,   _______
    ),
    [_LAYER3] = LAYOUT(
      _______,   _______,
      _______,   _______,   _______,   _______,
      _______,   _______,   _______,   _______,
      _______,   _______,   _______,   _______,
      QK_CLEAR_EEPROM ,   _______,   _______,   _______
    ),
};

// #ifdef ENCODER_MAP_ENABLE
// const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
//   [0] = { ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
//   [1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
//   [2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
//   [3] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
// };
// #endif

uint16_t last_key = 0;

bool encoder_update_user(uint8_t index, bool cw) {
    if (index == 0) { /* First encoder */
        if (pong_enabled) {
            if (cw) {
                pong_input(player_left, clockwise);
            } else {
                pong_input(player_left, anticlockwise);
            }
            return false;
        }
    } else if (index == 1) { /* Second encoder */
        if (pong_enabled) {
            if (cw) {
                pong_input(player_right, clockwise);
            } else {
                pong_input(player_right, anticlockwise);
            }
            return false;
        }
    }
    return true;
}


#ifdef OLED_ENABLE
#include <display/display.c>

bool oled_task_user(void) {
    if (pong_enabled) {
        pong_frame();
        return true;
    }
    oled_task_user_custom();
    char last_key_str[6];
    sprintf(last_key_str, "%u", last_key);
    oled_write_ln(last_key_str, false);
    return true;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    last_key = keycode;
    switch (keycode) {
        case PONG_START:
            if (record->event.pressed) {
                start_pong();
            }
            return false; // Skip all further processing of this key
            break;
        case LT(1, KC_NUM_LOCK):
            if (record->event.pressed) {
                if (pong_enabled) {
                    pong_press(player_left);
                    return false;
                } else {
                    return true;
                }
            }
            break;
        case LT(2, KC_MUTE):
            if (record->event.pressed) {
                if (pong_enabled) {
                    pong_press(player_right);
                    return false;
                } else {
                    return true;
                }
            }
            break;
        default:
            if (pong_enabled) {
                pong_enabled = false;
                oled_clear();
                return false;
            }
    }
    return true;
}
