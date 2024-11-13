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
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum { // add any other tap dance keys to this enum
    TD_EGUI,
    TD_HM_WWW,
    TD_GL_VWL,
    TD_GR_VWR,
    TD_GU_VWN,
    TD_GD_VWC,
    TD_WADD_TSK_CPS,
    TD_ENG_GZ,
    TD_CHS_TOG,
    TD_JPN_TOG,
    TD_LTB_AL,
    TD_RTB_AR,
    TD_NTB_AU,
    TD_CTB_AD,
    TD_F119_GH,
    TD_SF1_VWL,
    TD_SF2_VWR,
    TD_MINS_VWL,
    TD_EQL_VWR,
    TD_PU_HM_L1,
    TD_PD_ED_CL,
    TD_PL_F_C,
};

/* Declare the functions to be used with your tap dance key(s)
[TD_EGUI] is Single-Tap = ESC, Hold = GUI, Double-Tap = GUI+H, Double-Hold = PSCR
[TD_HM_WWW] is Single-Tap = Home, Hold = Layer1, Double-Tap = KC_WWW_HOME
[TD_GL_VWL] is Single-Tap = GUI+Left, Hold = same, Double-Tap = GUI+CTL+Left
[TD_GR_VWR] is Single-Tap = GUI+Right, Hold = same, Double-Tap = GUI+CTL+Right
[TD_GU_VWN] is Single-Tap = GUI+Up, Hold = same, Double-Tap = GUI+CTL+D
[TD_GD_VWC] is Single-Tap = GUI+Down, Hold = same, Double-Tap = GUI+CTL+F4

[TD_WADD_TSK_CPS] is Single-Tap = CTL+L, Hold = GUI+TAB, Double-Tap = Caps
[TD_ENG_GZ] is Single-Tap = LSA(KC_7), Hold = GUI+Z, Double-Tap = F5
[TD_CHS_TOG] is Single-Tap = LSA(KC_8), Hold = SFT, Double-Tap = SFT
[TD_JPN_TOG] is Single-Tap = LSA(KC_9), Hold = ALT+GRV, Double-Tap = ALT+GRV

[TD_LTB_AL] is Single-Tap = RCS+TAB, Hold = same, Double-Tap = ALT+Left
[TD_RTB_AR] is Single-Tap = CTL+TAB, Hold = same, Double-Tap = ALT+Right
[TD_NTB_AU] is Single-Tap = CTL+T, Hold = same, Double-Tap = ALT+Up
[TD_CTB_AD] is Single-Tap = CTL+W, Hold = same, Double-Tap = ALT+Down

[TD_F119_GH] is Single-Tap = F11, Hold = GUI+H, Double-Tap = F9

[TD_PU_HM_L1] is Single-Tap = PageUp, Hold = Layer1, Double-Tap = Home
[TD_PD_ED_CL] is Single-Tap = PageDown, Hold = CTL, Double-Tap = End
[TD_PL_F_C] is Single-Tap = MediaPlay, Hold = F, Double-Tap = C

[TD_SF1_VWL] is Single-Tap = !, Hold = GUI+CTL+Left, Double-Tap = !!
[TD_SF2_VWR] is Single-Tap = @, Hold = GUI+CTL+Right, Double-Tap = @@
[TD_MINS_VWL] is Single-Tap = _, Hold = GUI+CTL+Left, Double-Tap = __
[TD_EQL_VWR] is Single-Tap = +, Hold = GUI+CTL+Right, Double-Tap = ++
*/

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);
td_state_t cur_dance2(tap_dance_state_t *state);

// Functions associated with [TD_EGUI] tap dances
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

// Functions associated with [TD_HM_WWW] tap dances
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

// Functions associated with [TD_GL_VWL] tap dances
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
            tap_code16(LGUI(KC_LEFT));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LGUI(KC_LEFT));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LCTL(LGUI(KC_LEFT)));
            break;
        default:
            break;
    }
}

void ct_reset(tap_dance_state_t *state, void *user_data) {
    mgl_tap_state.state = TD_NONE;
}

// Functions associated with [TD_GR_VWR] tap dances
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
            tap_code16(LGUI(KC_RGHT));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LGUI(KC_RGHT));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LCTL(LGUI(KC_RGHT)));
            break;
        default:
            break;
    }
}

void dt_reset(tap_dance_state_t *state, void *user_data) {
    mgr_tap_state.state = TD_NONE;
}

// Functions associated with [TD_GU_VWN] tap dances
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
            tap_code16(LGUI(KC_UP));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LGUI(KC_UP));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LCTL(LGUI(KC_D)));
            break;
        default:
            break;
    }
}

