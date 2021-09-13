#pragma once

#include <Math/Number/Interval/AlbaNumberIntervalEndpoint.hpp>

namespace alba
{

class AlbaNumberInterval
{
public:

    AlbaNumberInterval(
            AlbaNumberIntervalEndpoint const& firstEndpoint,
            AlbaNumberIntervalEndpoint const& secondEndpoint);

    bool operator==(AlbaNumberInterval const& second) const;

    bool isValueInsideTheInterval(AlbaNumber const& value) const;
    bool isValueInsideTheIntervalExceptAtTheEndpoints(AlbaNumber const& value) const;
    bool isEndpointInsideTheInterval(AlbaNumberIntervalEndpoint const& endpoint) const;
    bool isIntervalInsideTheInterval(AlbaNumberInterval const& interval) const;

    AlbaNumberIntervalEndpoint const& getLowerEndpoint() const;
    AlbaNumberIntervalEndpoint const& getHigherEndpoint() const;
    std::string getDisplayableString() const;

    void setNewEndpoint(AlbaNumberIntervalEndpoint const& endpoint);

private:
    AlbaNumberIntervalEndpoint m_lowerEndpoint;
    AlbaNumberIntervalEndpoint m_higherEndpoint;
};

std::ostream & operator<<(std::ostream & out, AlbaNumberInterval const& interval);

}
