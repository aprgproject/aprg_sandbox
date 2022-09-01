#include "CombinatoricsHelpers.hpp"

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

using namespace std;

namespace alba
{

namespace mathHelper
{

int getStirlingNumberOfTheSecondKind(unsigned int const n, unsigned int const k)
{
    // In mathematics, particularly in combinatorics, a Stirling number of the second kind (or Stirling partition number)
    // is the number of ways to partition a set of n objects into k non-empty subsets

    // Stirling numbers of the second kind occur in the field of mathematics called combinatorics and the study of partitions.

    AlbaNumber sum(0);
    for(unsigned int i=0; i<=k; i++)
    {
        int sign = isDivisible(i, 2U) ? 1 : -1;
        sum += AlbaNumber(sign) * getNumberOfCombinations(k, i) * pow(k-i, n);
    }
    sum /= getFactorial(k);
    return static_cast<int>(sum.getInteger());
}

}//namespace mathHelper

}//namespace alba
