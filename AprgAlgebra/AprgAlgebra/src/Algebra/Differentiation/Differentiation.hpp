#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

bool isDifferentiableAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value);

Term getDerivativeByDefinition(
        Term const& term,
        std::string const& variableName,
        Term const& x);

void simplifyDerivativeByDefinition(Term & term);

}

}