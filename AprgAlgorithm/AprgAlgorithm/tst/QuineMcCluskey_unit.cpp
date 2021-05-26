#include <QuineMcCluskey/QuineMcCluskey.hpp>

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

TEST(QuineMcCluskeyTest, ImplicantEquivalentStringTest)
{
    Implicant implicant;    implicant.addMinterm(8);
    implicant.addMinterm(10);
    implicant.addMinterm(12);
    implicant.addMinterm(14);    EXPECT_EQ("00001--0", implicant.getEquivalentString(8));
}

TEST(QuineMcCluskeyTest, ImplicantCompatibilityTest)
{
    Implicant implicant1;
    implicant1.addMinterm(4);
    implicant1.addMinterm(12);
    Implicant implicant2;
    implicant2.addMinterm(8);
    implicant2.addMinterm(9);
    Implicant implicant3;
    implicant3.addMinterm(10);
    implicant3.addMinterm(11);

    EXPECT_FALSE(implicant1.isCompatible(implicant2));
    EXPECT_FALSE(implicant1.isCompatible(implicant3));
    EXPECT_FALSE(implicant2.isCompatible(implicant1));
    EXPECT_TRUE(implicant2.isCompatible(implicant3));
    EXPECT_FALSE(implicant3.isCompatible(implicant1));
    EXPECT_TRUE(implicant3.isCompatible(implicant2));
}

TEST(QuineMcCluskeyTest, ImplicantSubsetTest)
{
    Implicant implicant1;
    implicant1.addMinterm(4);
    implicant1.addMinterm(12);
    Implicant implicant2;
    implicant2.addMinterm(8);
    implicant2.addMinterm(9);
    Implicant implicant3;
    implicant3.addMinterm(8);
    implicant3.addMinterm(9);
    implicant3.addMinterm(10);
    implicant3.addMinterm(11);

    EXPECT_FALSE(implicant1.isSubset(implicant2));
    EXPECT_FALSE(implicant1.isSubset(implicant3));
    EXPECT_FALSE(implicant2.isSubset(implicant1));
    EXPECT_TRUE(implicant2.isSubset(implicant3));
    EXPECT_FALSE(implicant3.isSubset(implicant1));
    EXPECT_FALSE(implicant3.isSubset(implicant2));
}

TEST(QuineMcCluskeyTest, UnintializedOutputTest)
{
    QuineMcCluskey quineMcCluskey;
    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0xA));
    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0x1));
    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0xB));
    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0xA));
}

TEST(QuineMcCluskeyTest, InputOutputTest)
{
    QuineMcCluskey quineMcCluskey;
    quineMcCluskey.setInputOutput(0x4, LogicalValue::False);
    quineMcCluskey.setInputOutput(0x5, LogicalValue::True);
    quineMcCluskey.setInputOutput(0x6, LogicalValue::DontCare);
    EXPECT_EQ(LogicalValue::False, quineMcCluskey.getOutput(0x4));
    EXPECT_EQ(LogicalValue::True, quineMcCluskey.getOutput(0x5));
    EXPECT_EQ(LogicalValue::DontCare, quineMcCluskey.getOutput(0x6));
}

