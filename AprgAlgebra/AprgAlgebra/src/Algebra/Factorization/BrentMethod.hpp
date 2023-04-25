#pragma once

#include <Common/Math/Number/AlbaNumberTypes.hpp>

#include <vector>

namespace alba {

namespace algebra {

class BrentMethod {
public:
    struct CalculationValues {
        AlbaNumberOptional solutionOptional;
        AlbaNumber a;
        AlbaNumber b;
        AlbaNumber c;
        AlbaNumber d;
        AlbaNumber s;
        AlbaNumber fa;
        AlbaNumber fb;
        bool mflag;
    };
    using ListOfCoefficients = std::vector<AlbaNumbers>;

    BrentMethod(AlbaNumbers const& coefficients);

    bool isFinished() const;
    unsigned int getNumberOfIterationsExecuted() const;
    AlbaNumbers const& getCoefficients() const;
    CalculationValues const& getCalculationValues() const;

    AlbaNumberOptional const& getSolution();
    void resetCalculation(AlbaNumber const& start, AlbaNumber const& end);
    void runOneIteration();
    void runMaxNumberOfIterationsOrUntilFinished(unsigned int const maxIterations);

private:
    bool isAlmostEqualForBrentMethod(AlbaNumber const& value1, AlbaNumber const& value2) const;
    bool isAlmostEqualForBrentMethod(AlbaNumber const& value1, double const value2) const;
    AlbaNumber calculate(AlbaNumber const& inputValue) const;
    AlbaNumberOptional calculateInverseQuadraticInterpolation(
        AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c) const;
    AlbaNumberOptional calculateSecantMethod(AlbaNumber const& a, AlbaNumber const& b) const;
    AlbaNumber calculateBiSectionMethod(AlbaNumber const& a, AlbaNumber const& b) const;
    bool isBisectionMethodNeeded(
        AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c, AlbaNumber const& d, AlbaNumber const& s,
        bool const mflag) const;
    void convertSolutionToIntegerIfNeeded();
    unsigned int m_numberOfIterationsExecuted;
    AlbaNumbers m_coefficients;
    CalculationValues m_values;
};

}  // namespace algebra

}  // namespace alba
