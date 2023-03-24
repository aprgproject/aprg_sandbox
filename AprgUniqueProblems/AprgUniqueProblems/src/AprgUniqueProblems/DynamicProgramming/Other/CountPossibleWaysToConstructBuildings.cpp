#include "CountPossibleWaysToConstructBuildings.hpp"

#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>
#include <Math/NumberTheory/OtherUtilities.hpp>

using namespace alba::math;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

CountPossibleWaysToConstructBuildings::CountPossibleWaysToConstructBuildings(
        Count const numberOfSections)
    : m_numberOfSections(numberOfSections)
{}

CountPossibleWaysToConstructBuildings::Count CountPossibleWaysToConstructBuildings::getNumberOfWaysUsingCountOfBuildingAndSpaces() const
{
    // Time Complexity: O(numberOfSections)
    // Auxiliary Space: Constant

    // Approach:
    // We can simplify the problem to first calculate for one side only.
    // If we know the result for one side, we can always do the square of the result and get the result for two sides.

    // A new building can be placed on a section if section just before it has space.
    // A space can be placed anywhere (it doesn’t matter whether the previous section has a building or not).

    // Let countB(i) be count of possible ways with i sections
    //               ending with a building.
    //     countS(i) be count of possible ways with i sections
    //               ending with a space.

    // A space can be added after a building or after a space.
    // countS(N) = countB(N-1) + countS(N-1)

    // A building can only be added after a space.
    // countB[N] = countS(N-1)

    // Result for one side is sum of the above two counts.
    // result1(N) = countS(N) + countB(N)

    // Result for two sides is square of result1(N)
    // result2(N) = result1(N) * result1(N)

    Count resultInOnSide(0);
    if (m_numberOfSections == 0)
    {
        resultInOnSide = 1;
    }
    else if (m_numberOfSections == 1)
    {
        resultInOnSide = 2;  // 2 for one side and 4 for two sides
    }
    else
    {
        Count countOfBuildings=1, countOfSpaces=1;
        for (Count section=2; section<=m_numberOfSections; section++)
        {
            Count previousCountOfBuildings = countOfBuildings;
            Count previousCountOfSpaces = countOfSpaces;

            countOfSpaces = previousCountOfBuildings + previousCountOfSpaces;
            countOfBuildings = previousCountOfSpaces;
        }
        resultInOnSide = countOfBuildings + countOfSpaces;
    }
    return resultInOnSide*resultInOnSide;
}

CountPossibleWaysToConstructBuildings::Count CountPossibleWaysToConstructBuildings::getNumberOfWaysUsingFibonacciNumber() const
{
    // Time Complexity: O(Constant)
    // Auxiliary Space: Constant

    // Approach:
    // Let us think of buildings as the sequence of N (because there are N plots on either side) length binary string (each digit either 0 or 1) where :
    // -> 1 => Represents building has been made on the ith plot
    // -> 0 => Represents building has not been made on the ith plot

    // Now as the problem states we have to find the number of ways such that we don’t have consecutive Buildings on plots,
    // in the binary string, it can be interpreted as,
    // we need to find the number of ways such that we do not have consecutive 1 in the binary string (as 1 represented building being made)

    // Example :
    // -> N = 3
    // -> Total Combinations = 2n = 23 = 8
    // -> This will contain some combination in there will be consecutive building, so we have to reject that
    // ---> 000 (No building) (Possible)
    // ---> 001 (Building on 3rd plot) (Possible)
    // ---> 010 (Building on 2nd plot) (Possible)
    // ---> 011 (Building on 2nd and 3rd plot) (Not Possible as there are consecutive buildings)
    // ---> 100 (Building on 1st plot) (Possible)
    // ---> 101 (Building on 1st and 3rd plot) (Possible)
    // ---> 110 (Building on 1st and 2nd plot) (Not Possible as there are consecutive buildings)
    // ---> 111 (Building on 1st, 2nd, 3rd plot) (Not Possible as there are consecutive buildings)
    // -> Total Possible Ways = 5
    // -> These are only on one side, on other side it will also be same as there are N plots and same condition, so
    // -> Answer = Total Possible Ways * Total Possible Ways = 25

    // So now our problem is reduced to find the number of ways to represent N length binary string
    // such that it does not have consecutive 1 which is a pretty standard problem

    // Optimized Solution:
    // Note that the above solution can be further optimized. If we take a closer look at the results,
    // for different values, we can notice that the results for the two sides are squares of Fibonacci Numbers.
    // N = 1, result = 4 [result for one side = 2]
    // N = 2, result = 9 [result for one side = 3]
    // N = 3, result = 25 [result for one side = 5]
    // N = 4, result = 64 [result for one side = 8]
    // N = 5, result = 169 [result for one side = 13]
    // ...

    // In general, we can say that: result(N) = getFibonacciNumber(N+2)^2

    Count resultInOnSide = getNthFibonacciNumber(m_numberOfSections+2);
    return resultInOnSide*resultInOnSide;
}

CountPossibleWaysToConstructBuildings::Count CountPossibleWaysToConstructBuildings::getNumberOfWaysUsingCombinations() const
{
    // Time Complexity: O(numberOfSections)
    // Auxiliary Space: Constant

    // Approach: Using box and balls combinations (with spaces)

    Count maxNumberOfBuildings = (m_numberOfSections+1)/2;
    Count resultInOnSide(0);
    for (Count numberOfBuildings=0; numberOfBuildings<=maxNumberOfBuildings; numberOfBuildings++)
    {
        resultInOnSide += getNumberOfCombinations(m_numberOfSections-numberOfBuildings+1, numberOfBuildings);
    }
    return resultInOnSide*resultInOnSide;
}

}