void et_reset(tap_dance_state_t *state, void *user_data) {
    mgu_tap_state.state = TD_NONE;
}

// Functions associated with [TD_GD_VWC] tap dances
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
            tap_code16(LGUI(KC_DOWN));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LGUI(KC_DOWN));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LCTL(LGUI(KC_F4)));
            break;
        default:
            break;
    }
}

void ft_reset(tap_dance_state_t *state, void *user_data) {
    mgd_tap_state.state = TD_NONE;
};

// Functions associated with [TD_WADD_TSK_CPS] tap dances
void gt_finished(tap_dance_state_t *state, void *user_data);
void gt_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t wad_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void gt_finished(tap_dance_state_t *state, void *user_data) {
    wad_tap_state.state = cur_dance(state);
    switch (wad_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(LCTL(KC_L));
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            tap_code(KC_TAB);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_CAPS);
            break;
        default:
            break;
    }
}

void gt_reset(tap_dance_state_t *state, void *user_data) {
    if (wad_tap_state.state == TD_SINGLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LGUI));
    }
    wad_tap_state.state = TD_NONE;
};

// Functions associated with [TD_ENG_GZ] tap dances
void ht_finished(tap_dance_state_t *state, void *user_data);
void ht_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t eng_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ht_finished(tap_dance_state_t *state, void *user_data) {
    eng_tap_state.state = cur_dance(state);
    switch (eng_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(LSA(KC_7));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LGUI(KC_Z));
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_F5);
            break;
        default:
            break;
    }
}

void ht_reset(tap_dance_state_t *state, void *user_data) {
    eng_tap_state.state = TD_NONE;
};

// Functions associated with [TD_CHS_TOG] tap dances
void it_finished(tap_dance_state_t *state, void *user_data);
void it_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t chs_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void it_finished(tap_dance_state_t *state, void *user_data) {
    chs_tap_state.state = cur_dance(state);
    switch (chs_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(LSA(KC_8));
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_LSFT);
            break;
        default:
            break;
    }
}

void it_reset(tap_dance_state_t *state, void *user_data) {
    chs_tap_state.state = TD_NONE;
};

// Functions associated with [TD_JPN_TOG] tap dances
void jt_finished(tap_dance_state_t *state, void *user_data);
void jt_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t jpn_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void jt_finished(tap_dance_state_t *state, void *user_data) {
    jpn_tap_state.state = cur_dance(state);
    switch (jpn_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(LSA(KC_9));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LALT(KC_GRV));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LALT(KC_GRV));
            break;
        default:
            break;
    }
}

void jt_reset(tap_dance_state_t *state, void *user_data) {
    jpn_tap_state.state = TD_NONE;
};

// Functions associated with [TD_LTB_AL] tap dances
void kt_finished(tap_dance_state_t *state, void *user_data);
void kt_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t ltb_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void kt_finished(tap_dance_state_t *state, void *user_data) {
    ltb_tap_state.state = cur_dance(state);
    switch (ltb_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(RCS(KC_TAB));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(RCS(KC_TAB));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LALT(KC_LEFT));
            break;
        default:
            break;
    }
}

void kt_reset(tap_dance_state_t *state, void *user_data) {
    ltb_tap_state.state = TD_NONE;
};

// Functions associated with [TD_RTB_AR] tap dances
void lt_finished(tap_dance_state_t *state, void *user_data);
void lt_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t rtb_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void lt_finished(tap_dance_state_t *state, void *user_data) {
    rtb_tap_state.state = cur_dance(state);
    switch (rtb_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(LCTL(KC_TAB));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LCTL(KC_TAB));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LALT(KC_RGHT));
            break;
        default:
            break;
    }
}

void lt_reset(tap_dance_state_t *state, void *user_data) {
    rtb_tap_state.state = TD_NONE;
};

// Functions associated with [TD_NTB_AU] tap dances
void mt_finished(tap_dance_state_t *state, void *user_data);
void mt_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t ntb_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void mt_finished(tap_dance_state_t *state, void *user_data) {
    ntb_tap_state.state = cur_dance(state);
    switch (ntb_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(LCTL(KC_T));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LCTL(KC_T));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LALT(KC_UP));
            break;
        default:
            break;
    }
}

void mt_reset(tap_dance_state_t *state, void *user_data) {
    ntb_tap_state.state = TD_NONE;
};

