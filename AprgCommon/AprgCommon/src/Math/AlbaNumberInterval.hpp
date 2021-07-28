#pragma once

#include <Math/AlbaNumber.hpp>

namespace alba
{

class AlbaNumberIntervalEndpoint
{
public:
    enum class Type
    {
        Open,
        Close
    };

    AlbaNumberIntervalEndpoint(
            Type const type,
            AlbaNumber const value);

    bool operator==(AlbaNumberIntervalEndpoint const& second) const;
    bool isOpen() const;
    bool isClose() const;

    Type getType() const;
    AlbaNumber const& getValue() const;

    std::string getTypeString() const;
    std::string getDisplayableString() const;

    void setType(Type const type);

private:
    Type m_type;
    AlbaNumber m_value;
};

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

std::ostream & operator<<(std::ostream & out, AlbaNumberIntervalEndpoint const& endpoint);
std::ostream & operator<<(std::ostream & out, AlbaNumberInterval const& interval);

AlbaNumberIntervalEndpoint::Type getEndpointTypeWithCheckingIfItsClosed(bool const isCloseEndpoint);
AlbaNumberIntervalEndpoint createOpenEndpoint(AlbaNumber const value);
AlbaNumberIntervalEndpoint createCloseEndpoint(AlbaNumber const value);
AlbaNumberIntervalEndpoint createEndpoint(
        bool const isCloseEndpoint,
        AlbaNumber const value);
AlbaNumberInterval createAllRealValuesInterval();

}