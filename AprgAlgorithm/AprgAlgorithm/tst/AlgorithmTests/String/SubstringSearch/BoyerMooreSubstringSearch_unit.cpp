#include <Algorithm/String/SubstringSearch/BoyerMooreSubstringSearch.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Index = int;
using SubstringSearchForTest = BoyerMooreSubstringSearch<Index>;
}  // namespace

TEST(BoyerMooreSubstringSearchTest, SearchWorksUsingEmptyStringsAndDoesNotCrash) {
    testSearchUsingEmptyStringsAndDoesNotCrash<SubstringSearchForTest, Index>();
}

TEST(BoyerMooreSubstringSearchTest, SearchWorksUsingExample1) {
    testSearchUsingExample1<SubstringSearchForTest, Index>();
}

TEST(BoyerMooreSubstringSearchTest, SearchWorksUsingExample2) {
    testSearchUsingExample2<SubstringSearchForTest, Index>();
}

}  // namespace algorithm

}  // namespace alba