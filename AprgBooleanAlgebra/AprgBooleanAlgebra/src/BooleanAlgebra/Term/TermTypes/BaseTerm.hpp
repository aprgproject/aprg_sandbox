#pragma once

#include <string>

namespace alba
{

namespace booleanAlgebra
{

class BaseTerm
{
public:
    BaseTerm() = default;
    virtual ~BaseTerm() = default;

private:
};
std::ostream & operator<<(std::ostream & out, BaseTerm const& baseTerm);

}

}
