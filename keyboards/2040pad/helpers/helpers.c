#pragma once
#include QMK_KEYBOARD_H

enum custom_keycodes {
    LENC = SAFE_RANGE,
    RENC
};

enum encoder_modes {
    SCROLL,
    MOUSE,
    TEXT,
    APPSW,
    MEDIA,
    PONG
};

uint8_t enc_mode = SCROLL;
