//#include <gmock/gmock.h>
#include <gtest/gtest.h>

int main(int ac, char ** av)
{
    ::testing::InitGoogleTest(&ac, av);
    //::testing::InitGoogleMock(&ac, av);
    return RUN_ALL_TESTS();
}
