#include "FactorizationConfiguration.hpp"

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

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
    {false};
}

}
