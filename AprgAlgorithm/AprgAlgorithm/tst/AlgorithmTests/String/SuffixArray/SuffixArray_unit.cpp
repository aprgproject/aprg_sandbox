#include <Algorithm/String/SuffixArray/SuffixArray.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SuffixArrayForTest = SuffixArray<int>;
}

TEST(SuffixArrayTest, GetSizeWorks) {
    SuffixArrayForTest suffixArray("LetsDanceToThisSong");

    EXPECT_EQ(19, suffixArray.getSize());
}

TEST(SuffixArrayTest, GetIndexOnMainStringOfSuffixAtWorks) {
    SuffixArrayForTest suffixArray("LetsDanceToThisSong");

    EXPECT_EQ(5, suffixArray.getIndexOnMainStringOfSuffixAt(5));
    EXPECT_EQ(7, suffixArray.getIndexOnMainStringOfSuffixAt(6));
    EXPECT_EQ(8, suffixArray.getIndexOnMainStringOfSuffixAt(7));
}

TEST(SuffixArrayTest, GetRankWorks) {
    SuffixArrayForTest suffixArray("LetsDanceToThisSong");

    EXPECT_EQ(2, suffixArray.getRank("LetsSingInstead"));
}

TEST(SuffixArrayTest, GetSuffixAtWorks) {
    SuffixArrayForTest suffixArray("LetsDanceToThisSong");

    EXPECT_EQ("DanceToThisSong", suffixArray.getSuffixAt(0));
    EXPECT_EQ("LetsDanceToThisSong", suffixArray.getSuffixAt(1));
    EXPECT_EQ("Song", suffixArray.getSuffixAt(2));
    EXPECT_EQ("ThisSong", suffixArray.getSuffixAt(3));
    EXPECT_EQ("ToThisSong", suffixArray.getSuffixAt(4));
    EXPECT_EQ("anceToThisSong", suffixArray.getSuffixAt(5));
    EXPECT_EQ("ceToThisSong", suffixArray.getSuffixAt(6));
    EXPECT_EQ("eToThisSong", suffixArray.getSuffixAt(7));
    EXPECT_EQ("etsDanceToThisSong", suffixArray.getSuffixAt(8));
    EXPECT_EQ("g", suffixArray.getSuffixAt(9));
}

TEST(SuffixArrayTest, GetLongestCommonPrefixOfTwoSuffixesWorks) {
    SuffixArrayForTest suffixArray("LetsDanceToThisSong");

    EXPECT_EQ("T", suffixArray.getLongestCommonPrefixOfTwoSuffixes(3, 4));
    EXPECT_TRUE(suffixArray.getLongestCommonPrefixOfTwoSuffixes(5, 6).empty());
    EXPECT_EQ("e", suffixArray.getLongestCommonPrefixOfTwoSuffixes(7, 8));
}

}  // namespace algorithm

}  // namespace alba
