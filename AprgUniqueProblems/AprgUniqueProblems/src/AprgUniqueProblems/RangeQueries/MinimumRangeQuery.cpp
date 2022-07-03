#include "MinimumRangeQuery.hpp"

#include <Common/Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

MinimumRangeQuery::MinimumRangeQuery(Values const& valuesToCheck)
    : m_minimumValues()
{
    initialize(valuesToCheck);
}

MinimumRangeQuery::Value MinimumRangeQuery::getMinimumFromStartToEnd(Index const start, Index const end) const
{
    // This is now constant time
    Value result{};
    if(start<m_minimumValues.getNumberOfColumns() && end<m_minimumValues.getNumberOfColumns())
    {
        if(start<end)
        {
            Index exponentOf2OfMaxDistance(getLog2(end+1-start));
            Index powerOf2OfMaxDistance(getPow2(exponentOf2OfMaxDistance));
            if(powerOf2OfMaxDistance == end+1-start)
            {
                result = m_minimumValues.getEntry(start, exponentOf2OfMaxDistance);
            }
            else
            {
                result = min(m_minimumValues.getEntry(start, exponentOf2OfMaxDistance),
                             m_minimumValues.getEntry(end+1-powerOf2OfMaxDistance, exponentOf2OfMaxDistance));
            }
        }
        else if(start==end)
        {
            result = m_minimumValues.getEntry(start, 0U);
        }
    }
    return result;
}

MinimumRangeQuery::Index MinimumRangeQuery::getLog2(Index const index) const
{
    return getIntegerAfterFloorOfDoubleValue<Index>(getLogarithm(2U, index));
}

MinimumRangeQuery::Index MinimumRangeQuery::getPow2(Index const index) const
{
    return getIntegerAfterFloorOfDoubleValue<Index>(pow(2U, index));
}

void MinimumRangeQuery::initialize(Values const& valuesToCheck)
{
    if(!valuesToCheck.empty())
    {
        Index lastExponentOf2(getLog2(valuesToCheck.size()));
        m_minimumValues = ValueMatrix(valuesToCheck.size(), lastExponentOf2+1); // column is index, row is exponent of size with base 2
        for(Index index=0; index<valuesToCheck.size(); index++) // put values in first column
        {
            m_minimumValues.setEntry(index, 0U, valuesToCheck.at(index));
        }
        for(Index exponentOf2=0; exponentOf2<lastExponentOf2; exponentOf2++) // put remaining values with "powers of 2 sized" ranges
        {
            Index offset = getPow2(exponentOf2);
            Index limit = valuesToCheck.size()-offset;
            for(Index index=0; index<limit; index++)
            {
                m_minimumValues.setEntry(
                            index, exponentOf2+1, min(m_minimumValues.getEntry(index, exponentOf2), m_minimumValues.getEntry(index+offset, exponentOf2)));
            }
        }
    }
}

}
