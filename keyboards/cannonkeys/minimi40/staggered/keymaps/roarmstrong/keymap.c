// Copyright 2024 Andrew Kannan
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum {
    TIL_SHIFT,
    PARENL,
    PARENR,
    COM_BSL,
    DOT_FSL,
    TD_1,
    TD_2,
    TD_3,
    TD_4,
    TD_5,
    TD_6,
    TD_7,
    TD_8,
    TD_9,
    TD_0,
    TD_MINS,
    TD_EQUAL,
    TD_GRV,
    TD_SCLN,
    TD_QUOT
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_case_helper(uint16_t keycode, keyrecord_t *record);


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	    case TD(TIL_SHIFT):
		    tap_dance_tap_hold_case_helper(keycode, record);
		    break;
    }
    return true;
}


void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

void tap_dance_tap_hold_layer_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            layer_on(tap_hold->hold);
            tap_hold->held = 1;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_layer_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        layer_off(tap_hold->hold);
        tap_hold->held = 0;
    }
}


#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }


#define ACTION_TAP_DANCE_TAP_LAYER_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_layer_finished, tap_dance_tap_hold_layer_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [TIL_SHIFT] = ACTION_TAP_DANCE_TAP_HOLD(KC_TILD, KC_LSFT),
    [COM_BSL]   = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_BSLS),
    [DOT_FSL]   = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_SLSH),
    [TD_1]      = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_1),
    [TD_2]      = ACTION_TAP_DANCE_DOUBLE(KC_W, KC_2),
    [TD_3]      = ACTION_TAP_DANCE_DOUBLE(KC_E, KC_3),
    [TD_4]      = ACTION_TAP_DANCE_DOUBLE(KC_R, KC_4),
    [TD_5]      = ACTION_TAP_DANCE_DOUBLE(KC_T, KC_5),
    [TD_6]      = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_6),
    [TD_7]      = ACTION_TAP_DANCE_DOUBLE(KC_U, KC_7),
    [TD_8]      = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_8),
    [TD_9]      = ACTION_TAP_DANCE_DOUBLE(KC_O, KC_9),
    [TD_0]      = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_0),
    [TD_MINS]   = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_MINS),
    [TD_EQUAL]  = ACTION_TAP_DANCE_DOUBLE(KC_S, KC_EQUAL),
    [TD_GRV]    = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_GRV),
    [TD_SCLN]   = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_SCLN),
    [TD_QUOT]   = ACTION_TAP_DANCE_DOUBLE(KC_L, KC_QUOT)
}; 

void tap_dance_tap_hold_case_helper(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    action = &tap_dance_actions[TD_INDEX(keycode)];
    if (!record->event.pressed && action->state.count && !action->state.finished) {
        tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
        tap_code16(tap_hold->tap);
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_all(
    KC_ESC,        TD(TD_1),    TD(TD_2),    TD(TD_3),    TD(TD_4),    TD(TD_5),    TD(TD_6),    TD(TD_7),    TD(TD_8),    TD(TD_9),    TD(TD_0),    KC_BSPC,
    LT(3, KC_TAB),        TD(TD_MINS), TD(TD_EQUAL),KC_D,        KC_F,        KC_G,        KC_H,         TD(TD_GRV), TD(TD_SCLN), TD(TD_QUOT),       KC_ENT,
    TD(TIL_SHIFT), KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_N,        KC_M,        TD(COM_BSL), TD(DOT_FSL), MT(MOD_RSFT, KC_UP),
    KC_LCTL,       KC_NO,   KC_LGUI,         KC_SPC,      LT(1, KC_SPC),            LT(2, KC_RALT), KC_NO,  MT(MOD_RCTL, KC_RIGHT) 
),

[1] = LAYOUT_all(
    KC_ESC,  KC_1   , KC_2    ,KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0,    KC_TRNS,  
    KC_TRNS, KC_MINS, KC_EQUAL,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV, KC_SCLN, KC_QUOT, KC_TRNS,
    KC_TRNS, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_TRNS,          KC_TRNS, KC_TRNS,                   KC_TRNS, KC_NO,   KC_TRNS
),

[2] = LAYOUT_all(
    KC_ESC,  KC_PGUP   , KC_UP      ,KC_PGDN   , KC_HOME   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS,    KC_TRNS,
    KC_TRNS, KC_LEFT,    KC_DOWN    ,KC_RIGHT  , KC_END    , KC_TRNS,    KC_TRNS   , KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_TRNS,          KC_TRNS, KC_TRNS,                   KC_TRNS, KC_NO,   KC_TRNS
),

[3] = LAYOUT_all(
    KC_F1  ,  KC_F2  , KC_F3   ,KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11,  KC_F12,
    KC_TRNS, KC_TRNS, KC_TRNS ,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_TRNS,          KC_TRNS, KC_TRNS,                   KC_TRNS, KC_NO,   KC_TRNS
)
};
