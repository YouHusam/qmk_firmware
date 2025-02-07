#include QMK_KEYBOARD_H

#include "logo.c"
#include "helpers.c"
#include "calculator.c"

uint32_t timer        = 0;
bool     logo_cleared = false;

void render_lock_status(void) {
    led_t led_state = host_keyboard_led_state();

    oled_set_cursor(0, 0);
    oled_write_P(PSTR("Num:"), false);
    oled_write_P(PSTR(led_state.num_lock ? " On " : " Off"), led_state.num_lock);

    oled_set_cursor(oled_max_chars() - 9, 0);
    oled_write_P(PSTR("Caps:"), false);
    oled_write_P(PSTR(led_state.caps_lock ? " On " : " Off"), led_state.caps_lock);
}

void render_layer(void) {
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("Layer:"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR(" Numpad  "), false);
            break;
        case 1:
            oled_write_P(PSTR(" Layer 1"), true);
            break;
        case 2:
            oled_write_P(PSTR(" Layer 2"), true);
            break;
        case 3:
            oled_write_P(PSTR(" Layer 3"), true);
            break;
    }
}

void render_encoder_mode(void) {
    oled_set_cursor(0, 2);
    oled_write_P(PSTR("Enc Mode: "), false);
    oled_write_P(PSTR(encoder_mode_names[enc_mode]), false);
}

void render_normal_mode(void) {
    render_lock_status();
    render_layer();
    render_encoder_mode();
}

void render_encoder_select_mode(void) {
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("Encoder:"), false);
    oled_set_cursor(oled_max_chars() - 9, 0);
    oled_write_P(PSTR("Function:"), false);

    for (int i = 0; i < ENCODER_MODES_COUNT; i++) {
        oled_set_cursor(0, 2 + i);
        oled_write_P(PSTR(encoder_mode_names[i]), i == enc_mode);
    }

    for (int i = 0; i < ENCODER_SELECT; i++) {
        uint8_t col = oled_max_chars() - strlen(display_mode_names[i]);
        oled_set_cursor(col, 2 + i);
        oled_write_P(PSTR(display_mode_names[i]), i == display_mode_selector);
    }
}

bool oled_task_user(void) {
    static uint8_t previous_display_mode = NORMAL;

    if (timer_elapsed(timer) < 1000) {
        return false;
    }

    if (!logo_cleared) {
        oled_clear();
        logo_cleared = true;
    }

    if (previous_display_mode != display_mode) {
        oled_clear();
        previous_display_mode = display_mode;
    }

    switch (display_mode) {
        case NORMAL:
            render_normal_mode();
            break;
        case ENCODER_SELECT:
            render_encoder_select_mode();
            break;
        case CALCULATOR:
            render_calc();
            break;
    }

    return true;
}

void keyboard_post_init_user(void) {
    render_qmk_logo();
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 7; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);

    return true;
}
