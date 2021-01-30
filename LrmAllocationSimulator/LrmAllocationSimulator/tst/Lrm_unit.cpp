#include <Lrm.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(LrmTest, McdAllocation_MasterTcomIsPrioritizedForNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();

    SelectionDspResult selectionResult(lrm.allocateMcdForLcgId(1));

    hardwareConfiguration.printDspAllocations();

    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, selectionResult.address);
}

TEST(LrmTest, McdAllocation_MasterTcomIsPrioritizedForTurboNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    AddressToDspMap& addressToDspMap(hardwareConfiguration.getAddressToDspMapReference());
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();
    addressToDspMap.at(0x1230).setNumberOfUsers(1);
    addressToDspMap.at(0x1250).setNumberOfUsers(1);
    addressToDspMap.at(0x1270).setNumberOfUsers(1);

    SelectionDspResult selectionResult(lrm.allocateMcdForLcgId(1));

    hardwareConfiguration.printDspAllocations(1);

    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, selectionResult.address);
}

TEST(LrmTest, McdAllocation_BiggestNumberOfMcdCcdWithEmptyNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    AddressToDspMap& addressToDspMap(hardwareConfiguration.getAddressToDspMapReference());
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    addressToDspMap.at(0x1230).setNumberOfUsers(1);
    addressToDspMap.at(0x1240).setNumberOfUsers(1);
    addressToDspMap.at(0x1250).setNumberOfUsers(1);
    addressToDspMap.at(0x1260).setNumberOfUsers(1);
    addressToDspMap.at(0x1270).setNumberOfUsers(1);
    addressToDspMap.at(0x1280).setNumberOfUsers(1);

    SelectionDspResult selectionResult(lrm.allocateMcdForLcgId(1));

    hardwareConfiguration.printDspAllocations(1);

    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1350u, selectionResult.address);
}

TEST(LrmTest, CcdMcdAllocation_MasterTcomIsPrioritizedForNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();

    SelectionDspResultForCcdAndMcd selectionResult(lrm.allocateCcdMcdForLcgId(1));

    hardwareConfiguration.printDspAllocations();

    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, selectionResult.ccdAddress);
    EXPECT_EQ(0x1250u, selectionResult.mcdAddress);
}

TEST(LrmTest, TwoLcgTwoFspTwoCcdMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgId(2));

    hardwareConfiguration.printDspAllocations();

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
}

TEST(LrmTest, TwoLcgTwoFspTwoCcdNbicMcdPicWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmTest, TwoLcgTwoFspTwoCcdNbicMcdPicWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmTest, ThreeLcgTwoFspThreeCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgId(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgId(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmTest, ThreeLcgTwoFspThreeCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgId(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgId(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmTest, FourLcgTwoFspFourCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgId(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgId(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgId(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgId(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1330u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1350u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_FALSE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg4.ccdAddress);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280u, resultPicLcg3.address);
    EXPECT_EQ(3u, resultPicLcg3.dliPool);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmTest, FourLcgTwoFspFourCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgId(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgId(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgId(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgId(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1330u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1350u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_FALSE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg4.ccdAddress);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280u, resultPicLcg3.address);
    EXPECT_EQ(3u, resultPicLcg3.dliPool);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmTest, TwoLcgThreeFspTwoCcdNbicMcdPicWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmTest, TwoLcgThreeFspTwoCcdNbicMcdPicWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmTest, ThreeLcgThreeFspThreeCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgId(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgId(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmTest, ThreeLcgThreeFspThreeCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgId(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgId(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmTest, FourLcgThreeFspFourCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgId(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgId(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgId(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgId(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1430u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1450u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1460u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmTest, FourLcgThreeFspFourCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgId(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgId(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgId(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgId(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1430u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1330u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1340u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmTest, TwoLcgFourFspTwoCcdNbicMcdPicWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmTest, TwoLcgFourFspTwoCcdNbicMcdPicWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmTest, ThreeLcgFourFspThreeCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgId(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgId(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgId(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgId(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgId(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgId(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}
