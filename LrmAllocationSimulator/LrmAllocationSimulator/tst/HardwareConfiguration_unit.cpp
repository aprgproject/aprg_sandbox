#include <HardwareConfiguration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(HardwareConfigurationTest, OneFspOneLcgEvenDistribution)
{
    HardwareConfiguration hardwareConfiguration;    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();
    AddressToDspMap& addressToDspMap(hardwareConfiguration.getAddressToDspMapReference());
    AddressToFspMap& addressToFspMap(hardwareConfiguration.getAddressToFspMapReference());
    Dsp& dspIn1230(addressToDspMap.at(0x1230));    Dsp& dspIn1240(addressToDspMap.at(0x1240));
    Fsp& fspIn1200(addressToFspMap.at(0x1200));

    EXPECT_EQ(0x1230u, dspIn1230.getAddress());
    EXPECT_EQ(0u, dspIn1230.getNumberOfDchUsers());
    EXPECT_EQ(0u, dspIn1230.getNumberOfHsupaCfs());
    EXPECT_EQ(DspMode::NyquistDedicatedChannelDevice, dspIn1230.getMode());

    EXPECT_EQ(NyquistType::Nyquist, dspIn1230.getNyquistType());
    EXPECT_EQ(NyquistType::TurboNyquist, dspIn1240.getNyquistType());

    EXPECT_EQ(1u, dspIn1230.getLcgId());

    EXPECT_EQ(0x1200u, fspIn1200.getAddress());
    EXPECT_TRUE(fspIn1200.isMasterTcom());
}

TEST(HardwareConfigurationTest, OneFspTwoLcgEvenDistribution)
{
    HardwareConfiguration hardwareConfiguration;
    hardwareConfiguration.changeConfigurationToOneFspTwoLcgEvenDistribution();
    AddressToDspMap& addressToDspMap(hardwareConfiguration.getAddressToDspMapReference());
    AddressToFspMap& addressToFspMap(hardwareConfiguration.getAddressToFspMapReference());
    Dsp& dspIn1230(addressToDspMap.at(0x1230));
    Dsp& dspIn1240(addressToDspMap.at(0x1240));
    Dsp& dspIn1250(addressToDspMap.at(0x1250));
    Dsp& dspIn1260(addressToDspMap.at(0x1260));
    Dsp& dspIn1270(addressToDspMap.at(0x1270));
    Dsp& dspIn1280(addressToDspMap.at(0x1280));
    Fsp& fspIn1200(addressToFspMap.at(0x1200));

    EXPECT_EQ(0x1230u, dspIn1230.getAddress());
    EXPECT_EQ(0u, dspIn1230.getNumberOfDchUsers());
    EXPECT_EQ(0u, dspIn1230.getNumberOfHsupaCfs());
    EXPECT_EQ(DspMode::NyquistDedicatedChannelDevice, dspIn1230.getMode());

    EXPECT_EQ(NyquistType::Nyquist, dspIn1230.getNyquistType());
    EXPECT_EQ(NyquistType::TurboNyquist, dspIn1240.getNyquistType());

    EXPECT_EQ(2u, dspIn1230.getLcgId());
    EXPECT_EQ(1u, dspIn1240.getLcgId());
    EXPECT_EQ(1u, dspIn1250.getLcgId());
    EXPECT_EQ(2u, dspIn1260.getLcgId());
    EXPECT_EQ(2u, dspIn1270.getLcgId());
    EXPECT_EQ(1u, dspIn1280.getLcgId());

    EXPECT_EQ(0x1200u, fspIn1200.getAddress());
    EXPECT_TRUE(fspIn1200.isMasterTcom());
}

