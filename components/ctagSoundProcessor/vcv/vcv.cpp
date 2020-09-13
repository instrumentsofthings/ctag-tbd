/**
 * Title: Some helper functions from core API of VCV
 * Author: Henrik Langer (Instruments of Things)
 * Email: henrik@instrumentsofthings.com
 * Date: September 2020
 * 
 * API documentation at https://vcvrack.com/docs
 */

#include "vcv.hpp"

namespace rack
{
    namespace dsp
    {

    }
    namespace math
    {
        float rescale(float x, float xMin, float xMax, float yMin, float yMax)
        {
            return yMin + (x - xMin) / (xMax - xMin) * (yMax - yMin);
        }
        float clamp(float x, float a, float b)
        {
            return std::fmax(std::fmin(x, b), a);
        }
    } // namespace math
    namespace simd
    {
        float ifelse(bool cond, float a, float b)
        {
            return cond ? a : b;
        }
        template <typename T> int sgn(T val)
        {
            return (T(0) < val) - (val < T(0));
        }
    }
} // namespace rack
