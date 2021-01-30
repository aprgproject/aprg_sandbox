#include <Lrm.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(LrmMarkAlgorithmTest, McdAllocation_MasterTcomIsPrioritizedForNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();

    SelectionDspResult selectionResult(lrm.allocateMcdForLcgIdAccordingToMark(1));

    hardwareConfiguration.printDspAllocations();
    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, selectionResult.address);
}

TEST(LrmMarkAlgorithmTest, McdAllocation_MasterTcomIsPrioritizedForTurboNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    AddressToDspMap& addressToDspMap(hardwareConfiguration.getAddressToDspMapReference());    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();
    addressToDspMap.at(0x1230).setNumberOfUsers(1);
    addressToDspMap.at(0x1250).setNumberOfUsers(1);
    addressToDspMap.at(0x1270).setNumberOfUsers(1);

    SelectionDspResult selectionResult(lrm.allocateMcdForLcgIdAccordingToMark(1));

    //hardwareConfiguration.printDspAllocations(1);

    //ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    //EXPECT_EQ(0x1230u, selectionResult.address);
}

TEST(LrmMarkAlgorithmTest, McdAllocation_BiggestNumberOfMcdCcdWithEmptyNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    AddressToDspMap& addressToDspMap(hardwareConfiguration.getAddressToDspMapReference());    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    addressToDspMap.at(0x1230).setNumberOfUsers(1);    addressToDspMap.at(0x1240).setNumberOfUsers(1);
    addressToDspMap.at(0x1250).setNumberOfUsers(1);
    addressToDspMap.at(0x1260).setNumberOfUsers(1);
    addressToDspMap.at(0x1270).setNumberOfUsers(1);
    addressToDspMap.at(0x1280).setNumberOfUsers(1);

    SelectionDspResult selectionResult(lrm.allocateMcdForLcgIdAccordingToMark(1));

    hardwareConfiguration.printDspAllocations(1);
    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1350u, selectionResult.address);
}

TEST(LrmMarkAlgorithmTest, CcdMcdAllocation_MasterTcomIsPrioritizedForNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();

    SelectionDspResultForCcdAndMcd selectionResult(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));

    hardwareConfiguration.printDspAllocations();
    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, selectionResult.ccdAddress);
    EXPECT_EQ(0x1250u, selectionResult.mcdAddress);
}

TEST(LrmMarkAlgorithmTest, TwoLcgTwoFspTwoCcdMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations();
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
}

TEST(LrmMarkAlgorithmTest, TwoLcgTwoFspTwoCcdNbicMcdPicWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, TwoLcgTwoFspTwoCcdNbicMcdPicWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, ThreeLcgTwoFspThreeCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToTwoFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, ThreeLcgTwoFspThreeCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToTwoFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, FourLcgTwoFspFourCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToTwoFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, FourLcgTwoFspFourCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToTwoFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, TwoLcgThreeFspTwoCcdNbicMcdPicWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToThreeFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, TwoLcgThreeFspTwoCcdNbicMcdPicWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToThreeFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, ThreeLcgThreeFspThreeCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToThreeFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, ThreeLcgThreeFspThreeCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToThreeFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, FourLcgThreeFspFourCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToThreeFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, FourLcgThreeFspFourCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToThreeFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, TwoLcgFourFspTwoCcdNbicMcdPicWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToFourFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, TwoLcgFourFspTwoCcdNbicMcdPicWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToFourFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);
    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
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

TEST(LrmMarkAlgorithmTest, ThreeLcgFourFspThreeCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);
    hardwareConfiguration.changeConfigurationToFourFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1380u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmTest, ThreeLcgFourFspThreeCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1380u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmTest, FourLcgFourFspFourCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
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
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmTest, FourLcgFourFspFourCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

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
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmTest, TwoLcgFiveFspTwoCcdNbicMcdPicWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1340u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(3u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1380u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmTest, TwoLcgFiveFspTwoCcdNbicMcdPicWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1340u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(3u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1380u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmTest, ThreeLcgFiveFspThreeCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

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
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmTest, ThreeLcgFiveFspThreeCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

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
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmTest, FourLcgFiveFspFourCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1280u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1430u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmTest, FourLcgFiveFspFourCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1280u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1430u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmTest, TwoLcgSixFspTwoCcdNbicMcdPicWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(3u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2240u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmTest, TwoLcgSixFspTwoCcdNbicMcdPicWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(3u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2240u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmTest, ThreeLcgSixFspThreeCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

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
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2270u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmTest, ThreeLcgSixFspThreeCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

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
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2270u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmTest, FourLcgSixFspFourCcdNbicPicMcdWithHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

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
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2330u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2350u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2340u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmTest, FourLcgSixFspFourCcdNbicPicMcdWithoutHibernation)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfPicPoolsPerLcg(1, 1);
    lrm.setNumberOfPicPoolsPerLcg(2, 1);
    lrm.setNumberOfPicPoolsPerLcg(3, 1);
    lrm.setNumberOfPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

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
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2330u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2270u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_EQ(1u, resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}