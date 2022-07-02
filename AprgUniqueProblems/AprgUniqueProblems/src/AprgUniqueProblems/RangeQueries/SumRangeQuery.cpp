#include "SumRangeQuery.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

SumRangeQuery::SumRangeQuery(Values const& valuesToCheck)
    : m_partialSums()
{
    initialize(valuesToCheck);
}

SumRangeQuery::Value SumRangeQuery::getSumFromStartAndEnd(Index const start, Index const end) const
{
    // This is know constant time
    Value result{};
    if(start>0 && start<=end && start<m_partialSums.size() && end<m_partialSums.size())
    {
        result = m_partialSums.at(end) - m_partialSums.at(start-1);
    }
    return result;
}

void SumRangeQuery::initialize(Values const& valuesToCheck)
{
    m_partialSums.reserve(valuesToCheck.size());
    Value partialSum;
    for(Value const valueToCheck : valuesToCheck)
    {
        partialSum += valueToCheck;
        m_partialSums.emplace_back(partialSum);
    }
    m_partialSums.shrink_to_fit();
}

}
