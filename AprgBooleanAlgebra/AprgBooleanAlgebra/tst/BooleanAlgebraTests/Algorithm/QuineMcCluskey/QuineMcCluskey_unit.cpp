#include <BooleanAlgebra/Algorithm/QuineMcCluskey/QuineMcCluskey.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace booleanAlgebra {

namespace {
using MintermForTest = uint64_t;
using QuineMcCluskeyForTest = QuineMcCluskey<MintermForTest>;
using ImplicantForTest = QuineMcCluskeyForTest::Implicant;
using ImplicantsForTest = QuineMcCluskeyForTest::Implicants;
}  // namespace

TEST(QuineMcCluskeyTest, ImplicantEquivalentStringTest) {
    ImplicantForTest implicant({8, 10, 12, 14});
    EXPECT_EQ("00001--0", implicant.getEquivalentString(8));
}

TEST(QuineMcCluskeyTest, ImplicantCompatibilityTest) {
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

TEST(QuineMcCluskeyTest, ImplicantSubsetTest) {
    ImplicantForTest implicant1({4, 12});
    ImplicantForTest implicant2({8, 9});
    ImplicantForTest implicant3({8, 9, 10, 11});

    EXPECT_FALSE(implicant1.isASubsetOf(implicant2));
    EXPECT_FALSE(implicant1.isASubsetOf(implicant3));
    EXPECT_FALSE(implicant2.isASubsetOf(implicant1));
    EXPECT_TRUE(implicant2.isASubsetOf(implicant3));
    EXPECT_FALSE(implicant3.isASubsetOf(implicant1));
    EXPECT_FALSE(implicant3.isASubsetOf(implicant2));
}

TEST(QuineMcCluskeyTest, UnintializedOutputTest) {
    QuineMcCluskeyForTest quineMcCluskey;

    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0xA));
    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0x1));
    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0xB));
    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0xA));
}

TEST(QuineMcCluskeyTest, InputOutputTest) {
    QuineMcCluskeyForTest quineMcCluskey;
    quineMcCluskey.setInputOutput(0x4, LogicalValue::False);
    quineMcCluskey.setInputOutput(0x5, LogicalValue::True);
    quineMcCluskey.setInputOutput(0x6, LogicalValue::DontCare);

    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0x4));
    EXPECT_EQ(LogicalValue::True, quineMcCluskey.getOutput(0x5));
    EXPECT_EQ(LogicalValue::DontCare, quineMcCluskey.getOutput(0x6));
}

TEST(QuineMcCluskeyTest, GetImplicantsWithZeroCommonalityCount) {
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

    ImplicantsForTest mintermsWithZero(quineMcCluskey.getImplicants(0, 0));
    ImplicantsForTest mintermsWithOne(quineMcCluskey.getImplicants(1, 0));
    ImplicantsForTest mintermsWithTwo(quineMcCluskey.getImplicants(2, 0));
    ImplicantsForTest mintermsWithThree(quineMcCluskey.getImplicants(3, 0));
    ImplicantsForTest mintermsWithFour(quineMcCluskey.getImplicants(4, 0));
    ImplicantsForTest expectedWithOne{{4}, {8}};
    ImplicantsForTest expectedWithTwo{{9}, {10}, {12}};
    ImplicantsForTest expectedWithThree{{11}, {14}};
    ImplicantsForTest expectedWithFour{{15}};
    EXPECT_TRUE(mintermsWithZero.empty());
    EXPECT_EQ(expectedWithOne, mintermsWithOne);
    EXPECT_EQ(expectedWithTwo, mintermsWithTwo);
    EXPECT_EQ(expectedWithThree, mintermsWithThree);
    EXPECT_EQ(expectedWithFour, mintermsWithFour);
}

