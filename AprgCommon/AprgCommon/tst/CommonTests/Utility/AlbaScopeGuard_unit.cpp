#include <Common/Utility/AlbaScopeGuard.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaScopeGuardTest, SetInThisScopeThisConfigurationWorksAtDefaultValuesAndValuesAreSetBack) {
    int valueToTest = 1;
    {
        AlbaScopeGuard scopeGuard([&valueToTest]() { valueToTest = 2; });
        valueToTest = 3;
    }

    EXPECT_EQ(2, valueToTest);
}

}  // namespace alba
