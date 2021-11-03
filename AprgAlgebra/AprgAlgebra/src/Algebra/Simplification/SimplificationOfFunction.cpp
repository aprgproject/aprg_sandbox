#include "SimplificationOfFunction.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

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
        if(isANegativeTerm(inputTermReference))
        {
            inputTermReference = negateTerm(inputTermReference);
        }
    }
}

}

}

}
