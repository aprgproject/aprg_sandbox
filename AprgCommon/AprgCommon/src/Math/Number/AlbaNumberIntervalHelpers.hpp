#pragma once

#include <Math/Number/AlbaNumberInterval.hpp>
#include <Math/Number/AlbaNumberIntervalEndpoint.hpp>

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
