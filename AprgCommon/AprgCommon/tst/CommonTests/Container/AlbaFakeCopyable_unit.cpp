#include <Common/Container/AlbaFakeCopyable.hpp>

#include <gtest/gtest.h>

namespace alba {

struct FakeCopyableExample {
    FakeCopyableExample() : value(0) { ++numberOfConstructorExecutions; }

    FakeCopyableExample(int const valueAsParameter) : value(valueAsParameter) { ++numberOfConstructorExecutions; }

    static int numberOfConstructorExecutions;
    int value;
};

int FakeCopyableExample::numberOfConstructorExecutions = 0;

using AlbaFakeCopyableForTest = AlbaFakeCopyable<FakeCopyableExample>;

TEST(AlbaFakeCopyableTest, FakeCopyingWorks) {
    EXPECT_EQ(0, FakeCopyableExample::numberOfConstructorExecutions);

    AlbaFakeCopyableForTest example1(FakeCopyableExample(176));
    EXPECT_EQ(1, FakeCopyableExample::numberOfConstructorExecutions);
    EXPECT_EQ(176, example1.getObject().value);

    AlbaFakeCopyableForTest example2(example1);
    EXPECT_EQ(2, FakeCopyableExample::numberOfConstructorExecutions);
    EXPECT_EQ(0, example2.getObject().value);  // value is from default constructor
}

}  // namespace alba
