#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <SoosaConfiguration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace soosa
{

TEST(SoosaConfigurationTest, AParameterCanBeUpdated)
{
    SoosaConfiguration soosaConfiguration;

    soosaConfiguration.bufferNameAndValueString("m_numberOfChoices", "10");
    soosaConfiguration.update();

    EXPECT_EQ(10U, soosaConfiguration.getNumberOfChoices());
}

TEST(SoosaConfigurationTest, TwoParametersCanBeUpdated)
{
    SoosaConfiguration soosaConfiguration;

    soosaConfiguration.bufferNameAndValueString("m_numberOfChoices", "10");
    soosaConfiguration.bufferNameAndValueString("m_acceptableLineDeviationForLineModelInPixels", "200");
    soosaConfiguration.update();

    EXPECT_EQ(10U, soosaConfiguration.getNumberOfChoices());
    EXPECT_EQ(200U, soosaConfiguration.getAcceptableLineDeviationForLineModelInPixels());
}

TEST(SoosaConfigurationTest, LoadConfigurationFromFileWorks)
{
    AlbaLocalPathHandler fileForSoosa(APRG_DIR R"(\SOOSA\FilesForTests\SoosaConfigurationForTest.txt)");
    SoosaConfiguration soosaConfiguration;

    soosaConfiguration.loadConfigurationFromFile(fileForSoosa.getFullPath());

    EXPECT_EQ(2U, soosaConfiguration.getAcceptableLineDeviationForLineModelInPixels());
    EXPECT_DOUBLE_EQ(0.95, soosaConfiguration.getRetainRatioForSquareErrorsInLineModel());
    EXPECT_EQ(10U, soosaConfiguration.getMinimumLineSamples());

    EXPECT_EQ(500U, soosaConfiguration.getMaximumLineAndBarWidth());
    EXPECT_DOUBLE_EQ(0.10, soosaConfiguration.getAcceptableDistanceOverWidthRatioFromWidthMidpoint());
    EXPECT_EQ(2U, soosaConfiguration.getAcceptableMinimumDistanceFromWidthMidpoint());
    EXPECT_DOUBLE_EQ(0.50, soosaConfiguration.getAcceptableSdOverMeanDeviationForLine());
    EXPECT_DOUBLE_EQ(0.10, soosaConfiguration.getAcceptableSdOverMeanDeviationForBar());
    EXPECT_DOUBLE_EQ(0.95, soosaConfiguration.getRetainRatioForLineAndBar());
    EXPECT_DOUBLE_EQ(0.10, soosaConfiguration.getAcceptableSdOverMeanDeviationForBarHeight());
    EXPECT_DOUBLE_EQ(0.98, soosaConfiguration.getRetainRatioForBarHeight());

    EXPECT_EQ(5U, soosaConfiguration.getNumberOfChoices());
    EXPECT_EQ(170, soosaConfiguration.getColorIntensityForWhite());
    EXPECT_DOUBLE_EQ(0.50, soosaConfiguration.getRatioOfBarHeightToDiameter());
    EXPECT_DOUBLE_EQ(0.70, soosaConfiguration.getMinimumPercentageOfBlackPixelsForAFilledCircle());
}

}

}
