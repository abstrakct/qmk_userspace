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

#pragma once

#define TAPPING_TERM 250
// #define IGNORE_MOD_TAP_INTERRUPT

#define TAPPING_TOGGLE 2

#define LEADER_TIMEOUT 500

#define COMBO_COUNT 1

// Mouse key settings
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MOVE_DELTA 4
#define MOUSEKEY_WHEEL_MAX_SPEED 16

#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// Audio stuff
#define AUDIO_INIT_DELAY

#define IMPERIAL_MARCH_CUSTOM HD_NOTE(_A4), HD_NOTE(_A4), HD_NOTE(_A4), QD_NOTE(_F4), QD_NOTE(_C5), HD_NOTE(_A4), QD_NOTE(_F4), QD_NOTE(_C5), WD_NOTE(_A4), HD_NOTE(_E5), HD_NOTE(_E5), HD_NOTE(_E5), QD_NOTE(_F5), QD_NOTE(_C5), HD_NOTE(_A4), QD_NOTE(_F4), QD_NOTE(_C5), WD_NOTE(_A4)
#define ZELDA_TREASURE_CUSTOM Q__NOTE(_A4 ),Q__NOTE(_AS4),Q__NOTE(_B4 ),HD_NOTE(_C5 )

#ifdef AUDIO_ENABLE
//#    define STARTUP_SONG SONG(PREONIC_SOUND)

//#define STARTUP_SONG SONG(ZELDA_TREASURE_CUSTOM)
//#define STARTUP_SONG SONG(IMPERIAL_MARCH_CUSTOM)
#define STARTUP_SONG SONG(NO_SOUND)

#    define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND), SONG(DVORAK_SOUND) }
#endif

#define MUSIC_MASK (keycode != KC_NO)

/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2
