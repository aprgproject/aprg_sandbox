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
            Index exponentOf2(getCielOfLogOf2(end+1-start)-1); // Half of minimum distance that would fit
            Index powerOf2(getPowOf2(exponentOf2)); // Half of minimum distance that would fit
            result = min(m_minimumValues.getEntry(start, exponentOf2),
                         m_minimumValues.getEntry(end+1-powerOf2, exponentOf2));
        }
        else if(start==end)
        {
            result = m_minimumValues.getEntry(start, 0U);
        }
    }
    return result;
}

MinimumRangeQuery::Index MinimumRangeQuery::getCielOfLogOf2(Index const index) const
{
    return getIntegerAfterCeilingOfDoubleValue<Index>(getLogarithm(2U, index));
}

MinimumRangeQuery::Index MinimumRangeQuery::getPowOf2(Index const index) const
{
    //return getIntegerAfterFloorOfDoubleValue<Index>(pow(2U, index)); // this is costly
    return Index(1) << index;
}

void MinimumRangeQuery::initialize(Values const& valuesToCheck)
{
    if(!valuesToCheck.empty())
    {
        Index lastExponentOf2(getCielOfLogOf2(valuesToCheck.size())-1); // half (reason for minus1) of min exponent in power of 2 that would fit
        m_minimumValues = ValueMatrix(valuesToCheck.size(), lastExponentOf2+1); // column is index, row is exponent of size with base 2
        for(Index index=0; index<valuesToCheck.size(); index++) // put values in first column
        {
            m_minimumValues.setEntry(index, 0U, valuesToCheck.at(index));
        }
        for(Index exponentOf2=0; exponentOf2<lastExponentOf2; exponentOf2++) // put remaining values with "powers of 2 sized" ranges
        {
            Index offset = getPowOf2(exponentOf2);
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
