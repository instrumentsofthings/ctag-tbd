/**
 * Title: Virtual Analog Moog Ladder Filter based on Huovilainen model (CSound).
 * Author: Ported by Henrik Langer (Instruments of Things) to TBD
 * Email: henrik@instrumentsofthings.com
 * Date: September 2020
 * 
 * Huovilainen developed an improved and physically correct model of the Moog
 * Ladder filter that builds upon the work done by Smith and Stilson. This model
 * inserts nonlinearities inside each of the 4 one-pole sections on account of the
 * smoothly saturating function of analog transistors. The base-emitter voltages of
 * the transistors are considered with an experimental value of 1.22070313 which
 * maintains the characteristic sound of the analog Moog. This model also permits
 * self-oscillation for resonances greater than 1. The model depends on five
 * hyperbolic tangent functions (tanh) for each sample, and an oversampling factor
 * of two (preferably higher, if possible). Although a more faithful
 * representation of the Moog ladder, these dependencies increase the processing
 * time of the filter significantly. Lastly, a half-sample delay is introduced for 
 * phase compensation at the final stage of the filter. 
 * References: Huovilainen (2004), Huovilainen (2010), DAFX - Zolzer (ed) (2nd ed)
 * Original implementation: Victor Lazzarini for CSound5
 * Considerations for oversampling: 
 * http://music.columbia.edu/pipermail/music-dsp/2005-February/062778.html
 * http://www.synthmaker.co.uk/dokuwiki/doku.php?id=tutorials:oversampling
 * 
 * More information at https://github.com/ddiakopoulos/MoogLadders
 */

#include <atomic>
#include "ctagSoundProcessor.hpp"

namespace CTAG {
    namespace SP {
        class ctagSoundProcessorMoogFilt1 : public ctagSoundProcessor {
        public:
            virtual void Process(const ProcessData &) override;
            virtual ~ctagSoundProcessorMoogFilt1();
            ctagSoundProcessorMoogFilt1();
            virtual const char *GetCStrID() const override;

        private:
            void setParamValueInternal(const string &id, const string &key, const int val) override;
            void loadPresetInternal() override;

// autogenerated code here
// sectionHpp
const string id = "MoogFilt1";
void setIsStereo(){isStereo = false;}
atomic<int32_t> cutoff, cv_cutoff;
atomic<int32_t> resonance, cv_resonance;
// sectionHpp






            // private attributes could go here
            float stage[4];
	        float stageTanh[3];
	        float delay[6];

	        float thermal;
	        float tune;
	        float acr;
	        float resQuad;
        };
    }
}