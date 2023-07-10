#include <Algorithm/String/SubstringSearch/AhoCorasickMultipleSubstringsSearch.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Index = int;
using SubstringSearchForTest = AhoCorasickMultipleSubstringsSearch<Index>;
}  // namespace

TEST(AhoCorasickMultipleSubstringsSearchTest, SearchWorksUsingEmptyStringsAndDoesNotCrash) {
    string emptyString;
    string nonEmptyString("NonEmptyString");
    SubstringSearchForTest::Strings queries{emptyString, nonEmptyString};
    SubstringSearchForTest substringSearch(queries);

    SubstringSearchForTest::SearchResult expectedResult1;
    SubstringSearchForTest::SearchResult expectedResult2{{"NonEmptyString", {0}}};
    EXPECT_EQ(expectedResult1, substringSearch.search(emptyString));
    EXPECT_EQ(expectedResult2, substringSearch.search(nonEmptyString));
}

TEST(AhoCorasickMultipleSubstringsSearchTest, SearchWorksUsingExample1) {
    SubstringSearchForTest::Strings queries{"AACAA", "BBB"};
    SubstringSearchForTest substringSearch(queries);
    string searchSpace("AABRAACADABRAACAADABRA");

    SubstringSearchForTest::SearchResult expectedResult{{"AACAA", {12}}};
    EXPECT_EQ(expectedResult, substringSearch.search(searchSpace));
}

TEST(AhoCorasickMultipleSubstringsSearchTest, SearchWorksUsingExample2) {
    SubstringSearchForTest::Strings queries{"blue", "red"};
    SubstringSearchForTest substringSearch(queries);
    string searchSpace("Mr. Blue has a blue house");

    SubstringSearchForTest::SearchResult expectedResult{{"blue", {15}}};
    EXPECT_EQ(expectedResult, substringSearch.search(searchSpace));
}

TEST(AhoCorasickMultipleSubstringsSearchTest, SearchWorksUsingExample3) {
    SubstringSearchForTest::Strings queries{"lets", "Dance", "Too", "his", "Song", "T"};
    SubstringSearchForTest substringSearch(queries);
    string searchSpace("LetsDanceToThisSong");

    SubstringSearchForTest::SearchResult expectedResult{{"Dance", {4}}, {"Song", {15}}, {"T", {9, 11}}, {"his", {12}}};
    EXPECT_EQ(expectedResult, substringSearch.search(searchSpace));
}

}  // namespace algorithm

}  // namespace alba
