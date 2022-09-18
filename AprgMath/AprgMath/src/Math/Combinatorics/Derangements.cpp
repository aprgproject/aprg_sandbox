#include "Derangements.hpp"

#include <Common/Math/AlbaMathConstants.hpp>
#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

UnsignedInteger getNumberOfDerangements(UnsignedInteger const n)
{
    // As an example, let us count the number of derangements of elements {1,2,...,n},
    // i.e., permutations where no element remains in its original place.
    // For example, when n=3, there are two derangements: (2,3,1) and (3,1,2).
    // Note that symbol for getting number of derangements is !n (exaclamation point before the number)

    // One approach for solving the problem is to use inclusion-exclusion.
    // Let Xk be the set of permutations that fixed element k at position k.
    // For example, when n=3, the sets are as follows:
    // X1 = {(1,2,3),(1,3,2)}
    // X2 = {(1,2,3),(3,2,1)}
    // X3 = {(1,2,3),(2,1,3)}
    // Using these sets, the number of derangements equals number of permutations - size of union of X1 to Xn
    // So its number of derangements = !n = n! - |union of X1 and X2 ... Xn|
    // Using inclusion-exclusion, this reduces to calculating sizes of intersections which can be done efficiently.
    // For example, when n=3, the size of is |union of X1 and X2 and X3|.
    // |union of X1 and X2 and X3| = |X1| + |X2| + |X3| - |intersection of X1 and X2| - |intersection of X1 and X3| - |intersection of X2 and X3| - |intersection of X1 and X2 and X3|
    // number of derangements = !n = n! - |union of X1 and X2 and X3| = 6-4 =2

    // It turns out that the problem can also be solved without using inclusion exclusion.
    // Another approach let f (n) denote the number of derangements for {1,2,...,n}.
    // We can use the following recursive formula:
    // The value of f(n) =
    // -> If n==1, the f(n) = 0
    // -> Else if n==2, the f(n) = 1
    // -> Else, the f(n) = (n-1)*(f(n-2)+f(n-1))
    // Note: This is useful on dynamic programming.

    // The formula can be derived by considering the possibilities how the element 1 changes in the derangement.
    // There are n-1 ways to choose an element x that replaces the element 1.
    // In each such choice, there are two options:
    // -> Option 1: We also replace the element x with the element 1.
    // ---> After this, the remaining task is to construct a derangement of n-2 elements.
    // -> Option 2: We replace the element x with some other element than 1.
    // ---> Now we have to construct a derangement of n-1 element,
    // ---> because we cannot replace the element x with the element 1, and all other elements must be changed.

    // Example if n==4:
    // Permutations with n=4:
    // (1,2,3,4)
    // (1,2,4,3)
    // (1,3,2,4)
    // (1,3,4,2)
    // (1,4,2,3)
    // (1,4,3,2)
    // (2,1,3,4)
    // (2,1,4,3)
    // (2,3,1,4)
    // (2,3,4,1)
    // (2,4,1,3)
    // (2,4,3,1)
    // (3,1,2,4)
    // (3,1,4,2)
    // (3,2,1,4)
    // (3,2,4,1)
    // (3,4,1,2)
    // (3,4,2,1)
    // (4,1,2,3)
    // (4,1,3,2)
    // (4,2,1,3)
    // (4,2,3,1)
    // (4,3,1,2)
    // (4,3,2,1)
    // Let Xk be the set of permutations that contain the element k at position k.
    // X1 = {(1,2,3,4), (1,2,4,3), (1,3,2,4), (1,3,4,2), (1,4,2,3), (1,4,3,2)}
    // X2 = {(1,2,3,4), (1,2,4,3), (3,2,1,4), (3,2,4,1), (4,2,1,3), (4,2,3,1)}
    // X3 = {(1,2,3,4), (1,4,3,2), (2,1,3,4), (2,4,3,1), (4,1,3,2), (4,2,3,1)}
    // X4 = {(1,2,3,4), (1,3,2,4), (2,1,3,4), (2,3,1,4), (3,1,2,4), (3,2,1,4)}
    // union of X1 and X2 and X3:
    // {(1,2,3,4), (1,2,4,3), (1,3,2,4), (1,3,4,2), (1,4,2,3), (1,4,3,2), (3,2,1,4), (3,2,4,1),
    // (4,2,1,3), (4,2,3,1), (2,1,3,4), (2,4,3,1), (4,1,3,2), (2,3,1,4), (3,1,2,4)}

    // Derangement with n=4:
    // (2,1,4,3)
    // (2,3,4,1)
    // (2,4,1,3)
    // (3,1,4,2)
    // (3,4,1,2)
    // (3,4,2,1)
    // (4,1,2,3)
    // (4,3,1,2)
    // (4,3,2,1)

    // Notes:
    // -> Recursive formula is f(n) = (n-1)*(f(n-2)+f(n-1))
    // ---> f(4) = 3*(2+1) = 9 (matches with the count)
    // -> At first position, the values is {2,3,4} so its n-1.
    // ---> When there is a 2 in the first position:
    // -------> Option 1: We also replace the element 2 with the element 1 (element 1 is at position 1).
    // ---------> After this, the remaining task is to construct a derangement of n-2 elements.
    // ---------> This is {(2,1,4,3)}
    // -------> Option 2: We replace the element 2 with some other element than 1.
    // ---------> Now we have to construct a derangement of n-1 element,
    // ---------> because we cannot replace the element x with the element 1, and all other elements must be changed.
    // ---------> This is {(2,4,1,3), (2,3,4,1)}

    UnsignedInteger result{};
    if(n<=1)
    {
        result = 0;
    }
    else if(n==2)
    {
        result = 1;
    }
    else
    {
        UnsignedInteger previousOfPrevious=0;
        UnsignedInteger previous=1;
        result=1;
        for(UnsignedInteger i=3; i<=n; i++)
        {
            result = (i-1) * (previous + previousOfPrevious);
            previousOfPrevious = previous;
            previous = result;
        }
    }
    return result;
}

UnsignedInteger getNumberOfDerangementsApproximation(UnsignedInteger const n)
{
    // Derivation:
    // From the original formula above:
    // !n = n! - |union of X1 and X2 ... Xn|

    // For example, when n=3, the size of is |union of X1 and X2 and X3|.
    // |union of X1 and X2 and X3| = |X1| + |X2| + |X3| - |intersection of X1 and X2| - |intersection of X1 and X3| - |intersection of X2 and X3| - |intersection of X1 and X2 and X3|

    // This expands to:
    // !n = n! - n!/1! + n!/2! - n!/3! + n!/4! ... n!/n!
    // !n = n! * (1 - 1/1! + 1/2! - 1/3! + 1/4! ... 1/n!)
    // !n = n! * (1/e)
    // !n = n!/e

    return getIntegerAfterRoundingADoubleValue<UnsignedInteger>(getNumberOfPermutations(n, n) / E_DOUBLE_VALUE);
}

double getDerangementsProbability(UnsignedInteger const n)
{
    return static_cast<double>(getNumberOfDerangements(n)) / getNumberOfPermutations(n, n);
}

}

}
