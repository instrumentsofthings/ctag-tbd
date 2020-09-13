Title: Subset of VCV rack core lib port for IoT-Maker TBD Eurorack Module
Author: Henrik Langer (Instruments of Things) (c)
Date: September 2020

Description:
This is a subset of the VCV core lib ported to IoT-Maker TBD Eurorack module (ESP32).
The subset includes all necessary components to build the Befaco EvenVCO module.
Standard math functions were substituted with CTAG fastmath helpers (included in 
ctag-tbd firmware by default) for performance reasons.

Todo:
Port all components from VCV core lib related to audio processing by using Git
submodules.

Sources:
- https://github.com/ctag-fh-kiel/ctag-tbd
- https://github.com/VCVRack/Befaco
- https://github.com/VCVRack/Rack
- https://bitbucket.org/jpommier/pffft
