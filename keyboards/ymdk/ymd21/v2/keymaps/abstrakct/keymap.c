/* Copyright 2022 QMK / James Young (@noroadsleft)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

#include "secrets.h"

#define BASE_HUE 80
#define BASE_SAT 255
#define BASE_VAL 30

enum macropad_layers {
	_BASE,
	_GNUCASH,
	_GAMING,
	_DCSS,
	_DWARF,
	_I3,
	_I3RIGHT,
	_I3LEFT,
	_ADJUST,
  _MOVEMENT
};

enum macropad_keycodes {
    // layers
	BASE = SAFE_RANGE,
	GNUCASH,
	GAMING,
	DWARF,
	DCSS,
	ADJUST,
    MVMNT,
	// base
	PERSNR,
	// gnucash
	GCBASIC,
	GCAUTO,
	DBLZERO,
	// dcss
	DCSS_za,
	DCSS_zb,
	DCSS_zc,
	DCSS_zd,
	DCSS_ze,
	DCSS_zf,
	DCSS_zg,
	DCSS_zh,
	DCSS_zi,
	DCSS_zB,
    // dwarf fortress
	DF_BPR,
	DF_BFB,
	DF_BFT,
	DF_BFR,
	// i3
	I3CLR,
	I3LRSTD,
    TOP_1,
    TOP_2,
    TOP_3,
    // gaming / OBS
    OBSSCN1,
    OBSSCN2,
};

#define MO_ADJ   MO(_ADJUST)
#define TG_GNUC  TG(_GNUCASH)
#define TG_GAME  TG(_GAMING)
#define TG_DCSS  TG(_DCSS)
#define TG_DWARF TG(_DWARF)
#define TG_I3    TG(_I3)
#define TG_MVMNT TG(_MOVEMENT)

#define OSLI3L   OSL(_I3LEFT)
#define OSLI3R   OSL(_I3RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_ortho_6x4(
        TG_GNUC, _______, _______, _______,
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_ENT,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        MO_ADJ,  KC_P0,   KC_PDOT, KC_BSPC
    ),

    [_GNUCASH] = LAYOUT_ortho_6x4(
        TG_GNUC, GCBASIC, GCAUTO,  C(KC_A),
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_TAB,
        KC_P1,   KC_P2,   KC_P3,   KC_ENT,
        KC_P0,   DBLZERO, _______, KC_BSPC
    ),

    [_GAMING] = LAYOUT_ortho_6x4(
        _______,     _______,     _______, _______,
        _______,     _______,     _______, _______,
        _______,     _______,     _______, _______,
        _______,     KC_P,        _______, _______,
        C(S(KC_F1)), C(S(KC_F2)), _______, _______,
        MO_ADJ,      KC_P1,       KC_P2,   KC_P3
    ),

    [_DCSS] = LAYOUT_ortho_6x4(
        DCSS_zB, _______, _______, _______,
        KC_1,    KC_2,    KC_3,    KC_O,
        DCSS_zg, DCSS_zh, DCSS_zi, KC_TAB,
        DCSS_zd, DCSS_ze, DCSS_zf, KC_5,
        DCSS_za, DCSS_zb, DCSS_zc, KC_PENT,
        MO_ADJ,  _______, _______, _______
    ),

    [_DWARF] = LAYOUT_ortho_6x4(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,
        _______, _______, _______, NO_LABK,
        _______, _______, _______, NO_RABK,
        DF_BFB,  _______, _______, _______,
        DF_BPR,  DF_BFT,  DF_BFR,  _______,
        MO_ADJ,  _______, _______, _______
    ),

    // G(C(KC_8)),G(C(KC_9)),G(C(KC_0)), LM(_I3LEFT, MOD_LSFT),
    [_I3] = LAYOUT_ortho_6x4(
        I3CLR,   _______, _______, I3LRSTD,
        TOP_1,   TOP_2,   TOP_3,   LM(_I3LEFT, MOD_LSFT),
        G(KC_7), G(KC_8), G(KC_9), LM(_I3RIGHT, MOD_LSFT),
        G(KC_4), G(KC_5), G(KC_6), OSM(MOD_LSFT),
        G(KC_1), G(KC_2), G(KC_3), G(KC_0),
        MO_ADJ,  OSLI3L,  OSLI3R,  G(KC_TAB)
    ),

    [_I3RIGHT] = LAYOUT_ortho_6x4(
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        RCTL(KC_7), RCTL(KC_8), RCTL(KC_9), _______,
        RCTL(KC_4), RCTL(KC_5), RCTL(KC_6), _______,
        RCTL(KC_1), RCTL(KC_2), RCTL(KC_3), RCTL(KC_0),
        MO_ADJ,     _______,    _______,    _______
    ),

    [_I3LEFT] = LAYOUT_ortho_6x4(
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        LCTL(KC_7), LCTL(KC_8), LCTL(KC_9), _______,
        LCTL(KC_4), LCTL(KC_5), LCTL(KC_6), _______,
        LCTL(KC_1), LCTL(KC_2), LCTL(KC_3), LCTL(KC_0),
        MO_ADJ,     _______,    _______,    _______
    ),

    [_MOVEMENT] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, KC_UP,   _______, _______,
        KC_LEFT, _______, KC_RGHT, _______,
        _______, KC_DOWN, _______, KC_Q,
        MO_ADJ,  _______, _______, _______
    ),

    [_ADJUST] = LAYOUT_ortho_6x4(
        RGB_MOD, BL_STEP, RGB_TOG, QK_BOOT,
        RGB_M_P, RGB_M_K, RGB_M_X, RGB_VAD,
        _______, _______, _______, RGB_VAI,
        _______, _______, _______, _______,
        _______, TG_MVMNT,TG_I3,   TG_DWARF,
        _______, BASE,    TG_GAME, TG_DCSS
    ),
};


///// Functions

// Runs at the end of boot
void keyboard_post_init_user(void) {
    rgblight_sethsv(BASE_HUE, BASE_SAT, BASE_VAL);
}


// Process custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BASE:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE);
            }
            return false;
        case GNUCASH:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GNUCASH);
            }
            return false;
        case GAMING:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GAMING);
            }
            return false;
        case DCSS:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DCSS);
            }
            return false;
        case DWARF:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DWARF);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_ADJUST);
            }
            return false;
        case MVMNT:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_MOVEMENT);
            }
            return false;
        case PERSNR:
            if (record->event.pressed) {
                SEND_STRING(PNR);
            } else {
            }
            return false;
        case GCBASIC:
            if (record->event.pressed) {
                register_code(KC_LALT);
                wait_ms(100);
                tap_code(KC_V);
                unregister_code(KC_LALT);
                tap_code(KC_B);
            }
            return false;
        case GCAUTO:
            if (record->event.pressed) {
                register_code(KC_LALT);
                wait_ms(100);
                tap_code(KC_V);
                unregister_code(KC_LALT);
                tap_code(KC_A);
            }
            return false;
        case DBLZERO:
            if (record->event.pressed) {
                tap_code(KC_0);
                tap_code(KC_0);
            }
            return false;
        case TOP_1:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LCTL);
                tap_code(KC_8);
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
            }
            return false;
        case TOP_2:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LCTL);
                tap_code(KC_9);
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
            }
            return false;
        case TOP_3:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LCTL);
                tap_code(KC_0);
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
            }
            return false;
        case DCSS_za:
            if (record->event.pressed) {
                tap_code(KC_Z);
                tap_code(KC_A);
            }
            return false;
        case DCSS_zb:
            if (record->event.pressed) {
                tap_code(KC_Z);
                tap_code(KC_B);
            }
            return false;
        case DCSS_zc:
            if (record->event.pressed) {
                tap_code(KC_Z);
                tap_code(KC_C);
            }
            return false;
        case DCSS_zd:
            if (record->event.pressed) {
                tap_code(KC_Z);
                tap_code(KC_D);
            }
            return false;
        case DCSS_ze:
            if (record->event.pressed) {
                tap_code(KC_Z);
                tap_code(KC_E);
            }
            return false;
        case DCSS_zf:
            if (record->event.pressed) {
                tap_code(KC_Z);
                tap_code(KC_F);
            }
            return false;
        case DCSS_zg:
            if (record->event.pressed) {
                tap_code(KC_Z);
                tap_code(KC_G);
            }
            return false;
        case DCSS_zh:
            if (record->event.pressed) {
                tap_code(KC_Z);
                tap_code(KC_H);
            }
            return false;
        case DCSS_zi:
            if (record->event.pressed) {
                tap_code(KC_Z);
                tap_code(KC_I);
            }
            return false;
        case DCSS_zB:
            if (record->event.pressed) {
                tap_code(KC_Z);
                register_code(KC_LSFT);
                tap_code(KC_B);
                unregister_code(KC_LSFT);
            }
            return false;
        case DF_BPR:
            if (record->event.pressed) {
                tap_code(KC_B);
                tap_code(KC_P);
                tap_code(KC_R);
            }
            return false;
        case DF_BFB:
            if (record->event.pressed) {
                tap_code(KC_B);
                tap_code(KC_F);
                tap_code(KC_B);
            }
            return false;
        case DF_BFT:
            if (record->event.pressed) {
                tap_code(KC_B);
                tap_code(KC_F);
                tap_code(KC_T);
            }
            return false;
        case DF_BFR:
            if (record->event.pressed) {
                tap_code(KC_B);
                tap_code(KC_F);
                tap_code(KC_R);
            }
            return false;
        case I3CLR:
            if (record->event.pressed) {
                // TODO: add defines for these (and other)?
                SEND_STRING(SS_LCTL("1"));
                SEND_STRING(SS_RCTL("0"));
            }
            return false;
        case I3LRSTD:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("9"));
                SEND_STRING(SS_RCTL("4"));
            }
            return false;
        case OBSSCN1:
            if (record->event.pressed) {
                register_code(KC_LALT);
                wait_ms(20);
                register_code(KC_LCTL);
                wait_ms(20);
                register_code(KC_LSFT);
                wait_ms(20);
                register_code(KC_LGUI);
                wait_ms(20);
                tap_code(KC_1);
                wait_ms(20);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            }
            return false;
        case OBSSCN2:
            if (record->event.pressed) {
                register_code(KC_LALT);
                wait_ms(20);
                register_code(KC_LCTL);
                wait_ms(20);
                register_code(KC_LSFT);
                wait_ms(20);
                register_code(KC_LGUI);
                wait_ms(20);
                tap_code(KC_2);
                wait_ms(20);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            }
            return false;
    }

    return true;
}

///// RGB LIGHT stuff

#define DEFAULT_VAL 60

#define GNUCASH_HUE 127
#define GNUCASH_SAT 255
#define GNUCASH_VAL 30

#define I3_HUE 169
#define I3_SAT 255
#define I3_VAL 30


// Set rgb color brightness based on Num Lock state
bool led_update_user(led_t led_state) {
    if (!led_state.num_lock) {
        if (layer_state_is(_BASE)) {
            rgblight_sethsv(BASE_HUE, BASE_SAT, 255);
        } else if (layer_state_is(_GNUCASH)) {
            rgblight_sethsv(GNUCASH_HUE, GNUCASH_SAT, 255);
        }
    } else {
        if (layer_state_is(_BASE)) {
            rgblight_sethsv(BASE_HUE, BASE_SAT, BASE_VAL);
        } else if (layer_state_is(_GNUCASH)) {
            rgblight_sethsv(GNUCASH_HUE, GNUCASH_SAT, GNUCASH_VAL);
        }
    }

    return true;
}


// Set rgb color based on layer state
layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(state)) {
        case _BASE:
            //rgblight_setrgb(RGB_RED);
            rgblight_sethsv(BASE_HUE, BASE_SAT, BASE_VAL);
            break;
        case _GNUCASH:
            //rgblight_setrgb(RGB_BLUE);
            rgblight_sethsv(GNUCASH_HUE, GNUCASH_SAT, GNUCASH_VAL);
            break;
        case _GAMING:
            //rgblight_setrgb(RGB_ORANGE);
            rgblight_sethsv(180, 255, DEFAULT_VAL);
            break;
        case _DCSS:
            //rgblight_setrgb(RGB_ORANGE);
            rgblight_sethsv(40, 255, 30);
            break;
        case _DWARF:
            rgblight_sethsv(201, 255, 30);
            break;
        case _I3:
            rgblight_sethsv(I3_HUE, I3_SAT, I3_VAL);
            break;
        case _ADJUST:
            //rgblight_setrgb(RGB_ORANGE);
            rgblight_sethsv(21, 255, DEFAULT_VAL);
            break;
        default:
            //rgblight_setrgb(RGB_GREEN);
            rgblight_sethsv(127, 255, DEFAULT_VAL);
            break;
    }

    return state;
}
