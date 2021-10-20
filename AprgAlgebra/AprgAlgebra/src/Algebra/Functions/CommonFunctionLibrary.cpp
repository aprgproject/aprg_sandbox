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
        AlbaNumber result(0);
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
