#include "ctagSoundProcessorEvenVCO.hpp"
#include <iostream>
#include "helpers/ctagFastMath.hpp"
//#include "vcv/vcv.hpp"

#define SAMPLE_RATE 44100.0
#define SAMPLE_TIME 1.0 / SAMPLE_RATE

using namespace CTAG::SP;

ctagSoundProcessorEvenVCO::ctagSoundProcessorEvenVCO()
{
	setIsStereo();
	model = std::make_unique<ctagSPDataModel>(id, isStereo);
	model->LoadPreset(0);
}

// TODO: Integrate CV values
void ctagSoundProcessorEvenVCO::Process(const ProcessData &data)
{
	float fOctave = static_cast<float>(octave);
	float fTune = static_cast<float>(tune) / 1000.0f;
	float fPWM = static_cast<float>(pwm) / 1000.f;

	for (int i = 0; i < this->bufSz; i++)
	{
		// Compute frequency, pitch is 1V/oct
		float pitch = 1.f + fOctave + fTune / 12.f;
		//pitch += inputs[PITCH1_INPUT].getVoltage() + inputs[PITCH2_INPUT].getVoltage();
		//pitch += inputs[FM_INPUT].getVoltage() / 4.f;
		float freq = rack::dsp::FREQ_C4 * CTAG::SP::HELPERS::fastpow2(pitch);
		freq = rack::math::clamp(freq, 0.f, 20000.f);

		// Pulse width
		float pw = fPWM /* + inputs[PWM_INPUT].getVoltage() / 5.f*/;

		const float minPw = 0.05;
		pw = rack::math::rescale(rack::math::clamp(pw, -1.f, 1.f), -1.f, 1.f, minPw, 1.f - minPw);

		// Advance phase
		float deltaPhase = rack::math::clamp(freq * SAMPLE_TIME, 1e-6f, 0.5f);
		float oldPhase = phase;
		phase += deltaPhase;

		if (oldPhase < 0.5 && phase >= 0.5)
		{
			float crossing = -(phase - 0.5) / deltaPhase;
			triSquareMinBlep.insertDiscontinuity(crossing, 2.f);
			doubleSawMinBlep.insertDiscontinuity(crossing, -2.f);
		}

		if (!halfPhase && phase >= pw)
		{
			float crossing = -(phase - pw) / deltaPhase;
			squareMinBlep.insertDiscontinuity(crossing, 2.f);
			halfPhase = true;
		}

		// Reset phase if at end of cycle
		if (phase >= 1.f)
		{
			phase -= 1.f;
			float crossing = -phase / deltaPhase;
			triSquareMinBlep.insertDiscontinuity(crossing, -2.f);
			doubleSawMinBlep.insertDiscontinuity(crossing, -2.f);
			squareMinBlep.insertDiscontinuity(crossing, -2.f);
			sawMinBlep.insertDiscontinuity(crossing, -2.f);
			halfPhase = false;
		}

		// Outputs
		float triSquare = (phase < 0.5) ? -1.f : 1.f;
		triSquare += triSquareMinBlep.process();

		// Integrate square for triangle
		tri += 4.f * triSquare * freq * SAMPLE_TIME;
		tri *= (1.f - 40.f * SAMPLE_TIME);

		float sine = -CTAG::SP::HELPERS::fastcos(2 * M_PI * phase);
		float doubleSaw = (phase < 0.5) ? (-1.f + 4.f * phase) : (-1.f + 4.f * (phase - 0.5));
		doubleSaw += doubleSawMinBlep.process();
		float even = 0.55 * (doubleSaw + 1.27 * sine);
		float saw = -1.f + 2.f * phase;
		saw += sawMinBlep.process();
		float square = (phase < pw) ? -1.f : 1.f;
		square += squareMinBlep.process();

		// param to select waveform (TODO: add parameter to plugin descriptor)
		int wavParam = 0;
		switch (wavParam)
		{
		default:
		case 0:
			data.buf[i * 2 + this->processCh] = tri;
			break;
		case 1:
			data.buf[i * 2 + this->processCh] = sine;
			break;
		case 2:
			data.buf[i * 2 + this->processCh] = even;
			break;
		case 3:
			data.buf[i * 2 + this->processCh] = saw;
			break;
		case 4:
			data.buf[i * 2 + this->processCh] = square;
			break;
		}
	}
}

ctagSoundProcessorEvenVCO::~ctagSoundProcessorEvenVCO()
{
}

const char *ctagSoundProcessorEvenVCO::GetCStrID() const
{
	return id.c_str();
}

void ctagSoundProcessorEvenVCO::setParamValueInternal(const string &id, const string &key, const int val)
{
	// autogenerated code here
	// sectionCpp0
	if (id.compare("octave") == 0)
	{
		if (key.compare("current") == 0)
		{
			octave = val;
			return;
		}
		else if (key.compare("cv") == 0)
		{
			if (val >= -1 && val <= 3)
				cv_octave = val;
		}
		return;
	}
	if (id.compare("tune") == 0)
	{
		if (key.compare("current") == 0)
		{
			tune = val;
			return;
		}
		else if (key.compare("cv") == 0)
		{
			if (val >= -1 && val <= 3)
				cv_tune = val;
		}
		return;
	}
	if (id.compare("pwm") == 0)
	{
		if (key.compare("current") == 0)
		{
			pwm = val;
			return;
		}
		else if (key.compare("cv") == 0)
		{
			if (val >= -1 && val <= 3)
				cv_pwm = val;
		}
		return;
	}
	// sectionCpp0
}

void ctagSoundProcessorEvenVCO::loadPresetInternal()
{
	// autogenerated code here
	// sectionCpp1
	octave = model->GetParamValue("octave", "current");
	cv_octave = model->GetParamValue("octave", "cv");
	tune = model->GetParamValue("tune", "current");
	cv_tune = model->GetParamValue("tune", "cv");
	pwm = model->GetParamValue("pwm", "current");
	cv_pwm = model->GetParamValue("pwm", "cv");
	// sectionCpp1
}
