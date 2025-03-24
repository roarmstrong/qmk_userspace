/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

enum {
	TD_COMMA,
	TD_PERIOD,
	TD_MIN
};

tap_dance_action_t tap_dance_actions[] = {
	[TD_COMMA] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_BSLS),
	[TD_PERIOD] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_SLSH)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_TILD):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_TILD); // Send KC_TILD on tap
                return false;        // Return false to ignore further processing of key
            }
            break;
	case LALT_T(KC_LPRN):
	    if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LPRN); // Send KC_TILD on tap
                return false;        // Return false to ignore further processing of key
            }
            break;
	case LT(2, KC_RPRN):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_RPRN); // Send KC_TILD on tap
                return false;        // Return false to ignore further processing of key
            }
            break;

    }
    return true;
}


const key_override_t i3_up = ko_make_with_layers_and_negmods(MOD_MASK_GUI, KC_W, RGUI(KC_UP), 1, MOD_MASK_CTRL);
const key_override_t i3_left = ko_make_basic(MOD_MASK_GUI, KC_A, RGUI(KC_LEFT));
const key_override_t i3_right = ko_make_basic(MOD_MASK_GUI, KC_D, RGUI(KC_RIGHT));
const key_override_t i3_down = ko_make_basic(MOD_MASK_GUI, KC_S, RGUI(KC_DOWN));

const key_override_t shift_del = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
    &i3_up,
    &i3_down,
    &i3_left,
    &i3_right,
    &shift_del
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        [0] = LAYOUT_all(
                KC_ESC,          KC_Q,            KC_W,            KC_E,    KC_R,    KC_T,             KC_Y,            KC_U,             KC_I,            KC_O,    KC_P,    KC_BSPC,
                KC_TAB,          KC_A,            KC_S,            KC_D,    KC_F,    KC_G,             KC_H,            KC_J,             KC_K,            KC_L,    KC_ENT,
                LSFT_T(KC_TILD), KC_NO,           KC_Z,            KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,             KC_M,    TD(TD_COMMA),    TD(TD_PERIOD),    MT(MOD_RSFT, KC_UP),
                KC_LCTL,         LALT_T(KC_LPRN), LGUI_T(KC_LBRC), KC_SPC,  KC_NO,   LT(1, KC_SPC),    RGUI_T(KC_RBRC), LT(2, KC_RPRN),   RCTL_T(KC_RIGHT)
        ),
	[1] = LAYOUT_all(
                KC_ESC,          KC_1   , KC_2   , KC_3   , KC_4,    KC_5   ,          KC_6   , KC_7   , KC_8   ,         KC_9   , KC_0 ,   KC_TRNS,
                KC_TRNS,         KC_MINS, KC_EQL,  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_GRV, KC_SCLN,         KC_QUOT, KC_TRNS,
                KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS,          KC_TRNS, KC_TRNS,
                KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
	),
	[2] = LAYOUT_all(
		KC_ESC,          KC_PGUP, KC_UP,   KC_PGDN, KC_HOME, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS,         KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
		KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS,          KC_TRNS, KC_TRNS,
		KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
	)
};
