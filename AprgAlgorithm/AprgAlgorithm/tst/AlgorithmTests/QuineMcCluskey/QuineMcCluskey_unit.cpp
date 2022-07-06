#include <Algorithm/QuineMcCluskey/QuineMcCluskey.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using MintermForTest = unsigned int;
using ImplicantForTest = Implicant<unsigned int>;
using ImplicantsForTest = Implicants<unsigned int>;
using QuineMcCluskeyForTest = QuineMcCluskey<unsigned int>;
}

TEST(QuineMcCluskeyTest, ImplicantEquivalentStringTest)
{
    ImplicantForTest implicant({8, 10, 12, 14});
    EXPECT_EQ("00001--0", implicant.getEquivalentString(8));
}

TEST(QuineMcCluskeyTest, ImplicantCompatibilityTest)
{
    ImplicantForTest implicant1({4, 12});
    ImplicantForTest implicant2({8, 9});
    ImplicantForTest implicant3({10, 11});

    EXPECT_FALSE(implicant1.isCompatible(implicant2));
    EXPECT_FALSE(implicant1.isCompatible(implicant3));
    EXPECT_FALSE(implicant2.isCompatible(implicant1));
    EXPECT_TRUE(implicant2.isCompatible(implicant3));
    EXPECT_FALSE(implicant3.isCompatible(implicant1));
    EXPECT_TRUE(implicant3.isCompatible(implicant2));
}

TEST(QuineMcCluskeyTest, ImplicantSubsetTest)
{
    ImplicantForTest implicant1({4, 12});
    ImplicantForTest implicant2({8, 9});
    ImplicantForTest implicant3({8, 9, 10, 11});

    EXPECT_FALSE(implicant1.isSubset(implicant2));
    EXPECT_FALSE(implicant1.isSubset(implicant3));
    EXPECT_FALSE(implicant2.isSubset(implicant1));
    EXPECT_TRUE(implicant2.isSubset(implicant3));
    EXPECT_FALSE(implicant3.isSubset(implicant1));
    EXPECT_FALSE(implicant3.isSubset(implicant2));
}

TEST(QuineMcCluskeyTest, UnintializedOutputTest)
{
    QuineMcCluskeyForTest quineMcCluskey;

    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0xA));
    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0x1));
    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0xB));
    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0xA));
}

TEST(QuineMcCluskeyTest, InputOutputTest)
{
    QuineMcCluskeyForTest quineMcCluskey;
    quineMcCluskey.setInputOutput(0x4, LogicalValue::False);
    quineMcCluskey.setInputOutput(0x5, LogicalValue::True);
    quineMcCluskey.setInputOutput(0x6, LogicalValue::DontCare);

    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0x4));
    EXPECT_EQ(LogicalValue::True, quineMcCluskey.getOutput(0x5));
    EXPECT_EQ(LogicalValue::DontCare, quineMcCluskey.getOutput(0x6));
}

TEST(QuineMcCluskeyTest, GetImplicantsWithZeroCommonalityCount)
{
    QuineMcCluskeyForTest quineMcCluskey;
    quineMcCluskey.setInputOutput(4, LogicalValue::True);
    quineMcCluskey.setInputOutput(8, LogicalValue::True);
    quineMcCluskey.setInputOutput(9, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(10, LogicalValue::True);
    quineMcCluskey.setInputOutput(11, LogicalValue::True);
    quineMcCluskey.setInputOutput(12, LogicalValue::True);
    quineMcCluskey.setInputOutput(14, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(15, LogicalValue::True);

    quineMcCluskey.fillComputationalTableWithMintermsWithZeroCommonalityCount();

    ImplicantsForTest mintermsWithZero(quineMcCluskey.getImplicants(0,0));
    ImplicantsForTest mintermsWithOne(quineMcCluskey.getImplicants(1,0));
    ImplicantsForTest mintermsWithTwo(quineMcCluskey.getImplicants(2,0));
    ImplicantsForTest mintermsWithThree(quineMcCluskey.getImplicants(3,0));
    ImplicantsForTest mintermsWithFour(quineMcCluskey.getImplicants(4,0));
    EXPECT_EQ("Implicants : [(has size 0):{}]", mintermsWithZero.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 2):{'100 (4)', '1000 (8)', }]", mintermsWithOne.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 3):{'1001 (9)', '1010 (10)', '1100 (12)', }]", mintermsWithTwo.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 2):{'1011 (11)', '1110 (14)', }]", mintermsWithThree.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 1):{'1111 (15)', }]", mintermsWithFour.getDisplayableString());
}

