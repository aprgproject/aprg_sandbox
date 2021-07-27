#pragma once

#include <Math/AlbaNumber.hpp>

#include <functional>

namespace alba
{

namespace algebra
{

class NewtonMethod
{
public:
    using Function = std::function<AlbaNumber(AlbaNumber const&)>;

    NewtonMethod(
            AlbaNumber const& initialValue,
            Function const& functionToIterate);

    bool isSolved() const;
    bool isFinished() const;
    AlbaNumber getCurrentComputedValue() const;
    unsigned int getNumberOfIterationsExecuted() const;

    void runOneIteration();
    void runMaxNumberOfIterationsOrUntilFinished(unsigned int const iterations);
    void runUntilFinished();

private:
    AlbaNumber getSlopeApproximationAt(AlbaNumber const& value) const;
    void updatePositiveDeltaForSlopeIfNeeded(AlbaNumber const& newValue);
    unsigned int m_numberOfIterationsExecuted;
    AlbaNumber m_currentComputedValue;
    AlbaNumber m_positiveDeltaForSlope;
    Function m_functionToIterate;
};

}

}
