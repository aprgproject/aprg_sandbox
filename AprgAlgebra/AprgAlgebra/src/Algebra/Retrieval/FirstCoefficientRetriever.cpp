#include "FirstCoefficientRetriever.hpp"

namespace alba {

namespace algebra {

FirstCoefficientRetriever::FirstCoefficientRetriever() : m_isValueSet(false) {}

AlbaNumber const& FirstCoefficientRetriever::getFirstCoefficient() const { return m_firstCoefficient; }

void FirstCoefficientRetriever::retrieveFromEquations(Equations const& equations) {
    if (!m_isValueSet) {
        BaseRetriever::retrieveFromEquations(equations);
    }
}

void FirstCoefficientRetriever::retrieveFromEquation(Equation const& equation) {
    if (!m_isValueSet) {
        BaseRetriever::retrieveFromEquation(equation);
    }
}

void FirstCoefficientRetriever::retrieveFromTerm(Term const& term) {
    if (!m_isValueSet) {
        BaseRetriever::retrieveFromTerm(term);
    }
}
void FirstCoefficientRetriever::retrieveFromConstant(Constant const& constant) {
    if (!m_isValueSet) {
        m_firstCoefficient = constant.getNumber();
        m_isValueSet = true;
    }
}

void FirstCoefficientRetriever::retrieveFromVariable(Variable const&) {
    if (!m_isValueSet) {
        m_firstCoefficient = 1;
        m_isValueSet = true;
    }
}

void FirstCoefficientRetriever::retrieveFromMonomial(Monomial const& monomial) {
    if (!m_isValueSet) {
        m_firstCoefficient = monomial.getCoefficient();
        m_isValueSet = true;
    }
}
void FirstCoefficientRetriever::retrieveFromPolynomial(Polynomial const& polynomial) {
    if (!m_isValueSet) {
        BaseRetriever::retrieveFromPolynomial(polynomial);
    }
}

void FirstCoefficientRetriever::retrieveFromExpression(Expression const& expression) {
    if (!m_isValueSet) {
        BaseRetriever::retrieveFromExpression(expression);
    }
}

void FirstCoefficientRetriever::retrieveFromFunction(Function const& functionObject) {
    if (!m_isValueSet) {
        BaseRetriever::retrieveFromFunction(functionObject);
    }
}

void FirstCoefficientRetriever::retrieveFromPolynomials(Polynomials const& polynomials) {
    if (!m_isValueSet) {
        BaseRetriever::retrieveFromPolynomials(polynomials);
    }
}

}  // namespace algebra
}  // namespace alba