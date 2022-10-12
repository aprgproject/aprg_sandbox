#pragma once

#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

#include <algorithm>
#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Values>
class RangeQueryWithBlocks
{
public:
    // This is "range query selector" and "range query accumulator" type

    // Assuming there are k blocks:
    // The preprocessing of partial sum can be constructed in O(n) time.
    // The range query can be done in max(O(k), O(n/k)) time.
    // The updating of a value can be done in O(n/k) time.

    // Note that having sqrt(n) of blocks is special:
    // The idea is to divide the array into blocks of size sqrt(n) so that each block contains the sum of elements inside the block.
    // Since the number of single elements is O(sqrt(n)) and the number of blocks is also O(sqrt(n)), the sum query takes O(sqrt(n)) time.
    // The purpose of the block size sqrt(n) is that it balances two things:
    // -> the array is divided into sqrt(n) blocks, each of which contains sqrt(n) elements.
    // So all operations take O(sqrt(n)) time.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using Function = std::function<Value(Value const&, Value const&)>;

    RangeQueryWithBlocks(
            Index const suggestedNumberOfBlocks,
            Values const& valuesToCheck,
            Function const& functionObject)
        : m_blockSize(0U)
        , m_values(valuesToCheck)
        , m_blocks()
        , m_function(functionObject)
    {
        initialize(valuesToCheck, suggestedNumberOfBlocks);
    }

    Value getValueOnInterval(Index const start, Index const end) const
    {
        // This is max(O(k), O(n/k)) time.
        Value result{};
        if(start<m_values.size() && end<m_values.size() && start<=end)
        {
            Index startOfBlocks = mathHelper::getMultipleThatIsGreaterOrEqual(m_blockSize, start);
            Index endOfBlocks = mathHelper::getMultipleThatIsLesserOrEqual(m_blockSize, end);
            if(startOfBlocks+m_blockSize <= endOfBlocks)
            {
                Index blockStart = startOfBlocks/m_blockSize;
                Index blockEnd = endOfBlocks/m_blockSize;

                Values resultParts;
                if(start<startOfBlocks)
                {
                    resultParts.emplace_back(std::accumulate(m_values.cbegin()+start+1, m_values.cbegin()+startOfBlocks, m_values.at(start), m_function));
                }
                if(blockStart<blockEnd)
                {
                    resultParts.emplace_back(std::accumulate(m_blocks.cbegin()+blockStart+1, m_blocks.cbegin()+blockEnd, m_blocks.at(blockStart), m_function));
                }
                if(endOfBlocks<=end)
                {
                    resultParts.emplace_back(std::accumulate(m_values.cbegin()+endOfBlocks+1, m_values.cbegin()+end+1, m_values.at(endOfBlocks), m_function));
                }

                if(!resultParts.empty())
                {
                    result = std::accumulate(resultParts.cbegin()+1, resultParts.cend(), resultParts.front(), m_function);
                }
            }
            else
            {
                result = std::accumulate(m_values.cbegin()+start+1, m_values.cbegin()+end+1, m_values.at(start), m_function);
            }
        }
        return result;
    }

    void changeValueAtIndex(Index const index, Value const newValue)
    {
        // This has O(n/k) time.
        if(index < m_values.size())
        {
            m_values[index] = newValue;

            Index start = mathHelper::getMultipleThatIsLesserOrEqual(m_blockSize, index);
            Index end = std::min(start+m_blockSize, m_values.size());
            Value newPartialResult = m_values.at(start);
            for(Index i=start+1; i<end; i++)
            {
                newPartialResult = m_function(newPartialResult, m_values.at(i));
            }
            m_blocks[start/m_blockSize] = newPartialResult;
        }
    }

private:

    void initialize(Values const& valuesToCheck, Index const suggestedNumberOfBlocks)
    {
        if(!valuesToCheck.empty())
        {
            m_blockSize = std::max(valuesToCheck.size()/suggestedNumberOfBlocks, 1U);
            Index numberOfBlocks = mathHelper::getMultipleThatIsGreaterOrEqual(valuesToCheck.size(), m_blockSize);
            m_blocks.reserve(numberOfBlocks);
            for(Index start=0; start<m_values.size(); start+=m_blockSize)
            {
                Index end = std::min(start+m_blockSize, m_values.size());
                m_blocks.emplace_back(std::accumulate(m_values.cbegin()+start+1, m_values.cbegin()+end, m_values.at(start), m_function));
            }
        }
    }

    Index m_blockSize;
    Values m_values;
    Values m_blocks;
    Function m_function;
};

}

}
