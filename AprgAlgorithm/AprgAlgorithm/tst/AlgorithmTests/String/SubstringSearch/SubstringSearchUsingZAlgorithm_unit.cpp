#include <Algorithm/String/SubstringSearch/SubstringSearchUsingZAlgorithm.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Index = int;
using SubstringSearchForTest = SubstringSearchUsingZAlgorithm<Index, '#'>;
using Indexes = SubstringSearchForTest::Indexes;
}  // namespace

TEST(SubstringSearchUsingZAlgorithmTest, SearchWorksUsingEmptyStringsAndDoesNotCrash) {
    // SubstringSearchUsingZAlgorithm has unique results of handling empty strings

    string emptyString;
    string nonEmptyString("NonEmptyString");
    SubstringSearchForTest emptyStringSearch(emptyString);
    SubstringSearchForTest nonEmptyStringSearch(nonEmptyString);

    EXPECT_EQ(Index(string::npos), emptyStringSearch.search(emptyString));
    EXPECT_EQ(Index(string::npos), emptyStringSearch.search(nonEmptyString));
    EXPECT_EQ(Index(string::npos), nonEmptyStringSearch.search(emptyString));
    EXPECT_EQ(Index(0), nonEmptyStringSearch.search(nonEmptyString));
}

TEST(SubstringSearchUsingZAlgorithmTest, SearchWorksUsingExample1) {
    testSearchUsingExample1<SubstringSearchForTest, Index>();
}

TEST(SubstringSearchUsingZAlgorithmTest, SearchWorksUsingExample2) {
    testSearchUsingExample2<SubstringSearchForTest, Index>();
}

TEST(SubstringSearchUsingZAlgorithmTest, SearchForFirstSubstringWorksUsingExample1) {
    SubstringSearchForTest substringSearch("ATT");
    string searchSpace("HATTIVATTI");

    EXPECT_EQ(Index(1), substringSearch.searchForFirstSubstring(searchSpace));
}

TEST(SubstringSearchUsingZAlgorithmTest, SearchForAllSubstringsWorksUsingExample1) {
    SubstringSearchForTest substringSearch("ATT");
    string searchSpace("HATTIVATTI");

    EXPECT_EQ((Indexes{1, 6}), substringSearch.searchForAllSubstrings(searchSpace));
}

}  // namespace algorithm
}  // namespace alba