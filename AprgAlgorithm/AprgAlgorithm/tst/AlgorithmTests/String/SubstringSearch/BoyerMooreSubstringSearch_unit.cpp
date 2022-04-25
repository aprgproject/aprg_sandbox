#include <Algorithm/String/SubstringSearch/BoyerMooreSubstringSearch.hpp>
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
using SubstringSearchToTest = BoyerMooreSubstringSearch<unsigned int>;
}

TEST(BoyerMooreSubstringSearchTest, SearchWorksUsingExample1)
{
    testSearchUsingExample1<SubstringSearchToTest, Index>();
}

}

}
