#pragma once

#include <Equation/Term/BaseTermData.hpp>
#include <Math/AlbaNumber.hpp>

#include <string>

namespace alba
{

namespace equation
{

class Constant : public BaseTermData
{
    friend std::ostream & operator<<(std::ostream & out, Constant const& constant);
public:
    Constant();
    Constant(AlbaNumber const& constantValue);
    Constant(int const signedValue);
    Constant(unsigned int const unsignedValue);
    Constant(int const numerator, unsigned int const denominator);
    Constant(double const doubleValue);

    bool operator==(Constant const& second) const;
    bool operator!=(Constant const& second) const;
    bool operator<(Constant const& second) const;

    AlbaNumber const& getNumberConstReference() const;
    std::string getDisplayableString() const;

    void setNumber(AlbaNumber const& constantValue);

private:
    AlbaNumber m_constantValue;
};

std::ostream & operator<<(std::ostream & out, Constant const& constant);

}

}