// Functions associated with [TD_CTB_AD] tap dances
void nt_finished(tap_dance_state_t *state, void *user_data);
void nt_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t ctb_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void nt_finished(tap_dance_state_t *state, void *user_data) {
    ctb_tap_state.state = cur_dance(state);
    switch (ctb_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(LCTL(KC_W));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LCTL(KC_W));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LALT(KC_DOWN));
            break;
        default:
            break;
    }
}

void nt_reset(tap_dance_state_t *state, void *user_data) {
    ctb_tap_state.state = TD_NONE;
};

// Functions associated with [TD_F119_GH] tap dances
void ot_finished(tap_dance_state_t *state, void *user_data);
void ot_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t f119_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ot_finished(tap_dance_state_t *state, void *user_data) {
    f119_tap_state.state = cur_dance(state);
    switch (f119_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_F11);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            tap_code(KC_H);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_F9);
            break;
        default:
            break;
    }
}

void ot_reset(tap_dance_state_t *state, void *user_data) {
    if (f119_tap_state.state == TD_SINGLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LGUI)); 
    }
    f119_tap_state.state = TD_NONE;
};

// Functions associated with [TD_PU_HM_L1] tap dances
void o2t_finished(tap_dance_state_t *state, void *user_data);
void o2t_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t ph1_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void o2t_finished(tap_dance_state_t *state, void *user_data) {
    ph1_tap_state.state = cur_dance(state);
    switch (ph1_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_PGUP);
            break;
        case TD_SINGLE_HOLD:
            layer_on(1);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_HOME);
            break;
        default:
            break;
    }
}

void o2t_reset(tap_dance_state_t *state, void *user_data) {
    if (ph1_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(1);
    }
    ph1_tap_state.state = TD_NONE;
};

// Functions associated with [TD_PD_ED_CL] tap dances
void o3t_finished(tap_dance_state_t *state, void *user_data);
void o3t_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t pdc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void o3t_finished(tap_dance_state_t *state, void *user_data) {
    pdc_tap_state.state = cur_dance(state);
    switch (pdc_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_PGDN);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL));
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_END);
            break;
        default:
            break;
    }
}

void o3t_reset(tap_dance_state_t *state, void *user_data) {
    if (pdc_tap_state.state == TD_SINGLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LCTL));
    }
    pdc_tap_state.state = TD_NONE;
};

// Functions associated with [TD_PL_F_C] tap dances
void o4t_finished(tap_dance_state_t *state, void *user_data);
void o4t_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t plfc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void o4t_finished(tap_dance_state_t *state, void *user_data) {
    plfc_tap_state.state = cur_dance(state);
    switch (plfc_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MPLY);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_F);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_C);
            break;
        default:
            break;
    }
}

void o4t_reset(tap_dance_state_t *state, void *user_data) {
    plfc_tap_state.state = TD_NONE;
};

// Below is "TD_DOUBLE_SINGLE_TAP"

// Functions associated with [TD_SF1_VWL] tap dances
void pt_finished(tap_dance_state_t *state, void *user_data);
void pt_reset(tap_dance_state_t *state, void *user_data);

// Determine the tapdance state to return
td_state_t cur_dance2(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Initialize tap structure associated with this tap dance key
static td_tap_t sf1_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void pt_finished(tap_dance_state_t *state, void *user_data) {
    sf1_tap_state.state = cur_dance2(state);
    switch (sf1_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_EXLM);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            tap_code(KC_LEFT);
            break;
        case TD_DOUBLE_SINGLE_TAP: 
            tap_code16(KC_EXLM);
            register_code16(KC_EXLM);
            break;
        default:
            break;
    }
}

void pt_reset(tap_dance_state_t *state, void *user_data) {
    if (sf1_tap_state.state == TD_SINGLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI)); 
    }else if (sf1_tap_state.state == TD_DOUBLE_SINGLE_TAP) {
        unregister_code16(KC_EXLM);
    }
    sf1_tap_state.state = TD_NONE;
};

// Functions associated with [TD_SF2_VWR] tap dances
void qt_finished(tap_dance_state_t *state, void *user_data);
void qt_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t sf2_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void qt_finished(tap_dance_state_t *state, void *user_data) {
    sf2_tap_state.state = cur_dance2(state);
    switch (sf2_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_AT);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            tap_code(KC_RGHT);
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_AT);
            register_code16(KC_AT);
            break;
        default:
            break;
    }
}

void qt_reset(tap_dance_state_t *state, void *user_data) {
    if (sf2_tap_state.state == TD_SINGLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI)); 
    }else if (sf2_tap_state.state == TD_DOUBLE_SINGLE_TAP) {
        unregister_code16(KC_AT);
    }
    sf2_tap_state.state = TD_NONE;
};

