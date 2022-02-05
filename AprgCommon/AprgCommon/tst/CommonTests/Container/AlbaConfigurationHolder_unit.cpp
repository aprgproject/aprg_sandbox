#include <Common/Container/AlbaConfigurationHolder.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace
{

struct SampleConfigurationDetails
{
    unsigned int valueToTest;
};

using SampleConfigurationHolder=alba::AlbaConfigurationHolder<SampleConfigurationDetails>;
using SampleConfigurationScopeObject=alba::AlbaConfigurationScopeObject<SampleConfigurationDetails>;

}

namespace alba
{

template <>
SampleConfigurationDetails getDefaultConfigurationDetails<SampleConfigurationDetails>()
{
    return SampleConfigurationDetails{};
}

TEST(AlbaConfigurationHolderTest, ConfigurationWorks)
{
    SampleConfigurationHolder configurationHolder1;
    SampleConfigurationHolder configurationHolder2(SampleConfigurationDetails{75842});

    EXPECT_EQ(0U, configurationHolder1.getConfigurationDetails().valueToTest);
    EXPECT_EQ(75842U, configurationHolder2.getConfigurationDetails().valueToTest);
}

TEST(AlbaConfigurationHolderTest, GetConfigurationDetailsWorksAtDefault)
{
    SampleConfigurationDetails const& configurationDetails(
                SampleConfigurationHolder::getInstance().getConfigurationDetails());

    EXPECT_EQ(0U, configurationDetails.valueToTest);
}

TEST(AlbaConfigurationHolderTest, SetConfigurationDetailsWorks)
{
    SampleConfigurationHolder::getInstance().setConfigurationDetails(SampleConfigurationDetails{48564U});

    EXPECT_EQ(48564U, SampleConfigurationHolder::getInstance().getConfigurationDetails().valueToTest);

    SampleConfigurationHolder::getInstance().setConfigurationToDefault(); //Ensure set the static values back for other tests
}

TEST(AlbaConfigurationHolderTest, SetConfigurationToDefaultWorks)
{
    SampleConfigurationHolder::getInstance().setConfigurationDetails(SampleConfigurationDetails{48564U});

    SampleConfigurationHolder::getInstance().setConfigurationToDefault();

    EXPECT_EQ(0U, SampleConfigurationHolder::getInstance().getConfigurationDetails().valueToTest);
}

TEST(AlbaConfigurationScopeObjectTest, SetInThisScopeThisConfigurationWorksAtDefaultValuesAndValuesAreSetBack)
{
    EXPECT_EQ(0U, SampleConfigurationHolder::getInstance().getConfigurationDetails().valueToTest);

    {
        SampleConfigurationScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(SampleConfigurationDetails{1255U});

        EXPECT_EQ(1255U, SampleConfigurationHolder::getInstance().getConfigurationDetails().valueToTest);
    }

    EXPECT_EQ(0U, SampleConfigurationHolder::getInstance().getConfigurationDetails().valueToTest);
}


}
