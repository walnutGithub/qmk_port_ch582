/*
Copyright 2022 Huckies <https://github.com/Huckies>
Copyright 2023 OctopusZ <https://github.com/OctopusZ>

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

#pragma once

#include "quantum.h"
#include "extra_keycode.h"

#ifdef RGB_RAW_ENABLE
#include "dynamic_lighting.h"
#endif

// clang-format off

#define LAYOUT_all( \
	K000, K001, K002, K003, \
	K100, K101, K102, K103, \
	K200, K201, K202, K203, \
	K300, K301, K302, K303, \
	K400, K401, K402, K403, \
	K500, K501, K502, K503, \
	K600, K601, K602, K603, \
	K700, K701, K702, K703, \
	K800, K801, K802, K803, \
	K900, K901, K902, K903, \
	K100, K101, K102, K103, \
	K110, K111, K112, K113  \
) \
{ \
    { K000, K001, K002, K003 }, \
    { K100, K101, K102, K103 }, \
    { K200, K201, K202, K203 }, \
    { K300, K301, K302, K303 },  \
    { K400, K401, K402, K403 }, \
    { KC_NO, K501, K502, K503 }, \
    { KC_NO, K601, K602, K603 }, \
    { KC_NO, K701, K702, K703 }, \
    { KC_NO, K801, K802, K803 }, \
    { K900, KC_NO, K902, K903 }, \
    { K100, K101, KC_NO, K103 }, \
    { K110, K111, K112, K113 }  \
}
