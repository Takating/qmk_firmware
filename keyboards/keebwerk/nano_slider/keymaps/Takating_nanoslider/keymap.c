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

// ——— Tap‑dance 状态定义 ———
typedef enum {
    TD_NONE,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_UNKNOWN
} td_state_t;

typedef struct {
  bool is_press_action;
  td_state_t state;
} td_tap_t;

static td_state_t cur_dance(tap_dance_state_t *s) {
  if (s->count == 1) {
    return (s->interrupted || !s->pressed) ? TD_SINGLE_TAP : TD_SINGLE_HOLD;
  } else if (s->count == 2) {
    return (s->interrupted || !s->pressed) ? TD_DOUBLE_TAP : TD_DOUBLE_HOLD;
  }
  return TD_UNKNOWN;
}

#define INIT_TAP_STATE { .is_press_action = true, .state = TD_NONE }

/* TD_MU_TG_CL */
static td_tap_t mu_tg_cl_state = INIT_TAP_STATE;
void mu_tg_cl_finished(tap_dance_state_t *s, void *d) {
  mu_tg_cl_state.state = cur_dance(s);
  switch (mu_tg_cl_state.state) {
    case TD_SINGLE_TAP:  tap_code(KC_MUTE);        break;
    case TD_SINGLE_HOLD: layer_on(_TOGGLE);              break;
    case TD_DOUBLE_TAP:  tap_code16(LALT(KC_F4));  break;
    default: break;
  }
}
void mu_tg_cl_reset(tap_dance_state_t *s, void *d) {
  if (mu_tg_cl_state.state == TD_SINGLE_HOLD) layer_off(_TOGGLE);
  mu_tg_cl_state.state = TD_NONE;
}

/* TD_SP_LN_ET */
static td_tap_t sp_ln_et_state = INIT_TAP_STATE;
void sp_ln_et_finished(tap_dance_state_t *s, void *d) {
  sp_ln_et_state.state = cur_dance(s);
  switch (sp_ln_et_state.state) {
    case TD_SINGLE_TAP:  tap_code(KC_SPC);        break;
    case TD_SINGLE_HOLD: layer_on(_NAV);              break;
    case TD_DOUBLE_TAP:  tap_code(KC_ENT);  break;
    default: break;
  }
}
void sp_ln_et_reset(tap_dance_state_t *s, void *d) {
  if (sp_ln_et_state.state == TD_SINGLE_HOLD) layer_off(_NAV);
  sp_ln_et_state.state = TD_NONE;
}

/* TD_ESC_TSK_GUID */
static td_tap_t esc_tsk_guid_state = INIT_TAP_STATE;
void esc_tsk_guid_finished(tap_dance_state_t *s, void *d) {
  esc_tsk_guid_state.state = cur_dance(s);
  switch (esc_tsk_guid_state.state) {
    case TD_SINGLE_TAP: tap_code(KC_ESC); break;
    case TD_SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LGUI));
      tap_code(KC_TAB);
      break;
    case TD_DOUBLE_TAP: tap_code16(LGUI(KC_D)); break;
    default: break;
  }
}
void esc_tsk_guid_reset(tap_dance_state_t *s, void *d) {
  if (esc_tsk_guid_state.state == TD_SINGLE_HOLD) unregister_mods(MOD_BIT(KC_LGUI));
  esc_tsk_guid_state.state = TD_NONE;
}

/* TD_LTB_GL */
static td_tap_t ltb_gl_state = INIT_TAP_STATE;
void ltb_gl_finished(tap_dance_state_t *s, void *d) {
  ltb_gl_state.state = cur_dance(s);
  switch (ltb_gl_state.state) {
    case TD_SINGLE_TAP: tap_code16(RCS(KC_TAB));   break;
    case TD_SINGLE_HOLD:
    case TD_DOUBLE_TAP: tap_code16(LGUI(KC_LEFT)); break;
    default: break;
  }
}
void ltb_gl_reset(tap_dance_state_t *s, void *d) { ltb_gl_state.state = TD_NONE; }

/* TD_RTB_GR */
static td_tap_t rtb_gr_state = INIT_TAP_STATE;
void rtb_gr_finished(tap_dance_state_t *s, void *d) {
  rtb_gr_state.state = cur_dance(s);
  switch (rtb_gr_state.state) {
    case TD_SINGLE_TAP: tap_code16(LCTL(KC_TAB));  break;
    case TD_SINGLE_HOLD:
    case TD_DOUBLE_TAP: tap_code16(LGUI(KC_RGHT)); break;
    default: break;
  }
}
void rtb_gr_reset(tap_dance_state_t *s, void *d) { rtb_gr_state.state = TD_NONE; }

/* TD_NTB_GU */
static td_tap_t ntb_gu_state = INIT_TAP_STATE;
void ntb_gu_finished(tap_dance_state_t *s, void *d) {
  ntb_gu_state.state = cur_dance(s);
  switch (ntb_gu_state.state) {
    case TD_SINGLE_TAP: tap_code16(LCTL(KC_T));  break;
    case TD_SINGLE_HOLD:
    case TD_DOUBLE_TAP: tap_code16(LGUI(KC_UP)); break;
    default: break;
  }
}
void ntb_gu_reset(tap_dance_state_t *s, void *d) { ntb_gu_state.state = TD_NONE; }

