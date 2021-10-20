#pragma once

#include <Math/Number/Interval/AlbaNumberInterval.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalEndpoint.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

namespace alba
{

bool isValueInsideTheIntervals(AlbaNumberIntervals const& intervals, AlbaNumber const value);
bool isIntervalInsideTheIntervals(AlbaNumberIntervals const& intervals, AlbaNumberInterval const& intervalToCheck);
AlbaNumberIntervalEndpoint::Type getEndpointTypeWithCheckingIfItsClosed(bool const isCloseEndpoint);
AlbaNumberIntervalEndpoint createOpenEndpoint(AlbaNumber const value);
AlbaNumberIntervalEndpoint createCloseEndpoint(AlbaNumber const value);
AlbaNumberIntervalEndpoint createEndpoint(
        bool const isCloseEndpoint,
        AlbaNumber const value);
AlbaNumberIntervalEndpoint createPositiveInfinityOpenEndpoint();
AlbaNumberIntervalEndpoint createNegativeInfinityOpenEndpoint();
AlbaNumberInterval createAllRealValuesInterval();

AlbaNumbers getNumbersInsideTheInterval(AlbaNumbers const& numbersToCheck, AlbaNumberInterval const& intervalToCheck);

}