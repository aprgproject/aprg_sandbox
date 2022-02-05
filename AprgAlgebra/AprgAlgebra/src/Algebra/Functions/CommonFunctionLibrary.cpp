#include "CommonFunctionLibrary.hpp"

#include <Common/Math/AlbaMathHelper.hpp>

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

Function greatestIntegerFunction(Term const& term)
{
    return Function("greatestIntegerFunction", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return AlbaNumber(ceil(number.getDouble()));
    });
}

Function sgn(Term const& term)
{
    return Function("sgn", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        AlbaNumber result;
        if(number > 0)
        {
            result = 1;
        }
        else if(number < 0)
        {
            result = -1;
        }
        return result;
    });
}

Function factorial(Term const& term)
{
    return Function("factorial", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        AlbaNumber result;
        if(number.isIntegerType() && number >= 0)
        {
            result = AlbaNumber(getFactorial(static_cast<unsigned int>(number.getInteger())));
        }
        return result;
    });
}

Function ln(Term const& term)
{
    return Function("ln", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::log(number.getDouble());
    });
}

Function log(Term const& term)
{
    return Function("log", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::log10(number.getDouble());
    });
}

Function harmonicNumber(Term const& term)
{
    return Function("harmonicNumber", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        AlbaNumber result;
        if(number.getInteger() && number > 0)
        {
            unsigned int lastNumber = static_cast<unsigned int>(number.getInteger());
            for(unsigned int i=1; i<=lastNumber; i++)
            {
                result = result + AlbaNumber::createFraction(1, i);
            }
        }
        return result;
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

Function arcsin(Term const& term)
{
    return Function("arcsin", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::asin(number.getDouble());
    });
}

Function arccos(Term const& term)
{
    return Function("arccos", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::acos(number.getDouble());
    });
}

Function arctan(Term const& term)
{
    return Function("arctan", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::atan(number.getDouble());
    });
}

Function arccsc(Term const& term)
{
    return Function("arccsc", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::asin(1/number.getDouble());
    });
}

Function arcsec(Term const& term)
{
    return Function("arcsec", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::acos(1/number.getDouble());
    });
}

Function arccot(Term const& term)
{
    return Function("arccot", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::atan(1/number.getDouble());
    });
}

Function sinh(Term const& term)
{
    return Function("sinh", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::sinh(number.getDouble());
    });
}

Function cosh(Term const& term)
{
    return Function("cosh", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::cosh(number.getDouble());
    });
}

Function tanh(Term const& term)
{
    return Function("tanh", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::tanh(number.getDouble());
    });
}

Function csch(Term const& term)
{
    return Function("csch", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return 1 / ::sinh(number.getDouble());
    });
}

Function sech(Term const& term)
{
    return Function("sech", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return 1 / ::cosh(number.getDouble());
    });
}

Function coth(Term const& term)
{
    return Function("coth", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::cosh(number.getDouble()) / ::sinh(number.getDouble());
    });
}

Function arcsinh(Term const& term)
{
    return Function("arcsinh", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::asinh(number.getDouble());
    });
}

Function arccosh(Term const& term)
{
    return Function("arccosh", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::acosh(number.getDouble());
    });
}

Function arctanh(Term const& term)
{
    return Function("arctanh", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::atanh(number.getDouble());
    });
}

Function arccsch(Term const& term)
{
    return Function("arccsch", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::asinh(1/number.getDouble());
    });
}

Function arcsech(Term const& term)
{
    return Function("arcsech", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::acos(1/number.getDouble());
    });
}

Function arccoth(Term const& term)
{
    return Function("arccoth", term, [](AlbaNumber const&  number) -> AlbaNumber
    {
        return ::atanh(1/number.getDouble());
    });
}

Function sinHarmonic(
        Term const& term,
        AlbaNumber const& amplitude,
        AlbaNumber const& period,
        AlbaNumber const& phaseDifference)
{
    return Function("sinHarmonic", term, [&](AlbaNumber const&  number) -> AlbaNumber
    {
        return amplitude * ::sin((period*number + phaseDifference).getDouble());
    });
}


}

}

}
