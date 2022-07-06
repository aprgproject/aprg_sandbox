#include "SumRangeQuery.hpp"

using namespace std;

namespace alba
{

SumRangeQuery::SumRangeQuery(Values const& valuesToCheck)
    : m_partialSums()
{
    initialize(valuesToCheck);
}

SumRangeQuery::Value SumRangeQuery::getSumFromStartToEnd(Index const start, Index const end) const
{
    // This is now constant time
    Value result{};
    if(start<=end && start<m_partialSums.size() && end<m_partialSums.size())
    {
        if(start>0)
        {
            result = m_partialSums.at(end) - m_partialSums.at(start-1);
        }
        else
        {
            result = m_partialSums.at(end);
        }
    }
    return result;
}

void SumRangeQuery::initialize(Values const& valuesToCheck)
{
    m_partialSums.reserve(valuesToCheck.size());
    Value partialSum{};
    for(Value const valueToCheck : valuesToCheck)
    {
        partialSum += valueToCheck;
        m_partialSums.emplace_back(partialSum);
    }
    m_partialSums.shrink_to_fit();
}

}
