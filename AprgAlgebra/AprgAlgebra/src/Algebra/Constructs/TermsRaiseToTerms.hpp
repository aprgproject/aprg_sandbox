#pragma once

#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Constructs/TermsRaiseToExponents.hpp>

namespace alba
{

namespace algebra
{

using TermsRaiseToTermsBase = TermsRaiseToExponents<Term, TermRaiseToTerms>;
class TermsRaiseToTerms : public TermsRaiseToTermsBase
{
public:
    TermsRaiseToTerms();
    TermsRaiseToTerms(BaseToExponentMap const& baseToExponentMap);
};

}

}
