#include <Algorithm/String/SubstringSearch/KnuthMorrisPrattSubstringSearch.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Index = int;
using SubstringSearchForTest = KnuthMorrisPrattSubstringSearch<Index>;
}  // namespace

TEST(KnuthMorrisPrattSubstringSearchTest, SearchWorksUsingEmptyStringsAndDoesNotCrash) {
    testSearchUsingEmptyStringsAndDoesNotCrash<SubstringSearchForTest, Index>();
}

TEST(KnuthMorrisPrattSubstringSearchTest, SearchWorksUsingExample1) {
    testSearchUsingExample1<SubstringSearchForTest, Index>();
}

TEST(KnuthMorrisPrattSubstringSearchTest, SearchWorksUsingExample2) {
    testSearchUsingExample2<SubstringSearchForTest, Index>();
}

}  // namespace algorithm

}  // namespace alba
