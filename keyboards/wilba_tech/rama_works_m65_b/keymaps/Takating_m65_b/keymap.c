#include QMK_KEYBOARD_H
typedef enum {TD_NONE,TD_SINGLE_TAP,TD_SINGLE_HOLD,TD_DOUBLE_TAP,TD_DOUBLE_HOLD,TD_DOUBLE_SINGLE_TAP,TD_UNKNOWN} td_state_t;
typedef struct {bool is_press_action;td_state_t state;} td_tap_t;
static td_state_t cur_dance(tap_dance_state_t *s) {if (s->count == 1) {return (s->interrupted || !s->pressed) ? TD_SINGLE_TAP : TD_SINGLE_HOLD;} else if (s->count == 2) {return (s->interrupted || !s->pressed) ? TD_DOUBLE_TAP : TD_DOUBLE_HOLD;}return TD_UNKNOWN;}
static td_state_t cur_dance2(tap_dance_state_t *s) {if (s->count == 1) {return (s->interrupted || !s->pressed) ? TD_SINGLE_TAP : TD_SINGLE_HOLD;} else if (s->count == 2) {return TD_DOUBLE_SINGLE_TAP;}return TD_UNKNOWN;}
#define INIT_TAP_STATE { .is_press_action = true, .state = TD_NONE }
static td_tap_t egui_gh_state=INIT_TAP_STATE;void egui_gh_finished(tap_dance_state_t*s,void*d){egui_gh_state.state=cur_dance(s);switch(egui_gh_state.state){case TD_SINGLE_TAP:tap_code(KC_ESC);break;case TD_SINGLE_HOLD:register_code(KC_LGUI);break;case TD_DOUBLE_TAP:tap_code16(LGUI(KC_H));break;case TD_DOUBLE_HOLD:tap_code(KC_PSCR);break;default:break;}}void egui_gh_reset(tap_dance_state_t*s,void*d){if(egui_gh_state.state==TD_SINGLE_HOLD)unregister_code(KC_LGUI);egui_gh_state.state=TD_NONE;}
static td_tap_t hm_www_state=INIT_TAP_STATE;void hm_www_finished(tap_dance_state_t*s,void*d){hm_www_state.state=cur_dance(s);switch(hm_www_state.state){case TD_SINGLE_TAP:tap_code(KC_HOME);break;case TD_SINGLE_HOLD:layer_on(1);break;case TD_DOUBLE_TAP:tap_code16(KC_WWW_HOME);break;default:break;}}void hm_www_reset(tap_dance_state_t*s,void*d){if(hm_www_state.state==TD_SINGLE_HOLD)layer_off(1);hm_www_state.state=TD_NONE;}
static td_tap_t adb_tsk_cps_state=INIT_TAP_STATE;void adb_tsk_cps_finished(tap_dance_state_t*s,void*d){adb_tsk_cps_state.state=cur_dance(s);switch(adb_tsk_cps_state.state){case TD_SINGLE_TAP:tap_code16(LCTL(KC_L));break;case TD_SINGLE_HOLD:register_mods(MOD_BIT(KC_LGUI));tap_code(KC_TAB);break;case TD_DOUBLE_TAP:tap_code(KC_CAPS);break;default:break;}}void adb_tsk_cps_reset(tap_dance_state_t*s,void*d){if(adb_tsk_cps_state.state==TD_SINGLE_HOLD)unregister_mods(MOD_BIT(KC_LGUI));adb_tsk_cps_state.state=TD_NONE;}
static td_tap_t eng_btn2_f5_state=INIT_TAP_STATE;void eng_btn2_f5_finished(tap_dance_state_t*s,void*d){eng_btn2_f5_state.state=cur_dance(s);switch(eng_btn2_f5_state.state){case TD_SINGLE_TAP:tap_code16(LSA(KC_7));break;case TD_SINGLE_HOLD:tap_code(KC_APP);break;case TD_DOUBLE_TAP:tap_code(KC_F5);break;default:break;}}void eng_btn2_f5_reset(tap_dance_state_t*s,void*d){eng_btn2_f5_state.state=TD_NONE;}
static td_tap_t chs_tog_state=INIT_TAP_STATE;void chs_tog_finished(tap_dance_state_t*s,void*d){chs_tog_state.state=cur_dance(s);switch(chs_tog_state.state){case TD_SINGLE_TAP:tap_code16(LSA(KC_8));break;case TD_SINGLE_HOLD:case TD_DOUBLE_TAP:tap_code(KC_LSFT);break;default:break;}}void chs_tog_reset(tap_dance_state_t*s,void*d){chs_tog_state.state=TD_NONE;}
static td_tap_t jpn_tog_state=INIT_TAP_STATE;void jpn_tog_finished(tap_dance_state_t*s,void*d){jpn_tog_state.state=cur_dance(s);switch(jpn_tog_state.state){case TD_SINGLE_TAP:tap_code16(LSA(KC_9));break;case TD_SINGLE_HOLD:case TD_DOUBLE_TAP:tap_code16(LALT(KC_GRV));break;default:break;}}void jpn_tog_reset(tap_dance_state_t*s,void*d){jpn_tog_state.state=TD_NONE;}
static td_tap_t ltb_gl_state=INIT_TAP_STATE;void ltb_gl_finished(tap_dance_state_t*s,void*d){ltb_gl_state.state=cur_dance(s);switch(ltb_gl_state.state){case TD_SINGLE_TAP:tap_code16(RCS(KC_TAB));break;case TD_SINGLE_HOLD:case TD_DOUBLE_TAP:tap_code16(LGUI(KC_LEFT));break;default:break;}}void ltb_gl_reset(tap_dance_state_t*s,void*d){ltb_gl_state.state=TD_NONE;}
static td_tap_t rtb_gr_state=INIT_TAP_STATE;void rtb_gr_finished(tap_dance_state_t*s,void*d){rtb_gr_state.state=cur_dance(s);switch(rtb_gr_state.state){case TD_SINGLE_TAP:tap_code16(LCTL(KC_TAB));break;case TD_SINGLE_HOLD:case TD_DOUBLE_TAP:tap_code16(LGUI(KC_RGHT));break;default:break;}}void rtb_gr_reset(tap_dance_state_t*s,void*d){rtb_gr_state.state=TD_NONE;}
static td_tap_t ntb_gu_state=INIT_TAP_STATE;void ntb_gu_finished(tap_dance_state_t*s,void*d){ntb_gu_state.state=cur_dance(s);switch(ntb_gu_state.state){case TD_SINGLE_TAP:tap_code16(LCTL(KC_T));break;case TD_SINGLE_HOLD:case TD_DOUBLE_TAP:tap_code16(LGUI(KC_UP));break;default:break;}}void ntb_gu_reset(tap_dance_state_t*s,void*d){ntb_gu_state.state=TD_NONE;}
static td_tap_t ctb_gd_state=INIT_TAP_STATE;void ctb_gd_finished(tap_dance_state_t*s,void*d){ctb_gd_state.state=cur_dance(s);switch(ctb_gd_state.state){case TD_SINGLE_TAP:tap_code16(LCTL(KC_W));break;case TD_SINGLE_HOLD:case TD_DOUBLE_TAP:tap_code16(LGUI(KC_DOWN));break;default:break;}}void ctb_gd_reset(tap_dance_state_t*s,void*d){ctb_gd_state.state=TD_NONE;}
static td_tap_t f119_gh_state=INIT_TAP_STATE;void f119_gh_finished(tap_dance_state_t*s,void*d){f119_gh_state.state=cur_dance(s);switch(f119_gh_state.state){case TD_SINGLE_TAP:tap_code(KC_F11);break;case TD_SINGLE_HOLD:register_mods(MOD_BIT(KC_LGUI));tap_code(KC_H);break;case TD_DOUBLE_TAP:tap_code(KC_F9);break;default:break;}}void f119_gh_reset(tap_dance_state_t*s,void*d){if(f119_gh_state.state==TD_SINGLE_HOLD)unregister_mods(MOD_BIT(KC_LGUI));f119_gh_state.state=TD_NONE;}
static td_tap_t pu_hm_l2_state=INIT_TAP_STATE;void pu_hm_l2_finished(tap_dance_state_t*s,void*d){pu_hm_l2_state.state=cur_dance(s);switch(pu_hm_l2_state.state){case TD_SINGLE_TAP:tap_code(KC_PGUP);break;case TD_SINGLE_HOLD:layer_on(2);break;case TD_DOUBLE_TAP:tap_code(KC_HOME);break;default:break;}}void pu_hm_l2_reset(tap_dance_state_t*s,void*d){if(pu_hm_l2_state.state==TD_SINGLE_HOLD)layer_off(2);pu_hm_l2_state.state=TD_NONE;}
static td_tap_t pd_ed_rctl_state=INIT_TAP_STATE;void pd_ed_rctl_finished(tap_dance_state_t*s,void*d){pd_ed_rctl_state.state=cur_dance(s);switch(pd_ed_rctl_state.state){case TD_SINGLE_TAP:tap_code(KC_PGDN);break;case TD_SINGLE_HOLD:register_mods(MOD_BIT(KC_RCTL));break;case TD_DOUBLE_TAP:tap_code(KC_END);break;default:break;}}void pd_ed_rctl_reset(tap_dance_state_t*s,void*d){if(pd_ed_rctl_state.state==TD_SINGLE_HOLD)unregister_mods(MOD_BIT(KC_RCTL));pd_ed_rctl_state.state=TD_NONE;}
static td_tap_t ply_f_c_state=INIT_TAP_STATE;void ply_f_c_finished(tap_dance_state_t*s,void*d){ply_f_c_state.state=cur_dance(s);switch(ply_f_c_state.state){case TD_SINGLE_TAP:tap_code(KC_MPLY);break;case TD_SINGLE_HOLD:tap_code(KC_F);break;case TD_DOUBLE_TAP:tap_code(KC_C);break;default:break;}}void ply_f_c_reset(tap_dance_state_t*s,void*d){ply_f_c_state.state=TD_NONE;}
static td_tap_t pap_swl_state=INIT_TAP_STATE;void pap_swl_finished(tap_dance_state_t*s,void*d){pap_swl_state.state=cur_dance(s);switch(pap_swl_state.state){case TD_SINGLE_TAP:tap_code16(LALT(KC_ESC));break;case TD_SINGLE_HOLD:case TD_DOUBLE_TAP:tap_code16(RSG(KC_LEFT));break;default:break;}}void pap_swl_reset(tap_dance_state_t*s,void*d){pap_swl_state.state=TD_NONE;}
static td_tap_t nap_swr_state=INIT_TAP_STATE;void nap_swr_finished(tap_dance_state_t*s,void*d){nap_swr_state.state=cur_dance(s);switch(nap_swr_state.state){case TD_SINGLE_TAP:tap_code16(LSA(KC_ESC));break;case TD_SINGLE_HOLD:case TD_DOUBLE_TAP:tap_code16(RSG(KC_RGHT));break;default:break;}}void nap_swr_reset(tap_dance_state_t*s,void*d){nap_swr_state.state=TD_NONE;}
static td_tap_t quot_al_squo_state=INIT_TAP_STATE;void quot_al_squo_finished(tap_dance_state_t*s,void*d){quot_al_squo_state.state=cur_dance(s);switch(quot_al_squo_state.state){case TD_SINGLE_TAP:tap_code(KC_QUOT);break;case TD_SINGLE_HOLD:register_code(KC_LALT);break;case TD_DOUBLE_TAP:tap_code16(LSFT(KC_QUOT));break;default:break;}}void quot_al_squo_reset(tap_dance_state_t*s,void*d){if(quot_al_squo_state.state==TD_SINGLE_HOLD)unregister_code(KC_LALT);quot_al_squo_state.state=TD_NONE;}
static td_tap_t slsh_cl_quest_state=INIT_TAP_STATE;void slsh_cl_quest_finished(tap_dance_state_t*s,void*d){slsh_cl_quest_state.state=cur_dance(s);switch(slsh_cl_quest_state.state){case TD_SINGLE_TAP:tap_code(KC_SLSH);break;case TD_SINGLE_HOLD:register_code(KC_LCTL);break;case TD_DOUBLE_TAP:tap_code16(LSFT(KC_SLSH));break;default:break;}}void slsh_cl_quest_reset(tap_dance_state_t*s,void*d){if(slsh_cl_quest_state.state==TD_SINGLE_HOLD)unregister_code(KC_LCTL);slsh_cl_quest_state.state=TD_NONE;}
static td_tap_t pent_cl_num_state=INIT_TAP_STATE;void pent_cl_num_finished(tap_dance_state_t*s,void*d){pent_cl_num_state.state=cur_dance(s);switch(pent_cl_num_state.state){case TD_SINGLE_TAP:tap_code(KC_PENT);break;case TD_SINGLE_HOLD:register_code(KC_LCTL);break;case TD_DOUBLE_TAP:tap_code(KC_NUM);break;default:break;}}void pent_cl_num_reset(tap_dance_state_t*s,void*d){if(pent_cl_num_state.state==TD_SINGLE_HOLD)unregister_code(KC_LCTL);pent_cl_num_state.state=TD_NONE;}
static td_tap_t p0_rcs_del_state=INIT_TAP_STATE;void p0_rcs_del_finished(tap_dance_state_t*s,void*d){p0_rcs_del_state.state=cur_dance(s);switch(p0_rcs_del_state.state){case TD_SINGLE_TAP:tap_code(KC_P0);break;case TD_SINGLE_HOLD:register_mods(MOD_BIT(KC_RCTL)|MOD_BIT(KC_RSFT));break;case TD_DOUBLE_TAP:tap_code(KC_DEL);break;default:break;}}void p0_rcs_del_reset(tap_dance_state_t*s,void*d){if(p0_rcs_del_state.state==TD_SINGLE_HOLD)unregister_mods(MOD_BIT(KC_RCTL)|MOD_BIT(KC_RSFT));p0_rcs_del_state.state=TD_NONE;}
static td_tap_t exlm_vwl_state=INIT_TAP_STATE;void exlm_vwl_finished(tap_dance_state_t*s,void*d){exlm_vwl_state.state=cur_dance2(s);switch(exlm_vwl_state.state){case TD_SINGLE_TAP:tap_code16(KC_EXLM);break;case TD_SINGLE_HOLD:tap_code16(LCTL(LGUI(KC_LEFT)));break;case TD_DOUBLE_SINGLE_TAP:tap_code16(KC_EXLM);register_code16(KC_EXLM);break;default:break;}}void exlm_vwl_reset(tap_dance_state_t*s,void*d){if(exlm_vwl_state.state==TD_DOUBLE_SINGLE_TAP)unregister_code16(KC_EXLM);exlm_vwl_state.state=TD_NONE;}
static td_tap_t atm_vwr_state=INIT_TAP_STATE;void atm_vwr_finished(tap_dance_state_t*s,void*d){atm_vwr_state.state=cur_dance2(s);switch(atm_vwr_state.state){case TD_SINGLE_TAP:tap_code16(KC_AT);break;case TD_SINGLE_HOLD:tap_code16(LCTL(LGUI(KC_RGHT)));break;case TD_DOUBLE_SINGLE_TAP:tap_code16(KC_AT);register_code16(KC_AT);break;default:break;}}void atm_vwr_reset(tap_dance_state_t*s,void*d){if(atm_vwr_state.state==TD_DOUBLE_SINGLE_TAP)unregister_code16(KC_AT);atm_vwr_state.state=TD_NONE;}
static td_tap_t mins_vwl_state=INIT_TAP_STATE;void mins_vwl_finished(tap_dance_state_t*s,void*d){mins_vwl_state.state=cur_dance2(s);switch(mins_vwl_state.state){case TD_SINGLE_TAP:tap_code16(KC_UNDS);break;case TD_SINGLE_HOLD:tap_code16(LCTL(LGUI(KC_LEFT)));break;case TD_DOUBLE_SINGLE_TAP:tap_code16(KC_UNDS);register_code16(KC_UNDS);break;default:break;}}void mins_vwl_reset(tap_dance_state_t*s,void*d){if(mins_vwl_state.state==TD_DOUBLE_SINGLE_TAP)unregister_code16(KC_UNDS);mins_vwl_state.state=TD_NONE;}
static td_tap_t eql_vwr_state=INIT_TAP_STATE;void eql_vwr_finished(tap_dance_state_t*s,void*d){eql_vwr_state.state=cur_dance2(s);switch(eql_vwr_state.state){case TD_SINGLE_TAP:tap_code16(KC_PLUS);break;case TD_SINGLE_HOLD:tap_code16(LCTL(LGUI(KC_RGHT)));break;case TD_DOUBLE_SINGLE_TAP:tap_code16(KC_PLUS);register_code16(KC_PLUS);break;default:break;}}void eql_vwr_reset(tap_dance_state_t*s,void*d){if(eql_vwr_state.state==TD_DOUBLE_SINGLE_TAP)unregister_code16(KC_PLUS);eql_vwr_state.state=TD_NONE;}
static td_tap_t rcsh_spc_state=INIT_TAP_STATE;void rcsh_spc_finished(tap_dance_state_t*s,void*d){rcsh_spc_state.state=cur_dance(s);switch(rcsh_spc_state.state){case TD_SINGLE_TAP:tap_code16(RCS(KC_HOME));break;case TD_SINGLE_HOLD:register_code(KC_SPC);break;default:break;}}void rcsh_spc_reset(tap_dance_state_t*s,void*d){if(rcsh_spc_state.state==TD_SINGLE_HOLD)unregister_code(KC_SPC);rcsh_spc_state.state=TD_NONE;}
static td_tap_t rcse_spc_state=INIT_TAP_STATE;void rcse_spc_finished(tap_dance_state_t*s,void*d){rcse_spc_state.state=cur_dance(s);switch(rcse_spc_state.state){case TD_SINGLE_TAP:tap_code16(RCS(KC_END));break;case TD_SINGLE_HOLD:register_code(KC_SPC);break;default:break;}}void rcse_spc_reset(tap_dance_state_t*s,void*d){if(rcse_spc_state.state==TD_SINGLE_HOLD)unregister_code(KC_SPC);rcse_spc_state.state=TD_NONE;}
enum{TD_EGUI_GH=0,TD_HM_WWW,TD_ADB_TSK_CPS,TD_ENG_BTN2_F5,TD_CHS_TOG,TD_JPN_TOG,TD_LTB_GL,TD_RTB_GR,TD_NTB_GU,TD_CTB_GD,TD_F119_GH,TD_PU_HM_L2,TD_PD_ED_RCTL,TD_PLY_F_C,TD_PAP_SWL,TD_NAP_SWR,TD_QUOT_AL_SQUO,TD_SLSH_CL_QUEST,TD_PENT_CL_NUM,TD_P0_RCS_DEL,TD_EXLM_VWL,TD_ATM_VWR,TD_MINS_VWL,TD_EQL_VWR,TD_RCSH_SPC,TD_RCSE_SPC,TD_SELTEX_BFALL,TD_SELTEX_AFALL};
tap_dance_action_t tap_dance_actions[]={
[TD_EGUI_GH]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,egui_gh_finished,egui_gh_reset),
[TD_HM_WWW]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,hm_www_finished,hm_www_reset),
[TD_ADB_TSK_CPS]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,adb_tsk_cps_finished,adb_tsk_cps_reset),
[TD_ENG_BTN2_F5]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,eng_btn2_f5_finished,eng_btn2_f5_reset),
[TD_CHS_TOG]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,chs_tog_finished,chs_tog_reset),
[TD_JPN_TOG]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,jpn_tog_finished,jpn_tog_reset),
[TD_LTB_GL]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,ltb_gl_finished,ltb_gl_reset),
[TD_RTB_GR]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,rtb_gr_finished,rtb_gr_reset),
[TD_NTB_GU]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,ntb_gu_finished,ntb_gu_reset),
[TD_CTB_GD]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,ctb_gd_finished,ctb_gd_reset),
[TD_F119_GH]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,f119_gh_finished,f119_gh_reset),
[TD_PU_HM_L2]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,pu_hm_l2_finished,pu_hm_l2_reset),
[TD_PD_ED_RCTL]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,pd_ed_rctl_finished,pd_ed_rctl_reset),
[TD_PLY_F_C]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,ply_f_c_finished,ply_f_c_reset),
[TD_PAP_SWL]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,pap_swl_finished,pap_swl_reset),
[TD_NAP_SWR]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,nap_swr_finished,nap_swr_reset),
[TD_QUOT_AL_SQUO]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,quot_al_squo_finished,quot_al_squo_reset),
[TD_SLSH_CL_QUEST]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,slsh_cl_quest_finished,slsh_cl_quest_reset),
[TD_PENT_CL_NUM]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,pent_cl_num_finished,pent_cl_num_reset),
[TD_P0_RCS_DEL]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,p0_rcs_del_finished,p0_rcs_del_reset),
[TD_EXLM_VWL]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,exlm_vwl_finished,exlm_vwl_reset),
[TD_ATM_VWR]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,atm_vwr_finished,atm_vwr_reset),
[TD_MINS_VWL]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,mins_vwl_finished,mins_vwl_reset),
[TD_EQL_VWR]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,eql_vwr_finished,eql_vwr_reset),
[TD_RCSH_SPC]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,rcsh_spc_finished,rcsh_spc_reset),
[TD_RCSE_SPC]=ACTION_TAP_DANCE_FN_ADVANCED(NULL,rcse_spc_finished,rcse_spc_reset),
[TD_SELTEX_BFALL]=ACTION_TAP_DANCE_DOUBLE(RCS(KC_LEFT),RCS(KC_HOME)),
[TD_SELTEX_AFALL]=ACTION_TAP_DANCE_DOUBLE(RCS(KC_RGHT),RCS(KC_END))
};
const uint16_t PROGMEM combo_del_1[]={TD(TD_EGUI_GH),LT(1,KC_1),LT(1,KC_Q),COMBO_END};
const uint16_t PROGMEM combo_del_2[]={KC_BSPC,TD(TD_HM_WWW),COMBO_END};
const uint16_t PROGMEM combo_lca_tab_1[]={LT(3,KC_W),LT(2,KC_S),COMBO_END};
const uint16_t PROGMEM combo_lca_tab_2[]={LT(2,KC_BSLS),LT(3,KC_ENT),COMBO_END};
const uint16_t PROGMEM combo_meh_tab_1[]={KC_RBRC,TD(TD_QUOT_AL_SQUO),COMBO_END};
const uint16_t PROGMEM combo_meh_tab_2[]={LT(1,KC_Q),KC_A,COMBO_END};
const uint16_t PROGMEM combo_sft_tab_1[]={TD(TD_EGUI_GH),LT(2,KC_TAB),COMBO_END};
const uint16_t PROGMEM combo_sft_tab_2[]={KC_BSPC,KC_RBRC,COMBO_END};
const uint16_t PROGMEM combo_sft_tab_3[]={LT(3,KC_BSPC),KC_RBRC,COMBO_END};
const uint16_t PROGMEM combo_tab_1[]={KC_BSPC,LT(2,KC_BSLS),COMBO_END};
const uint16_t PROGMEM combo_lalt_left_1[]={LT(3,KC_Z),LT(1,KC_X),COMBO_END};
const uint16_t PROGMEM combo_lalt_left_2[]={KC_COMM,LT(2,KC_DOT),COMBO_END};
const uint16_t PROGMEM combo_lalt_right_1[]={LT(1,KC_X),KC_C,COMBO_END};
const uint16_t PROGMEM combo_lalt_right_2[]={LT(2,KC_DOT),TD(TD_SLSH_CL_QUEST),COMBO_END};
const uint16_t PROGMEM combo_f119_1[]={LT(3,KC_Z),MT(MOD_LALT,KC_ESC),COMBO_END};
const uint16_t PROGMEM combo_f119_2[]={TD(TD_SLSH_CL_QUEST),LT(2,KC_ESC),COMBO_END};
const uint16_t PROGMEM combo_rcs_t[]={TD(TD_PU_HM_L2),TD(TD_PD_ED_RCTL),COMBO_END};
const uint16_t PROGMEM combo_lgui_z[]={KC_LSFT,LT(3,KC_Z),COMBO_END};
const uint16_t PROGMEM combo_mycm_1[]={LT(2,KC_BSLS),TD(TD_HM_WWW),COMBO_END};
const uint16_t PROGMEM combo_mycm_2[]={TD(TD_EGUI_GH),LT(1,KC_Q),COMBO_END};
const uint16_t PROGMEM combo_adb_tsk_cps_1[]={LT(3,KC_GRV),KC_LSFT,COMBO_END};
const uint16_t PROGMEM combo_adb_tsk_cps_2[]={LT(3,KC_ENT),KC_RSFT,COMBO_END};
const uint16_t PROGMEM combo_pap_swl_1[]={LT(1,KC_Q),LT(3,KC_W),COMBO_END};
const uint16_t PROGMEM combo_pap_swl_2[]={KC_LBRC,KC_RBRC,COMBO_END};
const uint16_t PROGMEM combo_nap_swr_1[]={LT(3,KC_W),KC_E,COMBO_END};
const uint16_t PROGMEM combo_nap_swr_2[]={KC_RBRC,LT(2,KC_BSLS),COMBO_END};
const uint16_t PROGMEM combo_ltb_gl_1[]={KC_A,LT(2,KC_S),COMBO_END};
const uint16_t PROGMEM combo_ltb_gl_2[]={KC_LEFT,KC_DOWN,COMBO_END};
const uint16_t PROGMEM combo_rtb_gr_1[]={LT(2,KC_S),KC_D,COMBO_END};
const uint16_t PROGMEM combo_rtb_gr_2[]={KC_DOWN,KC_RGHT,COMBO_END};
const uint16_t PROGMEM combo_ntb_gu_1[]={KC_E,KC_D,COMBO_END};
const uint16_t PROGMEM combo_ntb_gu_2[]={KC_UP,KC_DOWN,COMBO_END};
const uint16_t PROGMEM combo_ctb_gd_1[]={KC_D,KC_C,COMBO_END};
const uint16_t PROGMEM combo_ctb_gd_2[]={KC_LEFT,KC_RGHT,COMBO_END};
const uint16_t PROGMEM combo_rcs_pgup_1[]={KC_A,LT(3,KC_Z),COMBO_END};
const uint16_t PROGMEM combo_rcs_pgup_2[]={KC_RSFT,KC_UP,COMBO_END};
const uint16_t PROGMEM combo_rcs_pgdn_1[]={LT(2,KC_S),LT(1,KC_X),COMBO_END};
const uint16_t PROGMEM combo_rcs_pgdn_2[]={KC_UP,MT(MOD_RALT,KC_END),COMBO_END};
const uint16_t PROGMEM combo_eng_btn2_f5_1[]={TD(TD_QUOT_AL_SQUO),LT(3,KC_ENT),COMBO_END};
const uint16_t PROGMEM combo_eng_btn2_f5_2[]={TD(TD_EGUI_GH),LT(1,KC_1),COMBO_END};
const uint16_t PROGMEM combo_chs_tog_1[]={TD(TD_QUOT_AL_SQUO),TD(TD_SLSH_CL_QUEST),COMBO_END};
const uint16_t PROGMEM combo_chs_tog_2[]={LT(1,KC_1),LT(2,KC_2),COMBO_END};
const uint16_t PROGMEM combo_jpn_tog_1[]={LT(3,KC_SCLN),TD(TD_QUOT_AL_SQUO),COMBO_END};
const uint16_t PROGMEM combo_jpn_tog_2[]={LT(2,KC_2),MT(MOD_LCTL,KC_3),COMBO_END};
const uint16_t PROGMEM combo_pent_cl_num[]={LT(2,KC_TAB),LT(3,KC_GRV),COMBO_END};
const uint16_t PROGMEM combo_caps[]={KC_LSFT,KC_RSFT,COMBO_END};
const uint16_t PROGMEM combo_lctl_e[]={LT(2,KC_BSLS),TD(TD_PU_HM_L2),COMBO_END};
const uint16_t PROGMEM combo_lctl_c_1[]={KC_C,LT(1,KC_SPC),COMBO_END};
const uint16_t PROGMEM combo_lctl_c_2[]={LT(2,KC_DOT),LT(1,KC_SPC),COMBO_END};
const uint16_t PROGMEM combo_lctl_v_1[]={LT(2,KC_V),LT(1,KC_SPC),COMBO_END};
const uint16_t PROGMEM combo_lctl_v_2[]={TD(TD_SLSH_CL_QUEST),LT(1,KC_SPC),COMBO_END};
const uint16_t PROGMEM combo_lctl_x_1[]={LT(1,KC_X),LT(1,KC_SPC),COMBO_END};
const uint16_t PROGMEM combo_lctl_x_2[]={KC_COMM,LT(1,KC_SPC),COMBO_END};
const uint16_t PROGMEM combo_pu_hm_l2[]={LT(2,KC_TAB),LT(1,KC_Q),COMBO_END};
const uint16_t PROGMEM combo_pd_ed_rctl[]={LT(3,KC_GRV),KC_A,COMBO_END};
const uint16_t PROGMEM combo_ply_f_c_1[]={KC_LSFT,LT(2,KC_BSPC),COMBO_END};
const uint16_t PROGMEM combo_ply_f_c_2[]={KC_RSFT,LT(2,KC_ESC),COMBO_END};
const uint16_t PROGMEM combo_kc_left[]={KC_D,KC_F,COMBO_END};
const uint16_t PROGMEM combo_kc_right[]={KC_F,LT(1,KC_G),COMBO_END};
const uint16_t PROGMEM combo_kc_up[]={LT(3,KC_R),KC_F,COMBO_END};
const uint16_t PROGMEM combo_kc_down[]={KC_F,LT(2,KC_V),COMBO_END};
const uint16_t PROGMEM combo_lctl_mins_1[]={KC_J,KC_M,COMBO_END};
const uint16_t PROGMEM combo_lctl_mins_2[]={KC_J,KC_N,COMBO_END};
const uint16_t PROGMEM combo_lctl_eql_1[]={KC_U,KC_J,COMBO_END};
const uint16_t PROGMEM combo_lctl_eql_2[]={KC_I,KC_J,COMBO_END};
const uint16_t PROGMEM combo_lctl_0[]={KC_H,KC_J,COMBO_END};
const uint16_t PROGMEM combo_lctl_1[]={KC_J,LT(1,KC_K),COMBO_END};
const uint16_t PROGMEM combo_exlm_vwl[]={LT(1,KC_1),LT(1,KC_Q),COMBO_END};
const uint16_t PROGMEM combo_atm_vwr[]={LT(2,KC_2),LT(3,KC_W),COMBO_END};
const uint16_t PROGMEM combo_hash[]={MT(MOD_LCTL,KC_3),KC_E,COMBO_END};
const uint16_t PROGMEM combo_dollar[]={MT(MOD_LSFT,KC_4),LT(3,KC_R),COMBO_END};
const uint16_t PROGMEM combo_percent[]={MT(MOD_LALT,KC_5),KC_T,COMBO_END};
const uint16_t PROGMEM combo_caret[]={MT(MOD_LGUI,KC_6),LT(2,KC_Y),COMBO_END};
const uint16_t PROGMEM combo_ampersand_1[]={KC_7,KC_U,COMBO_END};
const uint16_t PROGMEM combo_ampersand_2[]={KC_7,LT(2,KC_Y),COMBO_END};
const uint16_t PROGMEM combo_asterisk_1[]={KC_8,LT(3,KC_I),COMBO_END};
const uint16_t PROGMEM combo_asterisk_2[]={KC_8,KC_U,COMBO_END};
const uint16_t PROGMEM combo_lprn_1[]={KC_9,LT(3,KC_I),COMBO_END};
const uint16_t PROGMEM combo_lprn_2[]={KC_9,KC_O,COMBO_END};
const uint16_t PROGMEM combo_rprn_1[]={LT(1,KC_0),KC_O,COMBO_END};
const uint16_t PROGMEM combo_rprn_2[]={LT(1,KC_0),LT(2,KC_P),COMBO_END};
const uint16_t PROGMEM combo_mins_vwl_1[]={MT(MOD_LCTL,KC_MINS),LT(2,KC_P),COMBO_END};
const uint16_t PROGMEM combo_mins_vwl_2[]={MT(MOD_LCTL,KC_MINS),KC_LBRC,COMBO_END};
const uint16_t PROGMEM combo_eql_vwr_1[]={MT(MOD_LSFT,KC_EQL),KC_LBRC,COMBO_END};
const uint16_t PROGMEM combo_eql_vwr_2[]={MT(MOD_LSFT,KC_EQL),KC_RBRC,COMBO_END};
const uint16_t PROGMEM combo_home[]={MT(MOD_LCTL,KC_PDOT),LT(2,KC_BSPC),COMBO_END};
const uint16_t PROGMEM combo_end[]={LT(2,KC_BSPC),MT(MOD_LALT,KC_ESC),COMBO_END};
const uint16_t PROGMEM combo_lalt_f4[]={TD(TD_HM_WWW),TD(TD_PU_HM_L2),COMBO_END};
const uint16_t PROGMEM combo_p0_rcs_del[]={KC_LSFT,MT(MOD_LCTL,KC_PDOT),COMBO_END};
const uint16_t PROGMEM combo_rcsh_spc[]={MT(MOD_LALT,KC_ESC),LT(1,KC_SPC),COMBO_END};
const uint16_t PROGMEM combo_rcse_spc[]={LT(2,KC_ESC),LT(1,KC_SPC),COMBO_END};
combo_t key_combos[]={ 
    COMBO(combo_del_1,KC_DEL),COMBO(combo_del_2,KC_DEL),
    COMBO(combo_lca_tab_1,LCA(KC_TAB)),COMBO(combo_lca_tab_2,LCA(KC_TAB)),
    COMBO(combo_meh_tab_1,MEH(KC_TAB)),COMBO(combo_meh_tab_2,MEH(KC_TAB)),
    COMBO(combo_sft_tab_1,LSFT(KC_TAB)),COMBO(combo_sft_tab_2,LSFT(KC_TAB)),
    COMBO(combo_sft_tab_3,LSFT(KC_TAB)),COMBO(combo_tab_1,KC_TAB),
    COMBO(combo_lalt_left_1,LALT(KC_LEFT)),COMBO(combo_lalt_left_2,LALT(KC_LEFT)),
    COMBO(combo_lalt_right_1,LALT(KC_RGHT)),COMBO(combo_lalt_right_2,LALT(KC_RGHT)),
    COMBO(combo_f119_1,TD(TD_F119_GH)),COMBO(combo_f119_2,TD(TD_F119_GH)),
    COMBO(combo_rcs_t,RCS(KC_T)),COMBO(combo_lgui_z,LGUI(KC_Z)),
    COMBO(combo_mycm_1,KC_MYCM),COMBO(combo_mycm_2,KC_MYCM),
    COMBO(combo_adb_tsk_cps_1,TD(TD_ADB_TSK_CPS)),COMBO(combo_adb_tsk_cps_2,TD(TD_ADB_TSK_CPS)),
    COMBO(combo_pap_swl_1,TD(TD_PAP_SWL)),COMBO(combo_pap_swl_2,TD(TD_PAP_SWL)),
    COMBO(combo_nap_swr_1,TD(TD_NAP_SWR)),COMBO(combo_nap_swr_2,TD(TD_NAP_SWR)),
    COMBO(combo_ltb_gl_1,TD(TD_LTB_GL)),COMBO(combo_ltb_gl_2,TD(TD_LTB_GL)),
    COMBO(combo_rtb_gr_1,TD(TD_RTB_GR)),COMBO(combo_rtb_gr_2,TD(TD_RTB_GR)),
    COMBO(combo_ntb_gu_1,TD(TD_NTB_GU)),COMBO(combo_ntb_gu_2,TD(TD_NTB_GU)),
    COMBO(combo_ctb_gd_1,TD(TD_CTB_GD)),COMBO(combo_ctb_gd_2,TD(TD_CTB_GD)),
    COMBO(combo_rcs_pgup_1,RCS(KC_PGUP)),COMBO(combo_rcs_pgup_2,RCS(KC_PGUP)),
    COMBO(combo_rcs_pgdn_1,RCS(KC_PGDN)),COMBO(combo_rcs_pgdn_2,RCS(KC_PGDN)),
    COMBO(combo_eng_btn2_f5_1,TD(TD_ENG_BTN2_F5)),COMBO(combo_eng_btn2_f5_2,TD(TD_ENG_BTN2_F5)),
    COMBO(combo_chs_tog_1,TD(TD_CHS_TOG)),COMBO(combo_chs_tog_2,TD(TD_CHS_TOG)),
    COMBO(combo_jpn_tog_1,TD(TD_JPN_TOG)),COMBO(combo_jpn_tog_2,TD(TD_JPN_TOG)),
    COMBO(combo_pent_cl_num,TD(TD_PENT_CL_NUM)),COMBO(combo_caps,KC_CAPS),
    COMBO(combo_lctl_e,LCTL(KC_E)),COMBO(combo_lctl_c_1,LCTL(KC_C)),
    COMBO(combo_lctl_c_2,LCTL(KC_C)),COMBO(combo_lctl_v_1,LCTL(KC_V)),
    COMBO(combo_lctl_v_2,LCTL(KC_V)),COMBO(combo_lctl_x_1,LCTL(KC_X)),
    COMBO(combo_lctl_x_2,LCTL(KC_X)),COMBO(combo_pu_hm_l2,TD(TD_PU_HM_L2)),
    COMBO(combo_pd_ed_rctl,TD(TD_PD_ED_RCTL)),COMBO(combo_ply_f_c_1,TD(TD_PLY_F_C)),
    COMBO(combo_ply_f_c_2,TD(TD_PLY_F_C)),COMBO(combo_kc_left,KC_LEFT),
    COMBO(combo_kc_right,KC_RGHT),COMBO(combo_kc_up,KC_UP),COMBO(combo_kc_down,KC_DOWN),
    COMBO(combo_lctl_mins_1,LCTL(KC_MINS)),COMBO(combo_lctl_mins_2,LCTL(KC_MINS)),
    COMBO(combo_lctl_eql_1,LCTL(KC_EQL)),COMBO(combo_lctl_eql_2,LCTL(KC_EQL)),
    COMBO(combo_lctl_0,LCTL(KC_0)),COMBO(combo_lctl_1,LCTL(KC_1)),
    COMBO(combo_exlm_vwl,TD(TD_EXLM_VWL)),COMBO(combo_atm_vwr,TD(TD_ATM_VWR)),
    COMBO(combo_hash,KC_HASH),COMBO(combo_dollar,KC_DLR),COMBO(combo_percent,KC_PERC),
    COMBO(combo_caret,KC_CIRC),COMBO(combo_ampersand_1,KC_AMPR),COMBO(combo_ampersand_2,KC_AMPR),
    COMBO(combo_asterisk_1,KC_ASTR),COMBO(combo_asterisk_2,KC_ASTR),
    COMBO(combo_lprn_1,KC_LPRN),COMBO(combo_lprn_2,KC_LPRN),
    COMBO(combo_rprn_1,KC_RPRN),COMBO(combo_rprn_2,KC_RPRN),
    COMBO(combo_mins_vwl_1,TD(TD_MINS_VWL)),COMBO(combo_mins_vwl_2,TD(TD_MINS_VWL)),
    COMBO(combo_eql_vwr_1,TD(TD_EQL_VWR)),COMBO(combo_eql_vwr_2,TD(TD_EQL_VWR)),
    COMBO(combo_home,KC_HOME),COMBO(combo_end,KC_END),COMBO(combo_lalt_f4,LALT(KC_F4)),
    COMBO(combo_p0_rcs_del,TD(TD_P0_RCS_DEL)),COMBO(combo_rcsh_spc,TD(TD_RCSH_SPC)),
    COMBO(combo_rcse_spc,TD(TD_RCSE_SPC)),
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS]={
    [0]=LAYOUT_65_ansi_blocker_tsangan_split_bs(
     TD(TD_EGUI_GH),LT(1,KC_1),LT(2,KC_2),MT(MOD_LCTL,KC_3),MT(MOD_LSFT,KC_4),MT(MOD_LALT,KC_5),MT(MOD_LGUI,KC_6),KC_7,KC_8,KC_9,LT(1,KC_0),MT(MOD_LCTL,KC_MINS),MT(MOD_LSFT,KC_EQL),LT(3,KC_BSPC),KC_BSPC,TD(TD_HM_WWW),
     LT(2,KC_TAB),LT(1,KC_Q),LT(3,KC_W),KC_E,LT(3,KC_R),KC_T,LT(2,KC_Y),KC_U,LT(3,KC_I),KC_O,LT(2,KC_P),KC_LBRC,KC_RBRC,LT(2,KC_BSLS),TD(TD_PU_HM_L2),
     LT(3,KC_GRV),KC_A,LT(2,KC_S),KC_D,KC_F,LT(1,KC_G),KC_H,KC_J,LT(1,KC_K),KC_L,LT(3,KC_SCLN),TD(TD_QUOT_AL_SQUO),LT(3,KC_ENT),TD(TD_PD_ED_RCTL),
     KC_LSFT,LT(3,KC_Z),LT(1,KC_X),KC_C,LT(2,KC_V),LT(3,KC_B),KC_N,KC_M,KC_COMM,LT(2,KC_DOT),TD(TD_SLSH_CL_QUEST),KC_RSFT,KC_UP,MT(MOD_RALT,KC_END),
     MT(MOD_LCTL,KC_PDOT),LT(2,KC_BSPC),MT(MOD_LALT,KC_ESC),LT(1,KC_SPC),LT(2,KC_ESC),KC_LEFT,KC_DOWN,KC_RGHT
    ),
    [1]=LAYOUT_65_ansi_blocker_tsangan_split_bs(
     KC_UP,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,LALT(KC_LEFT),LALT(KC_RGHT),QK_COMBO_TOGGLE,
     KC_DOWN,KC_LEFT,KC_RGHT,RCS(KC_PGUP),RCS(KC_PGDN),LCTL(KC_T),KC_TRNS,KC_TRNS,LCTL(LGUI(KC_D)),KC_MYCM,RCS(KC_UP),LCTL(KC_LEFT),LCTL(KC_RGHT),RCS(KC_DOWN),QK_COMBO_ON,
     RCS(KC_UP),LCTL(KC_LEFT),LCTL(KC_RGHT),RCS(KC_DOWN),RCS(KC_TAB),LCTL(KC_W),LCTL(KC_TAB),LCTL(LGUI(KC_LEFT)),LCTL(LGUI(KC_F4)),LCTL(LGUI(KC_RGHT)),TD(TD_SELTEX_BFALL),TD(TD_SELTEX_AFALL),LGUI(KC_TAB),QK_COMBO_OFF,
     LSA(KC_P),TD(TD_SELTEX_BFALL),TD(TD_SELTEX_AFALL),LCTL(KC_C),LCTL(KC_V),LGUI(KC_TAB),LCTL(KC_N),KC_APP,LALT(KC_ESC),LSA(KC_ESC),LALT(KC_LEFT),LALT(KC_RGHT),LCTL(KC_EQL),KC_TRNS,
     LALT(KC_ENT),KC_F5,LGUI(KC_H),LGUI(KC_D),KC_PSCR,LCTL(KC_0),LCTL(KC_MINS),LCTL(KC_1)
    ),
    [2]=LAYOUT_65_ansi_blocker_tsangan_split_bs(
     LALT(KC_F4),KC_MYCM,KC_CALC,LCTL(KC_F),KC_PSLS,LALT(KC_LEFT),LALT(KC_RGHT),LSA(KC_8),KC_LSFT,LCTL(KC_C),LCTL(KC_V),LSFT(KC_TAB),KC_TAB,LCTL(KC_A),LALT(KC_F4),KC_MYCM,
     KC_DEL,KC_P7,KC_P8,KC_P9,KC_PAST,RCS(KC_T),KC_TRNS,LSA(KC_7),KC_INS,KC_TRNS,KC_TRNS,RCS(KC_HOME),RCS(KC_END),LCTL(KC_E),RCS(KC_PGUP),
     KC_NUM,KC_P4,KC_P5,KC_P6,KC_PMNS,KC_TRNS,LCTL(KC_H),LSA(KC_9),LALT(KC_GRV),LGUI(KC_L),LALT(KC_UP),LALT(KC_DOWN),LCTL(KC_L),RCS(KC_PGDN),
     KC_P0,KC_P1,KC_P2,KC_P3,KC_PPLS,LCTL(KC_B),LSA(KC_1),LSA(KC_2),LSA(KC_Q),LGUI(KC_DOT),LCTL(KC_B),KC_WWW_HOME,LCTL(KC_T),RCS(KC_T),
     KC_WWW_HOME,RCS(KC_T),LCTL(KC_A),KC_PENT,LCTL(KC_H),RCS(KC_TAB),LCTL(KC_W),LCTL(KC_TAB)
    ),
    [3]=LAYOUT_65_ansi_blocker_tsangan_split_bs(
     KC_F11,LALT(KC_LEFT),LALT(KC_RGHT),KC_F13,KC_F14,KC_F15,KC_F16,KC_F17,KC_F18,KC_F19,KC_F20,KC_F21,KC_F22,KC_F23,LALT(KC_ESC),LSA(KC_ESC),
     KC_HOME,KC_PGUP,KC_UP,LALT(KC_ESC),LSA(KC_ESC),LCTL(KC_EQL),LCTL(KC_1),KC_MPRV,KC_F,KC_MPLY,KC_C,KC_LSFT,LSA(KC_8),LSA(KC_7),MEH(KC_TAB),
     KC_F7,KC_PGDN,KC_DOWN,MEH(KC_TAB),LCA(KC_TAB),LCTL(KC_MINS),LCTL(KC_0),KC_MNXT,KC_MRWD,KC_MFFD,LALT(KC_GRV),LSA(KC_9),LALT(KC_F4),LCA(KC_TAB),
     KC_END,KC_LEFT,KC_RGHT,KC_TRNS,KC_TRNS,QK_BOOT,KC_VOLD,KC_VOLU,LALT(KC_LEFT),LALT(KC_RGHT),LCTL(KC_Z),RCS(KC_Z),KC_TRNS,KC_F24,
     KC_TRNS,KC_SLSH,LGUI(KC_X),KC_MUTE,KC_MPLY,KC_TRNS,KC_TRNS,KC_TRNS
    ),
   };