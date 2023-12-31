#include "MathVectorOfTermsUtilities.hpp"

#include <Algebra/Geometry/ThreeDimensions/ThreeDimensionsUtilities.hpp>
#include <Algebra/Integration/IntegrationGeometryUtilities.hpp>
#include <Algebra/Retrieval/SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Utilities/KnownNames.hpp>
#include <Common/Math/Vector/AlbaMathVectorUtilities.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

namespace VectorUtilities {

bool isDivergenceOfCurlZero(MathVectorOfThreeTerms const& termVector, ArrayOfThreeStrings const& coordinateVariables) {
    // This is always true
    return getDivergence<3>(getCurl(termVector, coordinateVariables), coordinateVariables) == 0;
}

bool isGaussDivergenceTheoremInAPlaneTrue(
    MathVectorOfTwoTerms const& vectorField, MathVectorOfTwoTerms const& regionOfLineIntegral,
    MathVectorOfTwoTerms const& unitOutwardNormal, DetailsForDefiniteIntegralWithTerms const& lineIntegralDetails,
    DetailsForDefiniteIntegralWithTerms const& areaDetailsInX,
    DetailsForDefiniteIntegralWithTerms const& areaDetailsInY, ArrayOfTwoStrings const& coordinateVariables) {
    // This is just an example of Gauss Divergence Theorem.
    // Gauss Divergence Theorem relates surface area to divergence of volume
    // This is always true

    // Line Integral result
    SubstitutionOfVariablesToTerms substitution;
    for (int i = 0; i < 2; i++) {
        substitution.putVariableWithTerm(coordinateVariables[i], regionOfLineIntegral.getValueAt(i));
    }
    MathVectorOfTwoTerms linePathInVectorField;
    for (int i = 0; i < 2; i++) {
        linePathInVectorField.getValueReferenceAt(i) = substitution.performSubstitutionTo(vectorField.getValueAt(i));
    }
    Term termIntegrate(getDotProduct(linePathInVectorField, unitOutwardNormal));
    Integration integration(lineIntegralDetails.variableName);
    Term lineIntegralResult(integration.integrateAtDefiniteTerms(
        termIntegrate, lineIntegralDetails.lowerEnd, lineIntegralDetails.higherEnd));

    // Area result
    Term divergence(getDivergence<2>(vectorField, coordinateVariables));
    Term areaResult(getDoubleIntegralInCartesianCoordinates(divergence, areaDetailsInX, areaDetailsInY));
    return lineIntegralResult == areaResult;
}

bool isStokesTheoremInAPlaneTrue(
    MathVectorOfTwoTerms const& vectorField, MathVectorOfTwoTerms const& regionOfLineIntegral,
    MathVectorOfTwoTerms const& unitTangentVector, DetailsForDefiniteIntegralWithTerms const& lineIntegralDetails,
    DetailsForDefiniteIntegralWithTerms const& areaDetailsInX,
    DetailsForDefiniteIntegralWithTerms const& areaDetailsInY, ArrayOfTwoStrings const& coordinateVariables) {
    // This is just an example of Stokes Theorem.
    // Stokes Theorem relates line integral to surface area

    // This is always true

    // Line Integral result
    SubstitutionOfVariablesToTerms substitution;
    for (int i = 0; i < 2; i++) {
        substitution.putVariableWithTerm(coordinateVariables[i], regionOfLineIntegral.getValueAt(i));
    }
    MathVectorOfTwoTerms linePathInVectorField;
    for (int i = 0; i < 2; i++) {
        linePathInVectorField.getValueReferenceAt(i) = substitution.performSubstitutionTo(vectorField.getValueAt(i));
    }
    Term termIntegrate(getDotProduct(linePathInVectorField, unitTangentVector));
    Integration integration(lineIntegralDetails.variableName);
    Term lineIntegralResult(integration.integrateAtDefiniteTerms(
        termIntegrate, lineIntegralDetails.lowerEnd, lineIntegralDetails.higherEnd));

    // Area result
    Term partialDerivativeOfYOnX(getPartialDerivative(vectorField.getValueAt(1), coordinateVariables[0]));
    Term partialDerivativeOfXOnY(getPartialDerivative(vectorField.getValueAt(0), coordinateVariables[1]));
    Term termToIntegrateForArea(partialDerivativeOfYOnX - partialDerivativeOfXOnY);
    Term areaResult(getDoubleIntegralInCartesianCoordinates(termToIntegrateForArea, areaDetailsInX, areaDetailsInY));
    return lineIntegralResult == areaResult;
}

Term getDyOverDx(MathVectorOfTwoTerms const& termVector, string const& variableName) {
    MathVectorOfTwoTerms derivative(differentiate(termVector, variableName));
    Term result(derivative.getValueAt(1) / derivative.getValueAt(0));
    result.simplify();
    return result;
}

Term getDirectionalDerivativeInTwoDimensions(
    Term const& term, ArrayOfTwoStrings const& coordinateVariables, AlbaAngle const& angleOfDirection) {
    MathVectorOfTwoTerms gradient(getGradient<2>(term, coordinateVariables));
    MathVectorOfTwoTerms unitDirection({::cos(angleOfDirection.getRadians()), ::sin(angleOfDirection.getRadians())});
    Term result(getDotProduct(gradient, unitDirection));
    simplifyForTermInVector(result);
    return result;
}

Term getDirectionalDerivativeInThreeDimensions(
    Term const& term, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeAngles const& coordinateAngles) {
    MathVectorOfThreeTerms gradient(getGradient<3>(term, coordinateVariables));
    MathVectorOfThreeTerms unitDirection(
        {::cos(coordinateAngles.getValueAt(0).getRadians()), ::cos(coordinateAngles.getValueAt(1).getRadians()),
         ::cos(coordinateAngles.getValueAt(2).getRadians())});
    Term result(getDotProduct(gradient, unitDirection));
    simplifyForTermInVector(result);
    return result;
}

Term getLineIntegralOfAClosedNonIntersectingPathUsingGreensTheorem(
    MathVectorOfTwoTerms const& vectorField, ArrayOfTwoStrings const& coordinateVariables,
    DetailsForDefiniteIntegralWithTerms const& xDetailsForLinePath,
    DetailsForDefiniteIntegralWithTerms const& yDetailsForLinePath) {
    // Green's Theorem is only usable on a line path that is closed and simple (non intersecting)
    // Green's Theorem relates line integral to area

    Term partialDerivativeOfYOnX(getPartialDerivative(vectorField.getValueAt(1), coordinateVariables[0]));
    Term partialDerivativeOfXOnY(getPartialDerivative(vectorField.getValueAt(0), coordinateVariables[1]));
    Term termToIntegrateForArea(partialDerivativeOfYOnX - partialDerivativeOfXOnY);
    return getDoubleIntegralInCartesianCoordinates(termToIntegrateForArea, xDetailsForLinePath, yDetailsForLinePath);
}

Term getAreaOfAClosedNonIntersectingPathUsingGreensTheorem(
    ArrayOfTwoStrings const& coordinateVariables, MathVectorOfTwoTerms const& linePath,
    DetailsForDefiniteIntegralWithTerms const& linePathIntegralDetails) {
    // Green's Theorem is only usable on a line path that is closed and simple (non intersecting)
    // Green's Theorem relates area to line integral

    MathVectorOfTwoTerms vectorField{coordinateVariables[1] * -1, coordinateVariables[0]};
    return getLineIntegral<2>(vectorField, coordinateVariables, linePath, linePathIntegralDetails) / 2;
}

MathVectorOfThreeTerms getNormalOfASurfaceOnAPoint(
    Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point) {
    using Values = typename MathVectorOfThreeTerms::ValuesInArray;
    Equation simplifiedSurface(surface);
    simplifiedSurface.simplify();
    MathVectorOfThreeTerms gradient(getGradient<3>(simplifiedSurface.getLeftHandTerm(), coordinateVariables));
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(coordinateVariables[0], point.getValueAt(0));
    substitution.putVariableWithValue(coordinateVariables[1], point.getValueAt(1));
    substitution.putVariableWithValue(coordinateVariables[2], point.getValueAt(2));

    MathVectorOfThreeTerms result;
    Values const& values(gradient.getValues());
    transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term) {
        return substitution.performSubstitutionTo(term);
    });
    return result;
}

