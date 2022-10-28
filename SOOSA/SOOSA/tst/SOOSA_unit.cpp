#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <SoosaTestUtilities/Utilities.hpp>
#include <SOOSA.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace soosa
{

TEST(SoosaTest, InvalidBitmapWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\InvalidBitmap.txt)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, EmptyWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Empty.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, JustABoxWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\JustABox.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, NoAnswersWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\NoAnswers.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, BasicWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Basic.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, LotsOfDirtInTheSidesWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfDirtInTheSides.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, LotsOfDirtInTheColumnWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfDirtInTheColumn.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, LotsOfCanvasSizeWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfCanvasSize.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, Scaled3TimesWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Scaled3Times.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, Rotated15DegreesWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Rotated15Degrees.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, Rotated25DegreesWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Rotated25Degrees.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, Rotated30DegreesWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Rotated30Degrees.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, Skew15DegreesWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Skew15Degrees.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, Noise20PercentWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Noise20Percent.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, Noise50PercentWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Noise50Percent.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, Scanned2BitExampleWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Scanned2BitExample.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, ScannedExampleWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\ScannedExample.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, Example_1Q20_DEM11_Works)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM11.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern1(soosa);
}

TEST(SoosaTest, Example_1Q20_DEM12_Works)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM12.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern2(soosa);
}

TEST(SoosaTest, Example_1Q20_DEM13_Works)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM13.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern3(soosa);
}

TEST(SoosaTest, Example_1Q20_DEM14_Works)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM14.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern4(soosa);
}

TEST(SoosaTest, Example_1Q20_DEM15_Works)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM15.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern5(soosa);
}

TEST(SoosaTest, DISABLED_LotsOfDirtAndCannotBeProcessedWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfDirtAndCannotBeProcessed.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_RandomWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Witcher.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_DistortedWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Distorted.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Noise100PercentWorks)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Noise100Percent.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, ProcessWorksWithADirectory)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM)");
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(inputFile.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();
}

}

}
