#include "CommonFunctionLibrary.hpp"

#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Functions
{

Function abs(Expression const& expression)
{
    return Function("abs", expression, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return getAbsoluteValue(number);
    });
}

}

}

}
