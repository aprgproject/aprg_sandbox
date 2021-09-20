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
    bool someCondition;
};

class Configuration
        : public AlbaConfigurationHolder<ConfigurationDetails>
{};

class ScopeObject : public AlbaConfigurationScopeObject<ConfigurationDetails>
{};

bool someCondition();


}

}

template <>
algebra::Factorization::ConfigurationDetails
getDefaultConfigurationDetails<algebra::Factorization::ConfigurationDetails>();

}
