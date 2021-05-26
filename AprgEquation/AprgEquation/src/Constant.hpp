#pragma once

#include <BaseTerm.hpp>
#include <Math/AlbaNumber.hpp>

namespace alba
{

namespace equation
{

class Constant : public BaseTerm
{
public:
    Constant();
    Constant(AlbaNumber const& constantValue);
    Constant(int const signedValue);
    Constant(unsigned int const unsignedValue);
    Constant(int const numerator, unsigned int const denominator);
    Constant(double const doubleValue);

    AlbaNumber const& getNumberConstReference() const;

    void setNumber(AlbaNumber const& constantValue);

private:
    AlbaNumber m_constantValue;
};

}

}