TEST(QuineMcCluskeyTest, GetImplicantsWithOneCommonalityCount) {
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
    quineMcCluskey.findCombinationOfImplicants(0, 0);
    quineMcCluskey.findCombinationOfImplicants(1, 0);
    quineMcCluskey.findCombinationOfImplicants(2, 0);
    quineMcCluskey.findCombinationOfImplicants(3, 0);
    quineMcCluskey.findCombinationOfImplicants(4, 0);

    ImplicantsForTest mintermsWithZero(quineMcCluskey.getImplicants(0, 1));
    ImplicantsForTest mintermsWithOne(quineMcCluskey.getImplicants(1, 1));
    ImplicantsForTest mintermsWithTwo(quineMcCluskey.getImplicants(2, 1));
    ImplicantsForTest mintermsWithThree(quineMcCluskey.getImplicants(3, 1));
    ImplicantsForTest mintermsWithFour(quineMcCluskey.getImplicants(4, 1));
    ImplicantsForTest expectedWithOne{{4, 12}, {8, 9}, {8, 10}, {8, 12}};
    ImplicantsForTest expectedWithTwo{{9, 11}, {10, 11}, {10, 14}, {12, 14}};
    ImplicantsForTest expectedWithThree{{11, 15}, {14, 15}};
    EXPECT_TRUE(mintermsWithZero.empty());
    EXPECT_EQ(expectedWithOne, mintermsWithOne);
    EXPECT_EQ(expectedWithTwo, mintermsWithTwo);
    EXPECT_EQ(expectedWithThree, mintermsWithThree);
    EXPECT_TRUE(mintermsWithFour.empty());
}

TEST(QuineMcCluskeyTest, GetImplicantsWithTwoCommonalityCounts) {
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

    ImplicantsForTest mintermsWithZero(quineMcCluskey.getImplicants(0, 2));
    ImplicantsForTest mintermsWithOne(quineMcCluskey.getImplicants(1, 2));
    ImplicantsForTest mintermsWithTwo(quineMcCluskey.getImplicants(2, 2));
    ImplicantsForTest mintermsWithThree(quineMcCluskey.getImplicants(3, 2));
    ImplicantsForTest mintermsWithFour(quineMcCluskey.getImplicants(4, 2));
    ImplicantsForTest expectedWithOne{{8, 9, 10, 11}, {8, 10, 12, 14}};
    ImplicantsForTest expectedWithTwo{{10, 11, 14, 15}};
    EXPECT_TRUE(mintermsWithZero.empty());
    EXPECT_EQ(expectedWithOne, mintermsWithOne);
    EXPECT_EQ(expectedWithTwo, mintermsWithTwo);
    EXPECT_TRUE(mintermsWithThree.empty());
    EXPECT_TRUE(mintermsWithFour.empty());
}

TEST(QuineMcCluskeyTest, GetAllPrimeImplicantsAndGetBestPrimeImplicantsWorksWithExample1) {
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

    ImplicantsForTest primeImplicants(quineMcCluskey.getAllPrimeImplicants());
    ImplicantsForTest expectedPrimeImplicants{{4, 12}, {8, 9, 10, 11}, {8, 10, 12, 14}, {10, 11, 14, 15}};
    EXPECT_EQ(expectedPrimeImplicants, primeImplicants);
    cout << quineMcCluskey.getOutputTable(primeImplicants);

    ImplicantsForTest bestPrimeImplicants(quineMcCluskey.getBestPrimeImplicants(primeImplicants));
    ImplicantsForTest expectedBestPrimeImplicants{{4, 12}, {8, 9, 10, 11}, {10, 11, 14, 15}};
    EXPECT_EQ(expectedBestPrimeImplicants, bestPrimeImplicants);
    cout << quineMcCluskey.getOutputTable(bestPrimeImplicants);
}

TEST(QuineMcCluskeyTest, GetAllPrimeImplicantsAndGetBestPrimeImplicantsWorksWithExample2) {
    QuineMcCluskeyForTest quineMcCluskey;
    quineMcCluskey.setInputOutput(0, LogicalValue::True);
    quineMcCluskey.setInputOutput(1, LogicalValue::True);
    quineMcCluskey.setInputOutput(2, LogicalValue::True);
    quineMcCluskey.setInputOutput(5, LogicalValue::True);
    quineMcCluskey.setInputOutput(6, LogicalValue::True);
    quineMcCluskey.setInputOutput(7, LogicalValue::True);

    quineMcCluskey.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    quineMcCluskey.findAllCombinations();

    ImplicantsForTest primeImplicants(quineMcCluskey.getAllPrimeImplicants());
    ImplicantsForTest expectedPrimeImplicants{{0, 1}, {0, 2}, {1, 5}, {2, 6}, {5, 7}, {6, 7}};
    EXPECT_EQ(expectedPrimeImplicants, primeImplicants);
    cout << quineMcCluskey.getOutputTable(primeImplicants);

    ImplicantsForTest bestPrimeImplicants(quineMcCluskey.getBestPrimeImplicants(primeImplicants));
    ImplicantsForTest expectedBestPrimeImplicants{{0, 1}, {2, 6}, {5, 7}};
    EXPECT_EQ(expectedBestPrimeImplicants, bestPrimeImplicants);
    cout << quineMcCluskey.getOutputTable(bestPrimeImplicants);
}

