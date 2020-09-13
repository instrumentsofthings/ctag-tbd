/**
 * Title: Port of EvenVCO by Befaco (VCV)
 * Author: Ported by Henrik Langer (Instruments of Things) to TBD
 * Email: henrik@instrumentsofthings.com
 * Date: September 2020
 * 
 * More information at https://github.com/VCVRack/Befaco
 */

#include <atomic>
#include "ctagSoundProcessor.hpp"
#include "vcv/minblep.hpp"

namespace CTAG
{
    namespace SP
    {
        class ctagSoundProcessorEvenVCO : public ctagSoundProcessor
        {
        public:
            virtual void Process(const ProcessData &) override;

            virtual ~ctagSoundProcessorEvenVCO();

            ctagSoundProcessorEvenVCO();

            virtual const char *GetCStrID() const override;

        private:
            void setParamValueInternal(const string &id, const string &key, const int val) override;
            void loadPresetInternal() override;

            // autogenerated code here
            // sectionHpp
            const string id = "EvenVCO";
            void setIsStereo() { isStereo = false; }
            atomic<int32_t> octave, cv_octave;
            atomic<int32_t> tune, cv_tune;
            atomic<int32_t> pwm, cv_pwm;
            // sectionHpp

            // private attributes could go here

            float phase = 0.0;
            /** The value of the last sync input */
            float sync = 0.0;
            /** The outputs */
            float tri = 0.0;
            /** Whether we are past the pulse width already */
            bool halfPhase = false;

            rack::dsp::MinBlepGenerator<16, 32> triSquareMinBlep;
            rack::dsp::MinBlepGenerator<16, 32> triMinBlep;
            rack::dsp::MinBlepGenerator<16, 32> sineMinBlep;
            rack::dsp::MinBlepGenerator<16, 32> doubleSawMinBlep;
            rack::dsp::MinBlepGenerator<16, 32> sawMinBlep;
            rack::dsp::MinBlepGenerator<16, 32> squareMinBlep;
        };
    } // namespace SP
} // namespace CTAG