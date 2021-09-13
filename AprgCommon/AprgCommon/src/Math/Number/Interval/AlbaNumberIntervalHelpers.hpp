#pragma once

#include <Math/Number/Interval/AlbaNumberInterval.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalEndpoint.hpp>

namespace alba
{
AlbaNumberIntervalEndpoint::Type getEndpointTypeWithCheckingIfItsClosed(bool const isCloseEndpoint);
AlbaNumberIntervalEndpoint createOpenEndpoint(AlbaNumber const value);
AlbaNumberIntervalEndpoint createCloseEndpoint(AlbaNumber const value);
AlbaNumberIntervalEndpoint createEndpoint(
        bool const isCloseEndpoint,
        AlbaNumber const value);
AlbaNumberInterval createAllRealValuesInterval();

}
