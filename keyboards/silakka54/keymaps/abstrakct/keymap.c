/* Copyright 2015-2021 Jack Humbert
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
#include "sendstring_norwegian.h"

#include "secrets.h"

// IDEA / TODO: egen layer for TMUX!?

#define ALTGR_WAIT 70

#define HOMEALT LALT_T(KC_Q)
#define HOMECTL LCTL_T(KC_W)
#define HOMESFT LSFT_T(KC_E)
#define HOMEGUI LGUI_T(KC_F)
#define HOME_I  RSFT_T(KC_I)
#define HOME_O  RCTL_T(KC_O)

#define S_RBRC  LSFT_T(KC_RBRC)

// #define KC_LOWR MO(_LOWER)
#define KC_LOWR QK_TRI_LAYER_LOWER
// #define KC_RAIS MO(_RAISE)
#define KC_RAIS QK_TRI_LAYER_UPPER
#define KC_CORN MO(_CORNER)
#define KC_NOEN TG(_NOENTER)

#define LOW_SPC LT(_LOWER,KC_SPC)
#define LOW_ENT LT(_LOWER,KC_ENT)
#define RAI_SPC LT(_RAISE,KC_SPC)
#define RAI_ENT LT(_RAISE,KC_ENT)


#define CTSH_V  C(S(KC_V))
#define CTSH_L  C(S(KC_L))
#define CTSH_M  C(S(KC_M))
#define SH_PSCR S(KC_PSCR)
#define CRCFLEX ALGR(NO_AE)

#define G_MINUS G(KC_SLSH)
#define G_PLUS  G(NO_PLUS)

#define COLON   S(KC_DOT)
#define SCOLON  S(KC_COMM)
#define UNDERSC S(KC_SLSH)

#define OSMLSFT OSM(MOD_LSFT)

// Ctrl-Alt-0 (ansible vault decrypt/encrypt in vscode)
#define CTALT_0 LCA(KC_0)

// Tapdance
// #define KC_TDOE TD(TD_OE_AST)
// #define KC_TDOE TD(TD_OE_AA)

// Layers and keycodes
enum silakka_layers {
  // Base layers
  _NORM,
  _GAME,
  _COLE,
  _TARMAK1,
  // _WORK,
  // Overlay layers
  _LOWER,
  _RAISE,
  _THIRD, // aka ADJUST
  _FOUR,
  _FIVE,
  _CORNER,
  _NOENTER,
  _MVMNT,
};

enum silakka_keycodes {
  // Layers
  NORM = SAFE_RANGE,
  LOWER,
  RAISE,
  // Layers (unused)
  FOUR, FIVE, BACKLIT,
  // Various secrets
  SECRET1, SECRET2, SECRET3, SECRET4, SECRET5, SECRET6, ADMINPW, PERSNR,
  // Work
  CWUSER,
  KC_JIGG,
  // Useful macros
  ARROW,
  DBLAROW,
  RSTPDBG,
  PARANT,
  DOUBLE0,
  DOTDOT,
  EXITENT,
  ABANG,
  ABANG2,
  ABANG3,
  AP,
  // Umlauts, currently not in use
  ADOTS, EDOTS, ODOTS, UDOTS,
  // Brackets
  LCURLY, RCURLY, LBRACK, RBRACK,
  // Alt-Gr
  CST_AT,
  CST_DLR,
  // Other stuff
  ALTTAB,
  TESTX,
};

// Key overrides
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t ctlesc_key_override = ko_make_basic(MOD_MASK_CTRL, KC_ESC, G(KC_L));
const key_override_t superl_key_override = ko_make_basic(MOD_MASK_GUI, KC_L, G(KC_RGHT));

// const key_override_t **key_overrides = (const key_override_t *[]) {
const key_override_t *key_overrides[] = {
    &delete_key_override,
    &ctlesc_key_override,
    &superl_key_override,
};

// Combos
// const uint16_t PROGMEM backslash_combo[] = { KC_J, KC_I, COMBO_END };
// const uint16_t PROGMEM ae_combo[] = { KC_K, KC_L, COMBO_END };
// const uint16_t PROGMEM aa_combo[] = { KC_K, KC_M, COMBO_END };

// combo_t key_combos[COMBO_COUNT] = {
//     COMBO(backslash_combo, NO_BSLS),
//     COMBO(ae_combo, NO_AE),
//     COMBO(aa_combo, NO_ARNG),
// };

// For the advanced tap dances. Put it here so it can be used in any keymap
void oe_finished(tap_dance_state_t *state, void *user_data);
void oe_reset(tap_dance_state_t *state, void *user_data);

// Tap dance declarations
enum {
    TD_ESC_CAPS,
    TD_OE_AA,
    TD_OE_AST,
    TD_ZERO,
    X_OE,
};

// Tap dance definitions
// tap_dance_action_t tap_dance_actions[] = {
//     //[TD_SLASH_TILDE] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, S(KC_RBRC)),
//     // tap once for esc, twice for caps lock
//     [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
//     [TD_OE_AA] = ACTION_TAP_DANCE_DOUBLE(NO_OSTR, NO_ARNG),
//     [TD_OE_AST] = ACTION_TAP_DANCE_DOUBLE(NO_OSTR, NO_ASTR),
// };

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

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool is_jiggling = false;
uint32_t idle_timeout = 10000;
uint32_t mouse_interval = 5000;


// KEYMAPS


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Norm(al) - Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  / ~ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  æøå |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Shift |Super |Lower |Space |Raise |Shift |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
//[_NORM] = LAYOUT_preonic_grid(
//  KC_ESC,             KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,   KC_0,    KC_BSPC,
//  LT(_RAISE, KC_TAB), HOMEALT, HOMECTL, HOMESFT, KC_R,    KC_T,   KC_Y,   KC_U,    HOME_I,  HOME_O, KC_P,    S_RBRC,
//  KC_LOWR,            KC_A,    KC_S,    KC_D,    HOMEGUI, KC_G,   KC_H,   KC_J,    KC_K,    KC_L,   TD(X_OE),KC_ENT,
//  OSMLSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, OSMLSFT,
//  KC_LCTL,            KC_NOEN, KC_LALT, KC_LGUI, KC_LOWR, KC_SPC, KC_SPC, KC_RAIS, QK_LEAD, FOUR,   FIVE,    KC_CORN
//),
[_NORM] = LAYOUT(
    KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
LSFT_T(KC_TAB), HOMEALT, HOMECTL, HOMESFT, KC_R,    KC_T,                               KC_Y,    KC_U,    HOME_I,  HOME_O,  KC_P,    S_RBRC,
    KC_LOWR,    KC_A,    KC_S,    KC_D,    HOMEGUI, KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    TD(X_OE),KC_ENT,
    KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OSMLSFT,
                                        OSMLSFT, KC_LGUI, KC_LOWR,            LGUI_T(KC_SPC), KC_RAIS, OSMLSFT
),
/* same as NORM but without homerow modifiers */
//[_GAME] = LAYOUT_preonic_grid(
//  KC_ESC,             KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,   KC_0,    KC_BSPC,
//  LT(_RAISE, KC_TAB), KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    S_RBRC,
//  KC_LOWR,            KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,   TD(X_OE),KC_ENT,
//  OSMLSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, OSMLSFT,
//  KC_LCTL,            KC_NOEN, KC_LALT, KC_LGUI, KC_LOWR, KC_SPC, KC_SPC, KC_RAIS, QK_LEAD, FOUR,   FIVE,    _______
//),
[_COLE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    TD(X_OE),S_RBRC,
    KC_LOWR, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_ENT,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                               KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, OSMLSFT,
                                        OSMLSFT, KC_LGUI, KC_LOWR,           LGUI_T(KC_SPC),  KC_RAIS, OSMLSFT
),
[_TARMAK1] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_J,    KC_R,    KC_T,                               KC_Y,    KC_U,    HOME_I,  HOME_O,  KC_P,    S_RBRC,
    KC_LOWR, KC_A,    KC_S,    KC_D,    HOMEGUI, KC_G,                               KC_H,    KC_N,    KC_E,    KC_L,    TD(X_OE),KC_ENT,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OSMLSFT,
                                        OSMLSFT, KC_LGUI, KC_LOWR,           LGUI_T(KC_SPC),  KC_RAIS, OSMLSFT
),



