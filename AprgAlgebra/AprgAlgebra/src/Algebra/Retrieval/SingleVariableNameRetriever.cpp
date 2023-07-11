#include "SingleVariableNameRetriever.hpp"

using namespace std;

namespace alba {

namespace algebra {

SingleVariableNameRetriever::SingleVariableNameRetriever()
    : m_hasEncounteredAVariable(false), m_hasMultipleVariables(false) {}

std::string const& SingleVariableNameRetriever::getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty() const {
    return m_singleVariableName;
}

bool SingleVariableNameRetriever::hasNoVariables() const { return !m_hasEncounteredAVariable; }

bool SingleVariableNameRetriever::hasOnlyASingleVariable() const {
    return m_hasEncounteredAVariable && !m_hasMultipleVariables;
}
bool SingleVariableNameRetriever::hasMultipleVariables() const { return m_hasMultipleVariables; }

void SingleVariableNameRetriever::retrieveFromEquations(Equations const& equations) {
    if (!m_hasMultipleVariables) {
        BaseRetriever::retrieveFromEquations(equations);
    }
}

void SingleVariableNameRetriever::retrieveFromEquation(Equation const& equation) {
    if (!m_hasMultipleVariables) {
        BaseRetriever::retrieveFromEquation(equation);
    }
}

void SingleVariableNameRetriever::retrieveFromTerm(Term const& term) {
    if (!m_hasMultipleVariables) {
        BaseRetriever::retrieveFromTerm(term);
    }
}

void SingleVariableNameRetriever::retrieveFromConstant(Constant const&) {}

void SingleVariableNameRetriever::retrieveFromVariable(Variable const& variable) {
    if (!m_hasMultipleVariables) {
        putVariableIfPossible(variable.getVariableName());
    }
}

void SingleVariableNameRetriever::retrieveFromMonomial(Monomial const& monomial) {
    if (!m_hasMultipleVariables) {
        auto const& variablesToExponentsMap(monomial.getVariablesToExponentsMap());
        if (variablesToExponentsMap.size() == 1) {
            string firstVariableOfMonomial = (variablesToExponentsMap.cbegin())->first;
            putVariableIfPossible(firstVariableOfMonomial);
        } else if (variablesToExponentsMap.size() > 1) {
            m_hasEncounteredAVariable = true;
            m_hasMultipleVariables = true;
            m_singleVariableName.clear();
        }
    }
}

void SingleVariableNameRetriever::retrieveFromPolynomial(Polynomial const& polynomial) {
    if (!m_hasMultipleVariables) {
        BaseRetriever::retrieveFromPolynomial(polynomial);
    }
}

void SingleVariableNameRetriever::retrieveFromExpression(Expression const& expression) {
    if (!m_hasMultipleVariables) {
        BaseRetriever::retrieveFromExpression(expression);
    }
}

void SingleVariableNameRetriever::retrieveFromFunction(Function const& functionObject) {
    if (!m_hasMultipleVariables) {
        BaseRetriever::retrieveFromFunction(functionObject);
    }
}

void SingleVariableNameRetriever::retrieveFromPolynomials(Polynomials const& polynomials) {
    if (!m_hasMultipleVariables) {
        BaseRetriever::retrieveFromPolynomials(polynomials);
    }
}

void SingleVariableNameRetriever::putVariableIfPossible(string const& variableName) {
    if (!m_hasEncounteredAVariable) {
        m_hasEncounteredAVariable = true;
        m_singleVariableName = variableName;
    } else if (m_singleVariableName != variableName) {
        m_hasMultipleVariables = true;
        m_singleVariableName.clear();
    }
}

}  // namespace algebra

}  // namespace alba
