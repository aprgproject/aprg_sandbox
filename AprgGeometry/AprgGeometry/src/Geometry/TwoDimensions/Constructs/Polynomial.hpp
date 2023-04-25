#pragma once

#include <Common/Container/AlbaValueRange.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <algorithm>
#include <array>

namespace alba {

namespace TwoDimensions {

template <unsigned int numberOfCoefficients>
class Polynomial {
public:
    Polynomial() {}

    Polynomial(std::initializer_list<double> const& coefficients) {
        static_assert(numberOfCoefficients > 0, "The numberOfCoefficients is not more than 0. Its not a polynomial");
        unsigned int limit = std::min(numberOfCoefficients, static_cast<unsigned int>(coefficients.size()));
        std::copy(coefficients.begin(), coefficients.begin() + limit, m_coefficients.rbegin());
        saveFirstDerivativeCoefficients();
    }

    double calculateOutputFromInput(double const input) const {
        double powerValueOfInput(1);
        double result(0);
        for (double const coefficient : m_coefficients) {
            result += coefficient * powerValueOfInput;
            powerValueOfInput *= input;
        }
        return result;
    }

    double getValueOfFirstDerivative(double const input) const {
        double powerValueOfInput(1);
        double result(0);
        for (double const coefficient : m_coefficientsOfFirstDerivative) {
            result += coefficient * powerValueOfInput;
            powerValueOfInput *= input;
        }
        return result;
    }

protected:
    void saveFirstDerivativeCoefficients() {
        for (unsigned int i = 1; i < numberOfCoefficients; i++) {
            m_coefficientsOfFirstDerivative[i - 1] = i * m_coefficients.at(i);
        }
    }

    std::array<double, numberOfCoefficients> m_coefficients;                       // form is c0 + c1*x + c2*x2....
    std::array<double, numberOfCoefficients - 1> m_coefficientsOfFirstDerivative;  // form is c0 + c1*x + c2*x2....
};

}  // namespace TwoDimensions
}  // namespace alba
