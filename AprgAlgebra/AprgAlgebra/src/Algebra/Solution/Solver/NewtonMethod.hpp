#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>

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
    unsigned int getNumberOfIterationsExecuted() const;
    AlbaNumber const& getCurrentValue() const;

    void runOneIteration();
    void runMaxNumberOfIterationsOrUntilFinished(unsigned int const maxIterations);
    void runUntilFinished();

private:
    AlbaNumber getSlopeApproximationAt(AlbaNumber const& value) const;
    void updatePositiveDeltaForSlopeIfNeeded(AlbaNumber const& newValue);
    unsigned int m_numberOfIterationsExecuted;
    AlbaNumber m_currentValue;
    AlbaNumber m_positiveDeltaForSlope;
    Function m_functionToIterate;
};

}

}