Equation getTangentPlaneOnAPointOfASurface(
    Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point) {
    MathVectorOfThreeTerms normalOfASurface(getNormalOfASurfaceOnAPoint(surface, coordinateVariables, point));
    SubstitutionOfVariablesToTerms substitution;
    substitution.putVariableWithTerm(a, normalOfASurface.getValueAt(0));
    substitution.putVariableWithTerm(b, normalOfASurface.getValueAt(1));
    substitution.putVariableWithTerm(c, normalOfASurface.getValueAt(2));
    substitution.putVariableWithTerm(x0, point.getValueAt(0));
    substitution.putVariableWithTerm(y0, point.getValueAt(1));
    substitution.putVariableWithTerm(z0, point.getValueAt(2));

    Equation generalPlane(ThreeDimensions::getPlaneEquationWithPointCoordinates());
    return substitution.performSubstitutionTo(generalPlane);
}

Equations getPerpendicularLineOnAPointOfASurface(
    Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point) {
    MathVectorOfThreeTerms normalOfASurface(getNormalOfASurfaceOnAPoint(surface, coordinateVariables, point));
    SubstitutionOfVariablesToTerms substitution;
    substitution.putVariableWithTerm(a, normalOfASurface.getValueAt(0));
    substitution.putVariableWithTerm(b, normalOfASurface.getValueAt(1));
    substitution.putVariableWithTerm(c, normalOfASurface.getValueAt(2));
    substitution.putVariableWithTerm(x0, point.getValueAt(0));
    substitution.putVariableWithTerm(y0, point.getValueAt(1));
    substitution.putVariableWithTerm(z0, point.getValueAt(2));

    Equations lineEquations(ThreeDimensions::getLineEquations());
    for (Equation& lineEquation : lineEquations) {
        lineEquation = substitution.performSubstitutionTo(lineEquation);
    }
    return lineEquations;
}

