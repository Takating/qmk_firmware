#include QMK_KEYBOARD_H
#include "analog.h"
#include "qmk_midi.h"

uint8_t midi2vol = 0x3E;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _MEDIA,
    _NAV,
    _VOLUME,
    _FNT,
    _SCALE,
    _TOGGLE
};


// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum { // add any other tap dance keys to this enum
    TD_MU_TG_CL,
    TD_F_F5,
};

/* Declare the functions to be used with your tap dance key(s)
TD_MU_TG_CL is Single-Tap = MUTE, Hold = MO(_TOGGLE), Dobble-Tap = ALT+F4
*/

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t mul_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(tap_dance_state_t *state, void *user_data) {
    mul_tap_state.state = cur_dance(state);
    switch (mul_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MUTE);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_TOGGLE);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LALT(KC_F4));// tap_code16 allow you to combine a modifier with a keycode
            break;
        default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (mul_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_TOGGLE);
    }
    mul_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [TD_MU_TG_CL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset),
    [TD_F_F5] = ACTION_TAP_DANCE_DOUBLE(KC_F, KC_F5),
};


// Combos setting by Takating 20240804-v1.1 (Put below "enum layer_names")
const uint16_t PROGMEM combo0[] = {LSFT(KC_TAB), KC_TAB, COMBO_END};
const uint16_t PROGMEM combo1[] = {KC_LEFT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM combo2[] = {KC_RGHT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM combo3[] = {KC_UP, KC_DOWN, COMBO_END};
const uint16_t PROGMEM combo4[] = {KC_LEFT, KC_RGHT, COMBO_END};
const uint16_t PROGMEM combo5[] = {LSFT(KC_TAB), KC_LEFT, COMBO_END};
const uint16_t PROGMEM combo6[] = {KC_TAB, KC_RGHT, COMBO_END};
const uint16_t PROGMEM combo7[] = {LSFT(KC_TAB), KC_UP, COMBO_END};
const uint16_t PROGMEM combo8[] = {KC_TAB, KC_UP, COMBO_END};
const uint16_t PROGMEM combo9[] = {KC_LEFT, KC_DOWN, KC_RGHT, COMBO_END};
const uint16_t PROGMEM combo10[] = {TD(TD_F_F5), LT(_SCALE, KC_MRWD), COMBO_END};
const uint16_t PROGMEM combo11[] = {KC_MPRV, KC_MNXT, COMBO_END};
const uint16_t PROGMEM combo12[] = {KC_C, LT(_VOLUME, KC_MFFD), COMBO_END};
const uint16_t PROGMEM combo13[] = {TD(TD_F_F5), KC_MPRV, COMBO_END};
const uint16_t PROGMEM combo14[] = {KC_C, KC_MPRV, COMBO_END};
const uint16_t PROGMEM combo15[] = {LT(_SCALE, KC_MRWD), KC_MNXT, COMBO_END};
const uint16_t PROGMEM combo16[] = {LT(_VOLUME, KC_MFFD), KC_MNXT, COMBO_END};

combo_t key_combos[] = {
  COMBO(combo0, KC_DEL),
  COMBO(combo1, LCTL(KC_PGUP)),
  COMBO(combo2, LCTL(KC_PGDN)),
  COMBO(combo3, LCTL(KC_T)),
  COMBO(combo4, LCTL(KC_W)),
  COMBO(combo5, MEH(KC_TAB)),
  COMBO(combo6, LCA(KC_TAB)),
  COMBO(combo7, RCS(KC_PGUP)),
  COMBO(combo8, RCS(KC_PGDN)),
  COMBO(combo9, LGUI(KC_TAB)),
  COMBO(combo10, KC_F11),
  COMBO(combo11, KC_F9),
  COMBO(combo12, KC_MPLY),
  COMBO(combo13, LALT(KC_LEFT)),
  COMBO(combo14, LALT(KC_RGHT)),
  COMBO(combo15, RSG(KC_LEFT)),
  COMBO(combo16, RSG(KC_RGHT)),
};


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { // In order to add more volume controls, add here a custom keycode
    DEFAULT= SAFE_RANGE,APP1,APP2,APP3,APP4,APP5
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_MEDIA] = LAYOUT(
        TD(TD_MU_TG_CL),
        TD(TD_F_F5), KC_MPRV, KC_C,
        LT(_SCALE, KC_MRWD), KC_MNXT, LT(_VOLUME, KC_MFFD), LT(_NAV, KC_SPC)
    ),
    [_NAV] = LAYOUT( 
        LT(_TOGGLE, KC_ESC),
        LSFT(KC_TAB), KC_UP, KC_TAB,
        KC_LEFT, KC_DOWN, KC_RGHT, LGUI_T(KC_ENT)
    ),
    [_VOLUME] = LAYOUT(
        LT(_TOGGLE, KC_MUTE),
        APP1, APP2, APP3,
        APP4, APP5, KC_NO, DEFAULT
    ),
    [_FNT] = LAYOUT(
        LT(_TOGGLE, KC_MUTE),
        RGB_TOG, RGB_MOD, RGB_VAI,
        QK_BOOT, RGB_RMOD, RGB_VAD, KC_NO
    ),
    [_SCALE] = LAYOUT( 
        LT(_TOGGLE, KC_MUTE),
        KC_TRNS, LCTL(KC_EQL), LCTL(KC_0),
        KC_TRNS, LCTL(KC_MINS), LCTL(KC_1), KC_SPC      
    ),
    [_TOGGLE] = LAYOUT(
        KC_NO,
        TO(_MEDIA), TO(_NAV), TO(_VOLUME),
        TO(_SCALE), KC_NO, KC_NO, TO(_FNT)
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) { // In order to add more volume controls, add here code to detect custom keycode
    switch (keycode) {
        case DEFAULT:
            if (record->event.pressed) {
                midi2vol= 0x3E;
            } else {

            }
            break;
        case APP1:
            if (record->event.pressed) {
                midi2vol= 0x3F;
            } else {

            }
            break;
        case APP2:
            if (record->event.pressed) {
                midi2vol= 0x40;
            } else {

            }
            break;
        case APP3:
            if (record->event.pressed) {
                midi2vol= 0x41;
            } else {
                
            }
            break;
        case APP4:
            if (record->event.pressed) {
                midi2vol= 0x42;
            } else {

            }
            break;
        case APP5:
            if (record->event.pressed) {
                midi2vol= 0x43;
            } else {
                
            }
            break;
    }
    return true;
}


uint8_t divisor = 0;

// Modified by name-nam.hateblo.jp
int tmp;

void slider(void) {
    if (divisor++) {
        return;
    }

    if(abs(tmp-analogReadPin(SLIDER_PIN))<20){
        return;
    }else{
        midi_send_cc(&midi_device, 2, midi2vol, 0x7F - (analogReadPin(SLIDER_PIN) >> 3));
        tmp=analogReadPin(SLIDER_PIN);
    }
}

void matrix_scan_user(void) {
    slider();
}
