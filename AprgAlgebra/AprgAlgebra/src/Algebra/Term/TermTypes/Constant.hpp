#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <string>
namespace alba
{
namespace algebra
{

class Constant : public BaseTermData
{
public:
    Constant();
    explicit Constant(int const signedValue);
    explicit Constant(unsigned int const unsignedValue);
    explicit Constant(double const doubleValue);
    explicit Constant(AlbaNumber const& constantValue);

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
