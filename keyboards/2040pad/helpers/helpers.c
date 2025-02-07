#pragma once
#include QMK_KEYBOARD_H

enum custom_keycodes {
    LENC = SAFE_RANGE,
    RENC,
    MODE_SELECT,
};

enum encoder_modes {
    DEFAULT,
    SCROLL,
    MOUSE,
    TEXT,
    APPSW,
    MEDIA,
    // PONG,
    ENCODER_MODES_COUNT
};

const char* encoder_mode_names[] = {
    "DEFAULT",
    "SCROLL",
    "MOUSE",
    "TEXT",
    "APPSW",
    "MEDIA",
    // "PONG"
};

uint8_t enc_mode = DEFAULT;

enum display_modes {
    NORMAL,
    CALCULATOR,
    ENCODER_SELECT
};

const char* display_mode_names[] = {
    "NUMPAD",
    "CALCULATOR"
};

uint8_t display_mode = NORMAL;
uint8_t display_mode_selector = NORMAL;
