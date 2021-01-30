#pragma once

#include <Dsp.hpp>
#include <Fsp.hpp>

#include <map>

namespace alba
{

using LcgIds = std::vector<unsigned int>;
using AddressToDspPair = std::pair<unsigned int, Dsp>;
using AddressToFspPair = std::pair<unsigned int, Fsp>;
using AddressToDspMap = std::map<unsigned int, Dsp>;
using AddressToFspMap = std::map<unsigned int, Fsp>;

class HardwareConfiguration
{
public:
    HardwareConfiguration();
    AddressToDspMap& getAddressToDspMapReference();
    AddressToFspMap& getAddressToFspMapReference();
    void clear();
    void changeConfigurationToOneFspOneLcgEvenDistribution();
    void changeConfigurationToOneFspTwoLcgEvenDistribution();
    void changeConfigurationToTwoFspOneLcgEvenDistribution();
    void changeConfigurationToTwoFspTwoLcgEvenDistribution();
    void changeConfigurationToTwoFspThreeLcgEvenDistribution();
    void changeConfigurationToTwoFspFourLcgEvenDistribution();
    void changeConfigurationToThreeFspOneLcgEvenDistribution();
    void changeConfigurationToThreeFspTwoLcgEvenDistribution();
    void changeConfigurationToThreeFspThreeLcgEvenDistribution();
    void changeConfigurationToThreeFspFourLcgEvenDistribution();
    void changeConfigurationToFourFspTwoLcgEvenDistribution();
    void changeConfigurationToFourFspThreeLcgEvenDistribution();
    unsigned int getTcomFspAddress() const;
    unsigned int getSharedLcgId() const;
    void printDspAllocations(unsigned int const printFlags=0);
private:
    void addFsp(unsigned int const fspAddress);
    void addDsp(unsigned int const dspAddress);
    void setLcgIdOfDsps(LcgIds const& lcgIds);
    NyquistType computeNyquistTypeBasedOnDspAddress(unsigned int const dspAddress) const;
    SmType getSmTypeBasedOnAddress(unsigned int const fspAddress) const;
    unsigned int m_sharedLcgId;
    unsigned int m_tcomFspAddress;
    AddressToDspMap m_dspAddressToDspMap;
    AddressToFspMap m_fspAddressToFspMap;
};

}
