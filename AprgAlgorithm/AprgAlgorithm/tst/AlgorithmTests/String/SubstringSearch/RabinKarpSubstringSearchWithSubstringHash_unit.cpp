#include <Algorithm/String/SubstringSearch/RabinKarpSubstringSearchWithSubstringHash.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Index = int;
using HashValue = uint64_t;
using SubstringSearchForTest = RabinKarpSubstringSearchWithSubstringHash<Index, HashValue>;
}  // namespace
TEST(RabinKarpSubstringSearchWithSubstringHashTest, SearchWorksUsingEmptyStringsAndDoesNotCrash) {
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

TEST(RabinKarpSubstringSearchWithSubstringHashTest, SearchWorksUsingExample1) {
    testSearchUsingExample1<SubstringSearchForTest, Index>();
}

}  // namespace algorithm

}  // namespace alba
