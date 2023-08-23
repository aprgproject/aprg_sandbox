#include <Dsp.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(DspTest, DspDetailsCanAssignedCorrectlyAtDefaultConstruction) {
    Dsp dsp;
    EXPECT_EQ(0U, dsp.getAddress());
    EXPECT_EQ(0U, dsp.getFspAddress());
    EXPECT_EQ(0U, dsp.getLcgId());
    EXPECT_EQ(0U, dsp.getNumberOfDchUsers());
    EXPECT_EQ(0U, dsp.getNumberOfHsupaCfs());
    EXPECT_EQ(0U, dsp.getNumberOfPreservedHsupaCfs());
    EXPECT_EQ(0U, dsp.getNumberOfDynamicallyAllocatedHsupaCfs());
    EXPECT_EQ(0U, dsp.getNumberOfHsRachCfs());
    EXPECT_EQ(DspMode::NyquistDedicatedChannelDevice, dsp.getMode());
    EXPECT_EQ("DCD", dsp.getModeString());
    EXPECT_EQ(NyquistType::Nyquist, dsp.getNyquistType());
    EXPECT_TRUE(dsp.isEmpty());
    EXPECT_FALSE(dsp.hasEmergencyCalls());
}

TEST(DspTest, DspDetailsCanAssignedCorrectlyAtConstruction) {
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

    EXPECT_EQ(0x1230U, dsp.getAddress());
    EXPECT_EQ(0x1200U, dsp.getFspAddress());
    EXPECT_EQ(1U, dsp.getLcgId());
    EXPECT_EQ(100U, dsp.getNumberOfDchUsers());
    EXPECT_EQ(12U, dsp.getNumberOfHsupaCfs());
    EXPECT_EQ(5U, dsp.getNumberOfPreservedHsupaCfs());
    EXPECT_EQ(7U, dsp.getNumberOfDynamicallyAllocatedHsupaCfs());
    EXPECT_EQ(10U, dsp.getNumberOfHsRachCfs());
    EXPECT_EQ(DspMode::NyquistCommonChannelDeviceNormal, dsp.getMode());
    EXPECT_EQ("CCDn", dsp.getModeString());
    EXPECT_EQ(NyquistType::TurboNyquist, dsp.getNyquistType());
    EXPECT_FALSE(dsp.isEmpty());
    EXPECT_TRUE(dsp.hasEmergencyCalls());
}

}  // namespace alba
