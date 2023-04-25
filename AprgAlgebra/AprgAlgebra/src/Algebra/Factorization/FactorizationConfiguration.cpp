#include "FactorizationConfiguration.hpp"

namespace alba {

namespace algebra {

namespace Factorization {

bool shouldSimplifyExpressionsToFactors() {
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyExpressionsToFactors;
}

bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue() {
    return Configuration::getInstance()
        .getConfigurationDetails()
        .shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
}

}  // namespace Factorization

}  // namespace algebra

template <>
algebra::Factorization::ConfigurationDetails
getDefaultConfigurationDetails<algebra::Factorization::ConfigurationDetails>() {
    return alba::algebra::Factorization::ConfigurationDetails{false, false};
}

}  // namespace alba
