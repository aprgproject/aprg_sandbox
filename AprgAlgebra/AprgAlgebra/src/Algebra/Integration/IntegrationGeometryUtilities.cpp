#include "IntegrationGeometryUtilities.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <algorithm>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

Term getAreaInBetweenTwoTermsInAnInterval(
        Term const& lowerTerm,
        Term const& higherTerm,
        string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval)
{
    Integration integration(variableName);
    Term difference(higherTerm-lowerTerm);
    return integration.integrateAtDefiniteValues(difference, lowerValueInInterval, higherValueInInterval);
}

Term getVolumeUsingOnCrossSectionalArea(
        Term const& crossSectionalArea,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    Integration integration(variableName);
    return integration.integrateAtDefiniteTerms(crossSectionalArea, lowerValueTerm, higherValueTerm);
}

Term getVolumeUsingOnSolidOfRevolution(
        Term const& term,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    // Let the function f be continuous on the closed interval [a, b], and assume that f(x) >= 0 for all x in [a, b].
    // If S is the solid of revolution obtained by revolving about the x axis the region bounded by the curve y=f(x),
    // the x axis and the lines x=a and x=b, and if the V cubic is the volume of S, then

    // The volume is equal to pi times the definite integral of square of f(x) from a to b.
    // This method uses disks.

    Integration integration(variableName);
    Term termToIntegrate = getPiAsTerm()*(term^Term(2));
    return integration.integrateAtDefiniteTerms(termToIntegrate, lowerValueTerm, higherValueTerm);
}

Term getVolumeUsingOnSolidOfRevolution(
        Term const& lowerFunctionTerm,
        Term const& higherFunctionTerm,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    // Let the functions f and g be continuous on the closed interval [a, b], and assume that f(x) >= g(x) >= 0 for all x in [a, b].
    // If V cubic units is the volume of the solid of revolution generated by revolving about the x axis the region
    // bounded by the curves y=f(x) and y=g(x) and the lines x=a and x=b, then

    // The volume is equal to pi times the definite integral of square of (f(x)-g(x)) from a to b.
    // This method uses washers(disks with holes).

    Integration integration(variableName);
    Term termToIntegrate = getPiAsTerm()*((higherFunctionTerm-lowerFunctionTerm)^Term(2));
    return integration.integrateAtDefiniteTerms(termToIntegrate, lowerValueTerm, higherValueTerm);
}

Term getVolumeUsingCylindricalShells(
        Term const& term,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    // Let the function f be continuous on the closed interval [a, b], where a>=0.
    // Assume that f(x) >= 0 for all x in [a, b].
    // If R is the region bounded by the curve y=f(x), the x axis and the lines x=a and x=b,
    // if S is the solid of revolution obtained by revolving R about the y axis, and if V cubic units is the volume of S, then

    // The volume is equal to 2*pi times the definite integral of x times f(x) from a to b.
    // This method uses cylindrical shells (like a can without the top and bottom)

    Integration integration(variableName);
    Term termToIntegrate = Term(2)*getPiAsTerm()*(Term(variableName)*term);
    return integration.integrateAtDefiniteTerms(termToIntegrate, lowerValueTerm, higherValueTerm);
}

Term getLengthOfArc(
        Term const& term,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    // If the function f and its derivative fPrime are continuous on the closed interval [a, b],
    // then the length of arc of the curve y=f(x) from the point (a, f(a) to the point (b, f(b)) is given by:

    // The length is equal to the the definite integral of the square root of (1+fPrime^2) from a to b.

    Differentiation differentiation(variableName);
    Integration integration(variableName);
    Term differentiatedTerm(differentiation.differentiate(term));
    Term termToIntegrate = (Term(1)+(differentiatedTerm^Term(2)))^Term(AlbaNumber::createFraction(1, 2));
    termToIntegrate.simplify();
    return integration.integrateAtDefiniteTerms(termToIntegrate, lowerValueTerm, higherValueTerm);
}

Term getLengthOfArcInPolarCoordinates(
        Term const& radiusInTermsOfTheta,
        std::string const& thetaName,
        Term const& lowerValueTermInTheta,
        Term const& higherValueTermInTheta)
{
    Differentiation differentiation(thetaName);
    Integration integration(thetaName);
    Term drOverDTheta(differentiation.differentiate(radiusInTermsOfTheta));
    Term termToIntegrate = ((drOverDTheta^Term(2))+(radiusInTermsOfTheta^Term(2)))^Term(AlbaNumber::createFraction(1, 2));
    termToIntegrate.simplify();
    return integration.integrateAtDefiniteTerms(termToIntegrate, lowerValueTermInTheta, higherValueTermInTheta);
}

Term getTotalMassOfARod(
        Term const& term,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    // A rod of length L meters has its left endpoint at the origin.
    // If p(x) kilograms per meter is the linear density at a point x meters from the origin, where p is continuous on [0, L], then:

    // The total mass of the rod is the definite integral of p(x) from 0 to L.

    Integration integration(variableName);
    return integration.integrateAtDefiniteTerms(term, lowerValueTerm, higherValueTerm);
}

