#include "BurnsideLemma.hpp"

#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

UnsignedInteger getNumberOfSymmetricCombinationsUsingBurnsideLemma(
        UnsignedInteger const numberOfWaysToChangePosition,
        UnsignedIntegerBinaryFunction const& getNumberOfCombinationsFunction)
{
    // Burnside’s lemma can be used to count the number of combinations so that
    // only one representative is counted for each group of symmetric combinations.

    // Burnside’s lemma states that the number of combinations is summation of c(k)/n and k is from 1 to n,
    // where there are n ways to change the position of a combination, and there are c(k) combinations that remain unchanged when the kth way is applied.

    UnsignedInteger result(0);
    if(numberOfWaysToChangePosition > 0)
    {
        for(UnsignedInteger kthWay=1; kthWay<=numberOfWaysToChangePosition; kthWay++)
        {
            result += getNumberOfCombinationsFunction(numberOfWaysToChangePosition, kthWay);
        }
        result /= numberOfWaysToChangePosition;
    }
    return result;
}

UnsignedInteger getNumberOfCombinationsOfAPearlNecklace(
        UnsignedInteger const numberOfPearls,
        UnsignedInteger const& numberOfColors)
{
    // As an example, let us calculate the number of necklaces of "n" pearls, where each pearl has "m" possible colors.
    // Two necklaces are symmetric if they are similar after rotating them.

    // For example, the necklace: [Green Red Blue Red]
    // has the following symmetric necklaces:
    // 1) [Green Red Blue Red]
    // 2) [Red Green Red Blue]
    // 3) [Blue Red Green Red]
    // 4) [Red Blue Red Green]

    // There are n ways to change the position of a necklace, because we can rotate it 0,1,...,n-1 steps clockwise.
    // If the number of steps is 0, all m^n necklaces remain the same.
    // If the number of steps is 1, only the m necklaces where each pearl has the same color remain the same.
    // More generally, when the number of steps is k, a total of m ^ gcf(k, n) necklaces remain the same.

    // For example, we RGB pearls and rotate 3 steps
    // -> If step is 0, possibilities are 3^(gcf(0,3)) = 27.
    // ---> RRR, RRG, RRB, RGR, RGG, RGB, RBR, RBG, RBB
    // ---> GRR, GRG, GRB, GGR, GGG, GGB, GBR, GBG, GBB
    // ---> BRR, BRG, BRB, BGR, BGG, BGB, BBR, BBG, BBB
    // -> If step is 1, possibilities are 3^(gcf(1,3)) = 3.
    // ---> RRR, GGG, BBB
    // -> If step is 2, possibilities are 3^(gcf(2,3)) = 3.
    // ---> RRR, GGG, BBB

    return getNumberOfSymmetricCombinationsUsingBurnsideLemma(
                numberOfPearls, [&](UnsignedInteger const nWays, UnsignedInteger const kthWay)
    {
        return getRaiseToPowerForIntegers(numberOfColors, getGreatestCommonFactor(kthWay-1, nWays));
    });
}

}

}
