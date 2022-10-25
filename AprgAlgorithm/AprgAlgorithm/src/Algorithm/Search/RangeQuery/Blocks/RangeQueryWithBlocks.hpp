#pragma once

#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

#include <algorithm>
#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Values, typename BlockValues>
class RangeQueryWithBlocks
{
public:
    // This supports "selector", "accumulator" and "count" type queries.

    // Assuming there are k blocks:
    // The preprocessing of partial sum can be constructed in O(n) time.
    // The range query can be done in max(O(k), O(n/k)) time.
    // The updating of a value can be done in O(n/k) time.

    // Note that having sqrt(n) of blocks is special.
    // The idea is to divide the array into blocks of size sqrt(n) so that each block contains the sum of elements inside the block.
    // Since the number of single elements is O(sqrt(n)) and the number of blocks is also O(sqrt(n)), the sum query takes O(sqrt(n)) time.
    // The purpose of the block size sqrt(n) is that it balances two things:
    // -> the array is divided into sqrt(n) blocks, each of which contains sqrt(n) elements.
    // So all operations take O(sqrt(n)) time.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using BlockValue = typename BlockValues::value_type;
    using Output = BlockValue;
    using ValuesFunction = std::function<BlockValue(typename Values::const_iterator, typename Values::const_iterator)>;
    using BlockValuesFunction = std::function<BlockValue(typename BlockValues::const_iterator, typename BlockValues::const_iterator)>;

    RangeQueryWithBlocks(
            Values const& valuesToCheck,
            Index const suggestedNumberOfBlocks,
            ValuesFunction const& valuesFunction,
            BlockValuesFunction const& blockValuesFunction)
        : m_values(valuesToCheck)
        , m_blockSize(0U)
        , m_blocks()
        , m_valuesFunction(valuesFunction)
        , m_blockValuesFunction(blockValuesFunction)
    {
        initialize(valuesToCheck, suggestedNumberOfBlocks);
    }

    Index getBlockSize() const
    {
        return m_blockSize;
    }

    BlockValues const& getBlocks() const
    {
        return m_blocks;
    }

    Output getResultOnInterval(Index const start, Index const end) const
    {
        // This is max(O(k), O(n/k)) time.
        Output result{};
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
                    resultParts.emplace_back(m_valuesFunction(m_values.cbegin()+start, m_values.cbegin()+startOfBlocks));
                }
                if(blockStart<blockEnd)
                {
                    resultParts.emplace_back(m_blockValuesFunction(m_blocks.cbegin()+blockStart, m_blocks.cbegin()+blockEnd));
                }
                if(endOfBlocks<=end)
                {
                    resultParts.emplace_back(m_valuesFunction(m_values.cbegin()+endOfBlocks, m_values.cbegin()+end+1));
                }

                if(!resultParts.empty())
                {
                    result = m_blockValuesFunction(resultParts.cbegin(), resultParts.cend());
                }
            }
            else
            {
                result = m_valuesFunction(m_values.cbegin()+start, m_values.cbegin()+end+1);
            }
        }
        return result;
    }

    void changeValueAtIndex(Index const index, Value const& newValue)
    {
        // This has O(n/k) time.
        if(index < m_values.size())
        {
            m_values[index] = newValue;

            Index start = mathHelper::getMultipleThatIsLesserOrEqual(m_blockSize, index);
            Index end = std::min(start+m_blockSize, m_values.size());
            m_blocks[start/m_blockSize] = m_valuesFunction(m_values.cbegin()+start, m_values.cbegin()+end);
        }
    }

protected:

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
                m_blocks.emplace_back(m_valuesFunction(m_values.cbegin()+start, m_values.cbegin()+end));
            }
            m_blocks.shrink_to_fit();
        }
    }

    Values m_values;
    Index m_blockSize;
    BlockValues m_blocks;
    ValuesFunction m_valuesFunction;
    BlockValuesFunction m_blockValuesFunction;
};

}

}