TEST(QuineMcCluskeyTest, GetImplicantsWithOneCommonalityCount)
{
    QuineMcCluskeyForTest quineMcCluskey;
    quineMcCluskey.setInputOutput(4, LogicalValue::True);
    quineMcCluskey.setInputOutput(8, LogicalValue::True);
    quineMcCluskey.setInputOutput(9, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(10, LogicalValue::True);
    quineMcCluskey.setInputOutput(11, LogicalValue::True);
    quineMcCluskey.setInputOutput(12, LogicalValue::True);
    quineMcCluskey.setInputOutput(14, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(15, LogicalValue::True);

    quineMcCluskey.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    quineMcCluskey.findCombinationOfImplicants(0,0);
    quineMcCluskey.findCombinationOfImplicants(1,0);
    quineMcCluskey.findCombinationOfImplicants(2,0);
    quineMcCluskey.findCombinationOfImplicants(3,0);
    quineMcCluskey.findCombinationOfImplicants(4,0);

    ImplicantsForTest mintermsWithZero(quineMcCluskey.getImplicants(0,1));
    ImplicantsForTest mintermsWithOne(quineMcCluskey.getImplicants(1,1));
    ImplicantsForTest mintermsWithTwo(quineMcCluskey.getImplicants(2,1));
    ImplicantsForTest mintermsWithThree(quineMcCluskey.getImplicants(3,1));
    ImplicantsForTest mintermsWithFour(quineMcCluskey.getImplicants(4,1));
    EXPECT_EQ("Implicants : [(has size 0):{}]", mintermsWithZero.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 4):{'-100 (4, 12, )', '100- (8, 9, )', '10-0 (8, 10, )', '1-00 (8, 12, )', }]", mintermsWithOne.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 4):{'10-1 (9, 11, )', '101- (10, 11, )', '1-10 (10, 14, )', '11-0 (12, 14, )', }]", mintermsWithTwo.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 2):{'1-11 (11, 15, )', '111- (14, 15, )', }]", mintermsWithThree.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 0):{}]", mintermsWithFour.getDisplayableString());
}

TEST(QuineMcCluskeyTest, GetImplicantsWithTwoCommonalityCounts)
{
    QuineMcCluskeyForTest quineMcCluskey;
    quineMcCluskey.setInputOutput(4, LogicalValue::True);
    quineMcCluskey.setInputOutput(8, LogicalValue::True);
    quineMcCluskey.setInputOutput(9, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(10, LogicalValue::True);
    quineMcCluskey.setInputOutput(11, LogicalValue::True);
    quineMcCluskey.setInputOutput(12, LogicalValue::True);
    quineMcCluskey.setInputOutput(14, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(15, LogicalValue::True);

    quineMcCluskey.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    quineMcCluskey.findAllCombinations();

    ImplicantsForTest mintermsWithZero(quineMcCluskey.getImplicants(0,2));
    ImplicantsForTest mintermsWithOne(quineMcCluskey.getImplicants(1,2));
    ImplicantsForTest mintermsWithTwo(quineMcCluskey.getImplicants(2,2));
    ImplicantsForTest mintermsWithThree(quineMcCluskey.getImplicants(3,2));
    ImplicantsForTest mintermsWithFour(quineMcCluskey.getImplicants(4,2));
    EXPECT_EQ("Implicants : [(has size 0):{}]", mintermsWithZero.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 2):{'10-- (8, 9, 10, 11, )', '1--0 (8, 10, 12, 14, )', }]", mintermsWithOne.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 1):{'1-1- (10, 11, 14, 15, )', }]", mintermsWithTwo.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 0):{}]", mintermsWithThree.getDisplayableString());
    EXPECT_EQ("Implicants : [(has size 0):{}]", mintermsWithFour.getDisplayableString());
}

