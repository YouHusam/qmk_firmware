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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LT(1, LENC),   LT(2, RENC),
        KC_KP_SLASH,   KC_KP_ASTERISK,   KC_KP_MINUS,   KC_KP_PLUS,
        KC_KP_7,   KC_KP_8,   KC_KP_9,   KC_KP_0,
        KC_KP_4,   KC_KP_5,   KC_KP_6,   KC_KP_ENTER,
        KC_KP_1,   KC_KP_2,   KC_KP_3,   KC_KP_DOT
    ),
    [1] = LAYOUT(
        LT(3, LENC),   LT(3, RENC),
        QK_BOOT,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______
    ),
    [2] = LAYOUT(
        LT(3, LENC),   LT(3, RENC),
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______
    ),
    [3] = LAYOUT(
        LENC,   RENC,
        _______,   _______,   _______,   _______,
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
#include <helpers/display.c>
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, LENC):
            if (record->event.pressed && record->tap.count == 1) {
                register_code(KC_NUM_LOCK);
            } else if (!record->event.pressed && record->tap.count == 1) {
                unregister_code(KC_NUM_LOCK);
            }
            break;
        case LT(2, RENC):
            if (record->event.pressed && record->tap.count == 1) {
                register_code(KC_MUTE);
            } else if (!record->event.pressed && record->tap.count == 1) {
                unregister_code(KC_MUTE);
            }
            break;
    }
    return true;
}
