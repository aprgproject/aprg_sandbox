#pragma once

#include <Algorithm/Search/NearestValue/LinearSearch/LinearNearestValueSearchWithTwoIndices.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <limits>

namespace alba
{

namespace algorithm
{

template <typename Values>
class JumpNearestValueSearch
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = std::numeric_limits<Index>::max();

    JumpNearestValueSearch(Values const& values) // values can be unsorted
        : m_blockSize(getOptimalSize(values))
        , m_values(values)
    {}

    Value getNearestValue(Value const& valueToCheck)
    {
        Value result{};
        Index selectedIndex(getIndexOfNearestValue(valueToCheck));
        if(selectedIndex != INVALID_INDEX)
        {
            result = m_values.at(selectedIndex);
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& valueToCheck)
    {
        Index result(INVALID_INDEX);
        bool shouldContinueToLinearSearch(true);

        // find the block where value is included
        Index blockStartIndex(0U);
        Index blockEndIndex(0U);
        while(blockEndIndex<m_values.size() && m_values.at(blockEndIndex)<=valueToCheck)
        {
            blockStartIndex = blockEndIndex;
            blockEndIndex += m_blockSize;
            if(m_values.at(blockStartIndex) > valueToCheck)
            {
                shouldContinueToLinearSearch = false;
                break;
            }
        }

        if(shouldContinueToLinearSearch)
        {
            // continue to linear search
            LinearNearestValueSearchWithTwoIndices<Values> linearSearch(
                        blockStartIndex, blockEndIndex, m_values); // perform linear search on that block
            result = linearSearch.getIndexOfNearestValue(valueToCheck);
        }
        return result;
    }

private:

    Index getOptimalSize(Values const& values) const
    {
        // optimal size is squareroot size
        return std::max(1U, mathHelper::getIntegerAfterFloorOfDoubleValue<Index>(sqrt(values.size())));
    }

    Index m_blockSize;
    Values const& m_values;
};

}

}
