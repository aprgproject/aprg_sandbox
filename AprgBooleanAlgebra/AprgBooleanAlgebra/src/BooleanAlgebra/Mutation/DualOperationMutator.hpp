#pragma once

#include <BooleanAlgebra/Mutation/BaseMutator.hpp>
#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace booleanAlgebra {

class DualOperationMutator final : public BaseMutator {
public:
    void mutateExpression(Expression& expression) override;
};

}  // namespace booleanAlgebra

}  // namespace alba
