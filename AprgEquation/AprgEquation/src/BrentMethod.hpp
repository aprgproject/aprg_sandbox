#pragma once

#include <Math/AlbaNumber.hpp>
#include <Math/AlbaNumberTypes.hpp>

namespace alba
{

namespace equation
{

class BrentMethod
{
public:
    BrentMethod(AlbaNumbers const& coefficients);
    AlbaNumberOptional calculateRoot();
    AlbaNumberOptional calculateRoot(AlbaNumber const& start, AlbaNumber const& end);
    AlbaNumberOptional calculateInverseQuadraticInterpolation(
            AlbaNumber const& a,
            AlbaNumber const& b,
            AlbaNumber const& c) const;
    AlbaNumberOptional calculateSecantMethod(
            AlbaNumber const& a,
            AlbaNumber const& b) const;
    AlbaNumber calculateBiSectionMethod(
            AlbaNumber const& a,
            AlbaNumber const& b) const;
    bool isBisectionMethodNeeded(
            AlbaNumber const& a,
            AlbaNumber const& b,
            AlbaNumber const& c,
            AlbaNumber const& d,
            AlbaNumber const& s,
            bool const mflag) const;
    AlbaNumber getMaxOfAbsoluteValueOfCoefficients() const;
    AlbaNumber calculate(AlbaNumber const& inputValue) const;

private:
    AlbaNumbers m_coefficients;
};

}

}
