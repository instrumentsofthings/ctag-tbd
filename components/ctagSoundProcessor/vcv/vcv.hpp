/**
 * Title: Some helper functions from core API of VCV
 * Author: Henrik Langer (Instruments of Things)
 * Email: henrik@instrumentsofthings.com
 * Date: September 2020
 * 
 * API documentation at https://vcvrack.com/docs
 */

#pragma once

#include <numeric>

namespace rack
{
    namespace dsp
    {
        static const float FREQ_C4 = 261.6256f;
        static const float FREQ_A4 = 440.0000f;
        static const float FREQ_SEMITONE = 1.0594630943592953f;
    } // namespace dsp
    namespace math
    {
        float clamp(float x, float a, float b);
        float rescale(float x, float xMin, float xMax, float yMin, float yMax);
    } // namespace math
    namespace simd
    {
        float ifelse(bool cond, float a, float b);
        template <typename T> int sgn(T val);
    } // namespace simd
} // namespace rack
