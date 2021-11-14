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
    , m_functionToPerform()
    , m_isSimplified(false)
{}

Function::Function(Function const& functionObject)    : m_functionName(functionObject.m_functionName)
    , m_inputTermPointer(make_unique<Term>(getTermConstReferenceFromUniquePointer(functionObject.m_inputTermPointer)))
    , m_functionToPerform(functionObject.m_functionToPerform)
    , m_isSimplified(false)
{}

Function::Function(        string const& functionName,
        BaseTerm const& baseTerm,
        FunctionToPerform const& functionToPerform)
    : m_functionName(functionName)
    , m_inputTermPointer(make_unique<Term>(getTermConstReferenceFromBaseTerm(baseTerm)))
    , m_functionToPerform(functionToPerform)
    , m_isSimplified(false)
{}

Function& Function::operator=(Function const& functionObject){
    m_functionName = functionObject.m_functionName;
    m_inputTermPointer= make_unique<Term>(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    m_functionToPerform = functionObject.m_functionToPerform;
    clearInternalFlags();
    return *this;
}
bool Function::operator==(Function const& second) const
{
    return m_functionName == second.m_functionName            && getTermConstReferenceFromBaseTerm(getInputTermConstReference())
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

string Function::getFunctionName() const
{
    return m_functionName;
}

string Function::getDisplayableString() const
{
    return m_functionName + "(" + getTermConstReferenceFromBaseTerm(getInputTermConstReference()).getDisplayableString() + ")";
}

string Function::getDebugString() const
{
    return m_functionName + "(" + getTermConstReferenceFromBaseTerm(getInputTermConstReference()).getDebugString() + ")";
}

AlbaNumber Function::performFunctionAndReturnResultIfPossible() const
{
    AlbaNumber result;
    Term const& term(getTermConstReferenceFromBaseTerm(getInputTermConstReference()));
    if(term.isConstant())
    {
        result = m_functionToPerform(term.getConstantValueConstReference());
    }
    return result;
}

BaseTerm const& Function::getInputTermConstReference() const
{
    return getBaseTermConstReferenceFromUniquePointer(m_inputTermPointer);
}

Function::FunctionToPerform const& Function::getFunctionToPerform() const
{
    return m_functionToPerform;
}

BaseTerm & Function::getInputTermReference()
{
    clearInternalFlags();
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

void Function::clearInternalFlags()
{
    m_isSimplified = false;
}

ostream & operator<<(ostream & out, Function const& functionObject)
{
    out << functionObject.getDisplayableString();    return out;
}

}
}