Term getMomentOfMassOfARod(
        Term const& term,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    // A rod of length L meters its left endpoint at the origin and p(x) kilograms per meter is the linear density at a point x meters from the origin,
    // where p is continuous on [0, L].

    // The moment of mass of the rod is the definite integral of x*p(x) from 0 to L.

    Integration integration(variableName);
    Term termToIntegrate = Term(variableName)*term;
    return integration.integrateAtDefiniteTerms(termToIntegrate, lowerValueTerm, higherValueTerm);
}

Term getCenterOfMassOfARod(
        Term const& term,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    return getMomentOfMassOfARod(term, variableName, lowerValueTerm, higherValueTerm)
            / getTotalMassOfARod(term, variableName, lowerValueTerm, higherValueTerm);
}

Term getTotalMassOfALamina(
        Term const& term,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    Integration integration(variableName);
    return integration.integrateAtDefiniteTerms(term, lowerValueTerm, higherValueTerm);
}

TermPair getMomentOfMassOfALamina(
        Term const& term,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    Integration integration(variableName);
    Term termToIntegrateInX = Term(AlbaNumber::createFraction(1, 2)) * Term(term^2);
    Term termToIntegrateInY = Term(variableName) * Term(term);
    TermPair xyPair;
    xyPair.first = integration.integrateAtDefiniteTerms(termToIntegrateInX, lowerValueTerm, higherValueTerm);
    xyPair.second = integration.integrateAtDefiniteTerms(termToIntegrateInY, lowerValueTerm, higherValueTerm);
    return xyPair;
}

TermPair getCenterOfMassOfALamina(
        Term const& term,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    Term totalMass(getTotalMassOfALamina(term, variableName, lowerValueTerm, higherValueTerm));
    TermPair xyPair(getMomentOfMassOfALamina(term, variableName, lowerValueTerm, higherValueTerm));
    xyPair.first = xyPair.first/totalMass;
    xyPair.second = xyPair.second/totalMass;
    return xyPair;
}

TermPair getCentroid(
        Term const& term,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    Integration integration(variableName);
    Term area(integration.integrateAtDefiniteTerms(term, lowerValueTerm, higherValueTerm));
    TermPair xyPair(getMomentOfMassOfALamina(term, variableName, lowerValueTerm, higherValueTerm));
    xyPair.first = xyPair.first / area;
    xyPair.second = xyPair.second / area;
    return xyPair;
}

Term getWork(
        Term const& force,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    Integration integration(variableName);
    return integration.integrateAtDefiniteTerms(force, lowerValueTerm, higherValueTerm);
}

Term getLiquidPressure(
        Term const& massDensity,
        Term const& accelerationDueToGravity,
        Term const& length,
        string const& depth,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    Integration integration(depth);
    Term termToIntegrate = massDensity*accelerationDueToGravity*Term(depth)*length;
    return integration.integrateAtDefiniteTerms(termToIntegrate, lowerValueTerm, higherValueTerm);
}

Term integrateInPolarCoordinates(
        Term const& radiusInTermsOfTheta,
        string const& thetaName,
        Term const& lowerValueTermInTheta,
        Term const& higherValueTermInTheta)
{
    Integration integration(thetaName);
    Term radiusSquared(radiusInTermsOfTheta^2);
    radiusSquared.simplify();
    return integration.integrateAtDefiniteTerms(radiusSquared, lowerValueTermInTheta, higherValueTermInTheta);
}

Term getDoubleIntegralInCartesianCoordinates(
        Term const& termWithXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails)
{
    return integrateWithCoordinateDetails(termWithXAndY, {xDetails, yDetails});
}

Term getTotalMassOfALamina(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails)
{
    return getDoubleIntegralInCartesianCoordinates(areaDensityAtPointInXAndY, xDetails, yDetails);
}

Term getMomentOfMassOfALaminaWithRespectToXAxis(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails)
{
    Term termToIntegrate(areaDensityAtPointInXAndY * Term(yDetails.variableName));
    return getDoubleIntegralInCartesianCoordinates(termToIntegrate, xDetails, yDetails);
}

Term getMomentOfMassOfALaminaWithRespectToYAxis(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails)
{
    Term termToIntegrate(areaDensityAtPointInXAndY * Term(xDetails.variableName));
    return getDoubleIntegralInCartesianCoordinates(termToIntegrate, xDetails, yDetails);
}

TermPair getCenterOfMassOfALamina(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails)
{
    Term totalMass = getTotalMassOfALamina(areaDensityAtPointInXAndY, xDetails, yDetails);
    Term centerOfMassInX = getMomentOfMassOfALaminaWithRespectToYAxis(areaDensityAtPointInXAndY, xDetails, yDetails) / totalMass;
    Term centerOfMassInY = getMomentOfMassOfALaminaWithRespectToXAxis(areaDensityAtPointInXAndY, xDetails, yDetails) / totalMass;
    return TermPair{centerOfMassInX, centerOfMassInY};
}

Term getMomentOfInertiaAboutTheXAxis(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails)
{
    Term termToIntegrate(areaDensityAtPointInXAndY * (Term(yDetails.variableName)^2));
    return getDoubleIntegralInCartesianCoordinates(termToIntegrate, xDetails, yDetails);
}

