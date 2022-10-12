#include <Algorithm/String/SubstringSearch/BruteForceSubstringSearch.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Index = unsigned int;
using BruteForceSubstringSearchWithOneLoop = BruteForceSubstringSearch<1U>;
using BruteForceSubstringSearchWithTwoLoops = BruteForceSubstringSearch<2U>;
}

TEST(BruteForceSubstringSearchTest, SearchWorksWithOneLoopUsingEmptyStringsAndDoesNotCrash)
{
    testSearchUsingEmptyStringsAndDoesNotCrash<BruteForceSubstringSearchWithOneLoop, Index>();
}

TEST(BruteForceSubstringSearchTest, SearchWorksWithTwoLoopsUsingEmptyStringsAndDoesNotCrash)
{
    testSearchUsingEmptyStringsAndDoesNotCrash<BruteForceSubstringSearchWithTwoLoops, Index>();
}

TEST(BruteForceSubstringSearchTest, SearchWorksWithOneLoopUsingExample1)
{
    testSearchUsingExample1<BruteForceSubstringSearchWithOneLoop, Index>();
}

TEST(BruteForceSubstringSearchTest, SearchWorksWithTwoLoopsUsingExample1)
{
    testSearchUsingExample1<BruteForceSubstringSearchWithTwoLoops, Index>();
}

}

}
