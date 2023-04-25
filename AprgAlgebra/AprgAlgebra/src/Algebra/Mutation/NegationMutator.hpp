#pragma once

#include <Algebra/Mutation/BaseMutator.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

class NegationMutator final : public BaseMutator {
public:
    void mutateTerm(Term &term) override;
    void mutateConstant(Constant &constant) override;
    void mutateVariable(Variable &) override;
    void mutateMonomial(Monomial &monomial) override;
    void mutateExpression(Expression &expression) override;
    void mutateFunction(Function &) override;
};

}  // namespace algebra

}  // namespace alba
