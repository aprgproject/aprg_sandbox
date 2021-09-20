#include "FactorizationConfiguration.hpp"

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

bool someCondition()
{
    return Configuration::getInstance().getConfigurationDetails().someCondition;
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
