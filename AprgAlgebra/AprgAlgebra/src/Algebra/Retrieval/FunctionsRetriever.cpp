#include "FunctionsRetriever.hpp"

namespace alba
{

namespace algebra
{

FunctionsRetriever::FunctionsRetriever(
        FunctionCondition const& isFunctionIncluded)
    : m_isFunctionIncluded(isFunctionIncluded)
{}

void FunctionsRetriever::retrieveFromConstant(Constant const& )
{
    // Do nothing
}

void FunctionsRetriever::retrieveFromVariable(Variable const&)
{
    // Do nothing
}

void FunctionsRetriever::retrieveFromMonomial(Monomial const&)
{
    // Do nothing
}

void FunctionsRetriever::retrieveFromPolynomial(Polynomial const&)
{
    // Do nothing
}

void FunctionsRetriever::retrieveFromFunction(Function const& functionObject)
{
    if(m_isFunctionIncluded(functionObject))
    {
        m_savedData.emplace(functionObject);
    }
}

}

}
