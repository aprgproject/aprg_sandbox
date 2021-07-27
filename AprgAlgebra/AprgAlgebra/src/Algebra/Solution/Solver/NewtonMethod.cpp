//In numerical analysis, Newton's method, also known as the Newton–Raphson method, named after Isaac Newton and Joseph Raphson,
//is a root-finding algorithm which produces successively better approximations to the roots (or zeroes) of a real-valued function.

#include "NewtonMethod.hpp"

#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

constexpr double INITIAL_DELTA_FOR_SLOPE = 1E-6;

NewtonMethod::NewtonMethod(
        AlbaNumber const& initialValue,
        Function const& functionToIterate)
    : m_numberOfIterationsExecuted(0)
    , m_currentComputedValue(initialValue)
    , m_positiveDeltaForSlope(INITIAL_DELTA_FOR_SLOPE)
    , m_functionToIterate(functionToIterate)
{}

bool NewtonMethod::isSolved() const
{
    return m_functionToIterate(m_currentComputedValue) == 0;
}

bool NewtonMethod::isFinished() const
{
    return !m_currentComputedValue.hasValidValue() || isSolved();
}

AlbaNumber NewtonMethod::getCurrentComputedValue() const
{
    return m_currentComputedValue;
}

unsigned NewtonMethod::getNumberOfIterationsExecuted() const
{
    return m_numberOfIterationsExecuted;
}

void NewtonMethod::runOneIteration()
{
    AlbaNumber newValue = m_currentComputedValue
            - (m_functionToIterate(m_currentComputedValue) / getSlopeApproximationAt(m_currentComputedValue));
    updatePositiveDeltaForSlopeIfNeeded(newValue);
    m_currentComputedValue = newValue;
    m_numberOfIterationsExecuted++;
}

void NewtonMethod::runMaxNumberOfIterationsOrUntilFinished(unsigned int const iterations)
{
    for(unsigned int i=0; !isFinished() && i<iterations; i++)
    {
        runOneIteration();
    }
}

void NewtonMethod::runUntilFinished()
{
    while(!isFinished())
    {
        runOneIteration();
    }
}

AlbaNumber NewtonMethod::getSlopeApproximationAt(
        AlbaNumber const& value) const
{
    return (m_functionToIterate(value+m_positiveDeltaForSlope)
            - m_functionToIterate(value-m_positiveDeltaForSlope))
            /(m_positiveDeltaForSlope*2);
}

void NewtonMethod::updatePositiveDeltaForSlopeIfNeeded(AlbaNumber const& newValue)
{
    AlbaNumber newPositiveDelta = getPositiveDelta(newValue, m_currentComputedValue);
    if(newPositiveDelta < m_positiveDeltaForSlope)
    {
        m_positiveDeltaForSlope = newPositiveDelta;
    }
}

}

}
