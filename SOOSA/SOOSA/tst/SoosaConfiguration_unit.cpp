#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <SoosaConfiguration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace soosa {

TEST(SoosaConfigurationTest, AParameterCanBeUpdated) {
    SoosaConfiguration soosaConfiguration;

    soosaConfiguration.bufferNameAndValueString("m_numberOfChoices", "10");
    soosaConfiguration.update();

    EXPECT_EQ(10, soosaConfiguration.getNumberOfChoices());
}

TEST(SoosaConfigurationTest, TwoParametersCanBeUpdated) {
    SoosaConfiguration soosaConfiguration;

    soosaConfiguration.bufferNameAndValueString("m_numberOfChoices", "10");
    soosaConfiguration.bufferNameAndValueString("m_acceptableLineDeviationForLineModelInPixels", "200");
    soosaConfiguration.update();

    EXPECT_EQ(10, soosaConfiguration.getNumberOfChoices());
    EXPECT_EQ(200, soosaConfiguration.getAcceptableLineDeviationForLineModelInPixels());
}

TEST(SoosaConfigurationTest, LoadConfigurationFromFileWorks) {
    AlbaLocalPathHandler fileForSoosa(APRG_DIR R"(\SOOSA\FilesForTests\SoosaConfigurationForTest.txt)");
    SoosaConfiguration soosaConfiguration;

    soosaConfiguration.loadConfigurationFromFile(fileForSoosa.getFullPath());

    // Line model parameters
    EXPECT_EQ(2, soosaConfiguration.getAcceptableLineDeviationForLineModelInPixels());
    EXPECT_DOUBLE_EQ(0.05, soosaConfiguration.getRemovalRatioForSquareErrorsInLineModel());
    EXPECT_EQ(10, soosaConfiguration.getMinimumLineSamples());

    // Line and bar parameters
    EXPECT_DOUBLE_EQ(0.05, soosaConfiguration.getBitmapWidthToBarWidthMultiplier());
    EXPECT_EQ(20, soosaConfiguration.getLineBarWidthSearchInitialBlackPointsValue());
    EXPECT_DOUBLE_EQ(0.80, soosaConfiguration.getLineBarWidthSearchAcceptedRunningBlackRatio());
    EXPECT_DOUBLE_EQ(0.40, soosaConfiguration.getAcceptableDistanceOverWidthRatioFromWidthMidpoint());
    EXPECT_DOUBLE_EQ(4.00, soosaConfiguration.getAcceptableMinimumDistanceFromWidthMidpoint());
    EXPECT_DOUBLE_EQ(0.50, soosaConfiguration.getAcceptableSdOverMeanDeviationForLine());
    EXPECT_DOUBLE_EQ(0.10, soosaConfiguration.getAcceptableSdOverMeanDeviationForBar());
    EXPECT_DOUBLE_EQ(0.05, soosaConfiguration.getRemovalRatioForLineAndBar());
    EXPECT_DOUBLE_EQ(10.00, soosaConfiguration.getInitialValueForMaximumDistanceBetweenBarHeights());
    EXPECT_DOUBLE_EQ(0.10, soosaConfiguration.getMultiplierForMaximumDistanceBetweenBarHeights());
    EXPECT_DOUBLE_EQ(0.10, soosaConfiguration.getAcceptableSdOverMeanDeviationForBarHeight());
    EXPECT_DOUBLE_EQ(0.02, soosaConfiguration.getRemovalRatioForBarHeight());

    // Choices related parameters
    EXPECT_EQ(5, soosaConfiguration.getNumberOfChoices());
    EXPECT_EQ(170, soosaConfiguration.getColorIntensityForWhite());
    EXPECT_DOUBLE_EQ(0.75, soosaConfiguration.getBarHeightToDiameterMultiplier());
    EXPECT_DOUBLE_EQ(0.40, soosaConfiguration.getMinimumPercentageOfBlackPixelsForAFilledCircle());
}

}  // namespace soosa

}  // namespace alba
