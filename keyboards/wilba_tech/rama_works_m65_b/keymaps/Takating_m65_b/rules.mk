# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
NO_SUSPEND_POWER_DOWN = yes

CIE1931_CURVE = yes
I2C_DRIVER_REQUIRED = yes

RGB_MATRIX_ENABLE = no
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes