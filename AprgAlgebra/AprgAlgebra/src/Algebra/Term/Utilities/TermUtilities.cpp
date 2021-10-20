#include "TermUtilities.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Factorization/FactorizationOfExpression.hpp>
#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Retrieval/FirstCoefficientRetriever.hpp>
#include <Algebra/Retrieval/NumberOfTermsRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>

using namespace alba::algebra::Factorization;
using namespace std;
namespace alba
{
namespace algebra
{

bool isNegatedTermSimpler(Term const& term, Term const& negatedTerm)
{
    FirstCoefficientRetriever firstCoefficientRetrieverForTerm;
    NumberOfTermsRetriever numberOfTermsRetrieverForTerm;
    NumberOfTermsRetriever numberOfTermsRetrieverForNegatedTerm;
    firstCoefficientRetrieverForTerm.retrieveFromTerm(term);
    numberOfTermsRetrieverForTerm.retrieveFromTerm(term);
    numberOfTermsRetrieverForNegatedTerm.retrieveFromTerm(negatedTerm);

    return numberOfTermsRetrieverForTerm.getSavedData() > numberOfTermsRetrieverForNegatedTerm.getSavedData()
            || firstCoefficientRetrieverForTerm.getSavedData() < 0;
}

bool isNonEmptyOrNonOperatorType(Term const& term)
{
    TermType termType(term.getTermType());
    return TermType::Empty != termType && TermType::Operator != termType;
}

bool isNonEmptyOrNonOperatorOrNonExpressionType(Term const& term)
{
    TermType termType(term.getTermType());
    return TermType::Empty != termType
            && TermType::Operator != termType
            && TermType::Expression != termType;
}

bool isARadicalTerm(Term const& term)
{
    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(term));
    return termRaiseToANumber.isRadical();
}

bool isANegativeTerm(Term const& term)
{
    bool result(false);
    if(term.isConstant())
    {
        result = isANegativeConstant(term.getConstantConstReference());
    }
    else if(term.isMonomial())
    {
        result = isANegativeMonomial(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        result = isANegativePolynomial(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        result = isANegativeExpression(term.getExpressionConstReference());
    }
    return result;
}

bool isANegativeConstant(Constant const& constant)
{
    return constant.getNumberConstReference() < 0;
}

bool isANegativeMonomial(Monomial const& monomial)
{
    return monomial.getConstantConstReference() < 0;
}

bool isANegativePolynomial(Polynomial const& polynomial)
{
    bool result(false);
    Monomials const& monomials(polynomial.getMonomialsConstReference());
    if(!monomials.empty())
    {
        result = monomials.front().getConstantConstReference() < 0;
    }
    return result;
}

bool isANegativeExpression(Expression const& expression)
{
    bool result(false);
    TermsWithDetails termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        if(!termsWithDetails.empty())
        {            Term const& firstTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.front().baseTermSharedPointer));
            result = isANegativeTerm(firstTerm);
        }
    }    else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        bool isNegative(false);
        for(TermWithDetails const& termWithDetails : termsWithDetails)
        {
            Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
            isNegative = isNegative ^ isANegativeTerm(term);
        }
        result = isNegative;
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        result = false;
    }
    return result;
}
AlbaNumber getConstantFactor(Term const& term)
{
    AlbaNumber result(1);    if(term.isConstant())
    {
        result = term.getConstantValueConstReference();
    }
    else if(term.isMonomial())
    {
        result = term.getMonomialConstReference().getConstantConstReference();
    }
    else if(term.isPolynomial())
    {
        Polynomials factors(factorizeCommonMonomial(term.getPolynomialConstReference()));
        for(Polynomial const& factor : factors)
        {
            if(factor.isOneMonomial())
            {
                result *= factor.getFirstMonomial().getConstantConstReference();
            }
        }
    }
    return result;
}

AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        string const& variableName,
        Term const& term)
{
    AlbaNumberPairs result;
    SubstitutionOfVariablesToValues substitution;
    for(AlbaNumber const& number : numbers)
    {
        substitution.putVariableWithValue(variableName, number);
        Term substituteTerm(substitution.performSubstitutionTo(term));
        if(substituteTerm.isConstant())
        {
            result.emplace_back(number, substituteTerm.getConstantValueConstReference());
        }
    }
    return result;
}

Term convertPositiveTermIfNegative(Term const& term)
{
    Term result;
    if(isANegativeTerm(term))
    {
        result = negateTerm(term);
    }
    else
    {
        result = term;
    }
    return result;
}

Term negateTerm(Term const& term)
{
    return term*Term(-1);
}

Term invertTerm(Term const& term, string const& variableName)
{
    string newVariableName(createVariableNameForSubstitution(term));
    Equation equationToIsolate(Term(newVariableName), "=", term);
    IsolationOfOneVariableOnEqualityEquation isolation(equationToIsolate);
    SubstitutionOfVariablesToTerms substitution{{newVariableName, Term(variableName)}};
    return substitution.performSubstitutionTo(isolation.getTermByIsolatingVariable(variableName));
}

Expression negateExpression(Expression const& expression)
{
    Expression negatedExpression(expression);    negatedExpression.putTermWithMultiplicationIfNeeded(Term(-1));
    negatedExpression.simplify();
    return negatedExpression;
}
}

}
