#include <Algorithm/String/SubstringSearch/RabinKarpSubstringSearchWithRunningHash.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Index = int;
using HashValue = unsigned long long;
using SubstringSearchForTest = RabinKarpSubstringSearchWithRunningHash<Index, HashValue>;
}  // namespace

TEST(RabinKarpSubstringSearchWithRunningHashTest, SearchWorksUsingEmptyStringsAndDoesNotCrash) {
    testSearchUsingEmptyStringsAndDoesNotCrash<SubstringSearchForTest, Index>();
}

TEST(RabinKarpSubstringSearchWithRunningHashTest, SearchWorksUsingExample1) {
    testSearchUsingExample1<SubstringSearchForTest, Index>();
}

}  // namespace algorithm

}  // namespace alba
