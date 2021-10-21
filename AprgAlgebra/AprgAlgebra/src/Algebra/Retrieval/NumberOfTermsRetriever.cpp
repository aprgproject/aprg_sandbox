#include "NumberOfTermsRetriever.hpp"

namespace alba
{

namespace algebra
{

NumberOfTermsRetriever::NumberOfTermsRetriever()
{
    m_savedData = 0U;
}

void NumberOfTermsRetriever::retrieveFromConstant(Constant const&)
{
    m_savedData++;
}

void NumberOfTermsRetriever::retrieveFromVariable(Variable const&)
{
    m_savedData++;
}

void NumberOfTermsRetriever::retrieveFromMonomial(Monomial const&)
{
    m_savedData++;
}

void NumberOfTermsRetriever::retrieveFromExpression(Expression const& expression)
{
    m_savedData++;
    BaseNumberOfTermsRetriever::retrieveFromExpression(expression);
}

void NumberOfTermsRetriever::retrieveFromFunction(Function const& functionObject)
{
    m_savedData++;
    BaseNumberOfTermsRetriever::retrieveFromFunction(functionObject);
}

}

}
