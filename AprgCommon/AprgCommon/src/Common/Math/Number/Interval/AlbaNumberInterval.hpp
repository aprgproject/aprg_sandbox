#pragma once

#include <Common/Math/Number/Interval/AlbaNumberIntervalEndpoint.hpp>

namespace alba
{

class AlbaNumberInterval
{
public:

    AlbaNumberInterval(
            AlbaNumberIntervalEndpoint const& firstEndpoint,
            AlbaNumberIntervalEndpoint const& secondEndpoint);

    // rule of zero

    bool operator==(AlbaNumberInterval const& second) const;
    bool isValueInsideTheInterval(AlbaNumber const& value) const;
    bool isValueInsideTheIntervalExceptAtTheEndpoints(AlbaNumber const& value) const;
    bool isEndpointInsideTheInterval(AlbaNumberIntervalEndpoint const& endpoint) const;
    bool isIntervalInsideTheInterval(AlbaNumberInterval const& interval) const;
    AlbaNumberIntervalEndpoint const& getLowerEndpoint() const;
    AlbaNumberIntervalEndpoint const& getHigherEndpoint() const;

    void setNewEndpoint(AlbaNumberIntervalEndpoint const& endpoint);

    friend std::ostream & operator<<(std::ostream & out, AlbaNumberInterval const& interval);

private:
    AlbaNumberIntervalEndpoint m_lowerEndpoint;
    AlbaNumberIntervalEndpoint m_higherEndpoint;
};

}
