#include "OtherUtilities.hpp"

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

bool isBinomialCoefficientEqualToItsCounterpart(UnsignedInteger const n, UnsignedInteger const k)
{
    // (n, k) = (n, n-k)
    // This is true because we actually divide a set of n elements into two subsets:
    // the first contains k elements and the second contains n-k elements.
    bool result(false); // false if input is wrong
    if(n>k)
    {
        result = getValueAtPascalTriangle(n, k) == getValueAtPascalTriangle(n, n-k);
    }
    return result;
}

bool isTheSumOfBinomialCoefficientsEqualTo2ToTheN(UnsignedInteger const n)
{
    // Sum of all (n, k) from k=0 to k=n is equal to 2^n
    UnsignedInteger sumOfBinomialCoefficients(0);
    for(UnsignedInteger k=0; k<=n; k++)
    {
        sumOfBinomialCoefficients += getValueAtPascalTriangle(n, k);
    }

    return sumOfBinomialCoefficients == AlbaBitValueUtilities<UnsignedInteger>::get2ToThePowerOf(n);

}

}

}