TEST(HardwareConfigurationTest, TwoFspOneLcgEvenDistribution_CheckSecondFsp)
{
    HardwareConfiguration hardwareConfiguration;
    hardwareConfiguration.changeConfigurationToTwoFspOneLcgEvenDistribution();
    AddressToDspMap& addressToDspMap(hardwareConfiguration.getAddressToDspMapReference());
    AddressToFspMap& addressToFspMap(hardwareConfiguration.getAddressToFspMapReference());
    Dsp& dspIn1330(addressToDspMap.at(0x1330));
    Dsp& dspIn1340(addressToDspMap.at(0x1340));
    Fsp& fspIn1300(addressToFspMap.at(0x1300));

    EXPECT_EQ(0x1330u, dspIn1330.getAddress());
    EXPECT_EQ(0u, dspIn1330.getNumberOfDchUsers());
    EXPECT_EQ(0u, dspIn1330.getNumberOfHsupaCfs());
    EXPECT_EQ(DspMode::NyquistDedicatedChannelDevice, dspIn1330.getMode());

    EXPECT_EQ(NyquistType::Nyquist, dspIn1330.getNyquistType());
    EXPECT_EQ(NyquistType::TurboNyquist, dspIn1340.getNyquistType());

    EXPECT_EQ(1u, dspIn1330.getLcgId());

    EXPECT_EQ(0x1300u, fspIn1300.getAddress());
    EXPECT_FALSE(fspIn1300.isMasterTcom());
}

TEST(HardwareConfigurationTest, TwoFspTwoLcgEvenDistribution)
{
    HardwareConfiguration hardwareConfiguration;
    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    AddressToDspMap& addressToDspMap(hardwareConfiguration.getAddressToDspMapReference());
    AddressToFspMap& addressToFspMap(hardwareConfiguration.getAddressToFspMapReference());
    Dsp& dspIn1230(addressToDspMap.at(0x1230));
    Dsp& dspIn1240(addressToDspMap.at(0x1240));
    Dsp& dspIn1250(addressToDspMap.at(0x1250));
    Dsp& dspIn1260(addressToDspMap.at(0x1260));
    Dsp& dspIn1270(addressToDspMap.at(0x1270));
    Dsp& dspIn1280(addressToDspMap.at(0x1280));
    Dsp& dspIn1330(addressToDspMap.at(0x1330));
    Dsp& dspIn1340(addressToDspMap.at(0x1340));
    Dsp& dspIn1350(addressToDspMap.at(0x1350));
    Dsp& dspIn1360(addressToDspMap.at(0x1360));
    Dsp& dspIn1370(addressToDspMap.at(0x1370));
    Dsp& dspIn1380(addressToDspMap.at(0x1380));
    Fsp& fspIn1200(addressToFspMap.at(0x1200));
    Fsp& fspIn1300(addressToFspMap.at(0x1300));

    EXPECT_EQ(0x1230u, dspIn1230.getAddress());
    EXPECT_EQ(0u, dspIn1230.getNumberOfDchUsers());
    EXPECT_EQ(0u, dspIn1230.getNumberOfHsupaCfs());
    EXPECT_EQ(DspMode::NyquistDedicatedChannelDevice, dspIn1230.getMode());

    EXPECT_EQ(NyquistType::Nyquist, dspIn1230.getNyquistType());
    EXPECT_EQ(NyquistType::TurboNyquist, dspIn1240.getNyquistType());

    EXPECT_EQ(1u, dspIn1230.getLcgId());
    EXPECT_EQ(1u, dspIn1240.getLcgId());
    EXPECT_EQ(2u, dspIn1250.getLcgId());
    EXPECT_EQ(2u, dspIn1260.getLcgId());
    EXPECT_EQ(1u, dspIn1270.getLcgId());
    EXPECT_EQ(1u, dspIn1280.getLcgId());
    EXPECT_EQ(2u, dspIn1330.getLcgId());
    EXPECT_EQ(2u, dspIn1340.getLcgId());
    EXPECT_EQ(1u, dspIn1350.getLcgId());
    EXPECT_EQ(1u, dspIn1360.getLcgId());
    EXPECT_EQ(2u, dspIn1370.getLcgId());
    EXPECT_EQ(2u, dspIn1380.getLcgId());

    EXPECT_EQ(0x1200u, fspIn1200.getAddress());
    EXPECT_TRUE(fspIn1200.isMasterTcom());
    EXPECT_EQ(0x1300u, fspIn1300.getAddress());
    EXPECT_FALSE(fspIn1300.isMasterTcom());
}

}