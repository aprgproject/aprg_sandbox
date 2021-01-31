#include <Lrm.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(LrmMarkAlgorithmWithoutHibernationTest, McdAllocation_MasterTcomIsPrioritizedForNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);

    SelectionDspResult selectionResult(lrm.allocateMcdForLcgIdAccordingToMark(1));

    hardwareConfiguration.printDspAllocations();

    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, selectionResult.address);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, McdAllocation_MasterTcomIsPrioritizedForTurboNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    AddressToDspMap& addressToDspMap(hardwareConfiguration.getAddressToDspMapReference());
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    addressToDspMap.at(0x1230).setNumberOfUsers(1);
    addressToDspMap.at(0x1250).setNumberOfUsers(1);
    addressToDspMap.at(0x1270).setNumberOfUsers(1);

    SelectionDspResult selectionResult(lrm.allocateMcdForLcgIdAccordingToMark(1));

    hardwareConfiguration.printDspAllocations(1);

    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, selectionResult.address);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, McdAllocation_BiggestNumberOfMcdCcdWithEmptyNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    AddressToDspMap& addressToDspMap(hardwareConfiguration.getAddressToDspMapReference());
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    addressToDspMap.at(0x1230).setNumberOfUsers(1);
    addressToDspMap.at(0x1240).setNumberOfUsers(1);
    addressToDspMap.at(0x1250).setNumberOfUsers(1);
    addressToDspMap.at(0x1260).setNumberOfUsers(1);
    addressToDspMap.at(0x1270).setNumberOfUsers(1);
    addressToDspMap.at(0x1280).setNumberOfUsers(1);

    SelectionDspResult selectionResult(lrm.allocateMcdForLcgIdAccordingToMark(1));

    hardwareConfiguration.printDspAllocations(1);

    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1350u, selectionResult.address);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, CcdMcdAllocation_MasterTcomIsPrioritizedForNyquist)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);

    SelectionDspResultForCcdAndMcd selectionResult(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));

    hardwareConfiguration.printDspAllocations();

    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, selectionResult.ccdAddress);
    EXPECT_EQ(0x1250u, selectionResult.mcdAddress);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgTwoFspTwoCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(4u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgTwoFspTwoCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgTwoFspThreeCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1280u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg2.address);
    EXPECT_EQ(3u, resultPicLcg2.dliPool);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgTwoFspThreeCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgTwoFspFourCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1330u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1350u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1370u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1380u, resultPicLcg2.address);
    EXPECT_EQ(3u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280u, resultPicLcg3.address);
    EXPECT_EQ(4u, resultPicLcg3.dliPool);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgTwoFspFourCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(4, 1);

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
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1330u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1350u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_FALSE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg4.ccdAddress);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280u, resultPicLcg3.address);
    EXPECT_EQ(3u, resultPicLcg3.dliPool);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgThreeFspTwoCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1280u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultPicLcg2.address);
    EXPECT_EQ(3u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgThreeFspTwoCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgThreeFspThreeCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1280u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg2.address);
    EXPECT_EQ(3u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1480u, resultPicLcg3.address);
    EXPECT_EQ(4u, resultPicLcg3.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgThreeFspThreeCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}


TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgThreeFspFourCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1280u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1330u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1340u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1480u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful); //problem this is not successful but sucessful on hibernation
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1440u, resultPicLcg3.address);
    EXPECT_EQ(3u, resultPicLcg3.dliPool);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful); //problem this is not successful but sucessful on hibernation
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgThreeFspFourCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(4, 1);

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
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1430u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1330u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1340u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgFourFspTwoCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(4u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgFourFspTwoCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgFourFspThreeCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg2.address);
    EXPECT_EQ(4u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1380u, resultPicLcg3.address);
    EXPECT_EQ(3u, resultPicLcg3.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgFourFspThreeCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);

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
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1380u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgFourFspFourCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1280u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg2.address);
    EXPECT_EQ(3u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg2.address);
    EXPECT_EQ(3u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1480u, resultPicLcg3.address);
    EXPECT_EQ(4u, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2240u, resultPicLcg4.address);
    EXPECT_EQ(2u, resultPicLcg4.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgFourFspFourCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(4, 1);

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
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgFiveFspTwoCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(4u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgFiveFspTwoCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1340u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(3u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1380u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgFiveFspThreeCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(4u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2360u, resultPicLcg3.address);
    EXPECT_EQ(2u, resultPicLcg3.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgFiveFspThreeCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);

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
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgFiveFspFourCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1280u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1380u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2360u, resultPicLcg2.address);
    EXPECT_EQ(4u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg3.address);
    EXPECT_EQ(3u, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1460u, resultPicLcg4.address);
    EXPECT_EQ(2u, resultPicLcg4.dliPool);
}


TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgFiveFspFourCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(4, 1);

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
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1430u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgSixFspTwoCcdNMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2340u, resultPicLcg2.address);
    EXPECT_EQ(4u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgSixFspTwoCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2250u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(3u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2240u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgSixFspThreeCcdNMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdMcdForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2270u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(4u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2360u, resultPicLcg3.address);
    EXPECT_EQ(2u, resultPicLcg3.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgSixFspThreeCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);

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
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2270u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(2u, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgSixFspFourCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(4, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg3(lrm.allocateCcdMcdForLcgIdAccordingToMark(3));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg4(lrm.allocateCcdMcdForLcgIdAccordingToMark(4));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg3(lrm.allocatePicForLcgIdAccordingToMark(3));
    SelectionDspResult resultPicLcg4(lrm.allocatePicForLcgIdAccordingToMark(4));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2330u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2270u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1280u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultPicLcg2.address);
    EXPECT_EQ(3u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2440u, resultPicLcg3.address);
    EXPECT_EQ(4u, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2460u, resultPicLcg4.address);
    EXPECT_EQ(2u, resultPicLcg4.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgSixFspFourCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(3, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(4, 1);

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
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2330u, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2370u, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4u, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2270u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}
