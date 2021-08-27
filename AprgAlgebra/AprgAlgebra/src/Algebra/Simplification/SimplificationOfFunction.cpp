#include "SimplificationOfFunction.hpp"

#include <Algebra/Retrieval/FirstCoefficientRetriever.hpp>
#include <Algebra/Retrieval/NumberOfTermsRetriever.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>


using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

SimplificationOfFunction::SimplificationOfFunction(
        Function const& functionObject)
    : m_function(functionObject)
{}

Function SimplificationOfFunction::getFunction() const
{
    return m_function;
}

void SimplificationOfFunction::simplify()
{
    Term & inputTermReference(getTermReferenceFromBaseTerm(m_function.getInputTermReference()));
    inputTermReference.simplify();

    if("abs" == m_function.getFunctionName())
    {
        Term inputTermNegated(createExpressionIfPossible({inputTermReference, Term("*"), Term(-1)}));
        inputTermNegated.simplify();

        if(isNegatedTermSimpler(inputTermReference, inputTermNegated))
        {
            inputTermReference = inputTermNegated;
        }
    }
}

bool SimplificationOfFunction::isNegatedTermSimpler(
        Term const& term,
        Term const& negatedTerm) const
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

}

}

}
