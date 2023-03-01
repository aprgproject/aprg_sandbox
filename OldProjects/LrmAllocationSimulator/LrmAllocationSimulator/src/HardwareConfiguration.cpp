#include "HardwareConfiguration.hpp"

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/User/DisplayTable.hpp>

#include <cassert>
#include <iostream>
#include <sstream>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

constexpr unsigned int TCOM_FSP_ADDRESS = 0x1200;

HardwareConfiguration::HardwareConfiguration()
    : m_sharedLcgId(0)
    , m_tcomFspAddress(0)
{}

AddressToDspMap& HardwareConfiguration::getAddressToDspMapReference()
{
    return m_dspAddressToDspMap;
}

AddressToFspMap& HardwareConfiguration::getAddressToFspMapReference()
{
    return m_fspAddressToFspMap;
}

void HardwareConfiguration::clear()
{
    m_dspAddressToDspMap.clear();
    m_fspAddressToFspMap.clear();
}

void HardwareConfiguration::changeConfigurationToOneFspOneLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
}

void HardwareConfiguration::changeConfigurationToOneFspTwoLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    setLcgIdOfDsps(LcgIds{2,1,1,2,2,1});
}

void HardwareConfiguration::changeConfigurationToTwoFspOneLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
}

void HardwareConfiguration::changeConfigurationToTwoFspTwoLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    setLcgIdOfDsps(LcgIds{1,1,2,2,1,1,2,2,1,1,2,2});
}

void HardwareConfiguration::changeConfigurationToTwoFspThreeLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    setLcgIdOfDsps(LcgIds{1,1,2,2,3,3,1,1,2,2,3,3});
}

void HardwareConfiguration::changeConfigurationToTwoFspFourLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    setLcgIdOfDsps(LcgIds{3,1,4,2,1,3,2,4,3,1,4,2});
}

void HardwareConfiguration::changeConfigurationToThreeFspOneLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
}

void HardwareConfiguration::changeConfigurationToThreeFspTwoLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    setLcgIdOfDsps(LcgIds{2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1});
}

void HardwareConfiguration::changeConfigurationToThreeFspThreeLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    setLcgIdOfDsps(LcgIds{1,1,2,2,3,3,1,1,2,2,3,3,1,1,2,2,3,3});
}

void HardwareConfiguration::changeConfigurationToThreeFspFourLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    setLcgIdOfDsps(LcgIds{2,1,1,2,3,3,4,4,2,1,1,2,3,3,4,4,2,1});
}

void HardwareConfiguration::changeConfigurationToFourFspTwoLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=2;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    addFsp(0x2200);
    setLcgIdOfDsps(LcgIds{1,1,2,2,1,1,2,2,1,1,1,2,1,1,1,2,1,1,2,2,2,2,2,2});
}

void HardwareConfiguration::changeConfigurationToFourFspThreeLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=3;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    addFsp(0x2200);
    setLcgIdOfDsps(LcgIds{2,2,1,1,2,3,1,2,2,1,1,3,2,2,1,1,2,3,3,3,3,3,3,3});
}

void HardwareConfiguration::changeConfigurationToFourFspFourLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    addFsp(0x2200);
    setLcgIdOfDsps(LcgIds{1,1,2,2,3,3,1,1,2,2,3,3,1,1,2,2,3,3,4,4,4,4,4,4});
}

void HardwareConfiguration::changeConfigurationToFiveFspTwoLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=2;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    addFsp(0x2200);
    addFsp(0x2300);
    setLcgIdOfDsps(LcgIds{1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2});
}

void HardwareConfiguration::changeConfigurationToFiveFspThreeLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=2;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    addFsp(0x2200);
    addFsp(0x2300);
    setLcgIdOfDsps(LcgIds{1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,3,3,3,2,3,3,3,2,3,3,3,3});
}

void HardwareConfiguration::changeConfigurationToFiveFspFourLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=1;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    addFsp(0x2200);
    addFsp(0x2300);
    setLcgIdOfDsps(LcgIds{3,3,4,4,1,1,3,3,4,4,3,1,4,3,3,4,4,1,2,2,1,1,2,2,2,1,2,2,2,1});
}

void HardwareConfiguration::changeConfigurationToSixFspTwoLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    addFsp(0x2200);
    addFsp(0x2300);
    addFsp(0x2400);
    setLcgIdOfDsps(LcgIds{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2});
}

void HardwareConfiguration::changeConfigurationToSixFspThreeLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=2;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    addFsp(0x2200);
    addFsp(0x2300);
    addFsp(0x2400);
    setLcgIdOfDsps(LcgIds{1,1,2,2,1,1,2,2,1,1,1,2,1,1,1,2,1,1,3,3,2,2,3,3,2,2,3,3,3,2,3,3,3,2,3,3});
}

void HardwareConfiguration::changeConfigurationToSixFspFourLcgEvenDistribution()
{
    clear();
    m_sharedLcgId=0;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    addFsp(0x2200);
    addFsp(0x2300);
    addFsp(0x2400);
    setLcgIdOfDsps(LcgIds{2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3});
}

void HardwareConfiguration::changeConfigurationToSharedLcgWithOneDspInMsm()
{
    clear();
    m_sharedLcgId=2;
    m_tcomFspAddress=TCOM_FSP_ADDRESS;
    addFsp(0x1200);
    addFsp(0x1300);
    addFsp(0x1400);
    addFsp(0x2200);
    addFsp(0x2300);
    addFsp(0x2400);
    setLcgIdOfDsps(LcgIds{1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2});
}