Term getMomentOfInertiaAboutTheYAxis(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails)
{
    Term termToIntegrate(areaDensityAtPointInXAndY * (Term(xDetails.variableName)^2));
    return getDoubleIntegralInCartesianCoordinates(termToIntegrate, xDetails, yDetails);
}

Term getMomentOfInertiaAboutTheOrigin(
        Term const& areaDensityAtPointInXAndY,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails)
{
    Term termToIntegrate(areaDensityAtPointInXAndY * ((Term(xDetails.variableName)^2) + (Term(yDetails.variableName)^2)));
    return getDoubleIntegralInCartesianCoordinates(termToIntegrate, xDetails, yDetails);
}

Term getRadiusOfGyration(
        Term const& momentOfInertia,
        Term const& totalMass)
{
    // Radius of gyration or gyradius of a body about an axis of rotation is defined
    // as the radial distance to a point which would have a moment of inertia the same as the body's actual distribution of mass,
    // if the total mass of the body were concentrated there.
    // This is applicable to any type of moment of inertia (x axis, y axis, origin)
    return (momentOfInertia/totalMass)^AlbaNumber::createFraction(1, 2);
}

Term getDoubleIntegralInPolarCoordinates(
        Term const& termWithRadiusAndTheta,
        CoordinateDetailsForIntegral const& radiusDetails,
        CoordinateDetailsForIntegral const& thetaDetails)
{
    Term termToIntegrate(termWithRadiusAndTheta * Term(radiusDetails.variableName));
    return integrateWithCoordinateDetails(termToIntegrate, {radiusDetails, thetaDetails});
}

Term getSurfaceAreaWithZInCartesianCoordinates(
        Term const& z,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails)
{
    Term derivativeInX(getPartialDerivative(z, xDetails.variableName));
    Term derivativeInY(getPartialDerivative(z, yDetails.variableName));
    Term termInsideSquareRoot((derivativeInX^Term(2)) + (derivativeInY^Term(2)) + 1);
    Term termToIntegrate(termInsideSquareRoot^Term(AlbaNumber::createFraction(1, 2)));
    return getDoubleIntegralInCartesianCoordinates(termToIntegrate, xDetails, yDetails);
}

Term getTripleIntegralInCartesianCoordinates(
        Term const& termWithXAndYAndZ,
        CoordinateDetailsForIntegral const& xDetails,
        CoordinateDetailsForIntegral const& yDetails,
        CoordinateDetailsForIntegral const& zDetails)
{
    return integrateWithCoordinateDetails(termWithXAndYAndZ, {xDetails, yDetails, zDetails});
}

Term getTripleIntegralInCylindricalCoordinates(
        Term const& termWithRadiusAndThetaAndZ,
        CoordinateDetailsForIntegral const& radiusDetails,
        CoordinateDetailsForIntegral const& thetaDetails,
        CoordinateDetailsForIntegral const& zDetails)
{
    Term termToIntegrate(termWithRadiusAndThetaAndZ * Term(radiusDetails.variableName));
    return integrateWithCoordinateDetails(termToIntegrate, {radiusDetails, thetaDetails, zDetails});
}

Term getTripleIntegralInSphericalCoordinates(
        Term const& termWithRawAndThetaAndPhi,
        CoordinateDetailsForIntegral const& rawDetails,
        CoordinateDetailsForIntegral const& thetaDetails,
        CoordinateDetailsForIntegral const& phiDetails)
{
    Term termToIntegrate(termWithRawAndThetaAndPhi * (Term(rawDetails.variableName)^Term(2)) * Term(sin(Term(phiDetails.variableName))));
    return integrateWithCoordinateDetails(termToIntegrate, {rawDetails, thetaDetails, phiDetails});
}

Term integrateWithCoordinateDetails(
        Term const& term,
        CoordinateDetailsForIntegrals const& integralsDetails)
{
    Term result(term);
    CoordinateDetailsForIntegrals integralsDetailsToEvaluate(integralsDetails);
    sortIntegralsDetailsToEvaluate(integralsDetailsToEvaluate);
    for(CoordinateDetailsForIntegral const& details : integralsDetailsToEvaluate)
    {
        Integration integration(details.variableName);
        result = integration.integrateAtDefiniteTerms(result, details.lowerValueTerm, details.higherValueTerm);
    }
    return result;
}

void sortIntegralsDetailsToEvaluate(CoordinateDetailsForIntegrals & integralsDetails)
{
    stable_sort(integralsDetails.begin(), integralsDetails.end(), [](
                CoordinateDetailsForIntegral const& integral1,
                CoordinateDetailsForIntegral const& integral2)
    {
        VariableNamesRetriever retriever1;
        VariableNamesRetriever retriever2;
        retriever1.retrieveFromTerm(integral1.lowerValueTerm);
        retriever1.retrieveFromTerm(integral1.higherValueTerm);
        retriever2.retrieveFromTerm(integral2.lowerValueTerm);
        retriever2.retrieveFromTerm(integral2.higherValueTerm);

        return retriever1.getSavedData().size() > retriever2.getSavedData().size();
    });
}



}

}
