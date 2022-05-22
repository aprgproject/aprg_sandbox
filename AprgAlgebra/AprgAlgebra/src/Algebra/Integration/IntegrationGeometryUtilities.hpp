#pragma once

#include <Algebra/Integration/DetailsForDefiniteIntegralWithTerms.hpp>
#include <Algebra/Integration/DetailsForDefiniteIntegralWithValues.hpp>
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
        DetailsForDefiniteIntegralWithValues const& integralDetails);

Term getVolumeUsingOnCrossSectionalArea(
        Term const& crossSectionalArea,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

Term getVolumeUsingOnSolidOfRevolution(
        Term const& term,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

Term getSurfaceAreaUsingOnSolidOfRevolution(
        Term const& term,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

Term getVolumeUsingOnSolidOfRevolution(
        Term const& lowerFunctionTerm,
        Term const& higherFunctionTerm,        DetailsForDefiniteIntegralWithTerms const& integralDetails);

Term getVolumeUsingCylindricalShells(
        Term const& term,        DetailsForDefiniteIntegralWithTerms const& integralDetails);

Term getLengthOfArc(
        Term const& term,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

Term getLengthOfArcInPolarCoordinates(
        Term const& radiusInTermsOfTheta,
        DetailsForDefiniteIntegralWithTerms const& thetaDetails);

Term getTotalMassOfARod(
        Term const& term,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

Term getMomentOfMassOfARod(
        Term const& term,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

Term getCenterOfMassOfARod(
        Term const& term,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

Term getTotalMassOfALamina(
        Term const& term,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

TermPair getMomentOfMassOfALamina(
        Term const& term,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

TermPair getCenterOfMassOfALamina(
        Term const& term,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

TermPair getCentroid(
        Term const& term,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

Term getWork(
        Term const& force,
        DetailsForDefiniteIntegralWithTerms const& integralDetails);

Term getLiquidPressure(
        Term const& massDensity,
        Term const& accelerationDueToGravity,
        Term const& length,
        DetailsForDefiniteIntegralWithTerms const& depthDetails);

Term integrateInPolarCoordinates(
        Term const& radiusInTermsOfTheta,
        DetailsForDefiniteIntegralWithTerms const& thetaDetails);

Term getDoubleIntegralInCartesianCoordinates(
        Term const& termWithXAndY,
        DetailsForDefiniteIntegralWithTerms const& xDetails,
        DetailsForDefiniteIntegralWithTerms const& yDetails);

Term getTotalMassOfALamina(
        Term const& areaDensityAtPointInXAndY,
        DetailsForDefiniteIntegralWithTerms const& xDetails,
        DetailsForDefiniteIntegralWithTerms const& yDetails);

Term getMomentOfMassOfALaminaWithRespectToXAxis(
        Term const& areaDensityAtPointInXAndY,
        DetailsForDefiniteIntegralWithTerms const& xDetails,
        DetailsForDefiniteIntegralWithTerms const& yDetails);

Term getMomentOfMassOfALaminaWithRespectToYAxis(
        Term const& areaDensityAtPointInXAndY,
        DetailsForDefiniteIntegralWithTerms const& xDetails,
        DetailsForDefiniteIntegralWithTerms const& yDetails);

TermPair getCenterOfMassOfALamina(
        Term const& areaDensityAtPointInXAndY,
        DetailsForDefiniteIntegralWithTerms const& xDetails,
        DetailsForDefiniteIntegralWithTerms const& yDetails);

Term getMomentOfInertiaAboutTheXAxis(
        Term const& areaDensityAtPointInXAndY,
        DetailsForDefiniteIntegralWithTerms const& xDetails,
        DetailsForDefiniteIntegralWithTerms const& yDetails);

Term getMomentOfInertiaAboutTheYAxis(
        Term const& areaDensityAtPointInXAndY,
        DetailsForDefiniteIntegralWithTerms const& xDetails,
        DetailsForDefiniteIntegralWithTerms const& yDetails);

Term getMomentOfInertiaAboutTheOrigin(
        Term const& areaDensityAtPointInXAndY,
        DetailsForDefiniteIntegralWithTerms const& xDetails,
        DetailsForDefiniteIntegralWithTerms const& yDetails);

Term getRadiusOfGyration(
        Term const& momentOfInertia,
        Term const& totalMass);

Term getDoubleIntegralInPolarCoordinates(
        Term const& termWithRadiusAndTheta,
        DetailsForDefiniteIntegralWithTerms const& radiusDetails,
        DetailsForDefiniteIntegralWithTerms const& thetaDetails);

Term getSurfaceAreaWithZInCartesianCoordinates(
        Term const& z,
        DetailsForDefiniteIntegralWithTerms const& xDetails,
        DetailsForDefiniteIntegralWithTerms const& yDetails);

Term getTripleIntegralInCartesianCoordinates(
        Term const& termWithXAndYAndZ,
        DetailsForDefiniteIntegralWithTerms const& xDetails,
        DetailsForDefiniteIntegralWithTerms const& yDetails,
        DetailsForDefiniteIntegralWithTerms const& zDetails);

Term getTripleIntegralInCylindricalCoordinates(
        Term const& termWithRadiusAndThetaAndZ,
        DetailsForDefiniteIntegralWithTerms const& radiusDetails,
        DetailsForDefiniteIntegralWithTerms const& thetaDetails,
        DetailsForDefiniteIntegralWithTerms const& zDetails);

Term getTripleIntegralInSphericalCoordinates(
        Term const& termWithRawAndThetaAndPhi,
        DetailsForDefiniteIntegralWithTerms const& rawDetails,
        DetailsForDefiniteIntegralWithTerms const& thetaDetails,
        DetailsForDefiniteIntegralWithTerms const& phiDetails);

Term integrateWithCoordinateDetails(Term const& term,  DetailsForDefiniteIntegralsWithTerms const& integralsDetails);
void sortIntegralsDetailsToEvaluate(DetailsForDefiniteIntegralsWithTerms & integrals);

}

}
