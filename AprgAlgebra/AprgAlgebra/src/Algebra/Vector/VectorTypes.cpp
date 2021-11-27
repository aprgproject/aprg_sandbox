#include "VectorTypes.hpp"

using namespace alba::algebra;

namespace alba
{

template<>
Term raiseToPowerForMathVectorDataType(Term const& value1, Term const& value2)
{
    return value1^value2;
}

}
