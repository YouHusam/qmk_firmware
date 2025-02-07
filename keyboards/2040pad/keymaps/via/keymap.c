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

#include <helpers/helpers.c>
#include <helpers/encoders.c>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LT(1, LENC),   LT(2, RENC),
        KC_KP_SLASH,   KC_KP_ASTERISK,   KC_KP_PLUS,   KC_KP_MINUS,
        KC_KP_7,   KC_KP_8,   KC_KP_9,   KC_KP_0,
        KC_KP_4,   KC_KP_5,   KC_KP_6,   KC_KP_ENTER,
        KC_KP_1,   KC_KP_2,   KC_KP_3,   KC_KP_DOT
    ),
    [1] = LAYOUT(
        LT(3, LENC),   MODE_SELECT,
        QK_BOOT,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______
    ),
    [2] = LAYOUT(
        MODE_SELECT,   LT(3, RENC),
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        QK_CLEAR_EEPROM,   _______,   _______,   _______
    ),
    [3] = LAYOUT(
        LENC,   RENC,
        MODE_SELECT,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        QK_CLEAR_EEPROM ,   _______,   _______,   _______
    ),
};


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [3] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif

#ifdef OLED_ENABLE
#    include <helpers/display.c>
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, LENC):
        case LENC:
            if (record->event.pressed && record->tap.count) {
                if (display_mode == ENCODER_SELECT) {
                    display_mode = NORMAL;
                    return false;
                }
                if (display_mode == CALCULATOR) {
                    process_record_user_calc(keycode, record);
                    return false;
                    break;
                }
                left_encoder_pressed(record->event.pressed);
                return false;
            } else if (!record->event.pressed && record->tap.count) {
                left_encoder_pressed(record->event.pressed);
                return false;
            }
            break;
        case LT(2, RENC):
        case RENC:
            if (display_mode == CALCULATOR) {
                process_record_user_calc(keycode, record);
                return false;
                break;
            }
            if (record->event.pressed && record->tap.count) {
                if (display_mode == ENCODER_SELECT) {
                    display_mode = display_mode_selector;
                    return false;
                }
                right_encoder_pressed(record->event.pressed);
                return false;
            } else if (!record->event.pressed && record->tap.count) {
                right_encoder_pressed(record->event.pressed);
                return false;
            }
            break;
        case MODE_SELECT:
            if (record->event.pressed) {
                display_mode_selector = display_mode;
                display_mode          = ENCODER_SELECT;
            }
            return false;
            break;
        default:
            if (record->event.pressed) {
                if (display_mode == CALCULATOR) {
                    process_record_user_calc(keycode, record);
                    return false;
                }
                return (display_mode != ENCODER_SELECT) || (display_mode != CALCULATOR);
            }
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            left_encoder_cw();
        } else {
            left_encoder_ccw();
        }
    } else if (index == 1) {
        if (clockwise) {
            right_encoder_cw();
        } else {
            right_encoder_ccw();
        }
    }
    return false;
}
#endif
