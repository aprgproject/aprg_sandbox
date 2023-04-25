#pragma once

#include <Algebra/Vector/MathVectorOfTermsUtilities.hpp>

namespace alba {

namespace algebra {

namespace VectorUtilities {

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getInstantaneousVelocity(MathVectorOfTerms<SIZE> const& path, std::string const& variableName) {
    return differentiate(path, variableName);
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getInstantaneousAccelerationFromVelocity(
    MathVectorOfTerms<SIZE> const& velocity, std::string const& variableName) {
    return differentiate(velocity, variableName);
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getInstantaneousAccelerationFromPath(
    MathVectorOfTerms<SIZE> const& path, std::string const& variableName) {
    return differentiateMultipleTimes(path, variableName, 2);
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getTangentPartOfAcceleration(
    MathVectorOfTerms<SIZE> const& path, std::string const& variableName) {
    Differentiation differentiation(variableName);
    Term secondDerivativeOfPath(differentiation.differentiateMultipleTimes(path.getMagnitude(), 2));
    MathVectorOfTerms<SIZE> result(getUnitTangentVector(path, variableName));
    result *= secondDerivativeOfPath;
    simplifyForTermVector(result);
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getNormalPartOfAcceleration(
    MathVectorOfTerms<SIZE> const& path, std::string const& variableName) {
    Differentiation differentiation(variableName);
    Term firstDerivativeSquared(differentiation.differentiate(path.getMagnitude()) ^ 2);
    Term curvature(getCurvature(path, variableName));
    MathVectorOfTerms<SIZE> result(getUnitNormalVector(path, variableName));
    result *= firstDerivativeSquared;
    result *= curvature;
    simplifyForTermVector(result);
    return result;
}

}  // namespace VectorUtilities

}  // namespace algebra

}  // namespace alba