// Functions associated with [TD_MINS_VWL] tap dances
void rt_finished(tap_dance_state_t *state, void *user_data);
void rt_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t mins_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void rt_finished(tap_dance_state_t *state, void *user_data) {
    mins_tap_state.state = cur_dance2(state);
    switch (mins_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_UNDS);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            tap_code(KC_LEFT);
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_UNDS);
            register_code16(KC_UNDS);
            break;
        default:
            break;
    }
}

void rt_reset(tap_dance_state_t *state, void *user_data) {
    if (mins_tap_state.state == TD_SINGLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI)); 
    }else if (mins_tap_state.state == TD_DOUBLE_SINGLE_TAP) {
        unregister_code16(KC_UNDS);
    }
    mins_tap_state.state = TD_NONE;
};

// Functions associated with [TD_EQL_VWR] tap dances
void st_finished(tap_dance_state_t *state, void *user_data);
void st_reset(tap_dance_state_t *state, void *user_data);

// Initialize tap structure associated with this tap dance key
static td_tap_t eql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void st_finished(tap_dance_state_t *state, void *user_data) {
    eql_tap_state.state = cur_dance2(state);
    switch (eql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_PLUS);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            tap_code(KC_RGHT);
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_PLUS);
            register_code16(KC_PLUS);
            break;
        default:
            break;
    }
}

void st_reset(tap_dance_state_t *state, void *user_data) {
    if (eql_tap_state.state == TD_SINGLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI)); 
    }else if (eql_tap_state.state == TD_DOUBLE_SINGLE_TAP) {
        unregister_code16(KC_PLUS);
    }
    eql_tap_state.state = TD_NONE;
};

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
// TAP_DANCE Complex one here
    [TD_EGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, at_finished, at_reset),
    [TD_HM_WWW] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bt_finished, bt_reset),
    [TD_GL_VWL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ct_finished, ct_reset),
    [TD_GR_VWR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dt_finished, dt_reset),
    [TD_GU_VWN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, et_finished, et_reset),
    [TD_GD_VWC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ft_finished, ft_reset),
    [TD_WADD_TSK_CPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gt_finished, gt_reset),
    [TD_ENG_GZ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ht_finished, ht_reset),
    [TD_CHS_TOG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, it_finished, it_reset),
    [TD_JPN_TOG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, jt_finished, jt_reset),
    [TD_LTB_AL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, kt_finished, kt_reset),
    [TD_RTB_AR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lt_finished, lt_reset),
    [TD_NTB_AU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mt_finished, mt_reset),
    [TD_CTB_AD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nt_finished, nt_reset),
    [TD_F119_GH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ot_finished, ot_reset),
    [TD_PU_HM_L1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, o2t_finished, o2t_reset),
    [TD_PD_ED_CL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, o3t_finished, o3t_reset),
    [TD_PL_F_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, o4t_finished, o4t_reset),
    [TD_SF1_VWL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pt_finished, pt_reset),
    [TD_SF2_VWR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, qt_finished, qt_reset),
    [TD_MINS_VWL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rt_finished, rt_reset),
    [TD_EQL_VWR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, st_finished, st_reset),
};


