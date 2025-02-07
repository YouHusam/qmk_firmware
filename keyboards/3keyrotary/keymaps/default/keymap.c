#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
      LT(1, KC_MUTE), KC_MEDIA_PREV_TRACK ,   KC_MEDIA_PLAY_PAUSE,   KC_MEDIA_NEXT_TRACK
    ),
    [1] = LAYOUT(
        _______,   MO(2),   _______,   QK_BOOT
    ),
    [2] = LAYOUT(
        _______,   _______,   MO(3),   _______
    ),
    [3] = LAYOUT(
        _______,   _______,   _______, QK_CLEAR_EEPROM
    ),
};


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(_______, _______) },
    [2] = { ENCODER_CCW_CW(_______, _______) },
    [3] = { ENCODER_CCW_CW(_______, _______) },
};
#endif
