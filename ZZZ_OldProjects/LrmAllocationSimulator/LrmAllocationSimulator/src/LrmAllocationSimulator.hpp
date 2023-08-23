#pragma once

#include <Dsp.hpp>
#include <Fsp.hpp>

#include <map>

namespace alba {

struct Configuration {
    std::map<unsigned int, Dsp> dspAddressToDspMap;
    std::map<unsigned int, Fsp> fspAddressToFspMap;
};

class LrmAllocationSimulator {
public:
    LrmAllocationSimulator();
    Configuration createConfigurationForOneFspOneLcg();
    Configuration createConfigurationForTwoFspsOneLcg();
    void addFspInConfiguration(unsigned int address);

private:
};

}  // namespace alba
