#pragma once

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Retrieval/SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever.hpp>
#include <Algebra/Retrieval/SegregateTermsByConditionInAdditionAndSubtractionRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Vector/VectorTypes.hpp>
#include <Math/Angle/AlbaAngle.hpp>
#include <Math/Vector/AlbaMathVectorUtilities.hpp>

#include <algorithm>

namespace alba
{

namespace algebra
{

namespace VectorUtilities
{

void simplifyForTermInVector(Term & term);

bool isDivergenceOfCurlZero(MathVectorOfThreeTerms const& termVector, ArrayOfThreeStrings const& coordinateVariables);
Term getDyOverDx(MathVectorOfTwoTerms const& termVector, std::string const& variableName);
Term getDirectionalDerivativeInTwoDimensions(Term const& term, ArrayOfTwoStrings const& coordinateVariables, AlbaAngle const& angleOfDirection);
Term getDirectionalDerivativeInThreeDimensions(Term const& term, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeAngles const& coordinateAngles);
MathVectorOfThreeTerms getNormalOfASurfaceOnAPoint(Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);
Equation getTangentPlaneOnAPointOfASurface(Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);
Equations getPerpendicularLineOnAPointOfASurface(Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);
MathVectorOfThreeTerms getCurl(MathVectorOfThreeTerms const& termVector, ArrayOfThreeStrings const& coordinateVariables);

template <unsigned int SIZE>
void simplifyForTermVector(
        MathVectorOfTerms<SIZE> & termVector)
{
    for(Term & term : termVector.getValuesReference())
    {
        simplifyForTermInVector(term);
    }
}

template <unsigned int SIZE> bool isContinuousAt(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& value);
template <unsigned int SIZE> bool isDifferentiableAt(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& value);
template <unsigned int SIZE> bool areOriginalAndDerivativeVectorsOrthogonal( MathVectorOfTerms<SIZE> const& termVector);
Term getDyOverDx(MathVectorOfTwoTerms const& termVector, std::string const& variableName);
template <unsigned int SIZE> Term getLengthOfArcDerivative(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> Term getLengthOfArc(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> Term getLengthOfArcFromStartToEnd(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, Term const& lowerValueTerm, Term const& higherValueTerm);
template <unsigned int SIZE> Term getCurvature(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> Term getTermThatYieldsToThisGradient(MathVectorOfTerms<SIZE> const& gradient, ArrayOfStrings<SIZE> const& coordinateVariables);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getLimit(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& valueToApproach);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> differentiate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> integrate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getUnitTangentVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getUnitNormalVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getCurvatureVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getGradient( Term const& term, ArrayOfStrings<SIZE> const& coordinateVariables);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getDel(MathVectorOfTerms<SIZE> const& termVector, ArrayOfStrings<SIZE> const& coordinateVariables);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getDoubleDel(MathVectorOfTerms<SIZE> const& termVector, ArrayOfStrings<SIZE> const& coordinateVariables);


template <unsigned int SIZE>
bool isContinuousAt(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName,
        AlbaNumber const& value)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    Values const& values(termVector.getValues());
    return std::all_of(values.cbegin(), values.cend(), [&](Term const& term)
    {
        return isContinuousAt(term, variableName, value, LimitAtAValueApproachType::BothSides);
    });
}

template <unsigned int SIZE>
bool isDifferentiableAt(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName,
        AlbaNumber const& value)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    Values const& values(termVector.getValues());
    return std::all_of(values.cbegin(), values.cend(), [&](Term const& term)
    {
        return isDifferentiableAt(term, variableName, value);
    });
}

template <unsigned int SIZE>
bool areOriginalAndDerivativeVectorsOrthogonal(
        MathVectorOfTerms<SIZE> const& termVector)
{
    return termVector.getMagnitude().isConstant();
}

template <unsigned int SIZE>
Term getLengthOfArcDerivative(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    return differentiate(termVector, variableName).getMagnitude();
}

template <unsigned int SIZE>
Term getLengthOfArc(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    Integration integration(variableName);
    return integration.integrate(getLengthOfArcDerivative(termVector, variableName));
}

template <unsigned int SIZE>
Term getLengthOfArcFromStartToEnd(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    return evaluateTermsAndGetDifference(
                getLengthOfArc(termVector, variableName),
                variableName,
                lowerValueTerm,
                higherValueTerm);
}

template <unsigned int SIZE>
Term getCurvature(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    MathVectorOfTerms<SIZE> curvatureVector(getCurvatureVector(termVector, variableName));
    Term result(curvatureVector.getMagnitude());
    simplifyForTermInVector(result);
    return result;
}

template <unsigned int SIZE>
Term getTermThatYieldsToThisGradient(
        MathVectorOfTerms<SIZE> const& gradient,
        ArrayOfStrings<SIZE> const& coordinateVariables,
        bool & isExactDifferential)
{
    Term result;
    bool isFirst(true);
    isExactDifferential = true;
    Term resultPartWithMultipleCoordinates;
    stringHelper::strings processedCoordinates;
    for(unsigned int i=0; isExactDifferential && i<SIZE; i++)
    {
        std::string const& coordinateVariableName(coordinateVariables.at(i));
        SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever retrieverWithAllCoordinates(
                    stringHelper::strings(coordinateVariables.cbegin(), coordinateVariables.cend()));
        retrieverWithAllCoordinates.retrieveFromTerm(gradient.getValueAt(i));
        Term termWithoutCoordinates(retrieverWithAllCoordinates.getRemainingTerm());
        Term termWithMultipleCoordinates(retrieverWithAllCoordinates.getTermWithMultipleVariableNames());
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
        processedCoordinates.emplace_back(coordinateVariableName);
        Integration integration(coordinateVariableName);
        if(isFirst)
        {
            resultPartWithMultipleCoordinates = integration.integrate(termWithMultipleCoordinates);
            isFirst = false;
        }
        else
        {
            Term currentPartWithMultipleCoordinates(integration.integrate(termWithMultipleCoordinates));
            SegregateTermsByConditionInAdditionAndSubtractionRetriever::ConditionFunction condition = [&](Term const& term) -> bool
            {
                VariableNamesRetriever retriever;
                retriever.retrieveFromTerm(term);
                VariableNamesSet const& names(retriever.getSavedData());
                bool isCurrentCoordinateFound = names.find(coordinateVariableName) != names.cend();
                bool isOneOfTheOtherPreviousCoordinatesFound(false);
                for(std::string const& processedCoordinate : processedCoordinates)
                {
                    if(processedCoordinate != coordinateVariableName
                            && names.find(processedCoordinate) != names.cend())
                    {
                        isOneOfTheOtherPreviousCoordinatesFound=true;
                        break;
                    }
                }
                return isCurrentCoordinateFound && isOneOfTheOtherPreviousCoordinatesFound;
            };
            SegregateTermsByConditionInAdditionAndSubtractionRetriever retriever1(condition);
            SegregateTermsByConditionInAdditionAndSubtractionRetriever retriever2(condition);
            retriever1.retrieveFromTerm(resultPartWithMultipleCoordinates);
            retriever2.retrieveFromTerm(currentPartWithMultipleCoordinates);
            isExactDifferential = retriever1.getTermWithCondition() == retriever2.getTermWithCondition();
            if(isExactDifferential)
            {
                resultPartWithMultipleCoordinates = retriever1.getTermWithCondition() + retriever1.getTermWithoutCondition() + retriever2.getTermWithoutCondition();
            }
            else
            {
                break;
            }
        }
        result += integration.integrate(termWithoutCoordinates);
    }
    if(isExactDifferential)
    {
        result += resultPartWithMultipleCoordinates;;
    }
    else
    {
        result.clear();
    }
    simplifyForTermInVector(result);
    return result;
}

template <unsigned int SIZE>
Term getPotentialFunctionForVectorFieldGradient(
        MathVectorOfTerms<SIZE> const& gradient,
        ArrayOfStrings<SIZE> const& coordinateVariables,
        bool & isConservative)
{
    return getTermThatYieldsToThisGradient(gradient, coordinateVariables, isConservative);
}

template <unsigned int SIZE>
Term getDivergence(
        MathVectorOfTerms<SIZE> const& termVector,
        ArrayOfStrings<SIZE> const& coordinateVariables)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> del(getDel(termVector, coordinateVariables));
    Values const& values(del.getValues());
    return std::accumulate(values.cbegin(), values.cend(), Term(0), std::plus<Term>());
}

template <unsigned int SIZE>
Term getLaplaceTerm(
        MathVectorOfTerms<SIZE> const& termVector,
        ArrayOfStrings<SIZE> const& coordinateVariables)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> del(getDoubleDel(termVector, coordinateVariables));
    Values const& values(del.getValues());
    return std::accumulate(values.cbegin(), values.cend(), Term(0), std::plus<Term>());
}

template <unsigned int SIZE>
Term getLineIntegral(
        MathVectorOfTerms<SIZE> const& vectorField,
        ArrayOfStrings<SIZE> const& coordinateVariables,
        MathVectorOfTerms<SIZE> const& linePath,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    SubstitutionOfVariablesToTerms substitution;
    Differentiation differentiation(variableName);
    for(unsigned int i=0; i<SIZE; i++)
    {
        substitution.putVariableWithTerm(coordinateVariables.at(i), linePath.getValueAt(i));
        DerivativeVariableName derivativeVariableName(1, "", coordinateVariables.at(i));
        substitution.putVariableWithTerm(derivativeVariableName.getNameInLeibnizNotation(), differentiation.differentiate(linePath.getValueAt(i)));
    }
    MathVectorOfTerms<SIZE> linePathInVectorField;
    for(unsigned int i=0; i<SIZE; i++)
    {
        linePathInVectorField.getValueReferenceAt(i) = substitution.performSubstitutionTo(vectorField.getValueAt(i));
    }
    MathVectorOfTerms<SIZE> differentiatedLinePath(differentiate(linePath, variableName));
    Term termIntegrate(getDotProduct(linePathInVectorField, differentiatedLinePath));
    Integration integration(variableName);
    return integration.integrateAtDefiniteTerms(termIntegrate, lowerValueTerm, higherValueTerm);
}

template <unsigned int SIZE>
Term getLineIntegralIndependentOfPath(
        MathVectorOfTerms<SIZE> const& vectorField,
        ArrayOfStrings<SIZE> const& coordinateVariables,
        MathVectorOfNumbers<SIZE> const& lowerValues,
        MathVectorOfNumbers<SIZE> const& higherValues)
{
    bool isConservative(false);
    Term potential(getPotentialFunctionForVectorFieldGradient(vectorField, coordinateVariables, isConservative));

    Term result;
    if(isConservative)
    {
        SubstitutionOfVariablesToValues substitutionForLowerValues;
        SubstitutionOfVariablesToValues substitutionForHigherValues;
        for(unsigned int i=0; i<SIZE; i++)
        {
            substitutionForLowerValues.putVariableWithValue(coordinateVariables.at(i), lowerValues.getValueAt(i));
            substitutionForHigherValues.putVariableWithValue(coordinateVariables.at(i), higherValues.getValueAt(i));
        }
        result = substitutionForHigherValues.performSubstitutionTo(potential) - substitutionForLowerValues.performSubstitutionTo(potential);
    }
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getLimit(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName,
        AlbaNumber const& valueToApproach)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Values const& values(termVector.getValues());
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term)
    {
        return getLimit(term, variableName, valueToApproach);
    });
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> differentiate(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Differentiation differentiation(variableName);
    Values const& values(termVector.getValues());
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term)
    {
        return differentiation.differentiate(term);
    });
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> differentiateMultipleTimes(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName,
        unsigned int const numberOfTimes)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Differentiation differentiation(variableName);
    Values const& values(termVector.getValues());
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term)
    {
        return differentiation.differentiateMultipleTimes(term, numberOfTimes);
    });
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> integrate(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Integration integration(variableName);
    Values const& values(termVector.getValues());
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term)
    {
        return integration.integrate(term);
    });
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getUnitTangentVector(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    MathVectorOfTerms<SIZE> result(differentiate(termVector, variableName));
    result /= result.getMagnitude();
    simplifyForTermVector(result);
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getUnitNormalVector(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    MathVectorOfTerms<SIZE> result(differentiate(getUnitTangentVector(termVector, variableName), variableName));
    result /= result.getMagnitude();
    simplifyForTermVector(result);
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getCurvatureVector(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    MathVectorOfTerms<SIZE> derivativeOfTermVector(differentiate(termVector, variableName));
    MathVectorOfTerms<SIZE> result(differentiate(getUnitTangentVector(termVector, variableName), variableName));
    result /= derivativeOfTermVector.getMagnitude();
    simplifyForTermVector(result);
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getGradient(
        Term const& term,
        ArrayOfStrings<SIZE> const& coordinateVariables)
{
    MathVectorOfTerms<SIZE> result;
    for(unsigned int i=0; i<SIZE; i++)
    {
        result.getValueReferenceAt(i) = getPartialDerivative(term, coordinateVariables.at(i));
    }
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getDel(
        MathVectorOfTerms<SIZE> const& termVector,
        ArrayOfStrings<SIZE> const& coordinateVariables)
{
    MathVectorOfTerms<SIZE> result(termVector);
    for(unsigned int i=0; i<SIZE; i++)
    {
        result.getValueReferenceAt(i) = getPartialDerivative(termVector.getValueAt(i), coordinateVariables.at(i));
    }
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getDoubleDel(
        MathVectorOfTerms<SIZE> const& termVector,
        ArrayOfStrings<SIZE> const& coordinateVariables)
{
    MathVectorOfTerms<SIZE> result;
    for(unsigned int i=0; i<SIZE; i++)
    {
        result.getValueReferenceAt(i) = getPartialDerivative(getPartialDerivative(termVector.getValueAt(i), coordinateVariables.at(i)), coordinateVariables.at(i));
    }
    return result;
}

}

}

}
