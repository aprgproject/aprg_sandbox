#include "CommonFunctionLibrary.hpp"

#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace equation
{

namespace Functions
{

Function abs(Expression const& expression)
{
    return Function("abs", expression, [](Constant const&  constant) -> Constant
    {
        return Constant(getAbsoluteValue(constant.getNumberConstReference()));
    });
}

}

}

}
