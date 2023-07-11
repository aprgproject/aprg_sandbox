#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

namespace alba {

namespace algebra {

class FirstCoefficientRetriever final : public BaseRetriever {
public:
    FirstCoefficientRetriever();

    AlbaNumber const& getFirstCoefficient() const;
    void retrieveFromEquations(Equations const& equations) override;
    void retrieveFromEquation(Equation const& equation) override;
    void retrieveFromTerm(Term const& term) override;
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromPolynomial(Polynomial const& polynomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& function) override;
    void retrieveFromPolynomials(Polynomials const& polynomials) override;

private:
    bool m_isValueSet;
    AlbaNumber m_firstCoefficient;
};

}  // namespace algebra

}  // namespace alba
