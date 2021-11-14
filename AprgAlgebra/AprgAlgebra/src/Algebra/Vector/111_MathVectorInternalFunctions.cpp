#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Vector/111_MathVectorInternalFunctions.hpp>

namespace alba
{

namespace algebra
{


Term raiseToPowerInternal(Term const& term1, Term const& term2)
{
    return term1^term2;
}

}

}