// TODO: consider a separate layer for key below TAB - it's really only used for wasd etc.

  //MO(_LOWER),      KC_A,    KC_S,    KC_D,    KC_F,             KC_G,   KC_H,   KC_J,              KC_K,    KC_L,   TD(TD_OE_AA), KC_ENT,
  //MO(_LOWER),      LCTL_T(KC_A),LALT_T(KC_S),LSFT_T(KC_D),LGUI_T(KC_F),     KC_G,   KC_H,   LGUI_T(KC_J),      LSFT_T(KC_K),  KC_L,   TD(TD_OE_AA), KC_ENT,

// WORK layout (not really being used...)
//[_WORK] = LAYOUT_preonic_grid(
//  KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,   KC_0,    KC_BSPC,
//  KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,   RCTL_P,  S_RBRC,
//  MO(_LOWER), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,   TD_OE_AA,KC_ENT,
//  KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
//  KC_LCTL,    KC_RCTL, KC_LALT, KC_LGUI, KC_LOWR, KC_SPC, KC_SPC, KC_RAIS, KC_LEAD, FOUR,   FIVE,    _______
//),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   &  |   /  |      |   +  |   ?  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |AltTab| PgUp |  Up  | PgDn |  ()  | [t]  | Home |   [  |   {  |   }  |   ]  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Left | Down |Right |   *  | [g]  |  &   |   :  |   ;  |   _  | {:?} |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |S-Ins | [b]  | End  |   <  |   >  |      |  =>  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
//_______, KC_PGUP, KC_UP,   KC_PGDN, PARANT,   _______, KC_HOME, ALGR(KC_8), ALGR(KC_7), ALGR(KC_0), ALGR(KC_9), NO_BSLS,

