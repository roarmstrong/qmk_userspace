// Copyright 2022 @whitefacemountain
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum {
    TIL_SHIFT,
    COL_QUOT,
    COM_BSL,
    DOT_FSL,
    RALT,
    LALT
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
            case TD(RALT):
            case TD(LALT):
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
    [COL_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
    [COM_BSL]   = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_BSLS),
    [DOT_FSL]   = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_SLSH),
    [LALT] = ACTION_TAP_DANCE_TAP_HOLD(KC_LPRN, KC_LALT),
    [RALT] = ACTION_TAP_DANCE_TAP_LAYER_HOLD(KC_RPRN, 2)
};


void tap_dance_tap_hold_case_helper(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    action = &tap_dance_actions[TD_INDEX(keycode)];
    if (!record->event.pressed && action->state.count && !action->state.finished) {
        tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
        tap_code16(tap_hold->tap);
    }
}

const key_override_t shift_del = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
    &shift_del
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,         KC_BSPC,
        LT(3, KC_TAB),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    TD(COL_QUOT), KC_ENT,
        TD(TIL_SHIFT),  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    TD(COM_BSL), TD(DOT_FSL),  MT(MOD_RSFT, KC_UP),
        KC_LCTL, TD(LALT), MT(MOD_LGUI, KC_LBRC),    KC_SPC,  LT(1, KC_SPC),    MT(MOD_RGUI, KC_RBRC), TD(RALT), MT(MOD_RCTL, KC_RIGHT)
    ),
    [1] = LAYOUT(
	KC_TRNS, KC_1   , KC_2    ,KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0,   KC_TRNS,
        KC_TRNS, KC_MINS, KC_EQUAL,KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_GRV,  KC_LBRC, KC_RBRC, KC_TRNS,KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS	
    ),
    [2] = LAYOUT(
        KC_TRNS, KC_PGUP, KC_UP,   KC_PGDN, KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT(
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11,   KC_F12,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
    )
};