MathVectorOfThreeTerms getCurl(
    MathVectorOfThreeTerms const& termVector, ArrayOfThreeStrings const& coordinateVariables) {
    Term const& a(termVector.getValueAt(0));
    Term const& b(termVector.getValueAt(1));
    Term const& c(termVector.getValueAt(2));
    Term x(getPartialDerivative(c, coordinateVariables[1]) - getPartialDerivative(b, coordinateVariables[2]));
    Term y(getPartialDerivative(a, coordinateVariables[2]) - getPartialDerivative(c, coordinateVariables[0]));
    Term z(getPartialDerivative(b, coordinateVariables[0]) - getPartialDerivative(a, coordinateVariables[1]));
    return MathVectorOfThreeTerms{x, y, z};
}

void simplifyForTermInVector(Term& term) {
    Simplification::simplifyTermByFactoringToNonDoubleFactorsToACommonDenominator(term);
    term.clearAllInnerSimplifiedFlags();
    term.simplify();
}

SegregateTermsByConditionInAdditionAndSubtractionRetriever getRetrieverForComparison(
    Term const& termToAnalyze, string const& coordinateVariableName, strings const& processedCoordinates) {
    SegregateTermsByConditionInAdditionAndSubtractionRetriever::ConditionFunction condition =
        [&](Term const& term) -> bool {
        VariableNamesRetriever retriever;
        retriever.retrieveFromTerm(term);
        VariableNamesSet const& names(retriever.getVariableNames());
        bool isCurrentCoordinateFound = names.find(coordinateVariableName) != names.cend();
        bool isOneOfTheOtherPreviousCoordinatesFound(false);
        for (string const& processedCoordinate : processedCoordinates) {
            if (processedCoordinate != coordinateVariableName && names.find(processedCoordinate) != names.cend()) {
                isOneOfTheOtherPreviousCoordinatesFound = true;
                break;
            }
        }
        return isCurrentCoordinateFound && isOneOfTheOtherPreviousCoordinatesFound;
    };
    SegregateTermsByConditionInAdditionAndSubtractionRetriever retriever(condition);
    retriever.retrieveFromTerm(termToAnalyze);
    return retriever;
}

void retrieveWithAndWithoutOtherCoordinates(
    Term& termWithOtherCoordinates, Term& termWithoutOtherCoordinates, Term const& termToAnalyze,
    string const& coordinateVariableName, strings const& allCoordinates) {
    SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever retriever(allCoordinates);
    retriever.retrieveFromTerm(termToAnalyze);
    termWithoutOtherCoordinates = retriever.getRemainingTerm();
    termWithOtherCoordinates = retriever.getTermWithMultipleVariableNames();
    for (auto const& [variableName, term] : retriever.getVariableNameToTermMap()) {
        if (variableName == coordinateVariableName) {
            termWithoutOtherCoordinates += term;
        } else {
            termWithOtherCoordinates += term;
        }
    }
}

}  // namespace VectorUtilities

}  // namespace algebra

}  // namespace alba