// Combos setting by Takating 20241109
const uint16_t PROGMEM combo0[] = {TD(TD_EGUI), LT(1,KC_1), LT(1,KC_Q), COMBO_END};
const uint16_t PROGMEM combo1[] = {KC_BSPC, TD(TD_HM_WWW), COMBO_END};
const uint16_t PROGMEM combo2[] = {LT(3,KC_W), KC_S, COMBO_END};
const uint16_t PROGMEM combo3[] = {LT(2,KC_BSLS), LT(3,KC_ENT), COMBO_END};
const uint16_t PROGMEM combo4[] = {KC_RBRC, MT(MOD_LCTL,KC_QUOT), COMBO_END};
const uint16_t PROGMEM combo5[] = {LT(1,KC_Q), KC_A, COMBO_END};
const uint16_t PROGMEM combo6[] = {TD(TD_EGUI), LT(2,KC_TAB), COMBO_END};
const uint16_t PROGMEM combo7[] = {KC_BSPC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM combo8[] = {KC_BSPC, LT(2,KC_BSLS), COMBO_END};
const uint16_t PROGMEM combo9[] = {LT(3,KC_Z), LT(1,KC_X), COMBO_END};
const uint16_t PROGMEM combo10[] = {MT(MOD_LALT,KC_COMM), LT(2,KC_DOT), COMBO_END};
const uint16_t PROGMEM combo11[] = {LT(1,KC_X), KC_C, COMBO_END};
const uint16_t PROGMEM combo12[] = {LT(2,KC_DOT), MT(MOD_LCTL,KC_SLSH), COMBO_END};
const uint16_t PROGMEM combo13[] = {LT(3,KC_Z), MT(MOD_LALT,KC_ESC), COMBO_END};
const uint16_t PROGMEM combo14[] = {MT(MOD_LCTL,KC_SLSH), LT(2,KC_ESC), COMBO_END};
const uint16_t PROGMEM combo15[] = {TD(TD_PU_HM_L1), TD(TD_PD_ED_CL), COMBO_END};
const uint16_t PROGMEM combo16[] = {KC_LSFT, LT(3,KC_Z), COMBO_END};
const uint16_t PROGMEM combo17[] = {LT(2,KC_BSLS), TD(TD_HM_WWW), COMBO_END};

const uint16_t PROGMEM combo18[] = {LT(3,KC_GRV), KC_LSFT, COMBO_END};
const uint16_t PROGMEM combo19[] = {LT(3,KC_ENT), KC_RSFT, COMBO_END};
const uint16_t PROGMEM combo20[] = {LT(1,KC_Q), LT(3,KC_W), COMBO_END};
const uint16_t PROGMEM combo21[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM combo22[] = {LT(3,KC_W), KC_E, COMBO_END};
const uint16_t PROGMEM combo23[] = {KC_RBRC, LT(2,KC_BSLS), COMBO_END};
const uint16_t PROGMEM combo24[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM combo25[] = {KC_LEFT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM combo26[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo27[] = {KC_DOWN, KC_RGHT, COMBO_END};
const uint16_t PROGMEM combo28[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM combo29[] = {KC_UP, KC_DOWN, COMBO_END};
const uint16_t PROGMEM combo30[] = {KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM combo31[] = {KC_LEFT, KC_RGHT, COMBO_END};
const uint16_t PROGMEM combo32[] = {KC_A, LT(3,KC_Z), COMBO_END};
const uint16_t PROGMEM combo33[] = {KC_RSFT, KC_UP, COMBO_END};
const uint16_t PROGMEM combo34[] = {KC_S, LT(1,KC_X), COMBO_END};
const uint16_t PROGMEM combo35[] = {KC_UP, LT(3,KC_END), COMBO_END};

const uint16_t PROGMEM combo36[] = {LT(3,KC_ENT), TD(TD_PD_ED_CL), COMBO_END};
const uint16_t PROGMEM combo37[] = {TD(TD_EGUI), LT(1,KC_1), COMBO_END};
const uint16_t PROGMEM combo38[] = {MT(MOD_LCTL,KC_QUOT), LT(3,KC_ENT), COMBO_END};
const uint16_t PROGMEM combo39[] = {LT(1,KC_1), LT(2,KC_2), COMBO_END};
const uint16_t PROGMEM combo40[] = {LT(3,KC_SCLN), MT(MOD_LCTL,KC_QUOT), COMBO_END};
const uint16_t PROGMEM combo41[] = {LT(2,KC_2), MT(MOD_LCTL,KC_3), COMBO_END};
const uint16_t PROGMEM combo42[] = {MT(MOD_LALT,KC_ESC), LT(1,KC_SPC), COMBO_END};
const uint16_t PROGMEM combo43[] = {LT(1,KC_SPC), LT(2,KC_ESC), COMBO_END};
const uint16_t PROGMEM combo44[] = {LT(2,KC_TAB), LT(3,KC_GRV), COMBO_END};
const uint16_t PROGMEM combo45[] = {KC_LSFT, KC_RSFT, COMBO_END};

const uint16_t PROGMEM combo46[] = {LT(2,KC_BSLS), TD(TD_PU_HM_L1), COMBO_END};
const uint16_t PROGMEM combo47[] = {LT(1,KC_X), KC_C, LT(1,KC_SPC), COMBO_END};
const uint16_t PROGMEM combo48[] = {KC_C, LT(2,KC_V), LT(1,KC_SPC), COMBO_END};

const uint16_t PROGMEM combo49[] = {LT(2,KC_TAB), LT(1,KC_Q), COMBO_END};
const uint16_t PROGMEM combo50[] = {LT(3,KC_GRV), KC_A, COMBO_END};
const uint16_t PROGMEM combo51[] = {KC_LSFT, LT(2,KC_BSPC), COMBO_END};
const uint16_t PROGMEM combo52[] = {KC_RSFT, LT(2,KC_ESC), COMBO_END};

const uint16_t PROGMEM combo53[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo54[] = {KC_F, LT(1,KC_G), COMBO_END};
const uint16_t PROGMEM combo55[] = {LT(3,KC_R), KC_F, COMBO_END};
const uint16_t PROGMEM combo56[] = {KC_F, LT(2,KC_V), COMBO_END};

const uint16_t PROGMEM combo57[] = {KC_J, KC_M, COMBO_END};
const uint16_t PROGMEM combo58[] = {KC_U, KC_J, COMBO_END};
const uint16_t PROGMEM combo59[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM combo60[] = {KC_J, LT(1,KC_K), COMBO_END};

const uint16_t PROGMEM combo61[] = {LT(1,KC_1), LT(1,KC_Q), COMBO_END};
const uint16_t PROGMEM combo62[] = {LT(2,KC_2), LT(3,KC_W), COMBO_END};
const uint16_t PROGMEM combo63[] = {MT(MOD_LCTL,KC_3), KC_E, COMBO_END};
const uint16_t PROGMEM combo64[] = {MT(MOD_LSFT,KC_4), LT(3,KC_R), COMBO_END};
const uint16_t PROGMEM combo65[] = {MT(MOD_LALT,KC_5), KC_T, COMBO_END};
const uint16_t PROGMEM combo66[] = {MT(MOD_LGUI,KC_6), LT(2,KC_Y), COMBO_END};
const uint16_t PROGMEM combo67[] = {KC_7, KC_U, COMBO_END};
const uint16_t PROGMEM combo68[] = {KC_8, LT(3,KC_I), COMBO_END};
const uint16_t PROGMEM combo69[] = {KC_9, LT(3,KC_I), COMBO_END};
const uint16_t PROGMEM combo70[] = {LT(1,KC_0), KC_O, COMBO_END};
const uint16_t PROGMEM combo71[] = {MT(MOD_LCTL,KC_MINS), LT(2,KC_P), COMBO_END};
const uint16_t PROGMEM combo72[] = {MT(MOD_LSFT,KC_EQL), KC_LBRC, COMBO_END};
const uint16_t PROGMEM combo73[] = {KC_9, KC_O, COMBO_END};
const uint16_t PROGMEM combo74[] = {LT(1,KC_0), LT(2,KC_P), COMBO_END};
const uint16_t PROGMEM combo75[] = {MT(MOD_LCTL,KC_MINS), KC_LBRC, COMBO_END};
const uint16_t PROGMEM combo76[] = {MT(MOD_LSFT,KC_EQL), KC_RBRC, COMBO_END};

const uint16_t PROGMEM combo77[] = {MT(MOD_LCTL,KC_PDOT), LT(2,KC_BSPC), COMBO_END};
const uint16_t PROGMEM combo78[] = {LT(2,KC_BSPC), MT(MOD_LALT,KC_ESC), COMBO_END};

combo_t key_combos[] = {
COMBO(combo0, KC_DEL),
COMBO(combo1, KC_DEL),
COMBO(combo2, LCA(KC_TAB)),
COMBO(combo3, LCA(KC_TAB)),
COMBO(combo4, MEH(KC_TAB)),
COMBO(combo5, MEH(KC_TAB)),
COMBO(combo6, LSFT(KC_TAB)),
COMBO(combo7, LSFT(KC_TAB)),
COMBO(combo8, KC_TAB),
COMBO(combo9, RSG(KC_LEFT)),
COMBO(combo10, RSG(KC_LEFT)),
COMBO(combo11, RSG(KC_RGHT)),
COMBO(combo12, RSG(KC_RGHT)),
COMBO(combo13, TD(TD_F119_GH)),
COMBO(combo14, TD(TD_F119_GH)),
COMBO(combo15, RCS(KC_T)),
COMBO(combo16, LGUI(KC_Z)),
COMBO(combo17, KC_MYCM),

COMBO(combo18, TD(TD_WADD_TSK_CPS)),
COMBO(combo19, TD(TD_WADD_TSK_CPS)),
COMBO(combo20, LALT(KC_ESC)),
COMBO(combo21, LALT(KC_ESC)),
COMBO(combo22, LSA(KC_ESC)),
COMBO(combo23, LSA(KC_ESC)),
COMBO(combo24, TD(TD_LTB_AL)),
COMBO(combo25, TD(TD_LTB_AL)),
COMBO(combo26, TD(TD_RTB_AR)),
COMBO(combo27, TD(TD_RTB_AR)),
COMBO(combo28, TD(TD_NTB_AU)),
COMBO(combo29, TD(TD_NTB_AU)),
COMBO(combo30, TD(TD_CTB_AD)),
COMBO(combo31, TD(TD_CTB_AD)),
COMBO(combo32, RCS(KC_PGUP)),
COMBO(combo33, RCS(KC_PGUP)),
COMBO(combo34, RCS(KC_PGDN)),
COMBO(combo35, RCS(KC_PGDN)),

COMBO(combo36, TD(TD_ENG_GZ)),
COMBO(combo37, TD(TD_ENG_GZ)),
COMBO(combo38, TD(TD_CHS_TOG)),
COMBO(combo39, TD(TD_CHS_TOG)),
COMBO(combo40, TD(TD_JPN_TOG)),
COMBO(combo41, TD(TD_JPN_TOG)),
COMBO(combo42, KC_SPC),
COMBO(combo43, KC_SPC),
COMBO(combo44, KC_PENT),
COMBO(combo45, KC_CAPS),

COMBO(combo46, LCTL(KC_E)),
COMBO(combo47, LCTL(KC_C)),
COMBO(combo48, LCTL(KC_V)),

COMBO(combo49, TD(TD_PU_HM_L1)),
COMBO(combo50, TD(TD_PD_ED_CL)),
COMBO(combo51, TD(TD_PL_F_C)),
COMBO(combo52, TD(TD_PL_F_C)),

COMBO(combo53, LGUI(KC_LEFT)),
COMBO(combo54, LGUI(KC_RGHT)),
COMBO(combo55, LGUI(KC_UP)),
COMBO(combo56, LGUI(KC_DOWN)),

COMBO(combo57, LCTL(KC_MINS)),
COMBO(combo58, LCTL(KC_EQL)),
COMBO(combo59, LCTL(KC_0)),
COMBO(combo60, LCTL(KC_1)),

COMBO(combo61, TD(TD_SF1_VWL)),
COMBO(combo62, TD(TD_SF2_VWR)),
COMBO(combo63, KC_HASH),
COMBO(combo64, KC_DLR),
COMBO(combo65, KC_PERC),
COMBO(combo66, KC_CIRC),
COMBO(combo67, KC_AMPR),
COMBO(combo68, KC_ASTR),
COMBO(combo69, KC_LPRN),
COMBO(combo70, KC_RPRN),
COMBO(combo71, TD(TD_MINS_VWL)),
COMBO(combo72, TD(TD_EQL_VWR)),
COMBO(combo73, KC_LPRN),
COMBO(combo74, KC_RPRN),
COMBO(combo75, TD(TD_MINS_VWL)),
COMBO(combo76, TD(TD_EQL_VWR)),

COMBO(combo77, LALT(KC_LEFT)),
COMBO(combo78, LALT(KC_RGHT)),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	// Default layer
	[0] = LAYOUT_all(
		TD(TD_EGUI), LT(1,KC_1), LT(2,KC_2), MT(MOD_LCTL,KC_3), MT(MOD_LSFT,KC_4), MT(MOD_LALT,KC_5), MT(MOD_LGUI,KC_6), KC_7, KC_8, KC_9, LT(1,KC_0), MT(MOD_LCTL,KC_MINS), MT(MOD_LSFT,KC_EQL), KC_BSPC, KC_BSPC, TD(TD_HM_WWW),
		LT(2,KC_TAB), LT(1,KC_Q), LT(3,KC_W), KC_E, LT(3,KC_R), KC_T, LT(2,KC_Y), KC_U, LT(3,KC_I), KC_O, LT(2,KC_P), KC_LBRC, KC_RBRC, LT(2,KC_BSLS), TD(TD_PU_HM_L1),
		LT(3,KC_GRV), KC_A, KC_S, KC_D, KC_F, LT(1,KC_G), KC_H, KC_J, LT(1,KC_K), KC_L, LT(3,KC_SCLN), MT(MOD_LCTL,KC_QUOT), LT(3,KC_ENT), TD(TD_PD_ED_CL),
		KC_LSFT, KC_LSFT, LT(3,KC_Z), LT(1,KC_X), KC_C, LT(2,KC_V), LT(3,KC_B), KC_N, KC_M, MT(MOD_LALT,KC_COMM), LT(2,KC_DOT), MT(MOD_LCTL,KC_SLSH), KC_RSFT, KC_UP, LT(3,KC_END),
		MT(MOD_LCTL,KC_PDOT), LT(2,KC_BSPC), MT(MOD_LALT,KC_ESC), LT(1,KC_SPC), LT(1,KC_SPC), LT(1,KC_SPC), KC_RALT, LT(2,KC_ESC), KC_LEFT, KC_DOWN, KC_RGHT
	),

	// Fn1 Layer
	[1] = LAYOUT_all(
		KC_F11, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7,KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_END, KC_END, QK_COMBO_TOGGLE,
		LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RGHT)), KC_UP, KC_TRNS, KC_TRNS, LCTL(KC_T), RCS(KC_PGUP), RCS(KC_PGDN), LCTL(LGUI(KC_D)), KC_MYCM, RCS(KC_UP), LCTL(KC_LEFT), LCTL(KC_RGHT), RCS(KC_DOWN), QK_COMBO_ON,
		KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, RCS(KC_TAB), LCTL(KC_W), LCTL(KC_TAB), LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_F4)), LCTL(LGUI(KC_RGHT)), RCS(KC_LEFT), RCS(KC_RGHT), LGUI(KC_TAB), QK_COMBO_OFF,
		LGUI(KC_Z), KC_TRNS, RSG(KC_LEFT), RSG(KC_RGHT), MEH(KC_TAB), LCA(KC_TAB), LGUI(KC_TAB), LCTL(KC_N), LSA(KC_P), LALT(KC_ESC), LSA(KC_ESC), RSG(KC_LEFT), RSG(KC_RGHT), LCTL(KC_EQL), KC_TRNS,
		LALT(KC_ENT), KC_F5, LGUI(KC_H), LGUI(KC_D), LGUI(KC_D), LGUI(KC_D), KC_PSCR, KC_PSCR, LCTL(KC_0), LCTL(KC_MINS), LCTL(KC_1)
    ),

	// Fn2 Layer
	[2] = LAYOUT_all(
		LALT(KC_F4), KC_MYCM, KC_CALC, LCTL(KC_F), KC_PSLS, LALT(KC_LEFT), LALT(KC_RGHT), LSA(KC_8), KC_LSFT, LCTL(KC_C), LCTL(KC_V), LSFT(KC_TAB), KC_TAB, LCTL(KC_A), LCTL(KC_A), KC_MYCM,
		KC_DEL, KC_P7, KC_P8, KC_P9, KC_PAST, RCS(KC_T), KC_TRNS, LSA(KC_7), KC_INS, KC_TRNS, KC_TRNS, RCS(KC_HOME), RCS(KC_END), LCTL(KC_E), RCS(KC_PGUP),
		KC_NUM, KC_P4, KC_P5, KC_P6, KC_PMNS, KC_TRNS, LCTL(KC_H), LSA(KC_9), LALT(KC_GRV), LGUI(KC_L), LALT(KC_UP), LALT(KC_DOWN), LCTL(KC_L), RCS(KC_PGDN),
		KC_P0, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_PPLS, LCTL(KC_B), LSA(KC_1), LSA(KC_2), LSA(KC_Q), LGUI(KC_DOT), LCTL(KC_B), KC_WWW_HOME, LCTL(KC_T), RCS(KC_T),
		KC_WWW_HOME, RCS(KC_T), LCTL(KC_A), KC_PENT, KC_PENT, KC_PENT, LCTL(KC_H), LCTL(KC_H), RCS(KC_TAB), LCTL(KC_W), LCTL(KC_TAB)
	),
	
	// Fn3 Layer
	[3] = LAYOUT_all(
		KC_F11, LALT(KC_LEFT), LALT(KC_RGHT), KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F23, KC_F24,
		KC_HOME, KC_PGUP, KC_UP, LALT(KC_ESC), LSA(KC_ESC), LCTL(KC_EQL), LCTL(KC_1), KC_MPRV, KC_F, KC_MPLY, KC_C, KC_LSFT, LSA(KC_8), LSA(KC_7), MEH(KC_TAB),
		LCTL(KC_L), KC_PGDN, KC_DOWN, KC_TRNS, LCTL(KC_BSLS), LCTL(KC_MINS), LCTL(KC_0), KC_MNXT, KC_MRWD, KC_MFFD, LALT(KC_GRV), LSA(KC_9), LALT(KC_F4), LCA(KC_TAB),
		KC_END, KC_TRNS, KC_LEFT, KC_RGHT, LCTL(KC_C), LCTL(KC_V), QK_BOOT, KC_VOLD, KC_VOLU, LALT(KC_LEFT), LALT(KC_RGHT), LCTL(KC_Z), RCS(KC_Z), TD(TD_GU_VWN), RGB_TOG,
		KC_F7, KC_SLSH, KC_F9, KC_MUTE, KC_MUTE, KC_MUTE, KC_MPLY, KC_MPLY, TD(TD_GL_VWL), TD(TD_GD_VWC), TD(TD_GR_VWR)
	),
};