TEST(QuineMcCluskeyTest, ExperimentalTest)  //
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

    ImplicantsForTest primeImplicants(quineMcCluskey.getAllPrimeImplicants());
    cout << quineMcCluskey.getOutputTable(primeImplicants);

    ImplicantsForTest bestPrimeImplicants(quineMcCluskey.getBestPrimeImplicants(primeImplicants));
    cout << quineMcCluskey.getOutputTable(bestPrimeImplicants);
}

namespace {

void setInputOutput(QuineMcCluskeyForTest& quineMcCluskey, MintermForTest const input, string const& output) {
    if (output == "1") {
        quineMcCluskey.setInputOutput(input, LogicalValue::True);
    } else if (output == "0") {
        quineMcCluskey.setInputOutput(input, LogicalValue::False);
    } else if (output == "X") {
        quineMcCluskey.setInputOutput(input, LogicalValue::DontCare);
    }
}

}  // namespace

TEST(QuineMcCluskeyTest, DISABLED_GetInputsFromFromFileWorks_HasZeroInDigitForByte)  //
{
    QuineMcCluskeyForTest quineMcCluskey;
    AlbaLocalPathHandler pathOfNewAlgorithm(
        APRG_DIR R"(\AprgBooleanAlgebra\FilesForTests\QuineMcKluskeyTest\HasZeroInDigitForByte.txt)");
    ifstream algorithmResultsFileStream(pathOfNewAlgorithm.getFullPath());
    AlbaFileReader algorithmResultsReader(algorithmResultsFileStream);
    while (algorithmResultsReader.isNotFinished()) {
        string lineInFile(algorithmResultsReader.getLineAndIgnoreWhiteSpaces());
        strings entries;
        splitToStrings<SplitStringType::WithoutDelimeters>(entries, lineInFile, " ");
        if (entries.size() >= 2) {
            MintermForTest input = convertStringToNumber<MintermForTest>(entries[0]);
            setInputOutput(quineMcCluskey, input, getStringWithCapitalLetters(entries[1]));
        }
    }

    quineMcCluskey.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    cout << "Initial computation table: \n" << quineMcCluskey.getComputationTableString() << "\n";
    quineMcCluskey.findAllCombinations();

    ImplicantsForTest primeImplicants(quineMcCluskey.getAllPrimeImplicants());
    ImplicantsForTest expectedPrimeImplicants{
        {0},
        {10},
        {20},
        {30},
        {40, 104},
        {60},
        {70, 102},
        {80, 208},
        {90},
        {100, 101, 102, 103},
        {100, 101, 108, 109},
        {100, 102, 108, 110},
        {102, 230},
        {104, 105, 106, 107},
        {104, 105, 108, 109},
        {104, 106, 108, 110},
        {104, 120},
        {130},
        {140, 204},
        {150},
        {160},
        {170},
        {180},
        {190},
        {200, 201, 202, 203, 204, 205, 206, 207},
        {204, 220},
        {208, 209},
        {208, 210},
        {208, 240},
        {250}};
    EXPECT_EQ(expectedPrimeImplicants, primeImplicants);
    cout << quineMcCluskey.getOutputTable(primeImplicants);

    ImplicantsForTest bestPrimeImplicants(quineMcCluskey.getBestPrimeImplicants(primeImplicants));
    ImplicantsForTest expectedBestPrimeImplicants{
        {0},
        {10},
        {20},
        {30},
        {40, 104},
        {60},
        {70, 102},
        {80, 208},
        {90},
        {100, 101, 102, 103},
        {100, 101, 108, 109},
        {100, 102, 108, 110},
        {102, 230},
        {104, 105, 106, 107},
        {104, 120},
        {130},
        {140, 204},
        {150},
        {160},
        {170},
        {180},
        {190},
        {200, 201, 202, 203, 204, 205, 206, 207},
        {204, 220},
        {208, 209},
        {208, 210},
        {208, 240},
        {250}};
    EXPECT_EQ(expectedBestPrimeImplicants, bestPrimeImplicants);
    cout << quineMcCluskey.getOutputTable(bestPrimeImplicants);
}

