#include "ctagSoundProcessorSideChain.hpp"
#include <iostream>
#include "vcv/vcv.hpp"

using namespace CTAG::SP;

ctagSoundProcessorSideChain::ctagSoundProcessorSideChain()
{
	setIsStereo();
	model = std::make_unique<ctagSPDataModel>(id, isStereo);
	model->LoadPreset(0);
}

void ctagSoundProcessorSideChain::Process(const ProcessData &data)
{
	float decayLambda = .0001f;
	float fRatio = static_cast<float>(ratio) / 4095.f;
	float fRelease = static_cast<float>(release) / 4095.f;
	float fCvRatio = 1.f, fCvRelease = 1.f;

	// process cv and pot parameters.
	// if external input is set to none (i.e. -1), use default value of 1.
	if (cv_ratio != -1)
	{
		fCvRatio = rack::math::clamp(data.cv[cv_ratio], 0.f, 1.f);
	}
	fRatio = fRatio * fCvRatio;

	if (cv_release != -1)
	{
		fCvRelease = rack::math::clamp(data.cv[cv_release], 0.f, 1.f);
	}
	fRelease = 1.f - (fRelease * fCvRelease) + .00001f;

	// process audio samples
	for (int i = 0; i < this->bufSz; i++)
	{

		// check if trigger was detected (rising edge)
		if (trig_trigger != -1 && data.trig[trig_trigger] != trigLast)
		{
			if ((trigLast = data.trig[trig_trigger]) == 1) // trigger detected
			{
				decayAmount = fCvRatio;
			}
		}

		data.buf[i * 2 + this->processCh] = data.buf[i * 2 + this->processCh] * (1.f - (fRatio * decayAmount));
		decayAmount = (decayAmount - (decayLambda * fRelease));
		if (decayAmount < 0.f)
		{
			decayAmount = 0.f;
		}
	}
}

ctagSoundProcessorSideChain::~ctagSoundProcessorSideChain()
{
}

const char *ctagSoundProcessorSideChain::GetCStrID() const
{
	return id.c_str();
}

void ctagSoundProcessorSideChain::setParamValueInternal(const string &id, const string &key, const int val)
{
	// autogenerated code here
	// sectionCpp0
	if (id.compare("trigger") == 0)
	{
		if (key.compare("current") == 0)
		{
			trigger = val;
			return;
		}
		else if (key.compare("trig") == 0)
		{
			if (val >= -1 && val <= 1)
				trig_trigger = val;
		}
		return;
	}
	if (id.compare("ratio") == 0)
	{
		if (key.compare("current") == 0)
		{
			ratio = val;
			return;
		}
		else if (key.compare("cv") == 0)
		{
			if (val >= -1 && val <= 3)
				cv_ratio = val;
		}
		return;
	}
	if (id.compare("release") == 0)
	{
		if (key.compare("current") == 0)
		{
			release = val;
			return;
		}
		else if (key.compare("cv") == 0)
		{
			if (val >= -1 && val <= 3)
				cv_release = val;
		}
		return;
	}
	// sectionCpp0
}

void ctagSoundProcessorSideChain::loadPresetInternal()
{
	// autogenerated code here
	// sectionCpp1
	trigger = model->GetParamValue("trigger", "current");
	trig_trigger = model->GetParamValue("trigger", "trig");
	ratio = model->GetParamValue("ratio", "current");
	cv_ratio = model->GetParamValue("ratio", "cv");
	release = model->GetParamValue("release", "current");
	cv_release = model->GetParamValue("release", "cv");
	// sectionCpp1
}
