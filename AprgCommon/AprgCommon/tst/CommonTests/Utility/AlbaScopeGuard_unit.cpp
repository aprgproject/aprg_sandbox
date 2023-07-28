#include <Common/Utility/AlbaScopeGuard.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaScopeGuardTest, FunctionIsExecutedWhenItGoesOutOfScope) {
    int valueToTest = 1;
    {
        AlbaScopeGuard scopeGuard([&valueToTest]() { valueToTest = 2; });        valueToTest = 3;
    }

    EXPECT_EQ(2, valueToTest);
}

TEST(AlbaScopeGuardTest, FunctionIsExecutedWhenItsCalledDirectly) {
    int valueToTest = 1;

    AlbaScopeGuard incrementer([&valueToTest]() { valueToTest++; });
    incrementer();
    incrementer();
    incrementer();
    incrementer();

    EXPECT_EQ(5, valueToTest);
}

}  // namespace alba