#include "CommonFunctionLibrary.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <cmath>

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

Function sin(Term const& term)
{
    return Function("sin", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::sin(number.getDouble());
    });
}

Function cos(Term const& term)
{
    return Function("cos", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::cos(number.getDouble());
    });
}

Function tan(Term const& term)
{
    return Function("tan", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::tan(number.getDouble());
    });
}

Function csc(Term const& term)
{
    return Function("csc", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return 1/::sin(number.getDouble());
    });
}

Function sec(Term const& term)
{
    return Function("sec", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return 1/::cos(number.getDouble());
    });
}

Function cot(Term const& term)
{
    return Function("cot", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return 1/::tan(number.getDouble());
    });
}

}

}

}