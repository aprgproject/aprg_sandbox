#include "Function.hpp"

#include <Equation/Term/Term.hpp>

using namespace std;

namespace alba
{

namespace equation
{

Function::Function()
{}

Function::Function(
        string const& functionName,
        Expression const& inputExpression,
        FunctionToPerform const& functionToPerform)
    : m_functionName(functionName)
    , m_inputExpression(inputExpression)
    , m_functionToPerform(functionToPerform)
{}

bool Function::operator==(Function const& second) const
{
    return m_functionName == second.m_functionName
            && m_inputExpression==second.m_inputExpression;
}

bool Function::operator!=(Function const& second) const
{
    return !(operator==(second));
}

bool Function::operator<(Function const& second) const
{
    bool result(false);
    if(m_functionName == second.m_functionName)
    {
        return m_inputExpression < second.m_inputExpression;
    }
    else
    {
        result = m_functionName < second.m_functionName;
    }
    return result;
}

bool Function::isInputExpressionAConstant() const
{
    bool result(false);
    if(m_inputExpression.containsOnlyOneTerm())
    {
        Term const& term = dynamic_cast<Term const&>(m_inputExpression.getFirstTermConstReference());
        result = term.isConstant();    }
    return result;
}

string Function::getFunctionName() const
{
    return m_functionName;
}

string Function::getDisplayableString() const
{
    return m_functionName + m_inputExpression.getDisplayableString();
}

string Function::getDebugString() const
{
    return m_functionName + m_inputExpression.getDebugString();
}

Constant Function::performFunctionAndReturnResultIfPossible() const
{
    Constant result;
    if(isInputExpressionAConstant())
    {
        Term const& term = dynamic_cast<Term const&>(m_inputExpression.getFirstTermConstReference());
        result = m_functionToPerform(term.getConstantConstReference());
    }
    return result;
}

Expression const& Function::getInputExpressionConstReference() const
{
    return m_inputExpression;
}

Expression & Function::getInputExpressionReference()
{
    return m_inputExpression;
}

void Function::simplify()
{
    m_inputExpression.simplify();}

ostream & operator<<(ostream & out, Function const& functionAsParameter)
{
    out << functionAsParameter.getDisplayableString();
    return out;
}

}

}
