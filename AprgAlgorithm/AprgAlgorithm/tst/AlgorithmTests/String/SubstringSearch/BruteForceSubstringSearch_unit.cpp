#include <Algorithm/String/SubstringSearch/BruteForceSubstringSearch.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Index = int;
using BruteForceSubstringSearchWithOneLoop = BruteForceSubstringSearch<1>;
using BruteForceSubstringSearchWithTwoLoops = BruteForceSubstringSearch<2>;
}  // namespace

TEST(BruteForceSubstringSearchTest, SearchWorksWithOneLoopUsingEmptyStringsAndDoesNotCrash) {
    testSearchUsingEmptyStringsAndDoesNotCrash<BruteForceSubstringSearchWithOneLoop, Index>();
}

TEST(BruteForceSubstringSearchTest, SearchWorksWithTwoLoopsUsingEmptyStringsAndDoesNotCrash) {
    testSearchUsingEmptyStringsAndDoesNotCrash<BruteForceSubstringSearchWithTwoLoops, Index>();
}

TEST(BruteForceSubstringSearchTest, SearchWorksWithOneLoopUsingExample1) {
    testSearchUsingExample1<BruteForceSubstringSearchWithOneLoop, Index>();
}

TEST(BruteForceSubstringSearchTest, SearchWorksWithOneLoopUsingExample2) {
    testSearchUsingExample2<BruteForceSubstringSearchWithOneLoop, Index>();
}

TEST(BruteForceSubstringSearchTest, SearchWorksWithTwoLoopsUsingExample1) {
    testSearchUsingExample1<BruteForceSubstringSearchWithTwoLoops, Index>();
}

TEST(BruteForceSubstringSearchTest, SearchWorksWithTwoLoopsUsingExample2) {
    testSearchUsingExample2<BruteForceSubstringSearchWithTwoLoops, Index>();
}

}  // namespace algorithm

}  // namespace alba