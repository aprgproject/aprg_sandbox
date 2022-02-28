#include <Components/LRM.hpp>
#include <FakeFramework/FakeFrameworkHelpers.hpp>
#include <MessageFactory.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace DesignDocumentCreator;

TEST(LrmTest, MasterTcomNidIsInvalidByDefault)
{
    LRM lrm(ComponentName::LRM);

    EXPECT_EQ(FakeFrameworkHelpers::INVALID_DSP_ADDRESS, lrm.getMasterTcomNid());
}

TEST(LrmTest, MasterTcomCanBeSet)
{
    LRM lrm(ComponentName::LRM);
    lrm.setMasterTcomNid(0xA1BA);

    EXPECT_EQ(0xA1BAu, lrm.getMasterTcomNid());
}

TEST(LrmTest, GetFspAddressWorks)
{
    LRM lrm(ComponentName::LRM);

    EXPECT_EQ(0xA1U, lrm.getFspAddressFromDspAddress(0xA1BA));
    EXPECT_EQ(0xA1U, lrm.getFspAddressFromDspAddress(0xA100));
    EXPECT_EQ(0xBAu, lrm.getFspAddressFromDspAddress(0xBAA1));
    EXPECT_EQ(0U, lrm.getFspAddressFromDspAddress(0));
}

TEST(LrmTest, GetKeplerAddressWithoutCorWorks)
{
    LRM lrm(ComponentName::LRM);

    EXPECT_EQ(0xA1B0U, lrm.getKeplerAddressWithoutCore(0xA1BA));
    EXPECT_EQ(0xA100U, lrm.getKeplerAddressWithoutCore(0xA100));
    EXPECT_EQ(0xBAA0U, lrm.getKeplerAddressWithoutCore(0xBAA1));
    EXPECT_EQ(0U, lrm.getKeplerAddressWithoutCore(0));
}

TEST(LrmTest, IsTcomInThisK2Works)
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

TEST(LrmTest, GetPowerGroupIdWorks)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);

    EXPECT_EQ(0U, lrm.getPowerGroupId(0xA1BA));
    EXPECT_EQ(1U, lrm.getPowerGroupId(0x1230));
    EXPECT_EQ(1U, lrm.getPowerGroupId(0x1240));
    EXPECT_EQ(2U, lrm.getPowerGroupId(0x1250));
    EXPECT_EQ(2U, lrm.getPowerGroupId(0x1260));
}

TEST(LrmTest, GetDspModeIdWorks)
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

TEST(LrmTest, GetNumberOfK2sInPowerGroupWorks)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.savePowerGroupInformation(payload);

    EXPECT_EQ(0U, lrm.getNumberOfK2sInPowerGroup(0));
    EXPECT_EQ(2U, lrm.getNumberOfK2sInPowerGroup(1));
    EXPECT_EQ(2U, lrm.getNumberOfK2sInPowerGroup(2));
}

TEST(LrmTest, GetDspAddressesForLcgIdWorks)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);

    LRM::AddressesVector dspAddressForLcg1(lrm.getDspAddressesForLcgId(1));
    LRM::AddressesVector dspAddressForLcg2(lrm.getDspAddressesForLcgId(2));

    ASSERT_EQ(4U, dspAddressForLcg1.size());
    EXPECT_EQ(0x1230U, dspAddressForLcg1[0]);
    EXPECT_EQ(0x1240U, dspAddressForLcg1[1]);
    EXPECT_EQ(0x1250U, dspAddressForLcg1[2]);
    EXPECT_EQ(0x1260U, dspAddressForLcg1[3]);

    ASSERT_EQ(0U, dspAddressForLcg2.size());
}

TEST(LrmTest, FindMcdCcdDFor1LcgWithMoreThan2K2WithNbic)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);

    EXPECT_EQ(0x1230U, lrm.findLocationOfMcdCcdDForLcgId(1));
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

    EXPECT_EQ(0x1240U, lrm.findLocationOfMcdCcdDForLcgId(1));
}

TEST(LrmTest, FindMcdCcdDRemoveDspWithInvalidNumberOfPowerGroup)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbicWithWrongPowerGroup(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);

    EXPECT_EQ(0x1240U, lrm.findLocationOfMcdCcdDForLcgId(1));
}

TEST(LrmTest, FindMcdCcdDRemoveUnacceptableOriginalDspMode)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);
    lrm.setDspModeInAddress(0x1230, EDspMode_Kepler_MCD_DCD);

    EXPECT_EQ(0x1240U, lrm.findLocationOfMcdCcdDForLcgId(1));
}

TEST(LrmTest, FindMcdCcdDPrioritizeNumberMcdCcdDInFspForOtherLcg)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForPrioritizationNumberMcdCcdDInFspForMcdCcdD(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);
    lrm.setDspModeInAddress(0x1230, EDspMode_Kepler_MCD_CCDD);

    EXPECT_EQ(0x1330U, lrm.findLocationOfMcdCcdDForLcgId(1));
}

