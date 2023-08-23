#include <Lrm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(LrmMarkAlgorithmWithoutHibernationTest, McdAllocation_MasterTcomIsPrioritizedForNyquist) {
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);

    SelectionDspResult selectionResult(lrm.allocateMcdForLcgIdAccordingToMark(1));

    hardwareConfiguration.printDspAllocations();

    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, selectionResult.address);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, McdAllocation_MasterTcomIsPrioritizedForTurboNyquist) {
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
    EXPECT_EQ(0x1240U, selectionResult.address);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, McdAllocation_BiggestNumberOfMcdCcdWithEmptyNyquist) {
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
    EXPECT_EQ(0x1350U, selectionResult.address);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, CcdMcdAllocation_MasterTcomIsPrioritizedForNyquist) {
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToOneFspOneLcgEvenDistribution();
    lrm.setHibernationCommissioned(false);

    SelectionDspResultForCcdAndMcd selectionResult(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));

    hardwareConfiguration.printDspAllocations();

    ASSERT_TRUE(selectionResult.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, selectionResult.ccdAddress);
    EXPECT_EQ(0x1250U, selectionResult.mcdAddress);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgTwoFspTwoCcdMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg2.address);
    EXPECT_EQ(4U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgTwoFspTwoCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg1.address);
    EXPECT_EQ(4U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg2.address);
    EXPECT_EQ(2U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgTwoFspThreeCcdMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1280U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg2.address);
    EXPECT_EQ(3U, resultPicLcg2.dliPool);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgTwoFspThreeCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1370U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg1.address);
    EXPECT_EQ(2U, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgTwoFspFourCcdMcdPic) {
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
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1330U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1350U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1370U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1380U, resultPicLcg2.address);
    EXPECT_EQ(3U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280U, resultPicLcg3.address);
    EXPECT_EQ(4U, resultPicLcg3.dliPool);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgTwoFspFourCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1330U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1350U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(2U, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_FALSE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg4.ccdAddress);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280U, resultPicLcg3.address);
    EXPECT_EQ(3U, resultPicLcg3.dliPool);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgThreeFspTwoCcdMcdPic) {
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
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1280U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260U, resultPicLcg2.address);
    EXPECT_EQ(3U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgThreeFspTwoCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg1.address);
    EXPECT_EQ(4U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg2.address);
    EXPECT_EQ(2U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgThreeFspThreeCcdMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1280U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg2.address);
    EXPECT_EQ(3U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1480U, resultPicLcg3.address);
    EXPECT_EQ(4U, resultPicLcg3.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgThreeFspThreeCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1370U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg1.address);
    EXPECT_EQ(2U, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgThreeFspFourCcdMcdPic) {
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
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1280U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1330U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1340U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1480U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);  // problem this is not successful but sucessful on hibernation
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1440U, resultPicLcg3.address);
    EXPECT_EQ(3U, resultPicLcg3.dliPool);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);  // problem this is not successful but sucessful on hibernation
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgThreeFspFourCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1430U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1330U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1340U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2U, resultCcdMcdLcg4.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgFourFspTwoCcdMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg2.address);
    EXPECT_EQ(4U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgFourFspTwoCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg1.address);
    EXPECT_EQ(4U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg2.address);
    EXPECT_EQ(2U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgFourFspThreeCcdMcdPic) {
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
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240U, resultPicLcg2.address);
    EXPECT_EQ(4U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1380U, resultPicLcg3.address);
    EXPECT_EQ(3U, resultPicLcg3.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgFourFspThreeCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1280U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1380U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg1.address);
    EXPECT_EQ(2U, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgFourFspFourCcdMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1280U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2250U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg2.address);
    EXPECT_EQ(3U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg2.address);
    EXPECT_EQ(3U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1480U, resultPicLcg3.address);
    EXPECT_EQ(4U, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2240U, resultPicLcg4.address);
    EXPECT_EQ(2U, resultPicLcg4.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgFourFspFourCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1370U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2250U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2U, resultCcdMcdLcg4.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgFiveFspTwoCcdMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg2.address);
    EXPECT_EQ(4U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgFiveFspTwoCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1340U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240U, resultPicLcg1.address);
    EXPECT_EQ(3U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1380U, resultPicLcg2.address);
    EXPECT_EQ(2U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgFiveFspThreeCcdMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2250U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg2.address);
    EXPECT_EQ(4U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2360U, resultPicLcg3.address);
    EXPECT_EQ(2U, resultPicLcg3.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgFiveFspThreeCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2250U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg1.address);
    EXPECT_EQ(2U, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgFiveFspFourCcdMcdPic) {
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
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1280U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2270U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1380U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2360U, resultPicLcg2.address);
    EXPECT_EQ(4U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg3.address);
    EXPECT_EQ(3U, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1460U, resultPicLcg4.address);
    EXPECT_EQ(2U, resultPicLcg4.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgFiveFspFourCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1280U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2270U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1430U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2U, resultCcdMcdLcg4.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgSixFspTwoCcdNMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2250U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2340U, resultPicLcg2.address);
    EXPECT_EQ(4U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, TwoLcgSixFspTwoCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x2250U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240U, resultPicLcg1.address);
    EXPECT_EQ(3U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2240U, resultPicLcg2.address);
    EXPECT_EQ(2U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgSixFspThreeCcdNMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2270U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1240U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg2.address);
    EXPECT_EQ(4U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2360U, resultPicLcg3.address);
    EXPECT_EQ(2U, resultPicLcg3.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, ThreeLcgSixFspThreeCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2270U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1360U, resultPicLcg1.address);
    EXPECT_EQ(2U, resultPicLcg1.dliPool);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgSixFspFourCcdMcdPic) {
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
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg1.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg2.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2330U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2370U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg3.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2270U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1280U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260U, resultPicLcg2.address);
    EXPECT_EQ(3U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2440U, resultPicLcg3.address);
    EXPECT_EQ(4U, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2460U, resultPicLcg4.address);
    EXPECT_EQ(2U, resultPicLcg4.dliPool);
}

TEST(LrmMarkAlgorithmWithoutHibernationTest, FourLcgSixFspFourCcdNbicMcdPic) {
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
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1240U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2330U, resultCcdMcdLcg3.ccdAddress);
    EXPECT_EQ(0x2370U, resultCcdMcdLcg3.mcdAddress);
    EXPECT_EQ(4U, resultCcdMcdLcg3.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg3.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2270U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2U, resultCcdMcdLcg4.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

}  // namespace alba
