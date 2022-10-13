#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Values, typename Values::value_type MAX_VALUE>
class RangeQueryForNumberOfDistinctValues
{
public:

    // As an example, consider a problem where we are given a set of queries, each of them corresponding to a range in an array,
    // and our task is to calculate for each query the number of distinct elements in the range.
    // In Mo’s algorithm, the queries are always sorted in the same way, but it depends on the problem how the answer to the query is maintained.
    // In this problem, we can maintain an array count where count[x] indicates the number of times an element x occurs in the active range.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using Range = std::pair<Index, Index>;
    using Ranges = std::vector<Range>;
    using InputAndOutputPair = std::pair<Range, Value>;
    using InputAndOutputPairs = std::vector<InputAndOutputPair>;
    using FrequencyArray = std::array<Index, MAX_VALUE>;

    RangeQueryForNumberOfDistinctValues(
            Values const& valuesToCheck)
        : m_values(valuesToCheck)
    {}

    Index getCountOfDistinctValuesOnInterval(
            Index const start,
            Index const end) const
    {
        Index numberOfDistinct(0);
        Range targetRange{start, end};
        if(isValidRange(targetRange))
        {
            FrequencyArray frequencyArray{};
            Range initialRange{start, start};
            addValueWithIndex(numberOfDistinct, frequencyArray, start);
            moveToTargetRange(numberOfDistinct, frequencyArray, initialRange, targetRange);
        }
        return numberOfDistinct;
    }

    InputAndOutputPairs getInputAndOutputPairsUsingMoAlgorithm(
            Ranges const& inputRanges) const
    {
        InputAndOutputPairs result;
        Ranges validRanges(getValidRangesAndSortForMoAlgorithm(inputRanges));
        if(!validRanges.empty())
        {
            Index numberOfDistinct(0);
            FrequencyArray frequencyArray{};
            Index start = validRanges.front().first;
            Range previousRange{start, start};
            addValueWithIndex(numberOfDistinct, frequencyArray, start);
            for(Range const currentRange : validRanges)
            {
                moveToTargetRange(numberOfDistinct, frequencyArray, previousRange, currentRange);
                result.emplace_back(currentRange, numberOfDistinct);
                previousRange = currentRange;
            }
        }
        return result;
    }

private:

    bool isValidRange(Range const& range) const
    {
        return range.first < m_values.size() && range.second < m_values.size();
    }

    Index getSquareRootSize(Index const numberOfValues) const
    {
        return static_cast<Index>(sqrt(numberOfValues));
    }

    void moveToTargetRange(
            Index & numberOfDistinct,
            FrequencyArray & frequencyArray,
            Range & currentRange,
            Range const& targetRange) const
    {
        // After each step, the array count needs to be updated.
        // After adding an elementx, we increase the value of count[x] by 1, and if count[x] Æ 1 after this,
        // we also increase the answer to the query by 1.
        // Similarly, after removing an element x, we decrease the value of count[x] by 1, and if count[x] Æ 0 after this,
        // we also decrease the answer to the query by 1.
        // In this problem, the time needed to perform each step is O(1), so the total time complexity of the algorithm is O(sqrt(n)).

        while(currentRange.first < targetRange.first)
        {
            removeValueWithIndex(numberOfDistinct, frequencyArray,currentRange.first);
            currentRange.first++;
        }
        while(currentRange.first > targetRange.first)
        {
            currentRange.first--;
            addValueWithIndex(numberOfDistinct, frequencyArray, currentRange.first);
        }
        while(currentRange.second < targetRange.second)
        {
            currentRange.second++;
            addValueWithIndex(numberOfDistinct, frequencyArray, currentRange.second);
        }
        while(currentRange.second > targetRange.second)
        {
            removeValueWithIndex(numberOfDistinct, frequencyArray, currentRange.second);
            currentRange.second--;
        }
    }

    void addValueWithIndex(
            Index & numberOfDistinct,
            FrequencyArray & frequencyArray,
            Index const index) const
    {
        Index & frequency(frequencyArray[m_values.at(index)]);
        frequency++;
        if(frequency == 1){numberOfDistinct++;}
    }

    void removeValueWithIndex(
            Index & numberOfDistinct,
            FrequencyArray & frequencyArray,
            Index const index) const
    {
        Index & frequency(frequencyArray[m_values.at(index)]);
        frequency--;
        if(frequency == 0){numberOfDistinct--;}
    }

    Ranges getValidRangesAndSortForMoAlgorithm(Ranges const& ranges) const
    {
        Ranges result;
        result.reserve(ranges.size());
        for(Range const& range : ranges)
        {
            if(isValidRange(range)) // index must be inside the give values
            {
                result.emplace_back(range);
            }
        }

        // The trick in Mo’s algorithm is the order in which the queries are processed:
        // The array is divided into blocks of k = O(sqrt(n)) elements,
        // and a query [a1,b1] is processed before a query [a2,b2] if either:
        // -> a1/k < a2/k or
        // -> a1/k = a2/k and b1 < b2.

        Index blockSize = getSquareRootSize(m_values.size());
        std::sort(result.begin(), result.end(),
                  [blockSize](Range const& range1, Range const& range2)
        {
            Index blockIndex1 = range1.first/blockSize;
            Index blockIndex2 = range2.first/blockSize;
            if(blockIndex1 == blockIndex2)
            {
                return range1.second < range2.second;
            }
            else
            {
                return blockIndex1 < blockIndex2;
            }
        });
        return result;
    }

    Values const& m_values;
};

}

}
