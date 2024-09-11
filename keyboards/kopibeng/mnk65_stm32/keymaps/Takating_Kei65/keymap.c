#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _MEDIA,
    _NAV,
    _VOLUME,
    _FNT,
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
    TD_EGUI,
    TD_HM_WWW,
    TD_MR_GL,
    TD_MF_GR,
    TD_MP_GU,
    TD_MN_GD,
};

/* Declare the functions to be used with your tap dance key(s)
TD_EGUI is Single-Tap = ESC, Hold = LGUI, Double-Tap = LGUI+H, Double-Hold = PSCR
TD_HM_WWW is Single-Tap = Home, Hold = layer1, Double-Tap = KC_WWW_HOME
TD_MR_GL is Single-Tap = KC_MRWD, Hold = Left, Double-Tap = GUI+Left, Double-Hold = GUI+CTL+Left
TD_MF_GR is Single-Tap = KC_MFFD, Hold = Right, Double-Tap = GUI+Right, Double-Hold = GUI+CTL+Right
TD_MP_GU is Single-Tap = KC_MPRV, Hold = Up, Double-Tap = GUI+Up, Double-Hold = GUI+CTL+D
TD_MN_GD is Single-Tap = KC_MNXT, Hold = Down, Double-Tap = GUI+Down, Double-Hold = GUI+CTL+F4
*/

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with TD_EGUI tap dances
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
static td_tap_t egui_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void at_finished(tap_dance_state_t *state, void *user_data) {
    egui_tap_state.state = cur_dance(state);
    switch (egui_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ESC);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LGUI);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LGUI(KC_H));// tap_code16 allow you to combine a modifier with a keycode
            break;
		case TD_DOUBLE_HOLD:
			tap_code(KC_PSCR);
            break;
        default:
            break;
    }
}

void at_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (egui_tap_state.state == TD_SINGLE_HOLD) {
        unregister_code(KC_LGUI);
    }
    egui_tap_state.state = TD_NONE;
}

// Functions associated with TD_HM_WWW tap dances
void bt_finished(tap_dance_state_t *state, void *user_data);
void bt_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t www_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void bt_finished(tap_dance_state_t *state, void *user_data) {
    www_tap_state.state = cur_dance(state);
    switch (www_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_HOME);
            break;
        case TD_SINGLE_HOLD:
            layer_on(1);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(KC_WWW_HOME);
            break;
        default:
            break;
    }
}

void bt_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (www_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(1);
    }
    www_tap_state.state = TD_NONE;
}

// Functions associated with TD_MR_GL tap dances
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
            register_code(KC_LEFT);
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
        unregister_code(KC_LEFT);
    } else if (mgl_tap_state.state == TD_DOUBLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI)); 
    }
    mgl_tap_state.state = TD_NONE;
}

// Functions associated with TD_MF_GR tap dances
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
            register_code(KC_RGHT);
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
        unregister_code(KC_RGHT);
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
            register_code(KC_UP);
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
            unregister_code(KC_UP);
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
            register_code(KC_DOWN);
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
            unregister_code(KC_DOWN);
            break;
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            break;
        default:
            break;
    }
    mgd_tap_state.state = TD_NONE;
};

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    // TAP_DANCE Complex one here
    [TD_EGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, at_finished, at_reset),
    [TD_HM_WWW] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bt_finished, bt_reset),
    [TD_MR_GL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ct_finished, ct_reset),
    [TD_MF_GR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dt_finished, dt_reset),
    [TD_MP_GU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, et_finished, et_reset),
    [TD_MN_GD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ft_finished, ft_reset),
};


