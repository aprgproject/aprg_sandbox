#include "FunctionsRetriever.hpp"

namespace alba
{

namespace algebra
{

FunctionsRetriever::FunctionsRetriever(
        FunctionCondition const& isFunctionIncluded)
    : m_isFunctionIncluded(isFunctionIncluded)
{}

void FunctionsRetriever::retrieveFromPolynomial(Polynomial const&)
{}

void FunctionsRetriever::retrieveFromFunction(Function const& functionObject)
{
    if(m_isFunctionIncluded(functionObject))
    {
        m_savedData.emplace(functionObject);
    }
}

}

}
