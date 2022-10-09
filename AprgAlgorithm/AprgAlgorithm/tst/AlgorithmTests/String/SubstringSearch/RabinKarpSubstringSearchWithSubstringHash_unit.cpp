#include <Algorithm/String/SubstringSearch/RabinKarpSubstringSearchWithSubstringHash.hpp>
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
using SubstringSearchToTest = RabinKarpSubstringSearchWithSubstringHash<unsigned int, unsigned long long>;
}

TEST(RabinKarpSubstringSearchWithSubstringHashTest, SearchWorksUsingExample1)
{
    testSearchUsingExample1<SubstringSearchToTest, Index>();
}
}

}
