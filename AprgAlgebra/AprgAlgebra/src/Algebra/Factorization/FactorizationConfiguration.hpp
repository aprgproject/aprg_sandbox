#pragma once

#include <Common/Container/AlbaConfigurationHolder.hpp>

namespace alba {

namespace algebra {

namespace Factorization {

struct ConfigurationDetails {
    bool shouldSimplifyExpressionsToFactors;
    bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
};

class Configuration : public AlbaConfigurationHolder<ConfigurationDetails> {};

class ScopeObject : public AlbaConfigurationScopeObject<ConfigurationDetails> {};

bool shouldSimplifyExpressionsToFactors();
bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue();

}  // namespace Factorization

}  // namespace algebra

template <>
algebra::Factorization::ConfigurationDetails
getDefaultConfigurationDetails<algebra::Factorization::ConfigurationDetails>();

}  // namespace alba
