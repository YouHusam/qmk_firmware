#pragma once
#define HAL_USE_I2C TRUE
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP26
#define I2C1_SCL_PIN GP27

#define OLED_DISPLAY_128X64
#define OLED_DISPLAY_WIDTH 128
#define OLED_DISPLAY_HEIGHT 64

#define OLED_FONT_H "keyboards/2040pad/glcdfont.c"
#define OLED_FONT_START 0
#define OLED_FONT_END 223
