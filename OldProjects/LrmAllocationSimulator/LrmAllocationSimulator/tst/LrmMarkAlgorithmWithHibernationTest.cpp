#include <Lrm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgTwoFspTwoCcdMcd)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations();

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270U, resultCcdMcdLcg1.mcdAddress);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
}

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgTwoFspTwoCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgTwoFspTwoCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, ThreeLcgTwoFspThreeCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, ThreeLcgTwoFspThreeCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, FourLcgTwoFspFourCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, FourLcgTwoFspFourCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1370U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg4.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgThreeFspTwoCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgThreeFspTwoCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, ThreeLcgThreeFspThreeCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, ThreeLcgThreeFspThreeCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, FourLcgThreeFspFourCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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
    EXPECT_EQ(0x1360U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1380U, resultPicLcg2.address);
    EXPECT_EQ(3U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1440U, resultPicLcg3.address);
    EXPECT_EQ(4U, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1460U, resultPicLcg4.address);
    EXPECT_EQ(2U, resultPicLcg4.dliPool);
}

TEST(LrmMarkAlgorithmWithHibenationTest, FourLcgThreeFspFourCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToThreeFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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
    EXPECT_EQ(0x1450U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1460U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2U, resultCcdMcdLcg4.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgFourFspTwoCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgFourFspTwoCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, ThreeLcgFourFspThreeCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, ThreeLcgFourFspThreeCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, FourLcgFourFspFourCcdNMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, FourLcgFourFspFourCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFourFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgFiveFspTwoCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgFiveFspTwoCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1440U, resultPicLcg1.address);
    EXPECT_EQ(4U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg2.address);
    EXPECT_EQ(2U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithHibenationTest, ThreeLcgFiveFspThreeCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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
    EXPECT_EQ(0x2240U, resultPicLcg3.address);
    EXPECT_EQ(2U, resultPicLcg3.dliPool);
}

TEST(LrmMarkAlgorithmWithHibenationTest, ThreeLcgFiveFspThreeCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, FourLcgFiveFspFourCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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
    EXPECT_EQ(0x2240U, resultPicLcg2.address);
    EXPECT_EQ(4U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg3.address);
    EXPECT_EQ(3U, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1460U, resultPicLcg4.address);
    EXPECT_EQ(2U, resultPicLcg4.dliPool);
}

TEST(LrmMarkAlgorithmWithHibenationTest, FourLcgFiveFspFourCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToFiveFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgSixFspTwoCcdNMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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
    EXPECT_EQ(0x2240U, resultPicLcg2.address);
    EXPECT_EQ(4U, resultPicLcg2.dliPool);
}

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgSixFspTwoCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, ThreeLcgSixFspThreeCcdNMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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
    EXPECT_EQ(0x2240U, resultPicLcg3.address);
    EXPECT_EQ(2U, resultPicLcg3.dliPool);
}

TEST(LrmMarkAlgorithmWithHibenationTest, ThreeLcgSixFspThreeCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspThreeLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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

TEST(LrmMarkAlgorithmWithHibenationTest, FourLcgSixFspFourCcdMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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
    EXPECT_EQ(0x2350U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2340U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0U, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1280U, resultPicLcg1.address);
    EXPECT_EQ(1U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260U, resultPicLcg2.address);
    EXPECT_EQ(3U, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2360U, resultPicLcg3.address);
    EXPECT_EQ(4U, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2380U, resultPicLcg4.address);
    EXPECT_EQ(2U, resultPicLcg4.dliPool);
}

TEST(LrmMarkAlgorithmWithHibenationTest, FourLcgSixFspFourCcdNbicMcdPic)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSixFspFourLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);
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
    EXPECT_EQ(0x2350U, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2340U, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2U, resultCcdMcdLcg4.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_FALSE(resultPicLcg1.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg2.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg3.isSelectionSuccessful);
    ASSERT_FALSE(resultPicLcg4.isSelectionSuccessful);
}

TEST(LrmMarkAlgorithmWithHibenationTest, SharedLcgWithOneDspCcdNbicMcdWithoutPicInMsm)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSharedLcgWithOneDspInMsm();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230U, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260U, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3U, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg1.address);
    EXPECT_EQ(4U, resultPicLcg1.dliPool);
}

TEST(LrmMarkAlgorithmWithHibenationTest, SharedLcgWithOneDspNbicMcdWithoutPicInMsm)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSharedLcgWithOneDspInMsm();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResult resultMcdLcg2(lrm.allocateNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260U, resultMcdLcg2.address);
    EXPECT_EQ(3U, resultMcdLcg2.dliPool);
    EXPECT_TRUE(resultMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg1.address);
    EXPECT_EQ(4U, resultPicLcg1.dliPool);
}

TEST(LrmMarkAlgorithmWithHibenationTest, SharedLcgWithOneDspNbicMcdWithPicInMsm)
{
    HardwareConfiguration hardwareConfiguration;
    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToSharedLcgWithOneDspInMsm();
    lrm.setHibernationCommissioned(true);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdNbicMcdForLcgIdAccordingToMark(1));
    SelectionDspResult resultMcdLcg2(lrm.allocateNbicMcdForLcgIdAccordingToMark(2));
    SelectionDspResult resultPicLcg1(lrm.allocatePicForLcgIdAccordingToMark(1));
    SelectionDspResult resultPicLcg2(lrm.allocatePicForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations(2);

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230U, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250U, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1U, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_FALSE(resultMcdLcg2.isSelectionSuccessful);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340U, resultPicLcg1.address);
    EXPECT_EQ(4U, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260U, resultPicLcg2.address);
    EXPECT_EQ(3U, resultPicLcg2.dliPool);
}

}
