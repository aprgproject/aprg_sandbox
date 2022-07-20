#include "DualOperationMutator.hpp"

#include <BooleanAlgebra/Term/Operators/TermOperators.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/EnumHelpers.hpp>

namespace alba
{

namespace booleanAlgebra
{

void DualOperationMutator::mutateExpression(Expression & expression)
{
    expression.setCommonOperatorLevel(getDualOperatorLevel(expression.getCommonOperatorLevel()));
    BaseMutator::mutateExpression(expression);
}

}

}
