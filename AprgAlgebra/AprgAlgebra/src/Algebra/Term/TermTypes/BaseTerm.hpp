#pragma once

#include <string>

namespace alba
{

namespace algebra
{

class BaseTerm
{
public:
    BaseTerm() = default;
    virtual ~BaseTerm() = default;

    virtual std::string getDisplayableString() const;
    virtual std::string getDebugString() const;

private:
};

std::ostream & operator<<(std::ostream & out, BaseTerm const& baseTerm);

}

}
