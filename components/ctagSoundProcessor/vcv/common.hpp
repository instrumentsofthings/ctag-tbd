#pragma once
#include "math.hpp"
//#include <simd/functions.hpp>
#include "helpers/ctagFastMath.hpp"
#include "vcv/vcv.hpp"

namespace rack {


/** Digital signal processing routines
*/
namespace dsp {


// Constants

//static const float FREQ_C4 = 261.6256f;
//static const float FREQ_A4 = 440.0000f;
//static const float FREQ_SEMITONE = 1.0594630943592953f;

// Mathematical functions

/** The normalized sinc function
See https://en.wikipedia.org/wiki/Sinc_function
*/
inline float sinc(float x) {
	if (x == 0.f)
		return 1.f;
	x *= M_PI;
	return CTAG::SP::HELPERS::fastsin(x) / x;
}

template <typename T>
T sinc(T x) {
	T zeromask = (x == 0.f);
	x *= M_PI;
	x = CTAG::SP::HELPERS::fastsin(x) / x;
	return simd::ifelse(zeromask, 1.f, x);
}

// Conversion functions

template <typename T>
T amplitudeToDb(T amp) {
	return CTAG::SP::HELPERS::fast_log10(amp) * 20;
}

template <typename T>
T dbToAmplitude(T db) {
	return CTAG::SP::HELPERS::fasterpow10(db / 20);
}

// Functions for parameter scaling

template <typename T>
T quadraticBipolar(T x) {
	return simd::sgn(x) * (x * x);
}

template <typename T>
T cubic(T x) {
	return x * x * x;
}

template <typename T>
T quarticBipolar(T x) {
	return simd::sgn(x) * (x * x * x * x);
}

template <typename T>
T quintic(T x) {
	// optimal with -fassociative-math
	return x * x * x * x * x;
}

template <typename T>
T sqrtBipolar(T x) {
	return simd::sgn(x) * std::sqrt(x);
}

/** This is pretty much a scaled sinh.
Slow. Not recommended for parameter scaling.
*/
template <typename T>
T exponentialBipolar(T b, T x) {
	return (std::pow(b, x) - std::pow(b, -x)) / (b - 1.f / b);
}


/** Useful for storing arrays of samples in ring buffers and casting them to `float*` to be used by interleaved processors, like SampleRateConverter */
template <size_t CHANNELS, typename T = float>
struct Frame {
	T samples[CHANNELS];
};


} // namespace dsp
} // namespace rack
