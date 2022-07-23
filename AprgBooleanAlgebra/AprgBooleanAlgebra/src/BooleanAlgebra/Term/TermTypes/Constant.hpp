#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermData.hpp>

#include <string>

namespace alba
{

namespace booleanAlgebra
{

class Constant : public BaseTermData
{
public:
    Constant();
    explicit Constant(bool const boolValue);

    bool operator==(Constant const& second) const;
    bool operator!=(Constant const& second) const;
    bool operator<(Constant const& second) const;

    Constant operator~() const;

    bool getBooleanValue() const;
    std::string getDisplayableString() const;

    void setValue(bool const boolValue);
    void negate();

private:
    bool m_booleanValue;
};

std::ostream & operator<<(std::ostream & out, Constant const& constant);

}

}
