#include <AprgUniqueProblems/DeBruijnSequences/DeBruijnSequences.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(DeBruijnSequencesTest, GetDeBruijnStringWorksWithNullAlphabetWithLength0)
{
    DeBruijnSequences deBruijnSequences(0, "");

    EXPECT_TRUE(deBruijnSequences.getDeBruijnString().empty());
}

TEST(DeBruijnSequencesTest, GetDeBruijnStringWorksWithNullAlphabetWithLength1)
{
    DeBruijnSequences deBruijnSequences(1, "");

    EXPECT_TRUE(deBruijnSequences.getDeBruijnString().empty());
}

TEST(DeBruijnSequencesTest, GetDeBruijnStringWorksWithBinaryAlphabetWithLength0)
{
    DeBruijnSequences deBruijnSequences(0, "01");

    EXPECT_TRUE(deBruijnSequences.getDeBruijnString().empty());
}

TEST(DeBruijnSequencesTest, GetDeBruijnStringWorksWithBinaryAlphabetWithLength1)
{
    DeBruijnSequences deBruijnSequences(1, "01");

    EXPECT_EQ("01", deBruijnSequences.getDeBruijnString());
}

TEST(DeBruijnSequencesTest, GetDeBruijnStringWorksWithBinaryAlphabetWithLength2)
{
    DeBruijnSequences deBruijnSequences(2, "01");

    EXPECT_EQ("01100", deBruijnSequences.getDeBruijnString());
}

TEST(DeBruijnSequencesTest, GetDeBruijnStringWorksWithBinaryAlphabetWithLength3)
{
    DeBruijnSequences deBruijnSequences(3, "01");

    EXPECT_EQ("0011101000", deBruijnSequences.getDeBruijnString());
}

TEST(DeBruijnSequencesTest, GetDeBruijnStringWorksWithBinaryAlphabetWithLength4)
{
    DeBruijnSequences deBruijnSequences(4, "01");

    EXPECT_EQ("0001111011001010000", deBruijnSequences.getDeBruijnString());
}

TEST(DeBruijnSequencesTest, GetDeBruijnStringWorksWithDnaAlphabetWithLength2)
{
    DeBruijnSequences deBruijnSequences(2, "ACTG");

    EXPECT_EQ("ATTGTCTAGGCGACCAA", deBruijnSequences.getDeBruijnString());
}

}
