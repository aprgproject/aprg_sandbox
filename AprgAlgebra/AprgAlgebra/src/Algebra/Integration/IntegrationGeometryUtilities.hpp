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

Term getVolumeUsingOnCrossSectionalArea(
        Term const& crossSectionalArea,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

Term getVolumeUsingOnSolidOfRevolution(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

Term getVolumeUsingOnSolidOfRevolution(
        Term const& lowerFunctionTerm,
        Term const& higherFunctionTerm,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

Term getVolumeUsingCylindricalShells(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

Term getLengthOfTheEdge(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);
}

}
