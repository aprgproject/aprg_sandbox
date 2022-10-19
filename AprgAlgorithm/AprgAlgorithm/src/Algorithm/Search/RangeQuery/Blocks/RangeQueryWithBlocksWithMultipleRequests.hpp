#pragma once

#include <Algorithm/Search/RangeQuery/Blocks/RangeQueryWithBlocks.hpp>

#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Values, typename BlockValues>
class RangeQueryWithBlocksWithMultipleRequests : RangeQueryWithBlocks<Values, BlockValues>
{
public:

    // Mo’s algorithm can be used in many problems that require processing range queries in a static array,
    // i.e., the array values do not change between the queries.
    // In each query, we are given a range [a,b], and we should calculate a value based on the array elements between positions a and b.
    // Since the array is static, the queries can be processed in any order,
    // and Mo’s algorithm processes the queries in a special order which guarantees that the algorithm works efficiently.

    using BaseClass = RangeQueryWithBlocks<Values, BlockValues>;
    using Index = typename BaseClass::Index;
    using Output = typename BaseClass::Output;
    using Value = typename BaseClass::Value;
    using BlockValue = typename BaseClass::BlockValue;
    using Range = std::pair<Index, Index>;
    using Ranges = std::vector<Range>;
    using InputAndOutputPair = std::pair<Range, Output>;
    using InputAndOutputPairs = std::vector<InputAndOutputPair>;
    using ValuesFunction = typename BaseClass::ValuesFunction;
    using BlockValuesFunction = typename BaseClass::BlockValuesFunction;
    using TwoBlocksFunction = std::function<BlockValue(BlockValue const&, BlockValue const&)>;

    RangeQueryWithBlocksWithMultipleRequests(
            Values const& valuesToCheck,
            ValuesFunction const& valuesFunction,
            BlockValuesFunction const& blockValuesFunction,
            TwoBlocksFunction const& accumulateFunction,
            TwoBlocksFunction const& inverseAccumulateFunction)
        : BaseClass(valuesToCheck, getSquareRootSize(valuesToCheck.size()), valuesFunction, blockValuesFunction)
        , b_values(BaseClass::m_values)
        , m_accumulateFunction(accumulateFunction)
        , m_inverseAccumulateFunction(inverseAccumulateFunction)
    {}

    InputAndOutputPairs getInputAndOutputPairsUsingMoAlgorithm(
            Ranges const& inputRanges) const
    {
        // Mo’s algorithm maintains an active range of the array, and the answer to a query concerning the active range is known at each moment.
        // The algorithm processes the queries one by one, and always moves the endpoints of the active range by inserting and removing elements.
        // The time complexity of the algorithm is O(n*sqrt(n)*f(n)) where the array contains n elements,
        // there are n queries and each insertion and removal of an element takes O(f(n)) time.

        // Thus, all queries whose left endpoints are in a certain block are processed one after another sorted according to their right endpoints.
        // Using this order, the algorithm only performs O(sqrt(n)) operations,
        // because the left endpoint moves O(n) times O(sqrt(n)) steps, and the right endpoint moves O(sqrt(n)) times O(n) steps.
        // Thus, both endpoints move a total of O(n*sqrt(n))) steps during the algorithm.

        InputAndOutputPairs result;
        Ranges validRanges(getValidRangesAndSortForMoAlgorithm(inputRanges));
        if(!validRanges.empty())
        {
            Range previousRange = validRanges.front();
            Output savedOutput = this->getResultOnInterval(previousRange.first, previousRange.second);
            result.emplace_back(previousRange, savedOutput);
            for(auto it=validRanges.cbegin()+1; it!=validRanges.cend(); it++)
            {
                Range const& currentRange(*it);
                if(previousRange.first < currentRange.first)
                {
                    savedOutput = m_inverseAccumulateFunction(savedOutput, this->getResultOnInterval(previousRange.first, currentRange.first-1)); // remove elements
                }
                else if(currentRange.first < previousRange.first)
                {
                    savedOutput = m_accumulateFunction(savedOutput, this->getResultOnInterval(currentRange.first, previousRange.first-1)); // add elements
                }
                if(previousRange.second < currentRange.second)
                {
                    savedOutput = m_accumulateFunction(savedOutput, this->getResultOnInterval(previousRange.second+1, currentRange.second)); // add elements
                }
                else if(currentRange.second < previousRange.second)
                {
                    savedOutput = m_inverseAccumulateFunction(savedOutput, this->getResultOnInterval(currentRange.second+1, previousRange.second)); // remove elements
                }
                result.emplace_back(currentRange, savedOutput);
                previousRange = currentRange;
            }
        }
        return result;
    }

private:

    Index getSquareRootSize(Index const numberOfValues) const
    {
        return static_cast<Index>(sqrt(numberOfValues));
    }

    Ranges getValidRangesAndSortForMoAlgorithm(Ranges const& ranges) const
    {
        Ranges result;
        result.reserve(ranges.size());
        for(Range const& range : ranges)
        {
            if(range.first < b_values.size() && range.second < b_values.size()) // index must be inside the give values
            {
                result.emplace_back(range);
            }
        }

        // The trick in Mo’s algorithm is the order in which the queries are processed:
        // The array is divided into blocks of k = O(sqrt(n)) elements,
        // and a query [a1,b1] is processed before a query [a2,b2] if either:
        // -> a1/k < a2/k or
        // -> a1/k = a2/k and b1 < b2.

        Index blockSize = this->getBlockSize();
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

    Values const& b_values;
    TwoBlocksFunction m_accumulateFunction;
    TwoBlocksFunction m_inverseAccumulateFunction;
};

}

}
