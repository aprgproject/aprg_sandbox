#include "AxisRotation.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>

using namespace std;

namespace alba {

namespace algebra {

AxisRotation::AxisRotation(string const& xName, string const& yName, double const angle, bool const doRotationBack) {
    initializeSubstitution(xName, yName, angle, doRotationBack);
}

Term AxisRotation::rotateTermByAngle(Term const& term) { return m_substitution.performSubstitutionTo(term); }

Term AxisRotation::rotateConstantByAngle(Constant const& constant) {
    return m_substitution.performSubstitutionTo(constant);
}

Term AxisRotation::rotateVariableByAngle(Variable const& variable) {
    return m_substitution.performSubstitutionTo(variable);
}

Term AxisRotation::rotateMonomialByAngle(Monomial const& monomial) {
    return m_substitution.performSubstitutionTo(monomial);
}

Term AxisRotation::rotatePolynomialByAngle(Polynomial const& polynomial) {
    return m_substitution.performSubstitutionTo(polynomial);
}

Term AxisRotation::rotateExpressionByAngle(Expression const& expression) {
    return m_substitution.performSubstitutionTo(expression);
}

Term AxisRotation::rotateFunctionByAngle(Function const& functionObject) {
    return m_substitution.performSubstitutionTo(functionObject);
}

void AxisRotation::initializeSubstitution(
    string const& xName, string const& yName, double const angle, bool const doRotationBack) {
    Term oldX(xName);
    Term oldY(yName);
    Term sinTheta(sin(angle));
    Term cosTheta(cos(angle));
    Term newX, newY;
    if (doRotationBack) {
        newX = oldX * cosTheta - oldY * sinTheta;
        newY = oldX * sinTheta + oldY * cosTheta;
    } else {
        newX = oldX * cosTheta + oldY * sinTheta;
        newY = -oldX * sinTheta + oldY * cosTheta;
    }
    m_substitution.putVariableWithTerm(xName, newX);
    m_substitution.putVariableWithTerm(yName, newY);
}

}  // namespace algebra

}  // namespace alba
