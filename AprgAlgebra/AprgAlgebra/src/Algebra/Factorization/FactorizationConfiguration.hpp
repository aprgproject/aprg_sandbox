#pragma once

#include <Container/AlbaConfigurationHolder.hpp>

namespace alba
{

namespace algebra
{

namespace Factorization
{

struct ConfigurationDetails
{
    bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
};

class Configuration
        : public AlbaConfigurationHolder<ConfigurationDetails>
{};

class ScopeObject : public AlbaConfigurationScopeObject<ConfigurationDetails>
{};

bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue();


}

}

template <>
algebra::Factorization::ConfigurationDetails
getDefaultConfigurationDetails<algebra::Factorization::ConfigurationDetails>();

}