/* TD_CTB_GD */
static td_tap_t ctb_gd_state = INIT_TAP_STATE;
void ctb_gd_finished(tap_dance_state_t *s, void *d) {
  ctb_gd_state.state = cur_dance(s);
  switch (ctb_gd_state.state) {
    case TD_SINGLE_TAP: tap_code16(LCTL(KC_W));    break;
    case TD_SINGLE_HOLD:
    case TD_DOUBLE_TAP: tap_code16(LGUI(KC_DOWN)); break;
    default: break;
  }
}
void ctb_gd_reset(tap_dance_state_t *s, void *d) { ctb_gd_state.state = TD_NONE; }

enum {
    TD_MU_TG_CL = 0,
    TD_SP_LN_ET,
    TD_ESC_TSK_GUID,
    TD_LTB_GL,
    TD_RTB_GR,
    TD_NTB_GU,
    TD_CTB_GD,
    TD_WWW_RCST,
    TD_F_F5,
    TD_C_MYCM
};

// ——— Tap‑dance 动作映射 ———
tap_dance_action_t tap_dance_actions[] = {
    [TD_MU_TG_CL]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mu_tg_cl_finished, mu_tg_cl_reset),
    [TD_SP_LN_ET]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sp_ln_et_finished, sp_ln_et_reset),
    [TD_ESC_TSK_GUID] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_tsk_guid_finished, esc_tsk_guid_reset),
    [TD_LTB_GL]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ltb_gl_finished, ltb_gl_reset),
    [TD_RTB_GR]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rtb_gr_finished, rtb_gr_reset),
    [TD_NTB_GU]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ntb_gu_finished, ntb_gu_reset),
    [TD_CTB_GD]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctb_gd_finished, ctb_gd_reset),
    [TD_WWW_RCST]    = ACTION_TAP_DANCE_DOUBLE(KC_WWW_HOME, RCS(KC_T)),
    [TD_F_F5]        = ACTION_TAP_DANCE_DOUBLE(KC_F, KC_F5),
    [TD_C_MYCM]      = ACTION_TAP_DANCE_DOUBLE(KC_C, KC_MYCM)
};


// Combos setting
const uint16_t PROGMEM combo_meh_tab[]={TD(TD_C_MYCM),LT(_SCALE,KC_LEFT),COMBO_END};
const uint16_t PROGMEM combo_lca_tab[]={TD(TD_F_F5),KC_RGHT,COMBO_END};
const uint16_t PROGMEM combo_lalt_left[]={TD(TD_C_MYCM),KC_UP,COMBO_END};
const uint16_t PROGMEM combo_lalt_right[]={KC_UP,TD(TD_C_MYCM),COMBO_END};
const uint16_t PROGMEM combo_www_rcs_t[]={TD(TD_F_F5),TD(TD_SP_LN_ET),COMBO_END};
const uint16_t PROGMEM combo_esc_tsk_guid[]={KC_RGHT,TD(TD_SP_LN_ET),COMBO_END};
const uint16_t PROGMEM combo_ltb_gl[]={LT(_SCALE,KC_LEFT),KC_DOWN,COMBO_END};
const uint16_t PROGMEM combo_rtb_gr[]={KC_DOWN,KC_RGHT,COMBO_END};
const uint16_t PROGMEM combo_ntb_gu[]={KC_UP,KC_DOWN,COMBO_END};
const uint16_t PROGMEM combo_ctb_gd[]={LT(_SCALE,KC_LEFT),KC_RGHT,COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_meh_tab,MEH(KC_TAB)),
    COMBO(combo_lca_tab,LCA(KC_TAB)),
    COMBO(combo_lalt_left,LALT(KC_LEFT)),
    COMBO(combo_lalt_right,LALT(KC_RGHT)),
    COMBO(combo_www_rcs_t,TD(TD_WWW_RCST)),
    COMBO(combo_esc_tsk_guid,TD(TD_ESC_TSK_GUID)),
    COMBO(combo_ltb_gl,TD(TD_LTB_GL)),
    COMBO(combo_rtb_gr,TD(TD_RTB_GR)),
    COMBO(combo_ntb_gu,TD(TD_NTB_GU)),
    COMBO(combo_ctb_gd,TD(TD_CTB_GD)),
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { // In order to add more volume controls, add here a custom keycode
    DEFAULT= SAFE_RANGE,APP1,APP2,APP3,APP4,APP5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_MEDIA] = LAYOUT(
        TD(TD_MU_TG_CL),
        TD(TD_C_MYCM), KC_UP, TD(TD_F_F5),
        LT(_SCALE, KC_LEFT), KC_DOWN, KC_RGHT, TD(TD_SP_LN_ET)
    ),
    [_NAV] = LAYOUT( 
        LT(_TOGGLE, KC_ESC),
        LSFT(KC_TAB), LCTL(LGUI(KC_D)), KC_TAB,
        LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_F4)), LCTL(LGUI(KC_RGHT)), KC_NO
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
        KC_TRNS, LCTL(KC_MINS), LCTL(KC_0), KC_NO      
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
