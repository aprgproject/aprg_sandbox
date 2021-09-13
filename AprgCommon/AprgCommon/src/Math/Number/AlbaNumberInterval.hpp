#pragma once

#include <Math/Number/AlbaNumberIntervalEndpoint.hpp>

namespace alba
{

class AlbaNumberInterval
{
public:

    AlbaNumberInterval(
            AlbaNumberIntervalEndpoint const& firstEndpoint,
            AlbaNumberIntervalEndpoint const& secondEndpoint);

    bool operator==(AlbaNumberInterval const& second) const;
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
