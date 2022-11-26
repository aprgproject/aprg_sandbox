#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermData.hpp>

#include <ostream>

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

    void setValue(bool const boolValue);
    void negate();

private:
    friend std::ostream & operator<<(std::ostream & out, Constant const& constant);

    bool m_booleanValue;
};

}

}