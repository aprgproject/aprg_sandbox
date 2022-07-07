#include <Common/Container/AlbaSingleton.hpp>

#include <gtest/gtest.h>

namespace alba
{

// IMPORTANT: this class can be used only in one test
// because singleton is held as static variable
class SingletonExample : public AlbaSingleton<SingletonExample>
{
public:
    SingletonExample()
    {
        ++numberOfConstructorExecutions;
    }

    static size_t numberOfConstructorExecutions;
};

size_t SingletonExample::numberOfConstructorExecutions = 0;


TEST(AlbaSingletonTest, ConstructorIsCalledOnlyOnceAndOnlyWhenFirstGetInstanceIsCalled)
{
    EXPECT_EQ(0U, SingletonExample::numberOfConstructorExecutions);
    SingletonExample::getInstance();
    EXPECT_EQ(1U, SingletonExample::numberOfConstructorExecutions);
    SingletonExample::getInstance();
    EXPECT_EQ(1U, SingletonExample::numberOfConstructorExecutions);
}

}
