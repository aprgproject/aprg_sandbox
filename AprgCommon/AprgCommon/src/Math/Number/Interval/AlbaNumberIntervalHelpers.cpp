#include "AlbaNumberIntervalHelpers.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

bool isValueInsideTheIntervals(AlbaNumberIntervals const& intervals, AlbaNumber const value)
{
    return any_of(intervals.cbegin(), intervals.cend(), [&](AlbaNumberInterval const& interval)
    {
        return interval.isValueInsideTheInterval(value);
    });
}

bool isIntervalInsideTheIntervals(AlbaNumberIntervals const& intervals, AlbaNumberInterval const& intervalToCheck)
{
    return any_of(intervals.cbegin(), intervals.cend(), [&](AlbaNumberInterval const& interval)
    {
        return interval.isIntervalInsideTheInterval(intervalToCheck);
    });
}

AlbaNumberIntervalEndpoint::Type getEndpointTypeWithCheckingIfItsClosed(bool const isCloseEndpoint)
{
    return isCloseEndpoint ? AlbaNumberIntervalEndpoint::Type::Close : AlbaNumberIntervalEndpoint::Type::Open;
}

AlbaNumberIntervalEndpoint createOpenEndpoint(AlbaNumber const value)
{    return AlbaNumberIntervalEndpoint(AlbaNumberIntervalEndpoint::Type::Open, value);
}

AlbaNumberIntervalEndpoint createCloseEndpoint(AlbaNumber const value)
{
    return AlbaNumberIntervalEndpoint(AlbaNumberIntervalEndpoint::Type::Close, value);
}

AlbaNumberIntervalEndpoint createEndpoint(
        bool const isCloseEndpoint,
        AlbaNumber const value)
{
    return AlbaNumberIntervalEndpoint(getEndpointTypeWithCheckingIfItsClosed(isCloseEndpoint), value);
}

AlbaNumberIntervalEndpoint createPositiveInfinityOpenEndpoint()
{
    return createOpenEndpoint(AlbaNumber::Value::PositiveInfinity);
}

AlbaNumberIntervalEndpoint createNegativeInfinityOpenEndpoint()
{
    return createOpenEndpoint(AlbaNumber::Value::NegativeInfinity);
}

AlbaNumberInterval createAllRealValuesInterval()
{
    return AlbaNumberInterval(
                createNegativeInfinityOpenEndpoint(),
                createPositiveInfinityOpenEndpoint());
}

}
