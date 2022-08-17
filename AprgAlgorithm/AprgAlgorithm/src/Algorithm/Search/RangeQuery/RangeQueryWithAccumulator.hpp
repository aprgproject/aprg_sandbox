#pragma once

#include <functional>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Value>
class RangeQueryWithAccumulator
{
public:
    // Example for "range query accumulator" is sum queries
    // We can easily process sum queries on a static array by constructing a prefix sum array.
    // Each value in the prefix sum array equals the sum of values in the original array up to that position, i.e., the value at position k is sumq(0,k).
    // The prefix sum array can be constructed in O(n) time.

    using Index = unsigned int;
    using Values = std::vector<Value>;
    using AccumulatorFunction = std::function<Value(Value const&, Value const&)>;

    RangeQueryWithAccumulator(
            Values const& valuesToCheck,
            AccumulatorFunction const& accumulator,
            AccumulatorFunction const& inverseAccumulator)
        : m_partialResults()
        , m_accumulator(accumulator)
        , m_inverseAccumulator(inverseAccumulator)
    {
        initialize(valuesToCheck);
    }

    Value getAccumulatedValueOnInterval(Index const start, Index const end) const
    {
        // This is now constant time
        Value result{};
        if(start<=end && start<m_partialResults.size() && end<m_partialResults.size())
        {
            if(start>0)
            {
                result = m_inverseAccumulator(m_partialResults.at(end), m_partialResults.at(start-1));
            }
            else
            {
                result = m_partialResults.at(end);
            }
        }
        return result;
    }

private:

    void initialize(Values const& valuesToCheck)
    {
        m_partialResults.reserve(valuesToCheck.size());

        Value partialResult{};
        if(!valuesToCheck.empty())
        {
            partialResult = valuesToCheck.front();
            m_partialResults.emplace_back(partialResult);
            for(unsigned int i=1; i<valuesToCheck.size(); i++)
            {
                partialResult = m_accumulator(partialResult, valuesToCheck.at(i));
                m_partialResults.emplace_back(partialResult);
            }
        }
        m_partialResults.shrink_to_fit();
    }

    Values m_partialResults;
    AccumulatorFunction m_accumulator;
    AccumulatorFunction m_inverseAccumulator;
};

}

}
