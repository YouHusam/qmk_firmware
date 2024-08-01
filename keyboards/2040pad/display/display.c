#include QMK_KEYBOARD_H

#include <display/logo.c>

uint32_t timer = 0;
bool logo_cleared = false;


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
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Numpad  "), false);
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


bool oled_task_user(void) {
    if (timer_elapsed(timer) < 1000) {
        return false;
    }

    if(!logo_cleared) {
        oled_clear();
        oled_render_dirty(true);
        oled_clear();
        logo_cleared = true;
    }

    render_lock_status();
    render_layer();
    oled_set_cursor(0, 2);

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
