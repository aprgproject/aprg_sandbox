#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

#include <string>

namespace alba
{

namespace algebra
{

struct CoordinateDetailsForIntegral
{
    std::string variableName;
    Term lowerValueTerm;
    Term higherValueTerm;
};

using CoordinateDetailsForIntegrals = std::vector<CoordinateDetailsForIntegral>;

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

Term getLengthOfArc(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

Term getLengthOfArcInPolarCoordinates(
        Term const& radiusInTermsOfTheta,
        std::string const& thetaName,
        Term const& lowerValueTermInTheta,
        Term const& higherValueTermInTheta);

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

Term integrateInPolarCoordinates(
        Term const& radiusInTermsOfTheta,
        std::string const& thetaName,
        Term const& lowerValueTermInTheta,
        Term const& higherValueTermInTheta);

Term getDoubleIntegralInCartesianCoordinates(
        Term const& termWithXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails);

Term getTotalMassOfALamina(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails);

Term getMomentOfMassOfALaminaWithRespectToXAxis(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails);

Term getMomentOfMassOfALaminaWithRespectToYAxis(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails);

TermPair getCenterOfMassOfALamina(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails);

Term getMomentOfInertiaAboutTheXAxis(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails);

Term getMomentOfInertiaAboutTheYAxis(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails);

Term getMomentOfInertiaAboutTheOrigin(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails);

Term getRadiusOfGyration(
        Term const& momentOfInertia,
        Term const& totalMass);

Term getDoubleIntegralInPolarCoordinates(
        Term const& termWithRadiusAndTheta,
        CoordinateDetailsForIntegral const& radiusDetails,
        CoordinateDetailsForIntegral const& thetaDetails);

Term getSurfaceAreaWithZInCartesianCoordinates(
        Term const& z,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails);

Term getTripleIntegralInCartesianCoordinates(
        Term const& termWithXAndYAndZ,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails,
        CoordinateDetailsForIntegral const& zDetails);

Term getTripleIntegralInCylindricalCoordinates(
        Term const& termWithRadiusAndThetaAndZ,
        CoordinateDetailsForIntegral const& radiusDetails,
        CoordinateDetailsForIntegral const& thetaDetails,
        CoordinateDetailsForIntegral const& zDetails);

Term getTripleIntegralInSphericalCoordinates(
        Term const& termWithRawAndThetaAndPhi,
        CoordinateDetailsForIntegral const& rawDetails,
        CoordinateDetailsForIntegral const& thetaDetails,
        CoordinateDetailsForIntegral const& phiDetails);

Term integrateWithCoordinateDetails(Term const& term,  CoordinateDetailsForIntegrals const& integralsDetails);
void sortIntegralsDetailsToEvaluate(CoordinateDetailsForIntegrals & integrals);

}

}