// Combos setting by Takating 20240910
const uint16_t PROGMEM combo0[] = {TD(TD_EGUI), LT(1,KC_Q), COMBO_END};
const uint16_t PROGMEM combo0b[] = {KC_BSPC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM combo1[] = {TD(TD_MR_GL), TD(TD_MN_GD), COMBO_END};
const uint16_t PROGMEM combo2[] = {TD(TD_MN_GD), TD(TD_MF_GR), COMBO_END};
const uint16_t PROGMEM combo3[] = {LT(1,KC_Q), KC_A, COMBO_END};
const uint16_t PROGMEM combo3b[] = {LT(2,KC_BSLS), LT(3,KC_ENT), COMBO_END};
const uint16_t PROGMEM combo4[] = {KC_RBRC, MT(MOD_LCTL,KC_QUOT), COMBO_END};
const uint16_t PROGMEM combo4b[] = {LT(2,KC_TAB), LT(3,KC_GRV), COMBO_END};
const uint16_t PROGMEM combo5[] = {LT(2,KC_TAB), LT(1,KC_Q), COMBO_END};
const uint16_t PROGMEM combo5b[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM combo6[] = {KC_RBRC, LT(2,KC_BSLS), COMBO_END};
const uint16_t PROGMEM combo7[] = {LT(3,KC_Z), LT(1,KC_X), COMBO_END};
const uint16_t PROGMEM combo7b[] = {MT(MOD_LALT,KC_COMM), LT(2,KC_DOT), COMBO_END};
const uint16_t PROGMEM combo8[] = {LT(1,KC_X), KC_C, COMBO_END};
const uint16_t PROGMEM combo8b[] = {LT(2,KC_DOT), MT(MOD_LCTL,KC_SLSH), COMBO_END};
const uint16_t PROGMEM combo9[] = {TD(TD_EGUI), LT(1,KC_1), COMBO_END};
const uint16_t PROGMEM combo9b[] = {KC_BSPC, TD(TD_HM_WWW), COMBO_END};

const uint16_t PROGMEM combo10[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo10b[] = {LT(3,KC_ENT), KC_RSFT, COMBO_END};
const uint16_t PROGMEM combo11[] = {LT(1,KC_Q), KC_W, COMBO_END};
const uint16_t PROGMEM combo12[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo13[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM combo14[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo15[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM combo16[] = {KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM combo17[] = {KC_E, LT(3,KC_R), COMBO_END};
const uint16_t PROGMEM combo18[] = {LT(3,KC_R), KC_T, COMBO_END};
const uint16_t PROGMEM combo19[] = {LT(1,KC_PGUP), MT(MOD_LGUI,KC_PGDN), COMBO_END};

const uint16_t PROGMEM combo20[] = {KC_LSFT, KC_RSFT, COMBO_END};

const uint16_t PROGMEM combo21[] = {MT(MOD_LCTL,KC_QUOT), LT(3,KC_ENT), COMBO_END};
const uint16_t PROGMEM combo21b[] = {LT(1,KC_1), LT(2,KC_2), COMBO_END};
const uint16_t PROGMEM combo22[] = {MT(MOD_LCTL,KC_SLSH), KC_RSFT, COMBO_END};
const uint16_t PROGMEM combo22b[] = {LT(2,KC_2), MT(MOD_LCTL,KC_3), COMBO_END};
const uint16_t PROGMEM combo22c[] = {LT(2,KC_2), MT(MOD_LCTL,KC_3), KC_E, COMBO_END};
const uint16_t PROGMEM combo23[] = {MT(MOD_LCTL,KC_QUOT), MT(MOD_LCTL,KC_SLSH), COMBO_END};
const uint16_t PROGMEM combo23b[] = {MT(MOD_LCTL,KC_3), MT(MOD_LSFT,KC_4), COMBO_END};
const uint16_t PROGMEM combo23c[] = {MT(MOD_LCTL,KC_3), MT(MOD_LSFT,KC_4), LT(3,KC_R), COMBO_END};
const uint16_t PROGMEM combo23d[] = {MT(MOD_LCTL,KC_SLSH), LT(2,KC_ESC), COMBO_END};
const uint16_t PROGMEM combo24[] = {MT(MOD_LALT,KC_ESC), LT(1,KC_SPC), COMBO_END};
const uint16_t PROGMEM combo24b[] = {LT(1,KC_SPC), LT(2,KC_ESC), COMBO_END};
const uint16_t PROGMEM combo25[] = {LT(2,KC_BSPC), MT(MOD_LALT,KC_ESC), COMBO_END};
const uint16_t PROGMEM combo26[] = {KC_LEFT, KC_DOWN, KC_RGHT, COMBO_END};

combo_t key_combos[] = {
  COMBO(combo0, KC_DEL),
  COMBO(combo0b, KC_DEL),
  COMBO(combo1, LALT(KC_LEFT)),
  COMBO(combo2, LALT(KC_RGHT)),
  COMBO(combo3, LCA(KC_TAB)),
  COMBO(combo3b, LCA(KC_TAB)),
  COMBO(combo4, MEH(KC_TAB)),
  COMBO(combo4b, MEH(KC_TAB)),
  COMBO(combo5, LSFT(KC_TAB)),
  COMBO(combo5b, LSFT(KC_TAB)),
  COMBO(combo6, KC_TAB),
  COMBO(combo7, RSG(KC_LEFT)),
  COMBO(combo7b, RSG(KC_LEFT)),
  COMBO(combo8, RSG(KC_RGHT)),
  COMBO(combo8b, RSG(KC_RGHT)),
  COMBO(combo9, KC_F11),
  COMBO(combo9b, KC_F11),

  COMBO(combo10, LGUI(KC_TAB)),
  COMBO(combo10b, LGUI(KC_TAB)),
  COMBO(combo11, LALT(KC_ESC)),
  COMBO(combo12, LSA(KC_ESC)),
  COMBO(combo13, LCTL(KC_PGUP)),
  COMBO(combo14, LCTL(KC_PGDN)),
  COMBO(combo15, LCTL(KC_T)),
  COMBO(combo16, LCTL(KC_W)),
  COMBO(combo17, RCS(KC_PGUP)),
  COMBO(combo18, RCS(KC_PGDN)),
  COMBO(combo19, RCS(KC_T)),

  COMBO(combo20, KC_CAPS),

  COMBO(combo21, LSA(KC_7)),
  COMBO(combo21b, LSA(KC_7)),
  COMBO(combo22, LSA(KC_8)),
  COMBO(combo22b, LSA(KC_8)),
  COMBO(combo22c, KC_LSFT),
  COMBO(combo23, LSA(KC_9)),
  COMBO(combo23b, LSA(KC_9)),
  COMBO(combo23c, LALT(KC_GRV)),
  COMBO(combo23d, LALT(KC_GRV)),
  COMBO(combo24, KC_SPC),
  COMBO(combo24b, KC_SPC),
  COMBO(combo25, KC_PENT),
  COMBO(combo26, KC_MPLY),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	// Default layer
	[0] = LAYOUT_all(
		TD(TD_EGUI), LT(1,KC_1), LT(2,KC_2), MT(MOD_LCTL,KC_3), MT(MOD_LSFT,KC_4), MT(MOD_LSFT,KC_5), MT(MOD_LGUI,KC_6), KC_7, KC_8, KC_9, LT(1,KC_0), MT(MOD_LCTL,KC_MINS), MT(MOD_LSFT,KC_EQL), KC_BSPC, KC_BSPC, TD(TD_HM_WWW),
		LT(2,KC_TAB), LT(1,KC_Q), KC_W, KC_E, LT(3,KC_R), KC_T, LT(2,KC_Y), KC_U, LT(3,KC_I), KC_O, LT(2,KC_P), KC_LBRC, KC_RBRC, LT(2,KC_BSLS), LT(1,KC_PGUP),
		LT(3,KC_GRV), KC_A, KC_S, KC_D, KC_F, LT(1,KC_G), KC_H, KC_J, KC_K, KC_L, LT(3,KC_SCLN), MT(MOD_LCTL,KC_QUOT), LT(3,KC_ENT), MT(MOD_LGUI,KC_PGDN),
		KC_LSFT, KC_LSFT, LT(3,KC_Z), LT(1,KC_X), KC_C, LT(2,KC_V), LT(3,KC_B), KC_N, KC_M, MT(MOD_LALT,KC_COMM), LT(2,KC_DOT), MT(MOD_LCTL,KC_SLSH), KC_RSFT, KC_UP, LT(3,KC_END),
		MT(MOD_LCTL,KC_PDOT), LT(2,KC_BSPC), MT(MOD_LALT,KC_ESC), LT(1,KC_SPC), LT(1,KC_SPC), LT(1,KC_SPC), KC_RALT, LT(2,KC_ESC), KC_LEFT, KC_DOWN, KC_RGHT
	),

	// Fn1 Layer
	[1] = LAYOUT_all(
		QK_COMBO_TOGGLE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7,KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_END, KC_END, QK_COMBO_TOGGLE,
		LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RGHT)), LGUI(KC_UP), LALT(KC_ESC), LSA(KC_ESC), LCTL(KC_T), RCS(KC_PGUP), RCS(KC_PGDN), LCTL(LGUI(KC_D)), KC_TRNS, RCS(KC_UP), LCTL(KC_LEFT), LCTL(KC_RGHT), RCS(KC_DOWN), QK_COMBO_ON,
		KC_CAPS, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_RGHT), RCS(KC_TAB), LCTL(KC_W), LCTL(KC_TAB), LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_F4)), LCTL(LGUI(KC_RGHT)), RCS(KC_LEFT), RCS(KC_RGHT), LGUI(KC_TAB), QK_COMBO_OFF,
		LSA(KC_P), KC_TRNS, RSG(KC_LEFT), RSG(KC_RGHT), MEH(KC_TAB), LCA(KC_TAB), LGUI(KC_TAB), LCTL(KC_N), LGUI(KC_C), LALT(KC_ESC), LSA(KC_ESC), RSG(KC_LEFT), RSG(KC_RGHT), LCTL(KC_EQL), KC_TRNS,
		LALT(KC_ENT), KC_F5, LGUI(KC_H), LGUI(KC_D), LGUI(KC_D), LGUI(KC_D), KC_PSCR, KC_PSCR, LCTL(KC_0), LCTL(KC_MINS), LCTL(KC_1)
    ),

	// Fn2 Layer
	[2] = LAYOUT_all(
		LALT(KC_F4), KC_MYCM, KC_CALC, LCTL(KC_F), KC_PSLS, LALT(KC_LEFT), LALT(KC_RGHT), LSA(KC_8), KC_LSFT, KC_TRNS, KC_TRNS, LSFT(KC_TAB), KC_TAB, LCTL(KC_A), LCTL(KC_A), KC_MYCM,
		KC_DEL, KC_P7, KC_P8, KC_P9, KC_PAST, RCS(KC_T), KC_TRNS, LSA(KC_7), KC_INS, KC_TRNS, KC_TRNS, RCS(KC_HOME), RCS(KC_END), LCTL(KC_E), RCS(KC_PGUP),
		KC_NUM, KC_P4, KC_P5, KC_P6, KC_PMNS, KC_TRNS, LCTL(KC_H), LSA(KC_9), LALT(KC_GRV), LGUI(KC_L), LALT(KC_UP), LALT(KC_DOWN), LCTL(KC_L), RCS(KC_PGDN),
		KC_P0, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_PPLS, LCTL(KC_B), LSA(KC_1), LSA(KC_2), LSA(KC_Q), LGUI(KC_DOT), LCTL(KC_B), KC_WWW_HOME, LCTL(KC_T), RCS(KC_T),
		KC_WWW_HOME, RCS(KC_T), LCTL(KC_A), KC_PENT, KC_PENT, KC_PENT, LCTL(KC_H), LCTL(KC_H), RCS(KC_TAB), LCTL(KC_W), LCTL(KC_TAB)
	),
	
	// Fn3 Layer
	[3] = LAYOUT_all(
		KC_F11, RCS(KC_PGUP), RCS(KC_PGDN), KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F23, KC_F24,
		KC_HOME, KC_PGUP, KC_UP, LCTL(KC_T), QK_BOOT, LCTL(KC_EQL), LCTL(KC_1), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LSFT, LSA(KC_8), LSA(KC_7), MEH(KC_TAB),
		LCTL(KC_L), KC_PGDN, KC_DOWN, LCTL(KC_W), LCTL(KC_BSLS), LCTL(KC_MINS), LCTL(KC_0), KC_TRNS, KC_TRNS, KC_TRNS, LALT(KC_GRV), LSA(KC_9), LALT(KC_F4), LCA(KC_TAB),
		KC_END, KC_TRNS, KC_LEFT, KC_RGHT, LALT(KC_LEFT), LALT(KC_RGHT), KC_TRNS, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, LCTL(KC_Z), RCS(KC_Z), TD(TD_MP_GU), RGB_TOG,
		KC_F7, KC_SLSH, KC_F9, KC_MUTE, KC_MUTE, KC_MUTE, KC_MPLY, KC_MPLY, TD(TD_MR_GL), TD(TD_MN_GD), TD(TD_MF_GR)
	),
};