TEST(LrmTest, FindMcdCcdDPrioritizeNumberK2s)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForPrioritizationNumberK2sForMcdCcdD(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);

    EXPECT_EQ(0x1250U, lrm.findLocationOfMcdCcdDForLcgId(1));
}

TEST(LrmTest, SetNumberOfIndicesCanBeDone)
{
    DelayedLinkIndices dli;

    dli.setIndices(10);
    EXPECT_EQ(0U, dli.getNumberOfIndices(0));
    EXPECT_EQ(10U, dli.getNumberOfIndices(1));
    EXPECT_EQ(0U, dli.getNumberOfIndices(2));
    EXPECT_EQ(0U, dli.getNumberOfIndices(3));
    EXPECT_EQ(0U, dli.getNumberOfIndices(4));

    dli.setIndices(20);
    EXPECT_EQ(0U, dli.getNumberOfIndices(0));
    EXPECT_EQ(12U, dli.getNumberOfIndices(1));
    EXPECT_EQ(8U, dli.getNumberOfIndices(2));
    EXPECT_EQ(0U, dli.getNumberOfIndices(3));
    EXPECT_EQ(0U, dli.getNumberOfIndices(4));

    dli.setIndices(40);
    EXPECT_EQ(0U, dli.getNumberOfIndices(0));
    EXPECT_EQ(12U, dli.getNumberOfIndices(1));
    EXPECT_EQ(12U, dli.getNumberOfIndices(2));
    EXPECT_EQ(12U, dli.getNumberOfIndices(3));
    EXPECT_EQ(4U, dli.getNumberOfIndices(4));

    dli.setIndices(0);
    EXPECT_EQ(0U, dli.getNumberOfIndices(0));
    EXPECT_EQ(0U, dli.getNumberOfIndices(1));
    EXPECT_EQ(0U, dli.getNumberOfIndices(2));
    EXPECT_EQ(0U, dli.getNumberOfIndices(3));
    EXPECT_EQ(0U, dli.getNumberOfIndices(4));
}

TEST(LrmTest, SetAsAllocatedOrNotCanBeDone)
{
    DelayedLinkIndices dli;

    EXPECT_FALSE(dli.isAllocated(0));
    EXPECT_FALSE(dli.isAllocated(1));
    EXPECT_FALSE(dli.isAllocated(2));
    EXPECT_FALSE(dli.isAllocated(3));
    EXPECT_FALSE(dli.isAllocated(4));

    dli.setPoolAsAllocated(1);

    EXPECT_FALSE(dli.isAllocated(0));
    EXPECT_TRUE(dli.isAllocated(1));
    EXPECT_FALSE(dli.isAllocated(2));
    EXPECT_FALSE(dli.isAllocated(3));
    EXPECT_FALSE(dli.isAllocated(4));

    dli.setPoolAsAllocated(0);
    dli.setPoolAsAllocated(2);
    dli.setPoolAsAllocated(3);
    dli.setPoolAsAllocated(4);

    EXPECT_TRUE(dli.isAllocated(0));
    EXPECT_TRUE(dli.isAllocated(1));
    EXPECT_TRUE(dli.isAllocated(2));
    EXPECT_TRUE(dli.isAllocated(3));
    EXPECT_TRUE(dli.isAllocated(4));

    dli.setPoolAsNotAllocated(0);
    dli.setPoolAsNotAllocated(1);
    dli.setPoolAsNotAllocated(2);
    dli.setPoolAsNotAllocated(3);
    dli.setPoolAsNotAllocated(4);

    EXPECT_FALSE(dli.isAllocated(0));
    EXPECT_FALSE(dli.isAllocated(1));
    EXPECT_FALSE(dli.isAllocated(2));
    EXPECT_FALSE(dli.isAllocated(3));
    EXPECT_FALSE(dli.isAllocated(4));
}

TEST(LrmTest, AllocatedDliAreNotIncludedInSelection)
{
    DelayedLinkIndices dli;

    dli.setIndices(20);
    dli.setPoolAsAllocated(1);

    EXPECT_EQ(2U, dli.getAvailablePoolIdForRel4(1));
}

TEST(LrmTest, IndicesDoesNotFitAreNotIncludedInSelection)
{
    DelayedLinkIndices dli;

    dli.setIndices(20);
    dli.setPoolAsAllocated(1);

    EXPECT_EQ(0U, dli.getAvailablePoolIdForRel4(12));
}

TEST(LrmTest, LowestNumberOfDlisIsPrioritized)
{
    DelayedLinkIndices dli;

    dli.setIndices(20);

    EXPECT_EQ(2U, dli.getAvailablePoolIdForRel4(8));
}

