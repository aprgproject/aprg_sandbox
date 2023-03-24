#include "BuildingBridges.hpp"

#include <AprgUniqueProblems/DynamicProgramming/SupersequenceAndSubsequence/IncreasingSubsequence/LongestIncreasingSubsequenceWithLinearithmicTime.hpp>

#include <algorithm>
#include <numeric>

using namespace std;

namespace alba
{

BuildingBridges::BuildingBridges(Bridges const& bridges)
    : m_bridges(bridges)
{}

BuildingBridges::Index BuildingBridges::getNumberOfPossibleBridges() const
{
    // Time Complexity – O(NlogN)
    // Space Complexity – O(N)

    Bridges sortedBridges(m_bridges);
    sort(sortedBridges.begin(), sortedBridges.end());

    LongestIncreasingSubsequenceWithLinearithmicTime::Values secondPoints;
    secondPoints.reserve(sortedBridges.size());
    transform(sortedBridges.cbegin(), sortedBridges.cend(), back_inserter(secondPoints), [](auto const& bridge)
    {
        return bridge.second;
    });

    LongestIncreasingSubsequenceWithLinearithmicTime lis(secondPoints);
    return lis.getLongestLength();
}

BuildingBridges::Bridges BuildingBridges::getPossibleBridges() const
{
    // Time Complexity – O(NlogN)
    // Space Complexity – O(N)

    Bridges result;
    if(!m_bridges.empty())
    {
        Bridges sortedBridges(m_bridges);
        sort(sortedBridges.begin(), sortedBridges.end());

        LongestIncreasingSubsequenceWithLinearithmicTime::Values secondPoints;
        secondPoints.reserve(sortedBridges.size());
        transform(sortedBridges.cbegin(), sortedBridges.cend(), back_inserter(secondPoints), [](auto const& bridge)
        {
            return bridge.second;
        });

        Index longestLength(1);
        IndexToValue lengthMinus1ToEndValue(secondPoints.size(), 0); // length minus one because its index
        IndexToIndex lengthMinus1ToEndIndex(secondPoints.size(), 0);
        IndexToIndex indexToPreviousIndex(secondPoints.size());
        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);
        lengthMinus1ToEndValue[0] = secondPoints.front();
        for (Index i=1; i<secondPoints.size(); i++)
        {
            Value const& value(secondPoints.at(i));
            auto beginIt = lengthMinus1ToEndValue.begin(), endIt = lengthMinus1ToEndValue.begin() + longestLength;
            auto lowerBoundItForEndValue = lower_bound(beginIt, endIt, value);

            if(lowerBoundItForEndValue == endIt) // if current value is the highest
            {
                indexToPreviousIndex[i] = lengthMinus1ToEndIndex.at(longestLength-1);
                lengthMinus1ToEndIndex[longestLength] = i;
                lengthMinus1ToEndValue[longestLength++] = value; // extend
            }
            else
            {
                Index currentLength = distance(lengthMinus1ToEndValue.begin(), lowerBoundItForEndValue);
                if(currentLength > 0)
                {
                    indexToPreviousIndex[i] = lengthMinus1ToEndIndex[currentLength-1];
                }
                lengthMinus1ToEndIndex[currentLength] = i;
                *lowerBoundItForEndValue = value; // replace
            }
        }

        // construct longest sequence
        Index traverseIndex=lengthMinus1ToEndIndex.at(longestLength-1);
        for(; traverseIndex!=indexToPreviousIndex.at(traverseIndex); traverseIndex=indexToPreviousIndex.at(traverseIndex))
        {
            result.emplace_back(sortedBridges.at(traverseIndex));
        }
        result.emplace_back(sortedBridges.at(traverseIndex));
        //reverse(result.begin(), result.end()); // no need for reverse
    }
    return result;
}

}