TEST(QuineMcCluskeyTest, GetFinalImplicants)
{
    QuineMcCluskeyForTest quineMcCluskey;
    quineMcCluskey.setInputOutput(4, LogicalValue::True);
    quineMcCluskey.setInputOutput(8, LogicalValue::True);
    quineMcCluskey.setInputOutput(9, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(10, LogicalValue::True);
    quineMcCluskey.setInputOutput(11, LogicalValue::True);
    quineMcCluskey.setInputOutput(12, LogicalValue::True);
    quineMcCluskey.setInputOutput(14, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(15, LogicalValue::True);

    quineMcCluskey.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    quineMcCluskey.findAllCombinations();

    ImplicantsForTest finalImplicants(quineMcCluskey.getAllFinalImplicants());
    ASSERT_EQ(4U, finalImplicants.getSize());
    EXPECT_EQ("Implicants : [(has size 4):{'-100 (4, 12, )', '10-- (8, 9, 10, 11, )', '1--0 (8, 10, 12, 14, )', '1-1- (10, 11, 14, 15, )', }]",
              finalImplicants.getDisplayableString());
    cout<<quineMcCluskey.getOutputTable(finalImplicants);
}

TEST(QuineMcCluskeyTest, DISABLED_ExperimentalTest)
{
    QuineMcCluskeyForTest quineMcCluskey;
    quineMcCluskey.setInputOutput(2, LogicalValue::True);
    quineMcCluskey.setInputOutput(3, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(4, LogicalValue::True);
    quineMcCluskey.setInputOutput(5, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(6, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(8, LogicalValue::True);
    quineMcCluskey.setInputOutput(9, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(10, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(11, LogicalValue::True);
    quineMcCluskey.setInputOutput(12, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(14, LogicalValue::True);
    quineMcCluskey.setInputOutput(15, LogicalValue::DontCare);

    quineMcCluskey.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    quineMcCluskey.findAllCombinations();

    ImplicantsForTest finalImplicants(quineMcCluskey.getAllFinalImplicants());
    cout<<quineMcCluskey.getOutputTable(finalImplicants);
}

namespace
{

void setInputOutput(QuineMcCluskeyForTest & quineMcCluskey, MintermForTest const input, string const& output)
{
    if(output == "1")
    {
        quineMcCluskey.setInputOutput(input, LogicalValue::True);
    }
    else if(output == "0")
    {
        quineMcCluskey.setInputOutput(input, LogicalValue::False);
    }
    else if(output == "X")
    {
        quineMcCluskey.setInputOutput(input, LogicalValue::DontCare);
    }
}

}

TEST(QuineMcCluskeyTest, DISABLED_GetInputsFromFromFile_HasZeroInDigitForByte)
{
    QuineMcCluskeyForTest quineMcCluskey;
    AlbaLocalPathHandler pathOfNewAlgorithm(APRG_DIR R"(\AprgAlgorithm\FilesForTests\QuineMcKluskeyTest\HasZeroInDigitForByte.txt)");
    ifstream algorithmResultsFileStream(pathOfNewAlgorithm.getFullPath());
    AlbaFileReader algorithmResultsReader(algorithmResultsFileStream);
    while(algorithmResultsReader.isNotFinished())
    {
        string lineInFile(algorithmResultsReader.getLineAndIgnoreWhiteSpaces());
        strings entries;
        splitToStrings<SplitStringType::WithoutDelimeters>(entries, lineInFile, " ");
        if(entries.size()>=2)
        {
            MintermForTest input = convertStringToNumber<MintermForTest>(entries.at(0));
            setInputOutput(quineMcCluskey, input, getStringWithCapitalLetters(entries.at(1)));
        }
    }

    quineMcCluskey.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    cout << "Initial computation table: " << endl << quineMcCluskey.getComputationTableString() << endl;
    quineMcCluskey.findAllCombinations();

    ImplicantsForTest finalImplicants(quineMcCluskey.getAllFinalImplicants());
    EXPECT_EQ("Implicants : [(has size 30):{' (0)', '1010 (10)', '10100 (20)', '11110 (30)', '-101000 (40, 104, )', '111100 (60)', '1-00110 (70, 102, )',"
              " '-1010000 (80, 208, )', '1011010 (90)', '11001-- (100, 101, 102, 103, )', '110-10- (100, 101, 108, 109, )', '110-1-0 (100, 102, 108, 110, )',"
              " '-1100110 (102, 230, )', '11010-- (104, 105, 106, 107, )', '1101-0- (104, 105, 108, 109, )', '1101--0 (104, 106, 108, 110, )', '11-1000 (104, 120, )',"
              " '10000010 (130)', '1-001100 (140, 204, )', '10010110 (150)', '10100000 (160)', '10101010 (170)', '10110100 (180)', '10111110 (190)',"
              " '11001--- (200, 201, 202, 203, 204, 205, 206, 207, )', '110-1100 (204, 220, )', '1101000- (208, 209, )', '110100-0 (208, 210, )',"
              " '11-10000 (208, 240, )', '11111010 (250)', }]",
              finalImplicants.getDisplayableString());
    cout << quineMcCluskey.getOutputTable(finalImplicants);
}

TEST(QuineMcCluskeyTest, DISABLED_GetInputsFromFromFile_LogarithmBase2ForByte)
{
    QuineMcCluskeyForTest qm0;
    QuineMcCluskeyForTest qm1;
    QuineMcCluskeyForTest qm2;
    AlbaLocalPathHandler pathOfNewAlgorithm(APRG_DIR R"(\AprgAlgorithm\FilesForTests\QuineMcKluskeyTest\LogarithmBase2ForByte.txt)");
    ifstream algorithmResultsFileStream(pathOfNewAlgorithm.getFullPath());
    AlbaFileReader algorithmResultsReader(algorithmResultsFileStream);
    while(algorithmResultsReader.isNotFinished())
    {
        string lineInFile(algorithmResultsReader.getLineAndIgnoreWhiteSpaces());
        strings entries;
        splitToStrings<SplitStringType::WithoutDelimeters>(entries, lineInFile, " ");
        if(entries.size()>=4)
        {
            MintermForTest input = convertStringToNumber<MintermForTest>(entries.at(0));
            setInputOutput(qm0, input, getStringWithCapitalLetters(entries.at(1)));
            setInputOutput(qm1, input, getStringWithCapitalLetters(entries.at(2)));
            setInputOutput(qm2, input, getStringWithCapitalLetters(entries.at(3)));
        }
    }

    qm0.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    qm1.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    qm2.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    cout << "Initial computation table: " << endl << qm0.getComputationTableString() << endl;
    cout << "Initial computation table: " << endl << qm1.getComputationTableString() << endl;
    cout << "Initial computation table: " << endl << qm2.getComputationTableString() << endl;
    qm0.findAllCombinations();
    qm1.findAllCombinations();
    qm2.findAllCombinations();

    ImplicantsForTest finalImplicants0(qm0.getAllFinalImplicants());
    ImplicantsForTest finalImplicants1(qm1.getAllFinalImplicants());
    ImplicantsForTest finalImplicants2(qm2.getAllFinalImplicants());
    cout << qm0.getOutputTable(finalImplicants0);
    cout << qm1.getOutputTable(finalImplicants1);
    cout << qm2.getOutputTable(finalImplicants2);
}

}

}
