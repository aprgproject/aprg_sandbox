#include "TermUtilities.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Factorization/FactorizationOfExpression.hpp>
#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Retrieval/FirstCoefficientRetriever.hpp>
#include <Algebra/Retrieval/NumberOfTermsRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

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

bool isRadicalTerm(Term const& term)
{
    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(term));
    return termRaiseToANumber.isRadical();
}

AlbaNumber getConstantFactor(Term const& term)
{
    AlbaNumber result(1);
    if(term.isConstant())
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

Term negateTerm(Term const& term)
{
    Term negatedTerm(createExpressionIfPossible({term, Term("*"), Term(-1)}));
    negatedTerm.simplify();
    return negatedTerm;
}

}

}
