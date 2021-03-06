/***************
CTAG TBD >>to be determined<< is an open source eurorack synthesizer module.

A project conceived within the Creative Technologies Arbeitsgruppe of
Kiel University of Applied Sciences: https://www.creative-technologies.de

(c) 2020 by Robert Manzke. All rights reserved.

The CTAG TBD software is licensed under the GNU General Public License
(GPL 3.0), available here: https://www.gnu.org/licenses/gpl-3.0.txt

The CTAG TBD hardware design is released under the Creative Commons
Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0).
Details here: https://creativecommons.org/licenses/by-nc-sa/4.0/

CTAG TBD is provided "as is" without any express or implied warranties.

License and copyright details for specific submodules are included in their
respective component folders / files if different from this license.
***************/


//
// Created by Robert Manzke on 20.02.20.
//
#include <cmath>
#include "ctagSineSource.hpp"
#include "ctagFastMath.hpp"

CTAG::SP::HELPERS::ctagSineSource::ctagSineSource() {
    //a = 2.f*(float)sin(M_PI*1000.f/44100.f);
    a = 2.f*(float)fastsin(M_PI*1000.f/44100.f);
    s[0] = 0.5f;
    s[1] = 0.f;
}

void CTAG::SP::HELPERS::ctagSineSource::SetSampleRate(float f_hz) {
    fSample = f_hz;
}

void CTAG::SP::HELPERS::ctagSineSource::SetFrequency(float f_hz) {
    //a = 2.f*(float)sin(M_PI*f_hz/fSample);
    a = 2.f*(float)fastsin(M_PI*f_hz/44100.f);
}

float CTAG::SP::HELPERS::ctagSineSource::Process() {
    s[0] = s[0] - a*s[1]; // sin
    s[1] = s[1] + a*s[0]; // cos
    return s[0];
}

float CTAG::SP::HELPERS::ctagSineSource::GetCos() {
    return s[1];
}

float CTAG::SP::HELPERS::ctagSineSource::GetSin() {
    return s[0];
}
