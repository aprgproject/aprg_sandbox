#include <Algorithm/String/SubstringSearch/SuffixTrieSubStringSearch.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Index = int;
using SubstringSearchForTest = SuffixTrieSubStringSearch<Index>;
}  // namespace

TEST(SuffixTrieSubStringSearchTest, SearchWorksUsingEmptyStringsAndDoesNotCrash) {
    testSearchUsingEmptyStringsAndDoesNotCrash<SubstringSearchForTest, Index>();
}

TEST(SuffixTrieSubStringSearchTest, SearchWorksUsingExample1) {
    testSearchUsingExample1<SubstringSearchForTest, Index>();
}

TEST(SuffixTrieSubStringSearchTest, SearchWorksUsingExample2) {
    testSearchUsingExample2<SubstringSearchForTest, Index>();
}

}  // namespace algorithm

}  // namespace alba
