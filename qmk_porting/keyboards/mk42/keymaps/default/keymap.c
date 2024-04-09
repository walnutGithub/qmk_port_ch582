/*
Copyright 2022 Huckies <https://github.com/Huckies>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "extra_keycode.h"

enum unicode_names {
    la = NEW_SAFE_RANGE,
    lA,
    rc,
    rC,
    rv,
    rV,
    rb,
    rB,
    rn,
    rN
};

const uint32_t PROGMEM unicode_map[] = {
    [la] = 0x03B1, // α
    [lA] = 0x0307, //
    [rc] = 0x2284, // ⊄
    [rC] = 0x2286, // ⊆
    [rv] = 0x2285, // ⊅
    [rV] = 0x2287, //⊇
    [rb] = 0x2227, // ∧
    [rB] = 0x22BC, //⊼
    [rn] = 0x2228, //∨
    [rN] = 0x22BB  //⊻
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(/* 0: qwerty */
                     KC_ESC,        KC_Q,    KC_W,    KC_E,   KC_R,        KC_T,  KC_Y,  KC_U,  KC_I,     KC_O,    KC_P,    KC_BSPC, 
                     LT(2,KC_CAPS), KC_A,    KC_S,    KC_D,   KC_F,        KC_G,  KC_H,  KC_J,  KC_K,     KC_L,    KC_NO,   KC_ENT, 
                     KC_LSFT,       KC_Z,    KC_X,    KC_C,   KC_V,        KC_B,  KC_N,  KC_M,  KC_SLSH,  KC_NO,   KC_UP,   KC_RSFT,
                     KC_LCTL,       KC_LGUI, KC_LALT, KC_SPC, LT(1,KC_NO), KC_NO, KC_NO, KC_NO, KC_NO,    KC_LEFT, KC_DOWN, KC_RGHT  ),
    [1] = LAYOUT_all(/* 1: fn */
                     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
                     KC_CAPS, KC_MYCM, KC_BRIU, KC_VOLU, KC_MPLY, KC_SLEP, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_NO,   KC_BSLS,
                     KC_LSFT, KC_WHOM, KC_BRID, KC_VOLD, KC_CALC, KC_SCLN, KC_QUOT, KC_COMM, KC_DOT,  KC_NO,   KC_PGUP, KC_RSFT,
                     KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_TOG, KC_PGDN, RGB_MOD  ),
    [2] = LAYOUT_all(/* 2: fn */
                     KC_TAB,  KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR, 
                     KC_NO,   KC_COPY, KC_PSTE, KC_CUT, KC_F,   KC_G,    KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_NO,   KC_BSLS,
                     KC_LSFT, KC_UNDO, KC_AGIN, KC_C,   KC_V,   KC_SCLN, KC_QUOT, KC_COMM, KC_DOT,  KC_NO,   KC_PGUP, KC_RSFT, 
                     KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RALT, KC_F11,  KC_F12   ),
};

#ifdef ENCODER_MAP_ENABLE

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};

#endif
