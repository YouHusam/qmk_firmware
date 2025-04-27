#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
      LT(1, KC_MUTE), KC_MEDIA_PREV_TRACK ,   KC_MEDIA_PLAY_PAUSE,   KC_MEDIA_NEXT_TRACK
    ),
    [1] = LAYOUT(
        TO(0),   TG(2),   TG(3),   TG(4)
    ),
    [2] = LAYOUT(
        TO(0),   TG(5),   TG(6),   TG(7)
    ),
    [3] = LAYOUT(
        TO(0),   MS_WHLR,   MS_WHLL,   _______
    ),
    [4] = LAYOUT(
      TO(0), _______ ,   _______,   _______
    ),
    [5] = LAYOUT(
        TO(0),   _______,   _______,   _______
    ),
    [6] = LAYOUT(
        TO(0),   _______,   _______,   _______
    ),
    [7] = LAYOUT(
        TO(0),   QK_CLEAR_EEPROM,   _______, QK_BOOT
    ),
};


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(_______, _______) },
    [2] = { ENCODER_CCW_CW(_______, _______) },
    [3] = { ENCODER_CCW_CW(MS_WHLU, KC_WH_D) },
    [4] = { ENCODER_CCW_CW(_______, _______) },
    [5] = { ENCODER_CCW_CW(_______, _______) },
    [6] = { ENCODER_CCW_CW(_______, _______) },
    [7] = { ENCODER_CCW_CW(_______, _______) },
};
#endif

bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case 0:
            rgb_matrix_set_color(3, 128, 128, 128);
            break;
        case 1:
            rgb_matrix_set_color(3, 0, 0, 128);
            break;
        case 2:
            rgb_matrix_set_color(3, 0, 128, 0);
            break;
        case 3:
            rgb_matrix_set_color(3, 128, 83, 0);
            break;
        case 4:
            rgb_matrix_set_color(3, 128, 128, 0);
            break;
        case 5:
            rgb_matrix_set_color(3, 128, 0, 128);
            break;
        case 6:
            rgb_matrix_set_color(3, 0, 128, 128);
            break;
        case 7:
            rgb_matrix_set_color(3, 128, 0, 0);
            rgb_matrix_set_color(2, 128, 0, 0);
            rgb_matrix_set_color(0, 0, 128, 0);
            break;
        default:
            break;
    }
    return true;
}