TEST(QuineMcCluskeyTest, GetImplicantsForCubeZero)
{
    QuineMcCluskey quineMcCluskey;
    quineMcCluskey.setInputOutput(4, LogicalValue::True);
    quineMcCluskey.setInputOutput(8, LogicalValue::True);
    quineMcCluskey.setInputOutput(9, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(10, LogicalValue::True);
    quineMcCluskey.setInputOutput(11, LogicalValue::True);
    quineMcCluskey.setInputOutput(12, LogicalValue::True);
    quineMcCluskey.setInputOutput(14, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(15, LogicalValue::True);

    quineMcCluskey.fillComputationalTableWithMintermsForZeroCube();

    Implicants mintermsWithZero(quineMcCluskey.getImplicants(0,0));
    Implicants mintermsWithOne(quineMcCluskey.getImplicants(1,0));
    Implicants mintermsWithTwo(quineMcCluskey.getImplicants(2,0));
    Implicants mintermsWithThree(quineMcCluskey.getImplicants(3,0));
    Implicants mintermsWithFour(quineMcCluskey.getImplicants(4,0));

    ASSERT_EQ(0u, mintermsWithZero.getSize());
    ASSERT_EQ(2u, mintermsWithOne.getSize());
    ASSERT_EQ(3u, mintermsWithTwo.getSize());
    ASSERT_EQ(2u, mintermsWithThree.getSize());
    ASSERT_EQ(1u, mintermsWithFour.getSize());

    EXPECT_EQ("", mintermsWithZero.getImplicantsString());
    EXPECT_EQ("[0 : 4|], [1 : 8|], ", mintermsWithOne.getImplicantsString());
    EXPECT_EQ("[0 : 9|], [1 : 10|], [2 : 12|], ", mintermsWithTwo.getImplicantsString());
    EXPECT_EQ("[0 : 11|], [1 : 14|], ", mintermsWithThree.getImplicantsString());
    EXPECT_EQ("[0 : 15|], ", mintermsWithFour.getImplicantsString());
}

TEST(QuineMcCluskeyTest, GetImplicantsCubeOne)
{
    QuineMcCluskey quineMcCluskey;
    quineMcCluskey.setInputOutput(4, LogicalValue::True);
    quineMcCluskey.setInputOutput(8, LogicalValue::True);
    quineMcCluskey.setInputOutput(9, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(10, LogicalValue::True);
    quineMcCluskey.setInputOutput(11, LogicalValue::True);
    quineMcCluskey.setInputOutput(12, LogicalValue::True);
    quineMcCluskey.setInputOutput(14, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(15, LogicalValue::True);

    quineMcCluskey.fillComputationalTableWithMintermsForZeroCube();
    quineMcCluskey.findCombinationOfImplicants(0,0);
    quineMcCluskey.findCombinationOfImplicants(1,0);
    quineMcCluskey.findCombinationOfImplicants(2,0);
    quineMcCluskey.findCombinationOfImplicants(3,0);
    quineMcCluskey.findCombinationOfImplicants(4,0);

    Implicants mintermsWithZero(quineMcCluskey.getImplicants(0,1));
    Implicants mintermsWithOne(quineMcCluskey.getImplicants(1,1));
    Implicants mintermsWithTwo(quineMcCluskey.getImplicants(2,1));
    Implicants mintermsWithThree(quineMcCluskey.getImplicants(3,1));
    Implicants mintermsWithFour(quineMcCluskey.getImplicants(4,1));

    ASSERT_EQ(0u, mintermsWithZero.getSize());
    ASSERT_EQ(4u, mintermsWithOne.getSize());
    ASSERT_EQ(4u, mintermsWithTwo.getSize());
    ASSERT_EQ(2u, mintermsWithThree.getSize());
    ASSERT_EQ(0u, mintermsWithFour.getSize());

    EXPECT_EQ("", mintermsWithZero.getImplicantsString());
    EXPECT_EQ("[0 : 4|12|], [1 : 8|9|], [2 : 8|10|], [3 : 8|12|], ", mintermsWithOne.getImplicantsString());
    EXPECT_EQ("[0 : 9|11|], [1 : 10|11|], [2 : 10|14|], [3 : 12|14|], ", mintermsWithTwo.getImplicantsString());
    EXPECT_EQ("[0 : 11|15|], [1 : 14|15|], ", mintermsWithThree.getImplicantsString());
    EXPECT_EQ("", mintermsWithFour.getImplicantsString());
}

TEST(QuineMcCluskeyTest, GetImplicantsCubeTwo)
{
    QuineMcCluskey quineMcCluskey;
    quineMcCluskey.setInputOutput(4, LogicalValue::True);
    quineMcCluskey.setInputOutput(8, LogicalValue::True);
    quineMcCluskey.setInputOutput(9, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(10, LogicalValue::True);
    quineMcCluskey.setInputOutput(11, LogicalValue::True);
    quineMcCluskey.setInputOutput(12, LogicalValue::True);
    quineMcCluskey.setInputOutput(14, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(15, LogicalValue::True);

    quineMcCluskey.fillComputationalTableWithMintermsForZeroCube();
    quineMcCluskey.findAllCombinations();

    Implicants mintermsWithZero(quineMcCluskey.getImplicants(0,2));
    Implicants mintermsWithOne(quineMcCluskey.getImplicants(1,2));
    Implicants mintermsWithTwo(quineMcCluskey.getImplicants(2,2));
    Implicants mintermsWithThree(quineMcCluskey.getImplicants(3,2));
    Implicants mintermsWithFour(quineMcCluskey.getImplicants(4,2));

    ASSERT_EQ(0u, mintermsWithZero.getSize());
    ASSERT_EQ(2u, mintermsWithOne.getSize());
    ASSERT_EQ(1u, mintermsWithTwo.getSize());
    ASSERT_EQ(0u, mintermsWithThree.getSize());
    ASSERT_EQ(0u, mintermsWithFour.getSize());

    EXPECT_EQ("", mintermsWithZero.getImplicantsString());
    EXPECT_EQ("[0 : 8|9|10|11|], [1 : 8|10|12|14|], ", mintermsWithOne.getImplicantsString());
    EXPECT_EQ("[0 : 10|11|14|15|], ", mintermsWithTwo.getImplicantsString());
    EXPECT_EQ("", mintermsWithThree.getImplicantsString());
    EXPECT_EQ("", mintermsWithFour.getImplicantsString());
}

TEST(QuineMcCluskeyTest, GetFinalImplicants)
{
    QuineMcCluskey quineMcCluskey;
    quineMcCluskey.setInputOutput(4, LogicalValue::True);
    quineMcCluskey.setInputOutput(8, LogicalValue::True);
    quineMcCluskey.setInputOutput(9, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(10, LogicalValue::True);
    quineMcCluskey.setInputOutput(11, LogicalValue::True);
    quineMcCluskey.setInputOutput(12, LogicalValue::True);
    quineMcCluskey.setInputOutput(14, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(15, LogicalValue::True);

    quineMcCluskey.fillComputationalTableWithMintermsForZeroCube();
    quineMcCluskey.findAllCombinations();

    Implicants finalImplicants(quineMcCluskey.getAllFinalImplicants());

    ASSERT_EQ(4u, finalImplicants.getSize());
    EXPECT_EQ("[0 : 4|12|], [1 : 8|9|10|11|], [2 : 8|10|12|14|], [3 : 10|11|14|15|], ", finalImplicants.getImplicantsString());
    cout<<quineMcCluskey.getOutputTable(finalImplicants);
}

TEST(QuineMcCluskeyTest, DISABLED_ExperimentalTest)
{

    QuineMcCluskey quineMcCluskey;
    /*quineMcCluskey.setInputOutput(0, LogicalValue::True);
    quineMcCluskey.setInputOutput(1, LogicalValue::True);
    quineMcCluskey.setInputOutput(3, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(4, LogicalValue::True);
    quineMcCluskey.setInputOutput(5, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(6, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(7, LogicalValue::True);
    quineMcCluskey.setInputOutput(8, LogicalValue::True);
    quineMcCluskey.setInputOutput(9, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(10, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(12, LogicalValue::DontCare);
    quineMcCluskey.setInputOutput(13, LogicalValue::True);
    quineMcCluskey.setInputOutput(15, LogicalValue::DontCare);*/

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

    quineMcCluskey.fillComputationalTableWithMintermsForZeroCube();
    quineMcCluskey.findAllCombinations();

    Implicants finalImplicants(quineMcCluskey.getAllFinalImplicants());

    cout<<quineMcCluskey.getOutputTable(finalImplicants);
}

TEST(QuineMcCluskeyTest, DISABLED_AnalyzeResultsFromFile)
{
    QuineMcCluskey quineMcCluskey;
    AlbaLocalPathHandler pathOfNewAlgorithm(R"(C:\APRG\DateAlgorithmStudy.csv)");

    ifstream algorithmResultsFileStream(pathOfNewAlgorithm.getFullPath());
    AlbaFileReader algorithmResultsReader(algorithmResultsFileStream);

    while(algorithmResultsReader.isNotFinished())
    {
        string lineInFile(algorithmResultsReader.getLineAndIgnoreWhiteSpaces());
        unsigned int input = stringHelper::convertStringToNumber<unsigned int>(stringHelper::getStringBeforeThisString(lineInFile, ","));
        unsigned int output = stringHelper::convertStringToNumber<unsigned int>(stringHelper::getStringAfterThisString(lineInFile, ","));
        if(output&0x1)
        {
            cout<<"input"<<input<<" output"<<output<<"is added"<<endl;
            quineMcCluskey.setInputOutput(input, LogicalValue::True);
        }
    }

    cout<<"quineMcCluskey.fillComputationalTableWithMintermsForZeroCube();"<<endl;
    quineMcCluskey.fillComputationalTableWithMintermsForZeroCube();
    cout<<"quineMcCluskey.findAllCombinations();"<<endl;
    quineMcCluskey.findAllCombinations();
    cout<<"quineMcCluskey.getAllFinalImplicants();"<<endl;
    Implicants finalImplicants(quineMcCluskey.getAllFinalImplicants());
    cout<<quineMcCluskey.getOutputTable(finalImplicants);
}

}