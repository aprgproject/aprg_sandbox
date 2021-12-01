#include "MathVectorOfTermsUtilities.hpp"

#include <Algebra/Geometry/ThreeDimensions/ThreeDimensionsUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Utilities/KnownNames.hpp>
#include <Math/Vector/AlbaMathVectorUtilities.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

namespace VectorUtilities
{

void simplifyForTermInVector(Term & term)
{
    Simplification::simplifyTermByFactoringToNonDoubleFactorsToACommonDenominator(term);
    term.clearAllInnerSimplifiedFlags();
    term.simplify();
}

SegregateTermsByConditionInAdditionAndSubtractionRetriever getRetrieverForComparison(
        Term const& termToAnalyze,
        std::string const& coordinateVariableName,
        stringHelper::strings const& processedCoordinates)
{
    SegregateTermsByConditionInAdditionAndSubtractionRetriever::ConditionFunction condition = [&](Term const& term) -> bool
    {
        VariableNamesRetriever retriever;
        retriever.retrieveFromTerm(term);        VariableNamesSet const& names(retriever.getSavedData());
        bool isCurrentCoordinateFound = names.find(coordinateVariableName) != names.cend();
        bool isOneOfTheOtherPreviousCoordinatesFound(false);
        for(std::string const& processedCoordinate : processedCoordinates)
        {
            if(processedCoordinate != coordinateVariableName
                    && names.find(processedCoordinate) != names.cend())            {
                isOneOfTheOtherPreviousCoordinatesFound=true;
                break;
            }        }
        return isCurrentCoordinateFound && isOneOfTheOtherPreviousCoordinatesFound;
    };
    SegregateTermsByConditionInAdditionAndSubtractionRetriever retriever(condition);
    retriever.retrieveFromTerm(termToAnalyze);
    return retriever;
}

void retrieveTermWithAndWithoutCoordinates(
        Term & termWithoutCoordinates,
        Term & termWithMultipleCoordinates,
        Term const& coordinateGradient,
        std::string const& coordinateVariableName,
        stringHelper::strings const& allCoordinates)
{
    SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever retrieverWithAllCoordinates(allCoordinates);
    retrieverWithAllCoordinates.retrieveFromTerm(coordinateGradient);
    termWithoutCoordinates = retrieverWithAllCoordinates.getRemainingTerm();
    termWithMultipleCoordinates = retrieverWithAllCoordinates.getTermWithMultipleVariableNames();
    for(auto const& variableNameAndTermPair : retrieverWithAllCoordinates.getVariableNameToTermMap())
    {
        if(variableNameAndTermPair.first == coordinateVariableName)
        {
            termWithoutCoordinates += variableNameAndTermPair.second;
        }
        else
        {
            termWithMultipleCoordinates += variableNameAndTermPair.second;
        }
    }
}

bool isDivergenceOfCurlZero(
        MathVectorOfThreeTerms const& termVector,
        ArrayOfThreeStrings const& coordinateVariables){
    //This is always true
    return getDivergence(getCurl(termVector, coordinateVariables), coordinateVariables) == Term(0);
}
Term getDyOverDx(
        MathVectorOfTwoTerms const& termVector,
        string const& variableName)
{
    MathVectorOfTwoTerms derivative(differentiate(termVector, variableName));
    Term result(derivative.getValueAt(1)/derivative.getValueAt(0));
    result.simplify();
    return result;
}

Term getDirectionalDerivativeInTwoDimensions(
        Term const& term,
        ArrayOfTwoStrings const& coordinateVariables,
        AlbaAngle const& angleOfDirection)
{
    MathVectorOfTwoTerms gradient(getGradient(term, coordinateVariables));
    MathVectorOfTwoTerms unitDirection(
    {Term(::cos(angleOfDirection.getRadians())), Term(::sin(angleOfDirection.getRadians()))});
    Term result(getDotProduct(gradient, unitDirection));
    simplifyForTermInVector(result);
    return result;
}

Term getDirectionalDerivativeInThreeDimensions(
        Term const& term,
        ArrayOfThreeStrings const& coordinateVariables,
        MathVectorOfThreeAngles const& coordinateAngles)
{
    MathVectorOfThreeTerms gradient(getGradient(term, coordinateVariables));
    MathVectorOfThreeTerms unitDirection(
    {Term(::cos(coordinateAngles.getValueAt(0).getRadians())),
     Term(::cos(coordinateAngles.getValueAt(1).getRadians())),
     Term(::cos(coordinateAngles.getValueAt(2).getRadians()))});
    Term result(getDotProduct(gradient, unitDirection));
    simplifyForTermInVector(result);
    return result;
}

MathVectorOfThreeTerms getNormalOfASurfaceOnAPoint(
        Equation const& surface,
        ArrayOfThreeStrings const& coordinateVariables,
        MathVectorOfThreeNumbers const& point)
{
    using Values = typename MathVectorOfThreeTerms::ValuesInArray;
    Equation simplifiedSurface(surface);
    simplifiedSurface.simplify();
    MathVectorOfThreeTerms gradient(getGradient(simplifiedSurface.getLeftHandTerm(), coordinateVariables));
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(coordinateVariables.at(0), point.getValueAt(0));
    substitution.putVariableWithValue(coordinateVariables.at(1), point.getValueAt(1));
    substitution.putVariableWithValue(coordinateVariables.at(2), point.getValueAt(2));

    MathVectorOfThreeTerms result;
    Values const& values(gradient.getValues());
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term)
    {
        return substitution.performSubstitutionTo(term);
    });
    return result;
}

