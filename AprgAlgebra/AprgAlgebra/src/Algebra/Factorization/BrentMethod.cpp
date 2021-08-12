//In numerical analysis, Brent's method is a root-finding algorithm combining the bisection method, the secant method and inverse quadratic interpolation.
//It has the reliability of bisection but it can be as quick as some of the less-reliable methods.
//The algorithm tries to use the potentially fast-converging secant method or inverse quadratic interpolation if possible, but it falls back to the more robust bisection method if necessary.
//Brent's method is due to Richard Brent[1] and builds on an earlier algorithm by Theodorus Dekker.[2]
//Consequently, the method is also known as the Brent–Dekker method.

#include "BrentMethod.hpp"

#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

BrentMethod::BrentMethod(AlbaNumbers const& coefficients)
    : m_numberOfIterationsExecuted(0)
    , m_coefficients(coefficients)
{}

bool BrentMethod::isFinished() const
{
    return m_values.solutionOptional.hasContent();
}

unsigned int BrentMethod::getNumberOfIterationsExecuted() const
{
    return m_numberOfIterationsExecuted;
}

BrentMethod::CalculationValues const& BrentMethod::getCalculationValues() const
{
    return m_values;
}

AlbaNumberOptional const& BrentMethod::getSolution()
{
    convertSolutionToIntegerIfNeeded();
    return m_values.solutionOptional;
}

void BrentMethod::resetCalculation(AlbaNumber const& start, AlbaNumber const& end)
{
    m_numberOfIterationsExecuted=0;
    m_values.solutionOptional.clear();
    m_values.a = start;
    m_values.b = end;
    m_values.d = 0;
    m_values.s = 0;
    m_values.fa = calculate(m_values.a);
    m_values.fb = calculate(m_values.b);
    m_values.mflag = true;

    if(getAbsoluteValueForAlbaNumber(m_values.fa) < getAbsoluteValueForAlbaNumber(m_values.fb))
    {
        swap(m_values.a, m_values.b);
        swap(m_values.fa, m_values.fb);    }
    m_values.c = m_values.a;
}
void BrentMethod::runOneIteration()
{
    if(calculate(m_values.s) == 0)
    {
        m_values.solutionOptional.setValue(m_values.s);
        return;
    }
    if(calculate(m_values.b) == 0)
    {
        m_values.solutionOptional.setValue(m_values.b);
        return;
    }
    if(isAlmostEqual(m_values.a.getDouble(), m_values.b.getDouble())
            && isAlmostEqual(calculate(m_values.a).getDouble(), 0.0, 1E-11))
    {
        m_values.solutionOptional.setValue(m_values.a);
        return;
    }
    AlbaNumber fc = calculate(m_values.c);
    if(m_values.fa != fc && m_values.fb != fc)
    {
        AlbaNumberOptional sOptional(calculateInverseQuadraticInterpolation(m_values.a, m_values.b, m_values.c));
        if(!sOptional.hasContent())
        {
            return;
        }
        m_values.s = sOptional.getConstReference();
    }
    else if(m_values.fa != m_values.fb)
    {
        AlbaNumberOptional sOptional(calculateSecantMethod(m_values.a, m_values.b));
        if(!sOptional.hasContent())
        {
            return;
        }
        m_values.s = sOptional.getConstReference();
    }
    if(isBisectionMethodNeeded(m_values.a, m_values.b, m_values.c, m_values.d, m_values.s, m_values.mflag)
            || isAlmostEqual(m_values.a.getDouble(), m_values.s.getDouble())
            || isAlmostEqual(m_values.b.getDouble(), m_values.s.getDouble()))
    {
        m_values.s = calculateBiSectionMethod(m_values.a, m_values.b);
        m_values.mflag = true;
    }
    else
    {
        m_values.mflag = false;
    }
    AlbaNumber fs = calculate(m_values.s);
    m_values.d = m_values.c;
    m_values.c = m_values.b;
    if(m_values.fa*fs < 0)
    {
        m_values.b = m_values.s;
    }
    else
    {
        m_values.a = m_values.s;
    }
    m_values.fa = calculate(m_values.a);
    m_values.fb = calculate(m_values.b);
    if(getAbsoluteValueForAlbaNumber(m_values.fa) < getAbsoluteValueForAlbaNumber(m_values.fb))
    {
        swap(m_values.a, m_values.b);
        swap(m_values.fa, m_values.fb);    }
    m_numberOfIterationsExecuted++;
}
void BrentMethod::runMaxNumberOfIterationsOrUntilFinished(unsigned int const maxIterations)
{
    for(unsigned int i=0; !isFinished() && i<maxIterations; i++)
    {
        runOneIteration();
    }
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
    bool isConditionTwo = mflag && getAbsoluteValueForAlbaNumber(s-b) >= (getAbsoluteValueForAlbaNumber(b-c)/2);
    bool isConditionThree = !mflag && getAbsoluteValueForAlbaNumber(s-b) >= (getAbsoluteValueForAlbaNumber(c-d)/2);
    bool isConditionFour = mflag && getAbsoluteValueForAlbaNumber(b-c) < getAbsoluteValueForAlbaNumber(gamma);
    bool isConditionFive = !mflag && getAbsoluteValueForAlbaNumber(c-d) < getAbsoluteValueForAlbaNumber(gamma);
    return isConditionOne || isConditionTwo || isConditionThree || isConditionFour || isConditionFive;
}
void BrentMethod::convertSolutionToIntegerIfNeeded()
{
    if(m_values.solutionOptional.hasContent() && !m_coefficients.empty())    {
        AlbaNumber aCoefficient(m_coefficients.front());
        if(aCoefficient.isIntegerOrFractionType())
        {
            AlbaNumber possibleValue(m_values.solutionOptional.getConstReference()*aCoefficient);
            possibleValue.convertToInteger();
            possibleValue = possibleValue/aCoefficient;
            if(calculate(possibleValue)==0)
            {
                m_values.solutionOptional.setValue(possibleValue);
            }
        }
    }
}

}

}
