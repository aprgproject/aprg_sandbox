#pragma once

#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Constructs/TermsRaiseToExponents.hpp>

namespace alba
{
namespace algebra
{

using TermsRaiseToNumbersBase = TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>;
class TermsRaiseToNumbers : public TermsRaiseToNumbersBase
{
public:
    TermsRaiseToNumbers();
    TermsRaiseToNumbers(BaseToExponentMap const& baseToExponentMap);
};

}
}
