#include <Common/Container/AlbaFakeCopyable.hpp>

#include <gtest/gtest.h>

namespace alba
{

struct FakeCopyableExample
{
    FakeCopyableExample()
        : value(0U)
    {
        ++numberOfConstructorExecutions;
    }

    FakeCopyableExample(unsigned int const valueAsParameter)
        : value(valueAsParameter)
    {
        ++numberOfConstructorExecutions;
    }

    static size_t numberOfConstructorExecutions;
    unsigned int value;
};

size_t FakeCopyableExample::numberOfConstructorExecutions = 0;

using AlbaFakeCopyableForTest=AlbaFakeCopyable<FakeCopyableExample>;

TEST(AlbaFakeCopyableTest, FakeCopyingWorks)
{
    EXPECT_EQ(0U, FakeCopyableExample::numberOfConstructorExecutions);

    AlbaFakeCopyableForTest example1(FakeCopyableExample(176U));
    EXPECT_EQ(1U, FakeCopyableExample::numberOfConstructorExecutions);
    EXPECT_EQ(176U, example1.getObject().value);

    AlbaFakeCopyableForTest example2(example1);
    EXPECT_EQ(2U, FakeCopyableExample::numberOfConstructorExecutions);
    EXPECT_EQ(0U, example2.getObject().value); // value is from default constructor
}

}