Equation getTangentPlaneOnAPointOfASurface(
        Equation const& surface,
        ArrayOfThreeStrings const& coordinateVariables,
        MathVectorOfThreeNumbers const& point)
{
    MathVectorOfThreeTerms normalOfASurface(getNormalOfASurfaceOnAPoint(surface, coordinateVariables, point));
    SubstitutionOfVariablesToTerms substitution;
    substitution.putVariableWithTerm(a, normalOfASurface.getValueAt(0));
    substitution.putVariableWithTerm(b, normalOfASurface.getValueAt(1));
    substitution.putVariableWithTerm(c, normalOfASurface.getValueAt(2));
    substitution.putVariableWithTerm(x0, Term(point.getValueAt(0)));
    substitution.putVariableWithTerm(y0, Term(point.getValueAt(1)));
    substitution.putVariableWithTerm(z0, Term(point.getValueAt(2)));

    Equation generalPlane(ThreeDimensions::getPlaneEquationWithPointCoordinates());
    return substitution.performSubstitutionTo(generalPlane);
}

Equations getPerpendicularLineOnAPointOfASurface(
        Equation const& surface,
        ArrayOfThreeStrings const& coordinateVariables,
        MathVectorOfThreeNumbers const& point)
{
    MathVectorOfThreeTerms normalOfASurface(getNormalOfASurfaceOnAPoint(surface, coordinateVariables, point));
    SubstitutionOfVariablesToTerms substitution;
    substitution.putVariableWithTerm(a, normalOfASurface.getValueAt(0));
    substitution.putVariableWithTerm(b, normalOfASurface.getValueAt(1));
    substitution.putVariableWithTerm(c, normalOfASurface.getValueAt(2));
    substitution.putVariableWithTerm(x0, Term(point.getValueAt(0)));
    substitution.putVariableWithTerm(y0, Term(point.getValueAt(1)));
    substitution.putVariableWithTerm(z0, Term(point.getValueAt(2)));

    Equations lineEquations(ThreeDimensions::getLineEquations());
    for(Equation & lineEquation : lineEquations)
    {
        lineEquation = substitution.performSubstitutionTo(lineEquation);
    }
    return lineEquations;
}

MathVectorOfThreeTerms getCurl(
        MathVectorOfThreeTerms const& termVector,
        ArrayOfThreeStrings const& coordinateVariables)
{
    Term const& a(termVector.getValueAt(0));
    Term const& b(termVector.getValueAt(1));
    Term const& c(termVector.getValueAt(2));
    Term x(getPartialDerivative(c, coordinateVariables.at(1)) - getPartialDerivative(b, coordinateVariables.at(2)));
    Term y(getPartialDerivative(a, coordinateVariables.at(2)) - getPartialDerivative(c, coordinateVariables.at(0)));
    Term z(getPartialDerivative(b, coordinateVariables.at(0)) - getPartialDerivative(a, coordinateVariables.at(1)));
    return MathVectorOfThreeTerms{x, y, z};
}

}

}

}
