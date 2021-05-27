#include <Lrm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(LrmMarkAlgorithmWithHibenationTest, TwoLcgTwoFspTwoCcdMcd)
{
    HardwareConfiguration hardwareConfiguration;    Lrm lrm(hardwareConfiguration);

    hardwareConfiguration.changeConfigurationToTwoFspTwoLcgEvenDistribution();
    lrm.setHibernationCommissioned(true);    lrm.setNumberOfUnallocatedPicPoolsPerLcg(1, 1);
    lrm.setNumberOfUnallocatedPicPoolsPerLcg(2, 1);

    SelectionDspResultForCcdAndMcd resultCcdMcdLcg1(lrm.allocateCcdMcdForLcgIdAccordingToMark(1));
    SelectionDspResultForCcdAndMcd resultCcdMcdLcg2(lrm.allocateCcdMcdForLcgIdAccordingToMark(2));

    hardwareConfiguration.printDspAllocations();

    ASSERT_TRUE(resultCcdMcdLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1270u, resultCcdMcdLcg1.mcdAddress);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
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
    ASSERT_TRUE(resultCcdMcdLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1370u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg4.dliPool);
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
    EXPECT_EQ(0x1360u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1380u, resultPicLcg2.address);
    EXPECT_EQ(3u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1440u, resultPicLcg3.address);
    EXPECT_EQ(4u, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1460u, resultPicLcg4.address);
    EXPECT_EQ(2u, resultPicLcg4.dliPool);
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
    EXPECT_EQ(0x1450u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x1460u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
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
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1440u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg2.address);
    EXPECT_EQ(2u, resultPicLcg2.dliPool);
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
    EXPECT_EQ(0x2240u, resultPicLcg3.address);
    EXPECT_EQ(2u, resultPicLcg3.dliPool);
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
    EXPECT_EQ(0x2240u, resultPicLcg2.address);
    EXPECT_EQ(4u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg3.address);
    EXPECT_EQ(3u, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x1460u, resultPicLcg4.address);
    EXPECT_EQ(2u, resultPicLcg4.dliPool);
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
    EXPECT_EQ(0x2240u, resultPicLcg2.address);
    EXPECT_EQ(4u, resultPicLcg2.dliPool);
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
    EXPECT_EQ(0x2240u, resultPicLcg3.address);
    EXPECT_EQ(2u, resultPicLcg3.dliPool);
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
    EXPECT_EQ(0x2350u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2340u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(0u, resultCcdMcdLcg4.dliPool);
    EXPECT_FALSE(resultCcdMcdLcg4.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1280u, resultPicLcg1.address);
    EXPECT_EQ(1u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultPicLcg2.address);
    EXPECT_EQ(3u, resultPicLcg2.dliPool);
    ASSERT_TRUE(resultPicLcg3.isSelectionSuccessful);
    EXPECT_EQ(0x2360u, resultPicLcg3.address);
    EXPECT_EQ(4u, resultPicLcg3.dliPool);
    ASSERT_TRUE(resultPicLcg4.isSelectionSuccessful);
    EXPECT_EQ(0x2380u, resultPicLcg4.address);
    EXPECT_EQ(2u, resultPicLcg4.dliPool);
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
    EXPECT_EQ(0x2350u, resultCcdMcdLcg4.ccdAddress);
    EXPECT_EQ(0x2340u, resultCcdMcdLcg4.mcdAddress);
    EXPECT_EQ(2u, resultCcdMcdLcg4.dliPool);
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
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultCcdMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x2230u, resultCcdMcdLcg2.ccdAddress);
    EXPECT_EQ(0x1260u, resultCcdMcdLcg2.mcdAddress);
    EXPECT_EQ(3u, resultCcdMcdLcg2.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
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
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_TRUE(resultMcdLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultMcdLcg2.address);
    EXPECT_EQ(3u, resultMcdLcg2.dliPool);
    EXPECT_TRUE(resultMcdLcg2.isNbicAllocated);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
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
    EXPECT_EQ(0x1230u, resultCcdMcdLcg1.ccdAddress);
    EXPECT_EQ(0x1250u, resultCcdMcdLcg1.mcdAddress);
    EXPECT_EQ(1u, resultCcdMcdLcg1.dliPool);
    EXPECT_TRUE(resultCcdMcdLcg1.isNbicAllocated);
    ASSERT_FALSE(resultMcdLcg2.isSelectionSuccessful);
    ASSERT_TRUE(resultPicLcg1.isSelectionSuccessful);
    EXPECT_EQ(0x1340u, resultPicLcg1.address);
    EXPECT_EQ(4u, resultPicLcg1.dliPool);
    ASSERT_TRUE(resultPicLcg2.isSelectionSuccessful);
    EXPECT_EQ(0x1260u, resultPicLcg2.address);
    EXPECT_EQ(3u, resultPicLcg2.dliPool);
}

}