TEST(LrmTest, LowestDliPoolIsPrioritized)
{
    DelayedLinkIndices dli;

    dli.setIndices(48);

    EXPECT_EQ(1U, dli.getAvailablePoolIdForRel4(12));
}

TEST(LrmTest, hasConflictWithNextAvailablePoolFor2And3WithRXGreaterThan8)
{
    DelayedLinkIndices dli;
    DelayedLinkIndices::PoolIdVector poolIds1;
    DelayedLinkIndices::PoolIdVector poolIds2;
    poolIds2.emplace_back(1);
    poolIds2.emplace_back(4);
    DelayedLinkIndices::PoolIdVector poolIds3;
    poolIds3.emplace_back(2);
    DelayedLinkIndices::PoolIdVector poolIds4;
    poolIds4.emplace_back(3);
    dli.setIndices(21);

    EXPECT_FALSE(dli.hasConflictWithNextAvailablePool(poolIds1, 9));
    EXPECT_FALSE(dli.hasConflictWithNextAvailablePool(poolIds2, 9));
    EXPECT_TRUE(dli.hasConflictWithNextAvailablePool(poolIds3, 9));
    EXPECT_TRUE(dli.hasConflictWithNextAvailablePool(poolIds4, 9));
}

TEST(LrmTest, hasConflictWithNextAvailablePoolFor2And3WithRXEqualTo8)
{
    DelayedLinkIndices dli;
    DelayedLinkIndices::PoolIdVector poolIds1;
    DelayedLinkIndices::PoolIdVector poolIds2;
    poolIds2.emplace_back(1);
    poolIds2.emplace_back(4);
    DelayedLinkIndices::PoolIdVector poolIds3;
    poolIds3.emplace_back(2);
    DelayedLinkIndices::PoolIdVector poolIds4;
    poolIds4.emplace_back(3);
    dli.setIndices(20);

    EXPECT_FALSE(dli.hasConflictWithNextAvailablePool(poolIds1, 8));
    EXPECT_FALSE(dli.hasConflictWithNextAvailablePool(poolIds2, 8));
    EXPECT_TRUE(dli.hasConflictWithNextAvailablePool(poolIds3, 8));
    EXPECT_FALSE(dli.hasConflictWithNextAvailablePool(poolIds4, 8));
}

TEST(LrmTest, hasConflictWithNextAvailablePoolFor1And4)
{
    DelayedLinkIndices dli;
    DelayedLinkIndices::PoolIdVector poolIds1;
    DelayedLinkIndices::PoolIdVector poolIds2;
    poolIds2.emplace_back(2);
    poolIds2.emplace_back(3);
    DelayedLinkIndices::PoolIdVector poolIds3;
    poolIds3.emplace_back(1);
    DelayedLinkIndices::PoolIdVector poolIds4;
    poolIds4.emplace_back(4);
    dli.setIndices(48);

    EXPECT_FALSE(dli.hasConflictWithNextAvailablePool(poolIds1, 12));
    EXPECT_FALSE(dli.hasConflictWithNextAvailablePool(poolIds2, 12));
    EXPECT_TRUE(dli.hasConflictWithNextAvailablePool(poolIds3, 12));
    EXPECT_TRUE(dli.hasConflictWithNextAvailablePool(poolIds4, 12));
}


TEST(LrmTest, FindNbicMcdCcd)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbicWith2Fsps(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);

    EXPECT_EQ(0x1230U, lrm.findLocationOfMcdCcdDWithNbicForLcgId(1));
}


TEST(LrmTest, FindNbicMcdCcdDRemoveFspsWithPic)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbicWith2Fsps(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);
    lrm.setDspModeInAddress(0x1230, EDspMode_Kepler_DCD_PIC);
    lrm.setDspModeInAddress(0x1240, EDspMode_Kepler_DCD_PIC);

    EXPECT_EQ(0x1330U, lrm.findLocationOfMcdCcdDWithNbicForLcgId(1));
}

TEST(LrmTest, FindNbicMcdCcdDRemoveFspsWithNbic)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbicWith2Fsps(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);
    lrm.setAsNbicMcdCcdDInAddress(0x1230);
    lrm.setAsNbicMcdCcdDInAddress(0x1240);

    EXPECT_EQ(0x1330U, lrm.findLocationOfMcdCcdDWithNbicForLcgId(1));
}

TEST(LrmTest, FindNbicMcdCcdDRemoveConflictDlis)
{
    SLrmConfigurationDataInd payload;
    MessageFactory::saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbicWith2Fsps(payload);
    LRM lrm(ComponentName::LRM);

    lrm.saveDspInformation(payload);
    lrm.saveLcgInformation(payload);
    lrm.savePowerGroupInformation(payload);
    lrm.saveDliInfo(payload);
    lrm.setPoolIdInDspAddress(0x1230, 4);

    EXPECT_EQ(0x1330U, lrm.findLocationOfMcdCcdDWithNbicForLcgId(1));
}