unsigned int HardwareConfiguration::getTcomFspAddress() const
{
    return m_tcomFspAddress;
}

unsigned int HardwareConfiguration::getSharedLcgId() const
{
    return m_sharedLcgId;
}

void HardwareConfiguration::printDspAllocations(unsigned int const printFlags)
{
    if(m_sharedLcgId!=0)
    {
        cout<<"SharedLcg: "<<m_sharedLcgId<<"\n";
    }
    DisplayTable table;
    table.setBorders("-"," | ");    table.addRow();
    table.getLastRow().addCell(" ");
    for(unsigned int cpu=30; cpu<=80 ;cpu+=10)
    {        stringstream streamTemp;
        streamTemp<<"0x"<<cpu<<" "<<(cpu%20==0 ? "TN" : "N");
        table.getLastRow().addCell(streamTemp.str(), DisplayTableCellMode::center);
    }
    for(auto const& addressToFspPair : m_fspAddressToFspMap)
    {
        table.addRow();
        stringstream firstCellStream;
        firstCellStream<<"0x"<<hex<<addressToFspPair.first<<dec;
        table.getLastRow().addCell(firstCellStream.str());
        for(unsigned int const dspAddress : addressToFspPair.second.getDspAddresses())
        {
            Dsp& dsp(m_dspAddressToDspMap.at(dspAddress));
            stringstream streamTemp;
            streamTemp<<"LCG:"<<dsp.getLcgId()<<"\n"<<dsp.getNbicString()<<dsp.getModeString();
            table.getLastRow().addCell(streamTemp.str(), DisplayTableCellMode::center);
        }
        if((printFlags & 1) > 0) //users
        {
            table.addRow();
            table.getLastRow().addCell("");
            for(unsigned int const dspAddress : addressToFspPair.second.getDspAddresses())
            {
                Dsp& dsp(m_dspAddressToDspMap.at(dspAddress));
                stringstream streamTemp;
                streamTemp<<"Users:"<<dsp.getNumberOfDchUsers();
                table.getLastRow().addCell(streamTemp.str(), DisplayTableCellMode::center);
            }
        }
        if((printFlags & 2) > 0) //DLI
        {
            table.addRow();
            table.getLastRow().addCell("");
            for(unsigned int const dspAddress : addressToFspPair.second.getDspAddresses())
            {
                Dsp& dsp(m_dspAddressToDspMap.at(dspAddress));
                stringstream streamTemp;
                streamTemp<<"DLI:"<<dsp.getDliPool();
                table.getLastRow().addCell(streamTemp.str(), DisplayTableCellMode::center);
            }
        }
    }
    cout<<table;
}

void HardwareConfiguration::addFsp(unsigned int const fspAddress){
    unsigned int correctFspAddress = fspAddress & 0xFF00;
    FspDetails fspDetails;
    fspDetails.smType = getSmTypeBasedOnAddress(correctFspAddress);    fspDetails.isMasterTcom = correctFspAddress==TCOM_FSP_ADDRESS;
    fspDetails.address = correctFspAddress;
    for(unsigned int cpu = 0x30; cpu<=0x80; cpu+=0x10)
    {
        unsigned int dspAddress = correctFspAddress | cpu;
        fspDetails.dspAddresses.emplace_back(dspAddress);
        addDsp(dspAddress);
    }
    m_fspAddressToFspMap.emplace(correctFspAddress, fspDetails);
}

void HardwareConfiguration::addDsp(unsigned int const dspAddress)
{
    DspDetails dspDetails;
    dspDetails.address = dspAddress;
    dspDetails.lcgId = 1;
    dspDetails.nyquistType = computeNyquistTypeBasedOnDspAddress(dspAddress);
    m_dspAddressToDspMap.emplace(dspAddress, dspDetails);
}

void HardwareConfiguration::setLcgIdOfDsps(LcgIds const& lcgIds)
{
    assert(lcgIds.size() == m_dspAddressToDspMap.size());

    AddressToDspMap::iterator mapIterator = m_dspAddressToDspMap.begin();
    AddressToDspMap::iterator mapIteratorEnd = m_dspAddressToDspMap.end();
    LcgIds::const_iterator lcgIdsIterator = lcgIds.cbegin();
    LcgIds::const_iterator lcgIdsIteratorEnd = lcgIds.cend();
    while(lcgIdsIterator!=lcgIdsIteratorEnd && mapIterator!=mapIteratorEnd)
    {
        mapIterator->second.setLcgId(*lcgIdsIterator);
        lcgIdsIterator++;
        mapIterator++;
    }
}

NyquistType HardwareConfiguration::computeNyquistTypeBasedOnDspAddress(unsigned int const dspAddress) const
{
    bool isCpuEven = isEven((dspAddress & 0x00F0) >> 4);
    return isCpuEven ? NyquistType::TurboNyquist : NyquistType::Nyquist;
}

SmType HardwareConfiguration::getSmTypeBasedOnAddress(unsigned int const fspAddress) const
{
    return ((fspAddress & 0xF000) >> 12 == 1) ? SmType::MSM : SmType::ESM;
}


}
