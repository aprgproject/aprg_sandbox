#pragma once

#include <Math/Number/AlbaNumber.hpp>

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

std::ostream & operator<<(std::ostream & out, AlbaNumberIntervalEndpoint const& endpoint);

}
