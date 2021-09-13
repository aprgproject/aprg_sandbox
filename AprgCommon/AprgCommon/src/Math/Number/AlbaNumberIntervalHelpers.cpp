#include "AlbaNumberIntervalHelpers.hpp"

using namespace std;

namespace alba
{

AlbaNumberIntervalEndpoint::Type getEndpointTypeWithCheckingIfItsClosed(bool const isCloseEndpoint)
{
    return isCloseEndpoint ? AlbaNumberIntervalEndpoint::Type::Close : AlbaNumberIntervalEndpoint::Type::Open;
}

AlbaNumberIntervalEndpoint createOpenEndpoint(AlbaNumber const value)
{
    return AlbaNumberIntervalEndpoint(AlbaNumberIntervalEndpoint::Type::Open, value);
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

AlbaNumberInterval createAllRealValuesInterval()
{
    return AlbaNumberInterval(
                createOpenEndpoint(AlbaNumber::Value::NegativeInfinity),
                createOpenEndpoint(AlbaNumber::Value::PositiveInfinity));
}

}