TEST(QuineMcCluskeyTest, DISABLED_GetInputsFromFromFile_LogarithmBase2ForByte) {
    QuineMcCluskeyForTest qm0;
    QuineMcCluskeyForTest qm1;
    QuineMcCluskeyForTest qm2;
    AlbaLocalPathHandler pathOfNewAlgorithm(
        APRG_DIR R"(\AprgBooleanAlgebra\FilesForTests\QuineMcKluskeyTest\LogarithmBase2ForByte.txt)");
    ifstream algorithmResultsFileStream(pathOfNewAlgorithm.getFullPath());
    AlbaFileReader algorithmResultsReader(algorithmResultsFileStream);
    while (algorithmResultsReader.isNotFinished()) {
        string lineInFile(algorithmResultsReader.getLineAndIgnoreWhiteSpaces());
        strings entries;
        splitToStrings<SplitStringType::WithoutDelimeters>(entries, lineInFile, " ");
        if (entries.size() >= 4) {
            MintermForTest input = convertStringToNumber<MintermForTest>(entries[0]);
            setInputOutput(qm0, input, getStringWithCapitalLetters(entries[1]));
            setInputOutput(qm1, input, getStringWithCapitalLetters(entries[2]));
            setInputOutput(qm2, input, getStringWithCapitalLetters(entries[3]));
        }
    }

    qm0.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    qm1.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    qm2.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    cout << "Initial computation table: \n" << qm0.getComputationTableString() << "\n";
    cout << "Initial computation table: \n" << qm1.getComputationTableString() << "\n";
    cout << "Initial computation table: \n" << qm2.getComputationTableString() << "\n";
    qm0.findAllCombinations();
    qm1.findAllCombinations();
    qm2.findAllCombinations();

    ImplicantsForTest primeImplicants0(qm0.getAllPrimeImplicants());
    ImplicantsForTest primeImplicants1(qm1.getAllPrimeImplicants());
    ImplicantsForTest primeImplicants2(qm2.getAllPrimeImplicants());
    cout << qm0.getOutputTable(primeImplicants0);
    cout << qm1.getOutputTable(primeImplicants1);
    cout << qm2.getOutputTable(primeImplicants2);
}

TEST(QuineMcCluskeyTest, DISABLED_GetInputsFromFromFile_ZeroesStartingFromMsb) {
    QuineMcCluskeyForTest qm0;
    QuineMcCluskeyForTest qm1;
    QuineMcCluskeyForTest qm2;
    QuineMcCluskeyForTest qm3;
    AlbaLocalPathHandler pathOfNewAlgorithm(
        APRG_DIR R"(\AprgBooleanAlgebra\FilesForTests\QuineMcKluskeyTest\ZeroesStartingFromMsb.txt)");
    ifstream algorithmResultsFileStream(pathOfNewAlgorithm.getFullPath());
    AlbaFileReader algorithmResultsReader(algorithmResultsFileStream);
    while (algorithmResultsReader.isNotFinished()) {
        string lineInFile(algorithmResultsReader.getLineAndIgnoreWhiteSpaces());
        strings entries;
        splitToStrings<SplitStringType::WithoutDelimeters>(entries, lineInFile, " ");
        if (entries.size() >= 5) {
            MintermForTest input = convertStringToNumber<MintermForTest>(entries[0]);
            setInputOutput(qm0, input, getStringWithCapitalLetters(entries[1]));
            setInputOutput(qm1, input, getStringWithCapitalLetters(entries[2]));
            setInputOutput(qm2, input, getStringWithCapitalLetters(entries[3]));
            setInputOutput(qm3, input, getStringWithCapitalLetters(entries[4]));
        }
    }

    qm0.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    qm1.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    qm2.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    qm3.fillComputationalTableWithMintermsWithZeroCommonalityCount();
    cout << "Initial computation table: \n" << qm0.getComputationTableString() << "\n";
    cout << "Initial computation table: \n" << qm1.getComputationTableString() << "\n";
    cout << "Initial computation table: \n" << qm2.getComputationTableString() << "\n";
    cout << "Initial computation table: \n" << qm3.getComputationTableString() << "\n";
    qm0.findAllCombinations();
    qm1.findAllCombinations();
    qm2.findAllCombinations();
    qm3.findAllCombinations();

    ImplicantsForTest primeImplicants0(qm0.getAllPrimeImplicants());
    ImplicantsForTest primeImplicants1(qm1.getAllPrimeImplicants());
    ImplicantsForTest primeImplicants2(qm2.getAllPrimeImplicants());
    ImplicantsForTest primeImplicants3(qm3.getAllPrimeImplicants());
    cout << qm0.getOutputTable(primeImplicants0);
    cout << qm1.getOutputTable(primeImplicants1);
    cout << qm2.getOutputTable(primeImplicants2);
    cout << qm3.getOutputTable(primeImplicants3);
}

}  // namespace booleanAlgebra

}  // namespace alba
