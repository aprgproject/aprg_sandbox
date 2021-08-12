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

Function abs(Term const& term)
{
    return Function("abs", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return getAbsoluteValueForAlbaNumber(number);
    });
}

}

}

}
