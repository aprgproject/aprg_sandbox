#include <Algorithm/String/SubstringSearch/SubstringSearchUsingZArray.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Index = int;
using SubstringSearchForTest = SubstringSearchUsingZArray<Index, '#'>;
using Indexes = SubstringSearchForTest::Indexes;
}  // namespace

TEST(SubstringSearchUsingZArrayTest, SearchWorksUsingEmptyStringsAndDoesNotCrash) {
    // SubstringSearchUsingZArray has unique results of handling empty strings

    string emptyString;
    string nonEmptyString("NonEmptyString");
    SubstringSearchForTest emptyStringSearch(emptyString);
    SubstringSearchForTest nonEmptyStringSearch(nonEmptyString);

    EXPECT_EQ(Index(string::npos), emptyStringSearch.search(emptyString));
    EXPECT_EQ(Index(string::npos), emptyStringSearch.search(nonEmptyString));
    EXPECT_EQ(Index(string::npos), nonEmptyStringSearch.search(emptyString));
    EXPECT_EQ(Index(0), nonEmptyStringSearch.search(nonEmptyString));
}

TEST(SubstringSearchUsingZArrayTest, SearchWorksUsingExample1) {
    testSearchUsingExample1<SubstringSearchForTest, Index>();
}

TEST(SubstringSearchUsingZArrayTest, SearchWorksUsingExample2) {
    testSearchUsingExample2<SubstringSearchForTest, Index>();
}

TEST(SubstringSearchUsingZArrayTest, SearchForFirstSubstringWorksUsingExample1) {
    SubstringSearchForTest substringSearch("ATT");
    string mainString("HATTIVATTI");

    EXPECT_EQ(Index(1), substringSearch.searchForFirstSubstring(mainString));
}

TEST(SubstringSearchUsingZArrayTest, SearchForAllSubstringsWorksUsingExample1) {
    SubstringSearchForTest substringSearch("ATT");
    string mainString("HATTIVATTI");

    EXPECT_EQ((Indexes{1, 6}), substringSearch.searchForAllSubstrings(mainString));
}

}  // namespace algorithm

}  // namespace alba
