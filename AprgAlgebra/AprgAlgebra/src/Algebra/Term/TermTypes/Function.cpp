#include "Function.hpp"

#include <Algebra/Simplification/SimplificationOfFunction.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

using namespace alba::algebra::Simplification;
using namespace std;

namespace alba
{

namespace algebra
{

Function::Function()
    : m_functionName()
    , m_inputTermPointer(make_unique<Term>())
    , m_evaluationFunction()
    , m_isSimplified(false)
{}

Function::Function(Function const& functionObject)
    : m_functionName(functionObject.m_functionName)
    , m_inputTermPointer(make_unique<Term>(getTermConstReferenceFromUniquePointer(functionObject.m_inputTermPointer)))
    , m_evaluationFunction(functionObject.m_evaluationFunction)
    , m_isSimplified(functionObject.isSimplified())
{}

Function::Function(
        string const& functionName,
        BaseTerm const& baseTerm,
        EvaluationFunction const& evaluationFunction)
    : m_functionName(functionName)
    , m_inputTermPointer(make_unique<Term>(getTermConstReferenceFromBaseTerm(baseTerm)))
    , m_evaluationFunction(evaluationFunction)
    , m_isSimplified(getTermConstReferenceFromBaseTerm(baseTerm).isSimplified())
{}

Function& Function::operator=(Function const& functionObject)
{
    m_functionName = functionObject.m_functionName;
    m_inputTermPointer= make_unique<Term>(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    m_evaluationFunction = functionObject.m_evaluationFunction;
    clearSimplifiedFlag();
    return *this;
}

bool Function::operator==(Function const& second) const
{
    return m_functionName == second.m_functionName
            && getTermConstReferenceFromBaseTerm(getInputTermConstReference())
            == getTermConstReferenceFromBaseTerm(second.getInputTermConstReference());
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
        return getTermConstReferenceFromBaseTerm(getInputTermConstReference())
                < getTermConstReferenceFromBaseTerm(second.getInputTermConstReference());
    }
    else
    {
        result = m_functionName < second.m_functionName;
    }
    return result;
}

bool Function::isSimplified() const
{
    return m_isSimplified;
}

string Function::getFunctionName() const
{
    return m_functionName;
}

string Function::getDebugString() const
{
    return m_functionName + "(" + getTermConstReferenceFromBaseTerm(getInputTermConstReference()).getDebugString() + ")";}

AlbaNumber Function::performFunctionAndReturnResultIfPossible() const
{
    AlbaNumber result;
    Term const& term(getTermConstReferenceFromBaseTerm(getInputTermConstReference()));
    if(term.isConstant())
    {
        result = m_evaluationFunction(term.getConstantValueConstReference());
    }
    return result;
}

BaseTerm const& Function::getInputTermConstReference() const
{
    return getBaseTermConstReferenceFromUniquePointer(m_inputTermPointer);
}

Function::EvaluationFunction const& Function::getEvaluationFunction() const
{
    return m_evaluationFunction;
}

BaseTerm & Function::getInputTermReference()
{
    clearSimplifiedFlag();
    return getBaseTermReferenceFromUniquePointer(m_inputTermPointer);
}

void Function::simplify()
{
    if(!m_isSimplified)
    {
        SimplificationOfFunction simplification(*this);
        simplification.simplify();
        *this = simplification.getFunction();
        setAsSimplified();
    }
}

void Function::setAsSimplified()
{
    m_isSimplified = true;
}

void Function::clearSimplifiedFlag()
{
    m_isSimplified = false;
}

void Function::clearAllInnerSimplifiedFlags()
{
    Term & term(getTermReferenceFromUniquePointer(m_inputTermPointer));
    term.clearAllInnerSimplifiedFlags();
    clearSimplifiedFlag();
}

ostream & operator<<(ostream & out, Function const& functionObject)
{
    out << functionObject.m_functionName
        << "(" << getTermConstReferenceFromUniquePointer(functionObject.m_inputTermPointer) << ")";
    return out;
}
}

}
