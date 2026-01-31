/*
Copyright 2018 Mattia Dal Ben <matthewdibi@gmail.com>

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

#include "keymap_norwegian.h"
#include "sendstring_norwegian.h"

// Shortcut to make keymap more readable
// #define SYM_L   MO(_SYMB)
//
// #define KC_ALAS LALT_T(KC_PAST)
// #define KC_CTPL LCTL_T(KC_BSLS)
//
// #define KC_NAGR LT(_NAV, KC_GRV)
// #define KC_NAMI LT(_NAV, KC_MINS)
//
// #define KC_ADEN LT(_ADJUST, KC_END)
// #define KC_ADPU LT(_ADJUST, KC_PGUP)

enum layers {
   _QWERTY,
   _LOWER,
   _RAISE,
   _EMPTY
};

// Homerow mods
#define H_ALT LALT_T(KC_Q)
#define H_CTL LCTL_T(KC_W)
#define H_SFT LSFT_T(KC_E)
#define H_GUI LGUI_T(KC_F)
#define H_I  RSFT_T(KC_I)
#define H_O  RCTL_T(KC_O)

#define S_RBRC  LSFT_T(KC_RBRC)

#define RAIENT LT(_RAISE, KC_ENT)
#define LOWBSP LT(_RAISE, KC_BSPC)

// For the advanced tap dances. Put it here so it can be used in any keymap
void oe_finished(tap_dance_state_t *state, void *user_data);
void oe_reset(tap_dance_state_t *state, void *user_data);

// Tap dance declarations
enum {
    X_OE,
};

// Tap dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [X_OE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, oe_finished, oe_reset)
};

// Quad function tap/hold stuff
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌──────┬─────┬─────┬─────┬─────┬─────┐                                 ┌─────┬───┬─────┬─────┬─────┬──────┐
//    │ esc  │  1  │  2  │  3  │  4  │  5  │                                 │  6  │ 7 │  8  │  9  │  0  │ bspc │
//    ├──────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌────────┼─────┼───┼─────┼─────┼─────┼──────┤
//    │ tab  │ q/A │ w/C │ e/S │  r  │  t  │     │                  │        │  y  │ u │ i/S │ o/C │  p  │  /   │
//    ├──────┼─────┼─────┼─────┼─────┼─────┼─────┤                  ├────────┼─────┼───┼─────┼─────┼─────┼──────┤
//    │ LOW  │  a  │  s  │  d  │ f/G │  g  │     │                  │        │  h  │ j │  k  │  l  │ æøå │ ent  │
//    ├──────┼─────┼─────┼─────┼─────┼─────┼─────┼────────┐   ┌─────┼────────┼─────┼───┼─────┼─────┼─────┼──────┤
//    │ lsft │  z  │  x  │  c  │  v  │  b  │     │        │   │     │        │  n  │ m │  ,  │  .  │  -  │ rsft │
//    ├──────┼─────┼─────┼─────┼─────┼─────┼─────┼────────┤   ├─────┼────────┼─────┼───┼─────┼─────┼─────┼──────┤
//    │ lctl │     │     │     │     │     │     │ LOWBSP │   │ spc │ RAIENT │     │   │     │     │     │      │
//    └──────┴─────┴─────┴─────┘     └─────┴─────┴────────┘   └─────┴────────┴─────┘   └─────┴─────┴─────┴──────┘
[_QWERTY] = LAYOUT(
  KC_ESC     , KC_1    , KC_2    , KC_3    , KC_4  , KC_5    ,                                             KC_6    , KC_7 , KC_8    , KC_9    , KC_0     , KC_BSPC,
  KC_TAB     , H_ALT   , H_CTL   , H_SFT   , KC_R  , KC_T    , _______ ,                         _______ , KC_Y    , KC_U , H_I     , H_O     , KC_P     , S_RBRC ,
  MO(_LOWER) , KC_A    , KC_S    , KC_D    , H_GUI , KC_G    , _______ ,                         _______ , KC_H    , KC_J , KC_K    , KC_L    , TD(X_OE) , KC_ENT ,
  KC_LSFT    , KC_Z    , KC_X    , KC_C    , KC_V  , KC_B    , _______ , _______ ,     _______ , _______ , KC_N    , KC_M , KC_COMM , KC_DOT  , KC_SLSH  , KC_RSFT,
  KC_LCTL    , _______ , _______ , _______ ,         _______ , _______ , LOWBSP  ,     KC_SPC  , RAIENT  , _______ ,        _______ , _______ , _______  , _______
),

//    ┌────┬────┬────┬────┬────┬────┐                       ┌────┬────┬────┬────┬────┬────┐
//    │ no │ no │ no │ no │ no │ no │                       │ no │ no │ no │ no │ no │ no │
//    ├────┼────┼────┼────┼────┼────┼────┐             ┌────┼────┼────┼────┼────┼────┼────┤
//    │ no │ no │ no │ no │ no │ no │ no │             │ no │ no │ no │ no │ no │ no │ no │
//    ├────┼────┼────┼────┼────┼────┼────┤             ├────┼────┼────┼────┼────┼────┼────┤
//    │ no │ no │ no │ no │ no │ no │ no │             │ no │ no │ no │ no │ no │ no │ no │
//    ├────┼────┼────┼────┼────┼────┼────┼────┐   ┌────┼────┼────┼────┼────┼────┼────┼────┤
//    │ no │ no │ no │ no │ no │ no │ no │ no │   │ no │ no │ no │ no │ no │ no │ no │ no │
//    ├────┼────┼────┼────┼────┼────┼────┼────┤   ├────┼────┼────┼────┼────┼────┼────┼────┤
//    │ no │ no │ no │ no │    │ no │ no │ no │   │ no │ no │ no │    │ no │ no │ no │ no │
//    └────┴────┴────┴────┘    └────┴────┴────┘   └────┴────┴────┘    └────┴────┴────┴────┘
[_EMPTY] = LAYOUT(
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                             XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,     XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,           XXXXXXX , XXXXXXX , XXXXXXX ,     XXXXXXX , XXXXXXX , XXXXXXX ,           XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
)
};

// Quad function tap/hold functions
/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
		return TD_SINGLE_TAP;
	}
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void oe_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(NO_OSTR); break;
        case TD_SINGLE_HOLD: register_code(NO_AE); break;
        case TD_DOUBLE_TAP: register_code(NO_ARNG); break;
        // case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        // case TD_DOUBLE_SINGLE_TAP: tap_code(NO_OSTR); register_code(NO_OSTR); break;
        case TD_DOUBLE_SINGLE_TAP: register_code(NO_ARNG); break;
        default: break;
    }
}

void oe_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(NO_OSTR); break;
        case TD_SINGLE_HOLD: unregister_code(NO_AE); break;
        case TD_DOUBLE_TAP: unregister_code(NO_ARNG); break;
        // case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(NO_ARNG); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

