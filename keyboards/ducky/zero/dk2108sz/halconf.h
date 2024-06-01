#define HAL_USE_PWM                 TRUE
#define HAL_USE_PAL                 TRUE
#define NUC123_PWM_USE_PWM1         TRUE
#define PAL_MODE_ALTERNATE
#define BACKLIGHT_PWM_DRIVER    PWMD1
#define BACKLIGHT_PWM_CHANNEL 4
#define BACKLIGHT_PAL_MODE PAL_MODE_NUC123_ALTERNATE_OUTPUT
#define BACKLIGHT_PIN A13
// #define BACKLIGHT_PIN D0
#define BACKLIGHT_DRIVER pwm
// #define BACKLIGHT_PINS { D0 }

// #define BACKLIGHT_ON_STATE 0


#include_next <halconf.h>
