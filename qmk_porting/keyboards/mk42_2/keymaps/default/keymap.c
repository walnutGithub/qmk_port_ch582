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
                     KC_ESC, LT(2,KC_CAPS), KC_LSFT, KC_LCTL,
                     KC_Q, KC_A, KC_Z, KC_LGUI,
                     KC_W, KC_S, KC_X, KC_LALT,
                     KC_E, KC_D, KC_C, KC_SPC, 
                     KC_R, KC_F, KC_V, LT(1,KC_NO), 
                     KC_T, KC_G, KC_B, KC_NO, 
                     KC_Y, KC_H, KC_N, KC_NO,
                     KC_U, KC_J, KC_M, KC_NO, 
                     KC_I, KC_K, KC_SLSH, KC_NO, 
                     KC_O, KC_L, KC_NO, KC_LEFT, 
                     KC_P, KC_NO, KC_UP, KC_DOWN, 
                     KC_BSPC, KC_ENT, KC_RSFT, KC_RGHT  ),
    [1] = LAYOUT_all(/* 1: fn */
                     KC_GRV, KC_CAPS, KC_LSFT, KC_LCTL, 
                     KC_1, KC_MYCM, KC_WHOM, KC_LGUI, 
                     KC_2, KC_BRIU, KC_BRID, KC_LALT, 
                     KC_3, KC_VOLU, KC_VOLD, KC_SPC,   
                     KC_4, KC_MPLY, KC_CALC, KC_NO,  
                     KC_5, KC_SLEP, KC_SCLN, KC_NO, 
                     KC_6, KC_MINS, KC_QUOT, KC_NO, 
                     KC_7, KC_EQL, KC_COMM, KC_NO, 
                     KC_8, KC_LBRC, KC_DOT, KC_NO, 
                     KC_9, KC_RBRC, KC_NO, RGB_TOG, 
                     KC_0, KC_NO, KC_PGUP, KC_PGDN, 
                     KC_DEL, KC_BSLS, KC_RSFT, RGB_MOD  ),
    [2] = LAYOUT_all(/* 2: fn */
                     KC_TAB,  KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR, 
                     KC_NO,   KC_COPY, KC_PSTE, KC_CUT, KC_F,   KC_G,    KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_NO,   KC_BSLS,
                     KC_LSFT, KC_UNDO, KC_AGIN, KC_C,   KC_V,   KC_SCLN, KC_QUOT, KC_COMM, KC_DOT,  KC_NO,   KC_PGUP, KC_RSFT, 
                     KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RALT, KC_F11,  KC_F12   
                     
                     KC_TAB, KC_NO, KC_LSFT, KC_LCTL, 
                     KC_F1, KC_COPY, KC_UNDO, KC_LGUI, 
                     KC_F2, KC_PSTE, KC_AGIN, KC_LALT, 
                     KC_F3, KC_CUT, KC_C, KC_SPC, 
                     KC_F4, KC_F, KC_V, KC_SPC, 
                     KC_F5, KC_G, KC_SCLN, KC_NO, 
                     KC_F6, KC_MINS, KC_QUOT, KC_NO, 
                     KC_F7, KC_EQL, KC_COMM, KC_NO, 
                     KC_F8, KC_LBRC, KC_DOT, KC_NO, 
                     KC_F9, KC_RBRC, KC_NO, KC_RALT, 
                     KC_F10, KC_NO, KC_PGUP, KC_F11, 
                     KC_PSCR, KC_BSLS, KC_RSFT, KC_F12  ),
};

#ifdef ENCODER_MAP_ENABLE

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};

#endif
