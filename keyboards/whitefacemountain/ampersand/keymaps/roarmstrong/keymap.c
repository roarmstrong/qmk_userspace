// Default layout for Ampersand
#include QMK_KEYBOARD_H

enum {
	TTILD_HLSHIFT,
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
    TD_MIN_EQ,
    TD_SLSH,
    TD_PARENLALT,
    TD_PARENRALT,
    TD_SEMI_QUOTE,
    TD_COM_BSL,
    TD_DOT_FSL,
    TD_BKTLGUI,
    TD_BKTRGUI
};


typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

typedef struct {
    uint16_t w;
    uint16_t up;
    uint16_t two;
    uint16_t tapped;
    uint16_t held;
} tap_dance_w_t;

void tap_dance_tap_hold_case_helper(uint16_t keycode, keyrecord_t *record);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TTILD_HLSHIFT):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_1):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_2):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_3):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_4):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_5):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_6):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_7):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_8):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_9):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_0):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_PARENLALT):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_PARENRALT):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_BKTLGUI):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_BKTRGUI):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
    }
    return true;
}

void tap_dance_tap_hold_unpermissive_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1 && !state->interrupted)
        {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
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

#define ACTION_TAP_DANCE_TAP_HOLD_UP(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_unpermissive_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

#define ACTION_TAP_DANCE_TAP_LAYER_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_layer_finished, tap_dance_tap_hold_layer_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }


tap_dance_action_t tap_dance_actions[] = {
    [TTILD_HLSHIFT] = ACTION_TAP_DANCE_TAP_HOLD(KC_TILD, KC_LSFT),
    [TD_1] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_Q, KC_1),
    [TD_3] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_E, KC_3),
    [TD_4] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_R, KC_4),
    [TD_5] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_T, KC_5),
    [TD_6] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_Y, KC_6),
    [TD_7] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_U, KC_7),
    [TD_8] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_I, KC_8),
    [TD_9] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_O, KC_9),
    [TD_0] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_P, KC_0),
    [TD_MIN_EQ] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQUAL),
    [TD_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
    [TD_SEMI_QUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
    [TD_COM_BSL] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_BSLS),
    [TD_DOT_FSL] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_SLSH),
    [TD_PARENLALT] = ACTION_TAP_DANCE_TAP_HOLD(KC_LPRN, KC_LALT),
    [TD_PARENRALT] = ACTION_TAP_DANCE_TAP_LAYER_HOLD(KC_RPRN, 3),
    [TD_2] =  ACTION_TAP_DANCE_TAP_HOLD_UP(KC_W, KC_2),
    [TD_BKTLGUI] = ACTION_TAP_DANCE_TAP_HOLD(KC_LBRC, KC_LGUI),
    [TD_BKTRGUI] = ACTION_TAP_DANCE_TAP_HOLD(KC_RBRC, KC_RGUI)
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

[0] = LAYOUT_split_bars(
	LT(2, KC_ESC),     TD(TD_1),TD(TD_2),TD(TD_3),TD(TD_4),TD(TD_5),TD(TD_6),TD(TD_7),TD(TD_8),TD(TD_9),TD(TD_0),TD(TD_MIN_EQ), KC_BSPC,
	KC_TAB,            KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    TD(TD_SEMI_QUOTE), KC_ENT,       KC_NO,
	TD(TTILD_HLSHIFT), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    TD(TD_COM_BSL), TD(TD_DOT_FSL),  KC_NO, MT(MOD_RSFT, KC_UP),
	KC_LCTL, TD(TD_PARENLALT),  TD(TD_BKTLGUI),            KC_SPC,  LT(1, KC_SPC),      TD(TD_BKTRGUI), TD(TD_PARENRALT), MT(MOD_RCTL, KC_RIGHT)),
[1] = LAYOUT_split_bars(
	KC_GRV, KC_1   , KC_2   , KC_3   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,  KC_TRNS,
	KC_TRNS, KC_MINS, KC_EQUAL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS),
[2] = LAYOUT_split_bars(
    KC_TRNS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11,   KC_F12,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS),
[3] = LAYOUT_split_bars(
    KC_ESC,  KC_PGUP, KC_UP, KC_PGDN, KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS),
};
