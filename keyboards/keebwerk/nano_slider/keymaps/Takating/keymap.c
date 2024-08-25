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
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum { // add any other tap dance keys to this enum
    TD_F_F5,
    TD_C_MYCM,
    TD_MU_TG_CL,
    TD_SP_LN_ET,
    TD_MR_LS_GL,
    TD_MF_LV_GR,
    TD_MP_GU,
    TD_MN_GD,
};

/* Declare the functions to be used with your tap dance key(s)
TD_MU_TG_CL is Single-Tap = MUTE, Hold = MO(_TOGGLE), Double-Tap = ALT+F4
TD_SP_LN_ET is Single-Tap = SPC, Hold = MO(_NAV), Double-Tap = ENT
TD_MR_LS_GL is Single-Tap = KC_MRWD, Hold = MO(_SCALE), Double-Tap = GUI+Left, Double-Hold = GUI+CTL+Left
TD_MF_LV_GR is Single-Tap = KC_MFFD, Hold = MO(_VOLUME), Double-Tap = GUI+Right, Double-Hold = GUI+CTL+Right
TD_MP_GU is Single-Tap = KC_MPRV, Double-Tap = GUI+Up, Double-Hold = GUI+CTL+D
TD_MN_GD is Single-Tap = KC_MNXT, Double-Tap = GUI+Down, Double-Hold = GUI+CTL+F4
*/

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with TD_MU_TG_CL tap dances
void at_finished(tap_dance_state_t *state, void *user_data);
void at_reset(tap_dance_state_t *state, void *user_data);

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;
    }
    return TD_UNKNOWN;
}

// Initialize tap structure associated with this tap dance key
static td_tap_t mul_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void at_finished(tap_dance_state_t *state, void *user_data) {
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

void at_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (mul_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_TOGGLE);
    }
    mul_tap_state.state = TD_NONE;
}

// Functions associated with TD_SP_LN_ET tap dances
void bt_finished(tap_dance_state_t *state, void *user_data);
void bt_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t cnt_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void bt_finished(tap_dance_state_t *state, void *user_data) {
    cnt_tap_state.state = cur_dance(state);
    switch (cnt_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_NAV);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_ENT);
            break;
        default:
            break;
    }
}

void bt_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (cnt_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_NAV);
    }
    cnt_tap_state.state = TD_NONE;
}

// Functions associated with TD_MR_LS_GL tap dances
void ct_finished(tap_dance_state_t *state, void *user_data);
void ct_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t mgl_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ct_finished(tap_dance_state_t *state, void *user_data) {
    mgl_tap_state.state = cur_dance(state);
    switch (mgl_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MRWD);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_SCALE);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LGUI(KC_LEFT));
            break;
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            tap_code(KC_LEFT);
            break;
        default:
            break;
    }
}

void ct_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (mgl_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_SCALE);
    } else if (mgl_tap_state.state == TD_DOUBLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI)); 
    }
    mgl_tap_state.state = TD_NONE;
}

// Functions associated with TD_MF_LV_GR tap dances
void dt_finished(tap_dance_state_t *state, void *user_data);
void dt_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t mgr_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void dt_finished(tap_dance_state_t *state, void *user_data) {
    mgr_tap_state.state = cur_dance(state);
    switch (mgr_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MFFD);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_VOLUME);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LGUI(KC_RGHT));
            break;
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            tap_code(KC_RGHT);
            break;
        default:
            break;
    }
}

void dt_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (mgr_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_VOLUME);
    } else if (mgr_tap_state.state == TD_DOUBLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI)); 
    }
    mgr_tap_state.state = TD_NONE;
}

// Functions associated with TD_MP_GU tap dances
void et_finished(tap_dance_state_t *state, void *user_data);
void et_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t mgu_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void et_finished(tap_dance_state_t *state, void *user_data) {
    mgu_tap_state.state = cur_dance(state);
    switch (mgu_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MPRV);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_MPRV);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LGUI(KC_UP));
            break;
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            tap_code(KC_D);
            break;
        default:
            break;
    }
}

void et_reset(tap_dance_state_t *state, void *user_data) {
    switch (mgu_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_MPRV);
            break;
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            break;
        default:
            break;
    }
    mgu_tap_state.state = TD_NONE;
}

