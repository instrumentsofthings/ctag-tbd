/**
 * Title: Port of SideChain by RJModules (VCV)
 * Author: Ported by Henrik Langer (Instruments of Things) to TBD
 * Email: henrik@instrumentsofthings.com
 * Date: September 2020
 * 
 * More information at https://github.com/Miserlou/RJModules
 */

#include <atomic>
#include "ctagSoundProcessor.hpp"

namespace CTAG {
    namespace SP {
        class ctagSoundProcessorSideChain : public ctagSoundProcessor {
        public:
            virtual void Process(const ProcessData &) override;

            virtual ~ctagSoundProcessorSideChain();

            ctagSoundProcessorSideChain();

            virtual const char *GetCStrID() const override;

        private:
            void setParamValueInternal(const string &id, const string &key, const int val) override;
            void loadPresetInternal() override;

// autogenerated code here
// sectionHpp
const string id = "SideChain";
void setIsStereo(){isStereo = false;}
atomic<int32_t> trigger, trig_trigger;
atomic<int32_t> ratio, cv_ratio;
atomic<int32_t> release, cv_release;
// sectionHpp


            // private attributes could go here
            bool trigLast = false;
            float decayAmount = 0.0;
        };
    }
}