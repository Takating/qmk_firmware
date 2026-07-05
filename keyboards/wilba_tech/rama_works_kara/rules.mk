ifeq ($(strip $(KEYMAP)), ten)
    RGB_BACKLIGHT_ENABLE ?= no
else
    RGB_BACKLIGHT_ENABLE ?= yes
endif

ifeq ($(strip $(RGB_BACKLIGHT_ENABLE)), yes)
    # Do not put the microcontroller into power saving mode
    # when we get USB suspend event. We want it to keep updating
    # backlight effects.
    NO_SUSPEND_POWER_DOWN = yes

    CIE1931_CURVE = yes
    I2C_DRIVER_REQUIRED = yes

    # project specific files
    SRC += keyboards/wilba_tech/wt_rgb_backlight.c \
           quantum/color.c \
           drivers/led/issi/is31fl3731.c
endif

SRC += keyboards/wilba_tech/wt_main.c