// Functions associated with TD_MN_GD tap dances
void ft_finished(tap_dance_state_t *state, void *user_data);
void ft_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t mgd_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ft_finished(tap_dance_state_t *state, void *user_data) {
    mgd_tap_state.state = cur_dance(state);
    switch (mgd_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MNXT);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_MNXT);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LGUI(KC_DOWN));
            break;
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            tap_code(KC_F4);
            break;
        default:
            break;
    }
}

void ft_reset(tap_dance_state_t *state, void *user_data) {
    switch (mgd_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_MNXT);
            break;
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            break;
        default:
            break;
    }
    mgd_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    // TAP_DANCE Simple one here
    [TD_F_F5] = ACTION_TAP_DANCE_DOUBLE(KC_F, KC_F5),
    [TD_C_MYCM] = ACTION_TAP_DANCE_DOUBLE(KC_C, KC_MYCM),
    // TAP_DANCE Complex one here
    [TD_MU_TG_CL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, at_finished, at_reset),
    [TD_SP_LN_ET] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bt_finished, bt_reset),
    [TD_MR_LS_GL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ct_finished, ct_reset),
    [TD_MF_LV_GR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dt_finished, dt_reset),
    [TD_MP_GU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, et_finished, et_reset),
    [TD_MN_GD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ft_finished, ft_reset),
};


// Combos setting by Takating 20240805-v1.2 (Put below "enum layer_names")
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
const uint16_t PROGMEM combo9b[] = {TD(TD_MR_LS_GL), TD(TD_MN_GD), TD(TD_MF_LV_GR), COMBO_END};
const uint16_t PROGMEM combo10[] = {TD(TD_F_F5), TD(TD_MR_LS_GL), COMBO_END};
const uint16_t PROGMEM combo11[] = {TD(TD_MP_GU), TD(TD_MN_GD), COMBO_END};
const uint16_t PROGMEM combo12[] = {TD(TD_C_MYCM), TD(TD_MF_LV_GR), COMBO_END};
const uint16_t PROGMEM combo13[] = {TD(TD_F_F5), TD(TD_MP_GU), COMBO_END};
const uint16_t PROGMEM combo14[] = {TD(TD_C_MYCM), TD(TD_MP_GU), COMBO_END};
const uint16_t PROGMEM combo15[] = {TD(TD_MR_LS_GL), TD(TD_MN_GD), COMBO_END};
const uint16_t PROGMEM combo16[] = {TD(TD_MF_LV_GR), TD(TD_MN_GD), COMBO_END};
const uint16_t PROGMEM combo17[] = {LCTL(KC_EQL), LCTL(KC_0), COMBO_END};
const uint16_t PROGMEM combo18[] = {LCTL(KC_MINS), LCTL(KC_1), COMBO_END};
const uint16_t PROGMEM combo19[] = {LCTL(KC_EQL), LCTL(KC_MINS), COMBO_END};
const uint16_t PROGMEM combo20[] = {LCTL(KC_0), LCTL(KC_1), COMBO_END};

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
  COMBO(combo9b, LGUI(KC_TAB)),
  COMBO(combo10, KC_F11),
  COMBO(combo11, KC_F9),
  COMBO(combo12, KC_MPLY),
  COMBO(combo13, LALT(KC_LEFT)),
  COMBO(combo14, LALT(KC_RGHT)),
  COMBO(combo15, RSG(KC_LEFT)),
  COMBO(combo16, RSG(KC_RGHT)),
  COMBO(combo17, KC_HOME),
  COMBO(combo18, KC_END),
  COMBO(combo19, KC_PGUP),
  COMBO(combo20, KC_PGDN),
};


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { // In order to add more volume controls, add here a custom keycode
    DEFAULT= SAFE_RANGE,APP1,APP2,APP3,APP4,APP5
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_MEDIA] = LAYOUT(
        TD(TD_MU_TG_CL),
        TD(TD_F_F5), TD(TD_MP_GU), TD(TD_C_MYCM),
        TD(TD_MR_LS_GL), TD(TD_MN_GD), TD(TD_MF_LV_GR), TD(TD_SP_LN_ET)
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
        KC_TRNS, LCTL(KC_EQL), LCTL(KC_1),
        KC_TRNS, LCTL(KC_MINS), LCTL(KC_0), KC_SPC      
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
