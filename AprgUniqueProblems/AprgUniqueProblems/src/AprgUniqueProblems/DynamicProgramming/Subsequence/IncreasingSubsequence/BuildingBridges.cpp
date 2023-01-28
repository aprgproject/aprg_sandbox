#include "BuildingBridges.hpp"

#include <AprgUniqueProblems/DynamicProgramming/Subsequence/IncreasingSubsequence/LongestIncreasingSubsequenceWithLinearithmicTime.hpp>

#include <algorithm>
#include <numeric>
using namespace std;

namespace alba{

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
        IndexToValue lengthToEndValue(secondPoints.size(), 0); // dynamic programming
        IndexToIndex lengthToEndIndex(secondPoints.size(), 0);
        IndexToIndex indexToPreviousIndex(secondPoints.size());
        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);
        lengthToEndValue[0] = secondPoints.front();
        for (Index i=1; i<secondPoints.size(); i++)
        {
            Value const& value(secondPoints.at(i));
            auto beginIt = lengthToEndValue.begin(), endIt = lengthToEndValue.begin() + longestLength;
            auto lowerBoundItForEndValue = lower_bound(beginIt, endIt, value);

            if(lowerBoundItForEndValue == endIt) // if current value is the highest
            {
                indexToPreviousIndex[i] = lengthToEndIndex.at(longestLength-1);
                lengthToEndIndex[longestLength] = i;
                lengthToEndValue[longestLength++] = value; // extend
            }
            else
            {
                Index currentLength = distance(lengthToEndValue.begin(), lowerBoundItForEndValue);
                if(currentLength > 0)
                {
                    indexToPreviousIndex[i] = lengthToEndIndex[currentLength-1];
                }
                lengthToEndIndex[currentLength] = i;
                *lowerBoundItForEndValue = value; // replace
            }
        }

        // construct longest sequence
        Index traverseIndex=lengthToEndIndex.at(longestLength-1);
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
