#include "Function.hpp"

#include <Algebra/Simplification/SimplificationOfFunction.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

using namespace alba::algebra::Simplification;
using namespace std;

namespace alba {

namespace algebra {

Function::Function()
    : m_functionName(), m_inputTermPointer(make_unique<Term>()), m_evaluationFunction(), m_isSimplified(false) {}

Function::Function(string const& functionName, BaseTerm const& baseTerm, EvaluationFunction const& evaluationFunction)
    : m_functionName(functionName),
      m_inputTermPointer(createBasePointer(baseTerm)),
      m_evaluationFunction(evaluationFunction),
      m_isSimplified(false) {}

Function::Function(string const& functionName, BaseTerm&& baseTerm, EvaluationFunction const& evaluationFunction)
    : m_functionName(functionName),
      m_inputTermPointer(createBasePointer(baseTerm)),
      m_evaluationFunction(evaluationFunction),
      m_isSimplified(false) {}

Function::Function(Function const& functionObject)
    : m_functionName(functionObject.m_functionName),
      m_inputTermPointer(duplicateUniquePointer(functionObject.m_inputTermPointer)),
      m_evaluationFunction(functionObject.m_evaluationFunction),
      m_isSimplified(functionObject.m_isSimplified) {}

Function& Function::operator=(Function const& functionObject) {
    m_functionName = functionObject.m_functionName;
    m_inputTermPointer = duplicateUniquePointer(functionObject.m_inputTermPointer);
    m_evaluationFunction = functionObject.m_evaluationFunction;
    m_isSimplified = functionObject.m_isSimplified;
    return *this;
}

bool Function::operator==(Function const& second) const {
    return m_functionName == second.m_functionName && getTermConstReferenceFromBaseTerm(getInputTerm()) ==
                                                          getTermConstReferenceFromBaseTerm(second.getInputTerm());
}

bool Function::operator!=(Function const& second) const { return !(operator==(second)); }

bool Function::operator<(Function const& second) const {
    bool result(false);
    if (m_functionName == second.m_functionName) {
        return getTermConstReferenceFromBaseTerm(getInputTerm()) <
               getTermConstReferenceFromBaseTerm(second.getInputTerm());
    } else {
        result = m_functionName < second.m_functionName;
    }
    return result;
}

bool Function::isSimplified() const { return m_isSimplified; }

string Function::getFunctionName() const { return m_functionName; }

string Function::getDebugString() const {
    return m_functionName + "(" + getTermConstReferenceFromBaseTerm(getInputTerm()).getDebugString() + ")";
}

AlbaNumber Function::performFunctionAndReturnResultIfPossible() const {
    AlbaNumber result;
    Term const& term(getTermConstReferenceFromBaseTerm(getInputTerm()));
    if (term.isConstant()) {
        result = m_evaluationFunction(term.getAsNumber());
    }
    return result;
}

BaseTerm const& Function::getInputTerm() const {
    return getBaseTermConstReferenceFromUniquePointer(m_inputTermPointer);
}

Function::EvaluationFunction const& Function::getEvaluationFunction() const { return m_evaluationFunction; }

BaseTerm& Function::getInputTermReference() {
    clearSimplifiedFlag();
    return getBaseTermReferenceFromUniquePointer(m_inputTermPointer);
}

void Function::simplify() {
    if (!m_isSimplified) {
        SimplificationOfFunction simplification(*this);
        simplification.simplify();
        *this = simplification.getFunction();
        setAsSimplified();
    }
}

void Function::setAsSimplified() { m_isSimplified = true; }

void Function::clearSimplifiedFlag() { m_isSimplified = false; }

void Function::clearAllInnerSimplifiedFlags() {
    Term& term(getTermReferenceFromUniquePointer(m_inputTermPointer));
    term.clearAllInnerSimplifiedFlags();
    clearSimplifiedFlag();
}

ostream& operator<<(ostream& out, Function const& functionObject) {
    out << functionObject.m_functionName << "("
        << getTermConstReferenceFromUniquePointer(functionObject.m_inputTermPointer) << ")";
    return out;
}

}  // namespace algebra

}  // namespace alba