[_LOWER] = LAYOUT(
  KC_TILD, KC_EXLM, CST_AT,  KC_HASH, CST_DLR,   KC_PERC,                            KC_CIRC, KC_AMPR, _______, NO_PLUS, NO_QUES, KC_BSPC,
  ALTTAB,  KC_PGUP, KC_UP,   KC_PGDN, PARANT,    _______,                            KC_HOME, LBRACK,  LCURLY,  RCURLY,  RBRACK,  NO_BSLS,
  KC_JIGG, KC_LEFT, KC_DOWN, KC_RGHT, NO_ASTR,   _______,                            KC_CIRC, COLON,   SCOLON,  UNDERSC, RSTPDBG, _______,
  _______, _______, _______, _______, S(KC_INS), _______,                            KC_END,  NO_LABK, NO_RABK, _______, DBLAROW, _______,
                                        _______, _______, _______,         _______,  _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | EXIT | SEC1 | SEC2 | SEC3 | ADMPW|BANKID|      |      | G(-) | G(+) |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | MBTN1| M UP | MBTN2| MW UP|      |      |      |      |      |   |  |  '   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | MLEFT| M DWN| MRGHT| MWDWN|      |cd .. |Ctrl-B|      |  -   |      |  +   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |C-S-v |      |      |C-S-m |      |      |  ->  |Acute |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |NumLck|      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT(
  EXITENT, SECRET1, SECRET2, SECRET3,  ADMINPW,  PERSNR,                             _______, CWUSER,  G_MINUS, G_PLUS,  _______, _______,
  _______, KC_BTN1, KC_MS_U, KC_BTN2,  KC_WH_U,  _______,                            _______, _______, _______, _______, NO_PIPE, NO_QUOT,
  _______, KC_MS_L, KC_MS_D, KC_MS_R,  KC_WH_D,  _______,                            DOTDOT,  C(KC_B), NO_ACUT, CTSH_L,  _______, NO_PLUS,
  _______, SECRET4, SECRET5, SECRET6,  CTSH_V,   _______,                            _______, CTSH_M,  _______, _______, ARROW,   _______,
                                        _______, _______, _______,         _______,  _______, _______
),


