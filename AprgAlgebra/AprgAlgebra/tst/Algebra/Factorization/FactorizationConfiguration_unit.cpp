#include <Algebra/Factorization/FactorizationConfiguration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

TEST(FactorizationConfigurationTest, SomeConditionWorksAsDefault)
{
    EXPECT_FALSE(someCondition());
}

TEST(FactorizationConfigurationTest, SomeConditionWorksAndCanBeChanged)
{
    ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<ConfigurationDetails>());
    configurationDetails.someCondition = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    EXPECT_TRUE(someCondition());
}

}

}

}
