#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

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

Term getTotalMassOfARod(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

Term getMomentOfMassOfARod(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

Term getCenterOfMassOfARod(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

Term getTotalMassOfALamina(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

TermPair getMomentOfMassOfALamina(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

TermPair getCenterOfMassOfALamina(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

TermPair getCentroid(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

Term getWork(
        Term const& force,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

Term getLiquidPressure(
        Term const& massDensity,
        Term const& accelerationDueToGravity,
        Term const& length,
        std::string const& depth,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);
}

}