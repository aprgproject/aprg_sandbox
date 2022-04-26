#include <Algorithm/String/SubstringSearch/RabinKarpSubstringSearch.hpp>
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
using SubstringSearchToTest = RabinKarpSubstringSearch<unsigned int, unsigned long long>;
}

TEST(RabinKarpSubstringSearchTest, SearchWorksUsingExample1)
{
    testSearchUsingExample1<SubstringSearchToTest, Index>();
}

}

}
