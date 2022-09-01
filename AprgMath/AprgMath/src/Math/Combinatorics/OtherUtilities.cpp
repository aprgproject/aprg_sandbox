#include "OtherUtilities.hpp"

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

bool isNumberOfCombinationsEqualToItsCounterpart(UnsignedInteger const n, UnsignedInteger const k)
{
    // (n, k) = (n, n-k)
    // This is true because we actually divide a set of n elements into two subsets:
    // the first contains k elements and the second contains n-k elements.

    // A boxes and balls visual example of [4 taken 1] is equal to [4 taken 3]: (4, 1) = (4, 3)
    // (4, 1) [balls are starting from the right for visual aid]
    // |o| | | |    Positions: {1}
    // | |o| | |    Positions: {2}
    // | | |o| |    Positions: {3}
    // | | | |o|    Positions: {4}

    // (4, 3) [balls are starting from the left for visual aid]
    // | |o|o|o|    Positions: {2, 3, 4}, its missing 1
    // |o| |o|o|    Positions: {1, 3, 4}, its missing 2
    // |o|o| |o|    Positions: {1, 2, 4}, its missing 3
    // |o|o|o| |    Positions: {1, 2, 3}, its missing 4

    // By just switching the balls to empty boxes and vice versa, we can see that the number its equal

    bool result(false); // false if input is wrong
    if(n>k)
    {
        result = getNumberOfCombinations(n, k) == getNumberOfCombinations(n, n-k);
    }
    return result;
}

bool isTheSumOfAllNumberOfCombinationsEqualTo2ToTheN(UnsignedInteger const n)
{
    // Sum of all (n, k) from k=0 to k=n is equal to 2^n
    UnsignedInteger sumOfNumberOfCombinations(0);
    for(UnsignedInteger k=0; k<=n; k++)
    {
        sumOfNumberOfCombinations += getNumberOfCombinations(n, k);
    }

    return sumOfNumberOfCombinations == AlbaBitValueUtilities<UnsignedInteger>::get2ToThePowerOf(n);
}

}

}
