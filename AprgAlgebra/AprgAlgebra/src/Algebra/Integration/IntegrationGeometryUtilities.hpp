#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

Term getAreaInBetweenTwoTermsInAnInterval(
        Term const& lowerTerm,
        Term const& higherTerm,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval);
}

}
