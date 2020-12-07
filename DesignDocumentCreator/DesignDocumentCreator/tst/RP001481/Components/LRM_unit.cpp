#include <gtest/gtest.h>

#include <Components/LRM.hpp>
#include <MessageFactory.hpp>
#include <Utils/AddressHelper.hpp>

using namespace std;
using namespace DesignDocumentCreator;

TEST(LrmTest, MasterTcomNidIsInvalidByDefault)
{
    LRM lrm(ComponentName::LRM);

    EXPECT_EQ(AddressHelper::INVALID_DSP_ADDRESS, lrm.getMasterTcomNid());
}

TEST(LrmTest, MasterTcomCanBeSet)
{
    LRM lrm(ComponentName::LRM);
    lrm.setMasterTcomNid(0xA1BA);

    EXPECT_EQ(0xA1BAu, lrm.getMasterTcomNid());
}

TEST(LrmTest, GetFspAddressWorksAsExpected)
{
    LRM lrm(ComponentName::LRM);

    EXPECT_EQ(0xA1u, lrm.getFspAddress(0xA1BA));
    EXPECT_EQ(0xA1u, lrm.getFspAddress(0xA100));
    EXPECT_EQ(0xBAu, lrm.getFspAddress(0xBAA1));
    EXPECT_EQ(0u, lrm.getFspAddress(0));
}

TEST(LrmTest, GetKeplerAddressWithoutCorWorksAsExpected)
{
    LRM lrm(ComponentName::LRM);

    EXPECT_EQ(0xA1B0u, lrm.getKeplerAddressWithoutCore(0xA1BA));
    EXPECT_EQ(0xA100u, lrm.getKeplerAddressWithoutCore(0xA100));
    EXPECT_EQ(0xBAA0u, lrm.getKeplerAddressWithoutCore(0xBAA1));
    EXPECT_EQ(0u, lrm.getKeplerAddressWithoutCore(0));
}

TEST(LrmTest, IsTcomInThisK2WorksAsExpected)
{
    LRM lrm(ComponentName::LRM);
    lrm.setMasterTcomNid(0xA1BA);

    EXPECT_TRUE(lrm.isTcomInThisK2(0xA1BA));
    EXPECT_TRUE(lrm.isTcomInThisK2(0xA1BB));
    EXPECT_FALSE(lrm.isTcomInThisK2(0xA100));
    EXPECT_FALSE(lrm.isTcomInThisK2(0x00BA));
    EXPECT_FALSE(lrm.isTcomInThisK2(0xA2BA));
    EXPECT_FALSE(lrm.isTcomInThisK2(0x0000));
}

TEST(LrmTest, GetPowerGroupIdWorksAsExpected)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);

    EXPECT_EQ(0u, lrm.getPowerGroupId(0xA1BA));
    EXPECT_EQ(1u, lrm.getPowerGroupId(0x1230));
    EXPECT_EQ(1u, lrm.getPowerGroupId(0x1240));
    EXPECT_EQ(2u, lrm.getPowerGroupId(0x1250));
    EXPECT_EQ(2u, lrm.getPowerGroupId(0x1260));
}

TEST(LrmTest, GetDspModeIdWorksAsExpected)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);

    EXPECT_EQ(EDspMode_Original, lrm.getDspMode(0xA1BA));
    EXPECT_EQ(EDspMode_Kepler_DCD_DCD, lrm.getDspMode(0x1230));
    EXPECT_EQ(EDspMode_Kepler_DCD_DCD, lrm.getDspMode(0x1240));
    EXPECT_EQ(EDspMode_Kepler_DCD_DCD, lrm.getDspMode(0x1250));
    EXPECT_EQ(EDspMode_Kepler_DCD_DCD, lrm.getDspMode(0x1260));
}

TEST(LrmTest, GetNumberOfK2sInPowerGroupWorksAsExpected)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.savePowerGroupInformation(payload);

    EXPECT_EQ(0u, lrm.getNumberOfK2sInPowerGroup(0));
    EXPECT_EQ(2u, lrm.getNumberOfK2sInPowerGroup(1));
    EXPECT_EQ(2u, lrm.getNumberOfK2sInPowerGroup(2));
}

TEST(LrmTest, GetDspAddressesForLcgIdWorksAsExpected)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);

    LRM::DspAddressesVector dspAddressForLcg1(lrm.getDspAddressesForLcgId(1));
    LRM::DspAddressesVector dspAddressForLcg2(lrm.getDspAddressesForLcgId(2));

    ASSERT_EQ(4u, dspAddressForLcg1.size());
    EXPECT_EQ(0x1230u, dspAddressForLcg1[0]);
    EXPECT_EQ(0x1240u, dspAddressForLcg1[1]);
    EXPECT_EQ(0x1250u, dspAddressForLcg1[2]);
    EXPECT_EQ(0x1260u, dspAddressForLcg1[3]);

    ASSERT_EQ(0u, dspAddressForLcg2.size());
}

TEST(LrmTest, FindMcdCcdDFor1LcgWithMoreThan2K2WithNbic)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);

    EXPECT_EQ(0x1230u, lrm.findLocationOfMcdCcdDForLcgId(1));
}

TEST(LrmTest, FindMcdCcdDRemoveMasterTcomAddress)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.setMasterTcomNid(0x123D);
    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);

    EXPECT_EQ(0x1240u, lrm.findLocationOfMcdCcdDForLcgId(1));
}

TEST(LrmTest, FindMcdCcdDRemoveDspWithInvalidNumberOfPowerGroup)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbicWithWrongPowerGroup(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);

    EXPECT_EQ(0x1240u, lrm.findLocationOfMcdCcdDForLcgId(1));
}

TEST(LrmTest, FindMcdCcdDRemoveUnacceptableOriginalDspMode)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);
    lrm.setDspModeToAddress(0x1230, EDspMode_Kepler_MCD_DCD);

    EXPECT_EQ(0x1240u, lrm.findLocationOfMcdCcdDForLcgId(1));
}

TEST(LrmTest, FindMcdCcdDPrioritizeNumberMcdCcdDInFspForOtherLcg)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForPrioritizationNumberMcdCcdDInFspForMcdCcdD(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);
    lrm.setDspModeToAddress(0x1230, EDspMode_Kepler_MCD_CCDD);

    EXPECT_EQ(0x1330u, lrm.findLocationOfMcdCcdDForLcgId(1));
}

TEST(LrmTest, FindMcdCcdDPrioritizeNumberK2s)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForPrioritizationNumberK2sForMcdCcdD(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);

    EXPECT_EQ(0x1250u, lrm.findLocationOfMcdCcdDForLcgId(1));
}

TEST(LrmTest, FindMcdDcdPrioritizeNumberMcdDcdAndMcdCcdDPackets)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForPrioritizationNumberPacketsForMcdDcd(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);
    lrm.setDspModeToAddress(0x1230, EDspMode_Kepler_MCD_CCDD);
    lrm.setDspModeToAddress(0x1240, EDspMode_Kepler_MCD_DCD);
    lrm.setDspModeToAddress(0x1260, EDspMode_Kepler_MCD_DCD);
    lrm.setDspModeToAddress(0x1330, EDspMode_Kepler_MCD_DCD);
    lrm.setDspModeToAddress(0x1340, EDspMode_Kepler_MCD_CCDD);

    EXPECT_EQ(0x1350u, lrm.findLocationOfMcdDcdForStartup(1));
}



