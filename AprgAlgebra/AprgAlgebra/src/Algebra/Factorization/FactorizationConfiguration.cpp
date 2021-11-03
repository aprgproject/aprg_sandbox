#include "FactorizationConfiguration.hpp"

namespace alba
{

namespace algebra
{

namespace Factorization
{

bool shouldSimplifyExpressionsToFactors()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyExpressionsToFactors;
}

bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue()
{
    return Configuration::getInstance().getConfigurationDetails().shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
}

}

}

template <>
algebra::Factorization::ConfigurationDetails
getDefaultConfigurationDetails<algebra::Factorization::ConfigurationDetails>()
{
    return alba::algebra::Factorization::ConfigurationDetails
    {false, false};
}

}
