#pragma once

#include <Algebra/Mutation/BaseMutator.hpp>

namespace alba {

namespace algebra {

class RemoveMonomialsWithNegativeExponentMutator final : public BaseMutator {
public:
    RemoveMonomialsWithNegativeExponentMutator(std::string const& variableName);
    void mutateTerm(Term& term) override;
    void mutateMonomial(Monomial& monomial) override;
    void mutatePolynomial(Polynomial& polynomial) override;
    void mutateExpression(Expression& expression) override;
    void mutateFunction(Function& functionObject) override;

private:
    bool isMonomialToBeRemoved(Monomial const& monomial) const;
    std::string m_variableName;
};

}  // namespace algebra

}  // namespace alba
