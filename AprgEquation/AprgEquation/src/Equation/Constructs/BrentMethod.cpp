#include "BrentMethod.hpp"

#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace equation
{

BrentMethod::BrentMethod(AlbaNumbers const& coefficients)
    : m_coefficients(coefficients)
{}

AlbaNumberOptional BrentMethod::calculateRoot()
{
    AlbaNumber maxValueOfCoefficients(getMaxOfAbsoluteValueOfCoefficients());
    return calculateRoot(maxValueOfCoefficients*-1, maxValueOfCoefficients);
}

AlbaNumberOptional BrentMethod::calculateRoot(AlbaNumber const& start, AlbaNumber const& end)
{
    AlbaNumberOptional result;
    AlbaNumber a = start;
    AlbaNumber b = end;
    AlbaNumber c;
    AlbaNumber d;
    AlbaNumber s;
    AlbaNumber fa = calculate(a);
    AlbaNumber fb = calculate(b);

    //if(fa*fb>=0){//exit?//}

    if(getAbsoluteValue(fa) < getAbsoluteValue(fb))
    {
        swap(a, b);
        fa = calculate(a);
        fb = calculate(b);
    }
    c=a;

    bool mflag(true);

    unsigned int const maxIterations = 1000;
    double aPreviousValue=b.getDouble();
    double bPreviousValue=a.getDouble();
    for(unsigned numberOfIterations=0; numberOfIterations<maxIterations; numberOfIterations++) //or |b − a| is small enough (convergence)
    {
        if(calculate(s) == 0)
        {
            result.setValue(s);
            break;
        }
        if(calculate(b) == 0)
        {
            result.setValue(b);
            break;
        }
        AlbaNumber fc = calculate(c);
        if(fa != fc && fb != fc)
        {
            AlbaNumberOptional sOptional(calculateInverseQuadraticInterpolation(a, b, c));
            if(!sOptional.hasContent())
            {
                break;
            }
            s = sOptional.getConstReference();
        }
        else if(fa != fb)
        {
            AlbaNumberOptional sOptional(calculateSecantMethod(a, b));
            if(!sOptional.hasContent())
            {
                break;
            }
            s = sOptional.getConstReference();
        }
        if(isBisectionMethodNeeded(a,b,c,d,s,mflag))
        {
            s = calculateBiSectionMethod(a, b);
            mflag = true;
        }
        else
        {
            mflag = false;
        }
        AlbaNumber fs = calculate(s);
        d = c;
        c = b;
        if(fa*fs < 0)
        {
            b = s;
        }
        else
        {
            a = s;
        }
        fa = calculate(a);
        fb = calculate(b);
        if(getAbsoluteValue(fa) < getAbsoluteValue(fb))
        {
            swap(a, b);
            fa = calculate(a);
            fb = calculate(b);
        }
        if(a.getDouble() == aPreviousValue && b.getDouble() == bPreviousValue)
        {
            break;
        }
        aPreviousValue = a.getDouble();
        bPreviousValue = b.getDouble();
    }

    if(result.hasContent() && !m_coefficients.empty())
    {
        AlbaNumber aCoefficient(m_coefficients.front());
        if(aCoefficient.isIntegerOrFractionType())
        {
            AlbaNumber possibleIntegerValue(result.getConstReference()*aCoefficient);
            if(canConvertedToInteger(possibleIntegerValue.getDouble(), 1E-5))
            {
                possibleIntegerValue.convertToInteger();
                possibleIntegerValue = possibleIntegerValue/aCoefficient;
                if(calculate(possibleIntegerValue)==0)
                {
                    result.setValue(possibleIntegerValue);
                }
            }
        }
    }

    return result;
}

AlbaNumberOptional BrentMethod::calculateInverseQuadraticInterpolation(
        AlbaNumber const& a,
        AlbaNumber const& b,
        AlbaNumber const& c) const
{
    AlbaNumberOptional result;
    AlbaNumber fa = calculate(a);
    AlbaNumber fb = calculate(b);
    AlbaNumber fc = calculate(c);
    AlbaNumber firstDenominator((fa-fb)*(fa-fc));
    AlbaNumber secondDenominator((fb-fa)*(fb-fc));
    AlbaNumber thirdDenominator((fc-fa)*(fc-fb));
    if(firstDenominator != 0 || secondDenominator != 0 || thirdDenominator != 0)
    {
        AlbaNumber firstPart = (a*fb*fc) / firstDenominator;
        AlbaNumber secondPart = (b*fa*fc) / secondDenominator;
        AlbaNumber thirdPart = (c*fa*fb) / thirdDenominator;
        result.setValue(firstPart+secondPart+thirdPart);
    }
    return result;
}

AlbaNumberOptional BrentMethod::calculateSecantMethod(
        AlbaNumber const& a,
        AlbaNumber const& b) const
{
    AlbaNumberOptional result;
    AlbaNumber fa = calculate(a);
    AlbaNumber fb = calculate(b);
    AlbaNumber denominator(fb-fa);
    if(denominator != 0)
    {
        AlbaNumber firstPart = b;
        AlbaNumber secondPart = (fb*(b-a)) / (denominator);
        result.setValue(firstPart-secondPart);
    }
    return result;
}

AlbaNumber BrentMethod::calculateBiSectionMethod(
        AlbaNumber const& a,
        AlbaNumber const& b) const
{
    return (a+b)/2;
}

bool BrentMethod::isBisectionMethodNeeded(
        AlbaNumber const& a,
        AlbaNumber const& b,
        AlbaNumber const& c,
        AlbaNumber const& d,
        AlbaNumber const& s,
        bool const mflag) const
{
    AlbaNumber first = ((a*3)+b)/4;
    AlbaNumber second = b;
    AlbaNumber minForConditionOne = min(first, second);
    AlbaNumber maxForConditionOne = max(first, second);
    AlbaNumber gamma = 1;
    bool isConditionOne = s < minForConditionOne || maxForConditionOne < s;
    bool isConditionTwo = mflag && getAbsoluteValue(s-b) >= (getAbsoluteValue(b-c)/2);
    bool isConditionThree = !mflag && getAbsoluteValue(s-b) >= (getAbsoluteValue(c-d)/2);
    bool isConditionFour = mflag && getAbsoluteValue(b-c) < getAbsoluteValue(gamma);
    bool isConditionFive = !mflag && getAbsoluteValue(c-d) < getAbsoluteValue(gamma);
    return isConditionOne || isConditionTwo || isConditionThree || isConditionFour || isConditionFive;
}

AlbaNumber BrentMethod::getMaxOfAbsoluteValueOfCoefficients() const
{
    AlbaNumber maxValue(0);
    for(AlbaNumber const& coefficient : m_coefficients)
    {
        maxValue = max(maxValue, getAbsoluteValue(coefficient));
    }
    return maxValue;
}

AlbaNumber BrentMethod::calculate(AlbaNumber const& inputValue) const
{
    AlbaNumber result;
    AlbaNumber partialProduct(1);
    for(AlbaNumbers::const_reverse_iterator it=m_coefficients.crbegin();
        it != m_coefficients.crend();
        it++)
    {
        result = result + (*it)*partialProduct;
        partialProduct = partialProduct*inputValue;
    }
    return result;
}

}

}