/* Four
 * ,-----------------------------------------------------------------------------------.
 * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |Pr Scr|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |C-S-L |  ^   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
//[_FOUR] = LAYOUT_preonic_grid(
//  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
//  _______, _______, _______, EDOTS,   _______, _______, _______, UDOTS,   _______, ODOTS,   KC_PSCR, _______,
//  _______, ADOTS,   _______, _______, _______, _______, _______, _______, _______, CTSH_L,  CRCFLEX, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//),


/* Five
 * ,-----------------------------------------------------------------------------------.
 * |      | REC 1| REC 2|RECSTP| SEC4 | SEC5 | SEC6 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |PLAY 1|PLAY 2|      |      |      |      |      |      |      |S-PrSc|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
//[_FIVE] = LAYOUT_preonic_grid(
//  _______, DM_REC1, DM_REC2, DM_RSTP, SECRET4, SECRET5, SECRET6, _______, _______, _______, _______, _______,
//  _______, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, _______, _______, SH_PSCR, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//),

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      | KP 7 | KP 8 | KP 9 |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | KP 4 | KP 5 | KP 6 |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | KP 1 | KP 2 | KP 3 |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | KP 0 | KP 00|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
//[_CORNER] = LAYOUT_preonic_grid(
//  _______, _______, _______, _______, _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, KC_KP_0, DOUBLE0, KC_NUM,  _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//),
//
//[_MVMNT] = LAYOUT_preonic_grid(
//  _______, ABANG,   ABANG2,  ABANG3,  _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______,   AP,    KC_DEL,
//  _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//),
//
//[_NOENTER] = LAYOUT_preonic_grid(
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | SysRq|      |      |      |      |      |      |      |      |      |C-A-0 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |      | Debug|RGBTOG|RGB P |RGB B |RGB R |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud cy|Aud on|AudOff|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Boot |      |      |      |TLOWER|      |      |TRAISE|TMVMNT|      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_THIRD] = LAYOUT(
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                             KC_F6,     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F12,
  KC_CAPS, _______, _______, _______, _______, _______,                      DF(_TARMAK1), _______, _______, _______, _______, DF(_COLE),
  QK_BOOT, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, DF(_NORM), // DF(_WORK),
  KC_SYRQ, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
                                      _______, _______, _______,        _______,  _______, _______
),

};


// Functions and stuff

void keyboard_post_init_user(void) {
    set_tri_layer_layers(_LOWER, _RAISE, _THIRD);
}

static uint32_t idle_callback(uint32_t trigger_time, void *cb_arg) {
    // now idle-ing
    if (is_jiggling) {
        // SEND_STRING(SS_TAP(X_F15));
        tap_code(KC_MS_L);
        wait_ms(100);
        tap_code(KC_MS_R);
        return mouse_interval;
    }

    return 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static deferred_token idle_token = INVALID_DEFERRED_TOKEN;

    if (!extend_deferred_exec(idle_token, idle_timeout)) {
        idle_token = defer_exec(idle_timeout, idle_callback, NULL);
    }

    switch (keycode) {
        case KC_JIGG:
            if (record->event.pressed) {
                is_jiggling = !is_jiggling;
            }
            break;
        case NORM:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_NORM);
            }
            return false;
            break;
        case RSTPDBG:
            if (record->event.pressed) {
                SEND_STRING("{:?}");
            } else {
            }
            return false;
        case PARANT:
            if (record->event.pressed) {
                SEND_STRING("()");
                tap_code(KC_LEFT);
            }
            return false;
        case ARROW:
            if (record->event.pressed) {
                SEND_STRING("->");
            } else {
                // keycode is released
            }
            return false;
        case DBLAROW:
            if (record->event.pressed) {
                SEND_STRING("=>");
            } else {
                // keycode is released
            }
            return false;
        case CWUSER:
            if (record->event.pressed) {
                SEND_STRING("cwadmin-rokl");
            } else {
                // keycode is released
            }
            return false;
        case CST_AT:
            if (record->event.pressed) {
                register_code(KC_ALGR);
                wait_ms(ALTGR_WAIT);
                tap_code(KC_2);
                unregister_code(KC_ALGR);
            } else {
            }
            return false;
        case CST_DLR:
            if (record->event.pressed) {
                register_code(KC_ALGR);
                wait_ms(ALTGR_WAIT);
                tap_code(KC_4);
                unregister_code(KC_ALGR);
            } else {
            }
            return false;
        case LBRACK:
            if (record->event.pressed) {
                register_code(KC_ALGR);
                wait_ms(ALTGR_WAIT);
                tap_code(KC_8);
                unregister_code(KC_ALGR);
            } else {
            }
            return false;
        case RBRACK:
            if (record->event.pressed) {
                register_code(KC_ALGR);
                wait_ms(ALTGR_WAIT);
                tap_code(KC_9);
                unregister_code(KC_ALGR);
            } else {
            }
            return false;
        case LCURLY:
            if (record->event.pressed) {
                register_code(KC_ALGR);
                wait_ms(ALTGR_WAIT);
                tap_code(KC_7);
                unregister_code(KC_ALGR);
            } else {
            }
            return false;
        case RCURLY:
            if (record->event.pressed) {
                register_code(KC_ALGR);
                wait_ms(ALTGR_WAIT);
                tap_code(KC_0);
                unregister_code(KC_ALGR);
            } else {
            }
            return false;
        case ADOTS:
            if (record->event.pressed) {
                register_code(KC_ALGR);
                // tap_code(KC_RBRACKET);
                tap_code(KC_RBRC);
                unregister_code(KC_ALGR);
                // TODO: handle shift, there's probably a way...
                tap_code(KC_A);
            } else {
            }
            return false;
            break;
        case EDOTS:
            if (record->event.pressed) {
                register_code(KC_ALGR);
                // tap_code(KC_RBRACKET);
                tap_code(KC_RBRC);
                unregister_code(KC_ALGR);
                tap_code(KC_E);
            } else {
            }
            return false;
            break;
        case ODOTS:
            if (record->event.pressed) {
                register_code(KC_ALGR);
                // tap_code(KC_RBRACKET);
                tap_code(KC_RBRC);
                unregister_code(KC_ALGR);
                tap_code(KC_O);
            } else {
            }
            return false;
            break;
        case UDOTS:
            if (record->event.pressed) {
                register_code(KC_ALGR);
                // tap_code(KC_RBRACKET);
                tap_code(KC_RBRC);
                unregister_code(KC_ALGR);
                tap_code(KC_U);
            } else {
            }
            return false;
            break;
        case DOUBLE0:
            if (record->event.pressed) {
                tap_code(KC_KP_0);
                tap_code(KC_KP_0);
            } else {
            }
            return false;
            break;
        case ALTTAB: // ALT+TAB
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case DOTDOT:
            if (record->event.pressed) {
                SEND_STRING("cd .." SS_TAP(X_ENT));
            } else {
                // keycode DOTDOT is released
            }
            return false;
        case SECRET1:
            if (record->event.pressed) {
                SEND_STRING(PW1);
            } else {
                // keycode SECRET1 is released
            }
            return false;
        case SECRET2:
            if (record->event.pressed) {
                SEND_STRING(PW2);
            } else {
                // keycode SECRET2 is released
            }
            return false;
        case SECRET3:
            if (record->event.pressed) {
                SEND_STRING(PW3);
            } else {
                // keycode SECRET3 is released
            }
            return false;
        case SECRET5:
            if (record->event.pressed) {
                SEND_STRING(PW5);
            } else {
                // keycode SECRET5 is released
            }
            return false;
        case SECRET6:
            if (record->event.pressed) {
                SEND_STRING(PW6);
            } else {
                // keycode SECRET6 is released
            }
            return false;
        case ADMINPW:
            if (record->event.pressed) {
                SEND_STRING(ADMINUSER SS_TAP(X_TAB) ADMINPASS SS_TAP(X_ENT));
            } else {
                // keycode ADMINPW is released
            }
            return false;
        case PERSNR:
            if (record->event.pressed) {
                SEND_STRING(PNR);
            } else {
                // keycode is released
            }
            return false;
        case EXITENT:
            if (record->event.pressed) {
                SEND_STRING("exit\n");
            } else {
                // keycode is released
            }
            return false;
        case ABANG:
            if (record->event.pressed) {
              tap_code(KC_A);
              wait_ms(ALTGR_WAIT);
              SEND_STRING(" !\n");
            } else {
                // keycode is released
            }
            return false;
        case ABANG2:
            if (record->event.pressed) {
              tap_code(KC_A);
              wait_ms(ALTGR_WAIT);
              SEND_STRING(" !!\n");
            } else {
                // keycode is released
            }
            return false;
        case ABANG3:
            if (record->event.pressed) {
              tap_code(KC_A);
              wait_ms(ALTGR_WAIT);
              SEND_STRING(" !!!\n");
            } else {
                // keycode is released
            }
            return false;
        case AP:
            if (record->event.pressed) {
              tap_code(KC_A);
              wait_ms(ALTGR_WAIT);
              SEND_STRING(" p\n");
            } else {
                // keycode is released
            }
            return false;
      }
    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        // dash is on KC_SLSH in Norwegian layout
        case KC_SLSH:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
	return state;
}

void tmux_prefix(void) {
    register_code(KC_LCTL);
    tap_code(KC_B);
    unregister_code(KC_LCTL);
}

void leader_end_user(void) {
    // if (leader_sequence_one_key(KC_A)) {
    //     tmux_prefix();
    //     tap_code(KC_LEFT);
    // } else if (leader_sequence_one_key(KC_D)) {
    //     tmux_prefix();
    //     tap_code(KC_RIGHT);
    // } else if (leader_sequence_one_key(KC_W)) {
    //     tmux_prefix();
    //     tap_code(KC_UP);
    // } else if (leader_sequence_one_key(KC_S)) {
    //     tmux_prefix();
    //     tap_code(KC_DOWN);
    // } else if (leader_sequence_one_key(KC_B)) {
    //      SEND_STRING(EMAIL1);
    // }


    // old stuff
    //
    if(leader_sequence_one_key(KC_A)) {
        SEND_STRING(EMAIL1);
    } else if(leader_sequence_one_key(KC_R)) {
        SEND_STRING(EMAIL2);
    } else if(leader_sequence_one_key(KC_C)) {
        SEND_STRING(EMAIL3);
    } else if(leader_sequence_one_key(KC_W)) {
        SEND_STRING(CW);
    } else if(leader_sequence_one_key(KC_Q)) {
        SEND_STRING(":qa\n");
    }
}

void matrix_scan_user(void) {
    // Alt-Tab
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 600) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}



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

