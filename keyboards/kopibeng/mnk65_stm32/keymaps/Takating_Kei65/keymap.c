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
const uint16_t PROGMEM combo0[] = {TD(TD_EGUI), LT(1,KC_1), COMBO_END};
const uint16_t PROGMEM combo1[] = {KC_BSPC, TD(TD_HM_WWW), COMBO_END};
const uint16_t PROGMEM combo2[] = {LT(3,KC_END), KC_DOWN, COMBO_END};
const uint16_t PROGMEM combo3[] = {LT(3,KC_END), KC_RGHT, COMBO_END};
const uint16_t PROGMEM combo4[] = {KC_W, KC_S, COMBO_END};
const uint16_t PROGMEM combo5[] = {LT(2,KC_BSLS), LT(3,KC_ENT), COMBO_END};
const uint16_t PROGMEM combo6[] = {KC_RBRC, MT(MOD_LCTL,KC_QUOT), COMBO_END};
const uint16_t PROGMEM combo7[] = {LT(1,KC_Q), KC_A, COMBO_END};
const uint16_t PROGMEM combo8[] = {LT(2,KC_TAB), LT(1,KC_Q), COMBO_END};
const uint16_t PROGMEM combo9[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM combo10[] = {KC_RBRC, LT(2,KC_BSLS), COMBO_END};
const uint16_t PROGMEM combo11[] = {LT(3,KC_Z), LT(1,KC_X), COMBO_END};
const uint16_t PROGMEM combo12[] = {MT(MOD_LALT,KC_COMM), LT(2,KC_DOT), COMBO_END};
const uint16_t PROGMEM combo13[] = {LT(1,KC_X), KC_C, COMBO_END};
const uint16_t PROGMEM combo14[] = {LT(2,KC_DOT), MT(MOD_LCTL,KC_SLSH), COMBO_END};
const uint16_t PROGMEM combo15[] = {LT(3,KC_Z), MT(MOD_LALT,KC_ESC), COMBO_END};
const uint16_t PROGMEM combo16[] = {TD(TD_HM_WWW), LT(1,KC_PGUP), COMBO_END};
const uint16_t PROGMEM combo17[] = {LT(1,KC_PGUP), MT(MOD_LGUI,KC_PGDN), COMBO_END};
const uint16_t PROGMEM combo18[] = {MT(MOD_LGUI,KC_PGDN), LT(3,KC_END), COMBO_END};
const uint16_t PROGMEM combo19[] = {KC_LSFT, KC_RSFT, COMBO_END};

const uint16_t PROGMEM combo20[] = {LT(3,KC_GRV), KC_A, COMBO_END};
const uint16_t PROGMEM combo21[] = {LT(3,KC_ENT), MT(MOD_LGUI,KC_PGDN), COMBO_END};
const uint16_t PROGMEM combo22[] = {LT(1,KC_Q), KC_W, COMBO_END};
const uint16_t PROGMEM combo23[] = {KC_BSPC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM combo24[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo25[] = {KC_BSPC, LT(2,KC_BSLS), COMBO_END};
const uint16_t PROGMEM combo26[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM combo27[] = {KC_LEFT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM combo28[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo29[] = {KC_DOWN, KC_RGHT, COMBO_END};
const uint16_t PROGMEM combo30[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM combo31[] = {KC_UP, KC_DOWN, COMBO_END};
const uint16_t PROGMEM combo32[] = {KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM combo33[] = {KC_LEFT, KC_RGHT, COMBO_END};
const uint16_t PROGMEM combo34[] = {KC_A, LT(3,KC_Z), COMBO_END};
const uint16_t PROGMEM combo35[] = {KC_RSFT, KC_UP, COMBO_END};

const uint16_t PROGMEM combo36[] = {KC_S, LT(1,KC_X), COMBO_END};
const uint16_t PROGMEM combo37[] = {KC_UP, LT(3,KC_END), COMBO_END};
const uint16_t PROGMEM combo38[] = {MT(MOD_LCTL,KC_QUOT), LT(3,KC_ENT), COMBO_END};
const uint16_t PROGMEM combo39[] = {LT(1,KC_1), LT(2,KC_2), COMBO_END};
const uint16_t PROGMEM combo40[] = {LT(3,KC_ENT), KC_RSFT, COMBO_END};
const uint16_t PROGMEM combo41[] = {LT(2,KC_2), MT(MOD_LCTL,KC_3), COMBO_END};
const uint16_t PROGMEM combo42[] = {LT(2,KC_2), MT(MOD_LCTL,KC_3), KC_E, COMBO_END};
const uint16_t PROGMEM combo43[] = {MT(MOD_LCTL,KC_QUOT), MT(MOD_LCTL,KC_SLSH), COMBO_END};
const uint16_t PROGMEM combo44[] = {MT(MOD_LCTL,KC_3), MT(MOD_LSFT,KC_4), COMBO_END};
const uint16_t PROGMEM combo45[] = {MT(MOD_LCTL,KC_3), MT(MOD_LSFT,KC_4), LT(3,KC_R), COMBO_END};
const uint16_t PROGMEM combo46[] = {MT(MOD_LCTL,KC_SLSH), LT(2,KC_ESC), COMBO_END};
const uint16_t PROGMEM combo47[] = {MT(MOD_LALT,KC_ESC), LT(1,KC_SPC), COMBO_END};
const uint16_t PROGMEM combo48[] = {LT(1,KC_SPC), LT(2,KC_ESC), COMBO_END};

const uint16_t PROGMEM combo49[] = {LT(2,KC_BSPC), MT(MOD_LALT,KC_ESC), COMBO_END};
const uint16_t PROGMEM combo50[] = {KC_RSFT, LT(2,KC_ESC), COMBO_END};
const uint16_t PROGMEM combo51[] = {LT(3,KC_ENT), MT(MOD_LGUI,KC_PGDN), KC_RSFT, COMBO_END};
const uint16_t PROGMEM combo52[] = {LT(3,KC_GRV), KC_A, LT(3,KC_Z), COMBO_END};
const uint16_t PROGMEM combo53[] = {LT(2,KC_BSLS), LT(1,KC_PGUP), COMBO_END};

const uint16_t PROGMEM combo54[] = {KC_S, KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM combo55[] = {KC_D, KC_F, LT(2,KC_V), COMBO_END};

const uint16_t PROGMEM combo56[] = {TD(TD_EGUI), LT(2,KC_TAB), COMBO_END};
const uint16_t PROGMEM combo57[] = {LT(2,KC_TAB), LT(3,KC_GRV), COMBO_END};
const uint16_t PROGMEM combo58[] = {LT(3,KC_GRV), KC_LSFT, COMBO_END};
const uint16_t PROGMEM combo59[] = {KC_LSFT, LT(2,KC_BSPC), COMBO_END};

const uint16_t PROGMEM combo60[] = {LT(1,KC_1), LT(1,KC_Q), COMBO_END};
const uint16_t PROGMEM combo61[] = {MT(MOD_LCTL,KC_MINS), LT(2,KC_P), COMBO_END};
const uint16_t PROGMEM combo62[] = {LT(2,KC_2), KC_W, COMBO_END};
const uint16_t PROGMEM combo63[] = {MT(MOD_LSFT,KC_EQL), KC_LBRC, COMBO_END};

const uint16_t PROGMEM combo64[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo65[] = {KC_F, LT(1,KC_G), COMBO_END};
const uint16_t PROGMEM combo66[] = {LT(3,KC_R), KC_F, COMBO_END};
const uint16_t PROGMEM combo67[] = {KC_F, LT(2,KC_V), COMBO_END};

combo_t key_combos[] = {
  COMBO(combo0, KC_DEL),
  COMBO(combo1, KC_DEL),
  COMBO(combo2, LALT(KC_LEFT)),
  COMBO(combo3, LALT(KC_RGHT)),
  COMBO(combo4, LCA(KC_TAB)),
  COMBO(combo5, LCA(KC_TAB)),
  COMBO(combo6, MEH(KC_TAB)),
  COMBO(combo7, MEH(KC_TAB)),
  COMBO(combo8, LSFT(KC_TAB)),
  COMBO(combo9, LSFT(KC_TAB)),
  COMBO(combo10, KC_TAB),
  COMBO(combo11, RSG(KC_LEFT)),
  COMBO(combo12, RSG(KC_LEFT)),
  COMBO(combo13, RSG(KC_RGHT)),
  COMBO(combo14, RSG(KC_RGHT)),
  COMBO(combo15, KC_F11),
  COMBO(combo16, KC_F11),
  COMBO(combo17, RCS(KC_T)),
  COMBO(combo18, KC_F5),
  COMBO(combo19, KC_CAPS),

  COMBO(combo20, LGUI(KC_TAB)),
  COMBO(combo21, LGUI(KC_TAB)),
  COMBO(combo22, LALT(KC_ESC)),
  COMBO(combo23, LALT(KC_ESC)),
  COMBO(combo24, LSA(KC_ESC)),
  COMBO(combo25, LSA(KC_ESC)),
  COMBO(combo26, RCS(KC_TAB)),
  COMBO(combo27, RCS(KC_TAB)),
  COMBO(combo28, LCTL(KC_TAB)),
  COMBO(combo29, LCTL(KC_TAB)),
  COMBO(combo30, LCTL(KC_T)),
  COMBO(combo31, LCTL(KC_T)),
  COMBO(combo32, LCTL(KC_W)),
  COMBO(combo33, LCTL(KC_W)),
  COMBO(combo34, RCS(KC_PGUP)),
  COMBO(combo35, RCS(KC_PGUP)),
  COMBO(combo36, RCS(KC_PGDN)),
  COMBO(combo37, RCS(KC_PGDN)),

  COMBO(combo38, LSA(KC_7)),
  COMBO(combo39, LSA(KC_7)),
  COMBO(combo40, LSA(KC_8)),
  COMBO(combo41, LSA(KC_8)),
  COMBO(combo42, KC_LSFT),
  COMBO(combo43, LSA(KC_9)),
  COMBO(combo44, LSA(KC_9)),
  COMBO(combo45, LALT(KC_GRV)),
  COMBO(combo46, LALT(KC_GRV)),
  COMBO(combo47, KC_SPC),
  COMBO(combo48, KC_SPC),
  COMBO(combo49, KC_PENT),
  COMBO(combo50, KC_MPLY),

  COMBO(combo51, LCTL(KC_L)),
  COMBO(combo52, LCTL(KC_L)),
  COMBO(combo53, LCTL(KC_E)),
  COMBO(combo54, LCTL(KC_C)),
  COMBO(combo55, LCTL(KC_V)),

  COMBO(combo56, KC_HOME),
  COMBO(combo57, KC_PGUP),
  COMBO(combo58, KC_PGDN),
  COMBO(combo59, KC_END),

  COMBO(combo60, LCTL(LGUI(KC_LEFT))),
  COMBO(combo61, LCTL(LGUI(KC_LEFT))),
  COMBO(combo62, LCTL(LGUI(KC_RGHT))),
  COMBO(combo63, LCTL(LGUI(KC_RGHT))),

  COMBO(combo64, KC_LEFT),
  COMBO(combo65, KC_RGHT),
  COMBO(combo66, KC_UP),
  COMBO(combo67, KC_DOWN)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	// Default layer
	[0] = LAYOUT_all(
		TD(TD_EGUI), LT(1,KC_1), LT(2,KC_2), MT(MOD_LCTL,KC_3), MT(MOD_LSFT,KC_4), MT(MOD_LSFT,KC_5), MT(MOD_LGUI,KC_6), KC_7, KC_8, KC_9, LT(1,KC_0), MT(MOD_LCTL,KC_MINS), MT(MOD_LSFT,KC_EQL), KC_BSPC, KC_BSPC, TD(TD_HM_WWW),
		LT(2,KC_TAB), LT(1,KC_Q), KC_W, KC_E, LT(3,KC_R), KC_T, LT(2,KC_Y), KC_U, LT(3,KC_I), KC_O, LT(2,KC_P), KC_LBRC, KC_RBRC, LT(2,KC_BSLS), LT(1,KC_PGUP),
		LT(3,KC_GRV), KC_A, KC_S, KC_D, KC_F, LT(1,KC_G), KC_H, KC_J, LT(1,KC_K), KC_L, LT(3,KC_SCLN), MT(MOD_LCTL,KC_QUOT), LT(3,KC_ENT), MT(MOD_LGUI,KC_PGDN),
		KC_LSFT, KC_LSFT, LT(3,KC_Z), LT(1,KC_X), KC_C, LT(2,KC_V), LT(3,KC_B), KC_N, KC_M, MT(MOD_LALT,KC_COMM), LT(2,KC_DOT), MT(MOD_LCTL,KC_SLSH), KC_RSFT, KC_UP, LT(3,KC_END),
		MT(MOD_LCTL,KC_PDOT), LT(2,KC_BSPC), MT(MOD_LALT,KC_ESC), LT(1,KC_SPC), LT(1,KC_SPC), LT(1,KC_SPC), KC_RALT, LT(2,KC_ESC), KC_LEFT, KC_DOWN, KC_RGHT
	),

	// Fn1 Layer
	[1] = LAYOUT_all(
		KC_F11, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7,KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_END, KC_END, QK_COMBO_TOGGLE,
		LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RGHT)), LGUI(KC_UP), LALT(KC_ESC), LSA(KC_ESC), LCTL(KC_T), RCS(KC_PGUP), RCS(KC_PGDN), LCTL(LGUI(KC_D)), KC_TRNS, RCS(KC_UP), LCTL(KC_LEFT), LCTL(KC_RGHT), RCS(KC_DOWN), QK_COMBO_ON,
		KC_CAPS, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_RGHT), RCS(KC_TAB), LCTL(KC_W), LCTL(KC_TAB), LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_F4)), LCTL(LGUI(KC_RGHT)), RCS(KC_LEFT), RCS(KC_RGHT), LGUI(KC_TAB), QK_COMBO_OFF,
		LSA(KC_P), KC_TRNS, RSG(KC_LEFT), RSG(KC_RGHT), MEH(KC_TAB), LCA(KC_TAB), LGUI(KC_TAB), LCTL(KC_N), LGUI(KC_C), LALT(KC_ESC), LSA(KC_ESC), RSG(KC_LEFT), RSG(KC_RGHT), LCTL(KC_EQL), KC_TRNS,
		LALT(KC_ENT), KC_F5, LGUI(KC_H), LGUI(KC_D), LGUI(KC_D), LGUI(KC_D), KC_PSCR, KC_PSCR, LCTL(KC_0), LCTL(KC_MINS), LCTL(KC_1)
    ),

	// Fn2 Layer
	[2] = LAYOUT_all(
		LALT(KC_F4), KC_MYCM, KC_CALC, LCTL(KC_F), KC_PSLS, LALT(KC_LEFT), LALT(KC_RGHT), LSA(KC_8), KC_LSFT, KC_TRNS, KC_TRNS, LCTL(KC_C), LCTL(KC_V), LCTL(KC_A), LCTL(KC_A), KC_MYCM,
		KC_DEL, KC_P7, KC_P8, KC_P9, KC_PAST, RCS(KC_T), KC_TRNS, LSA(KC_7), KC_INS, KC_TRNS, KC_TRNS, RCS(KC_HOME), RCS(KC_END), LCTL(KC_E), RCS(KC_PGUP),
		KC_NUM, KC_P4, KC_P5, KC_P6, KC_PMNS, KC_TRNS, LCTL(KC_H), LSA(KC_9), LALT(KC_GRV), LGUI(KC_L), LALT(KC_UP), LALT(KC_DOWN), LCTL(KC_L), RCS(KC_PGDN),
		KC_P0, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_PPLS, LCTL(KC_B), LSA(KC_1), LSA(KC_2), LSA(KC_Q), LGUI(KC_DOT), LCTL(KC_B), KC_WWW_HOME, LCTL(KC_T), RCS(KC_T),
		KC_WWW_HOME, RCS(KC_T), LCTL(KC_A), KC_PENT, KC_PENT, KC_PENT, LCTL(KC_H), LCTL(KC_H), RCS(KC_TAB), LCTL(KC_W), LCTL(KC_TAB)
	),
	
	// Fn3 Layer
	[3] = LAYOUT_all(
		KC_F11, RCS(KC_PGUP), RCS(KC_PGDN), KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F23, KC_F24,
		KC_HOME, KC_PGUP, KC_UP, LCTL(KC_T), QK_BOOT, LCTL(KC_EQL), LCTL(KC_1), RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, KC_LSFT, LSA(KC_8), LSA(KC_7), MEH(KC_TAB),
		LCTL(KC_L), KC_PGDN, KC_DOWN, LCTL(KC_W), LCTL(KC_BSLS), LCTL(KC_MINS), LCTL(KC_0), RGB_HUD, RGB_SAD, RGB_VAD, LALT(KC_GRV), LSA(KC_9), LALT(KC_F4), LCA(KC_TAB),
		KC_END, KC_TRNS, KC_LEFT, KC_RGHT, LALT(KC_LEFT), LALT(KC_RGHT), KC_TRNS, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, LCTL(KC_Z), RCS(KC_Z), TD(TD_MP_GU), RGB_TOG,
		KC_F7, KC_SLSH, KC_F9, KC_MUTE, KC_MUTE, KC_MUTE, KC_MPLY, KC_MPLY, TD(TD_MR_GL), TD(TD_MN_GD), TD(TD_MF_GR)
	),
};

