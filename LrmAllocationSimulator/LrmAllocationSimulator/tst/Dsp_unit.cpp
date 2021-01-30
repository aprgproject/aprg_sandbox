#include <Dsp.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(DspTest, DspDetailsCanAssignedCorrectlyAtDefaultConstruction)
{
    Dsp dsp;
    EXPECT_EQ(0u, dsp.getAddress());
    EXPECT_EQ(0u, dsp.getFspAddress());
    EXPECT_EQ(0u, dsp.getLcgId());
    EXPECT_EQ(0u, dsp.getNumberOfDchUsers());
    EXPECT_EQ(0u, dsp.getNumberOfHsupaCfs());
    EXPECT_EQ(0u, dsp.getNumberOfPreservedHsupaCfs());
    EXPECT_EQ(0u, dsp.getNumberOfDynamicallyAllocatedHsupaCfs());
    EXPECT_EQ(0u, dsp.getNumberOfHsRachCfs());
    EXPECT_EQ(DspMode::NyquistDedicatedChannelDevice, dsp.getMode());
    EXPECT_EQ("DCD", dsp.getModeString());
    EXPECT_EQ(NyquistType::Nyquist, dsp.getNyquistType());
    EXPECT_TRUE(dsp.isEmpty());
    EXPECT_FALSE(dsp.hasEmergencyCalls());
}


TEST(DspTest, DspDetailsCanAssignedCorrectlyAtConstruction)
{
    DspDetails dspDetails;
    dspDetails.address = 0x1230;
    dspDetails.lcgId = 1;
    dspDetails.numberOfDchUsers = 100;
    dspDetails.numberOfPreservedHsupaCfs = 5;
    dspDetails.numberOfDynamicallyAllocatedHsupaCfs = 7;
    dspDetails.numberOfHsRachCfs = 10;
    dspDetails.hasEmergencyCalls = true;
    dspDetails.mode = DspMode::NyquistCommonChannelDeviceNormal;
    dspDetails.nyquistType = NyquistType::TurboNyquist;
    Dsp dsp(dspDetails);

    EXPECT_EQ(0x1230u, dsp.getAddress());
    EXPECT_EQ(0x1200u, dsp.getFspAddress());
    EXPECT_EQ(1u, dsp.getLcgId());
    EXPECT_EQ(100u, dsp.getNumberOfDchUsers());
    EXPECT_EQ(12u, dsp.getNumberOfHsupaCfs());
    EXPECT_EQ(5u, dsp.getNumberOfPreservedHsupaCfs());
    EXPECT_EQ(7u, dsp.getNumberOfDynamicallyAllocatedHsupaCfs());
    EXPECT_EQ(10u, dsp.getNumberOfHsRachCfs());
    EXPECT_EQ(DspMode::NyquistCommonChannelDeviceNormal, dsp.getMode());
    EXPECT_EQ("CCDn", dsp.getModeString());
    EXPECT_EQ(NyquistType::TurboNyquist, dsp.getNyquistType());
    EXPECT_FALSE(dsp.isEmpty());
    EXPECT_TRUE(dsp.hasEmergencyCalls());
}