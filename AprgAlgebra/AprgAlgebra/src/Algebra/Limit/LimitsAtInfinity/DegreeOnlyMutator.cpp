#include "DegreeOnlyMutator.hpp"

using namespace std;

namespace alba {

namespace algebra {

DegreeOnlyMutator::DegreeOnlyMutator(string const& variableName) : m_variableName(variableName) {}

void DegreeOnlyMutator::mutateTerm(Term& term) {
    Term beforeMutation;
    do {
        beforeMutation = term;
        BaseMutator::mutateTerm(term);
        term.simplify();
    } while (beforeMutation != term);
}

void DegreeOnlyMutator::mutateMonomial(Monomial& monomial) {
    AlbaNumber degreeForVariable(monomial.getExponentForVariable(m_variableName));
    monomial = getMonomialWithDegree(degreeForVariable);
}

void DegreeOnlyMutator::mutatePolynomial(Polynomial& polynomial) {
    AlbaNumber maxDegreeForVariable(getMaxDegreeForVariable(polynomial));
    polynomial.clear();
    polynomial.addMonomial(getMonomialWithDegree(maxDegreeForVariable));
}

void DegreeOnlyMutator::mutateExpression(Expression& expression) {
    Expression beforeMutation;
    do {
        beforeMutation = expression;
        BaseMutator::mutateExpression(expression);
        expression.simplify();
    } while (beforeMutation != expression);
}

AlbaNumber DegreeOnlyMutator::getMaxDegreeForVariable(Polynomial const& polynomial) {
    AlbaNumber maxDegreeForVariable;
    auto const& monomials(polynomial.getMonomialsConstReference());
    if (!monomials.empty()) {
        maxDegreeForVariable = monomials.front().getExponentForVariable(m_variableName);
        for (auto it = monomials.cbegin() + 1; it != monomials.cend(); it++) {
            AlbaNumber currentDegreeForVariable(it->getExponentForVariable(m_variableName));
            if (maxDegreeForVariable < currentDegreeForVariable) {
                maxDegreeForVariable = currentDegreeForVariable;
            }
        }
    }
    return maxDegreeForVariable;
}

Monomial DegreeOnlyMutator::getMonomialWithDegree(AlbaNumber const& degree) const {
    Monomial result(1, {{m_variableName, degree}});
    if (degree == 0) {
        result = Monomial(1, {});
    }
    return result;
}

}  // namespace algebra

}  // namespace alba
