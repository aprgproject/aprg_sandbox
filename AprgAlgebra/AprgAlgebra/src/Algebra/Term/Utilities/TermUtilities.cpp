#include "TermUtilities.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Retrieval/FirstCoefficientRetriever.hpp>
#include <Algebra/Retrieval/NumberOfTermsRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

using namespace std;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

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

}

}
