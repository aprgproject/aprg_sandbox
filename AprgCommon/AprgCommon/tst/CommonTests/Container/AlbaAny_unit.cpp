#include <Common/Container/AlbaAny.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaAnyTest, DefaultConstructorWorks) {
    AlbaAny any;

    EXPECT_FALSE(any.hasContent());
}

TEST(AlbaAnyTest, CopyConstructorWorks) {
    AlbaAny originalAny(1234);

    AlbaAny copiedAny(originalAny);

    EXPECT_EQ(1234, originalAny.getContentAs<int>());
    EXPECT_EQ(1234, copiedAny.getContentAs<int>());
}

TEST(AlbaAnyTest, CopyAssignmentWorks) {
    AlbaAny originalAny(1234);

    AlbaAny copiedAny = originalAny;

    EXPECT_EQ(1234, originalAny.getContentAs<int>());
    EXPECT_EQ(1234, copiedAny.getContentAs<int>());
}

TEST(AlbaAnyTest, MoveConstructorWorks) {
    AlbaAny originalAny(1234);

    AlbaAny movedAny(std::move(originalAny));

    EXPECT_FALSE(originalAny.hasContent());
    EXPECT_EQ(1234, movedAny.getContentAs<int>());}

TEST(AlbaAnyTest, MoveAssignmentWorks) {
    AlbaAny originalAny(1234);

    AlbaAny assignedAny = std::move(originalAny);

    EXPECT_FALSE(originalAny.hasContent());
    EXPECT_EQ(1234, assignedAny.getContentAs<int>());}

TEST(AlbaAnyTest, BoolOperatorWorks) {
    AlbaAny emptyAny;
    AlbaAny nonEmptyAny(1234);

    EXPECT_FALSE(static_cast<bool>(emptyAny));
    EXPECT_TRUE(static_cast<bool>(nonEmptyAny));
}

TEST(AlbaAnyTest, HasContentWorks) {
    AlbaAny emptyAny;
    AlbaAny nonEmptyAny(1234);

    EXPECT_FALSE(emptyAny.hasContent());
    EXPECT_TRUE(nonEmptyAny.hasContent());
}

TEST(AlbaAnyTest, GetContentAsWorks) {
    AlbaAny any(1234);

    EXPECT_EQ(1234, any.getContentAs<int>());
}

TEST(AlbaAnyTest, GetContentReferenceAsWorks) {
    AlbaAny any(1234);

    int& intReference = any.getContentReferenceAs<int>();
    intReference = 5678;

    EXPECT_EQ(5678, any.getContentAs<int>());
}

TEST(AlbaAnyTest, SaveContentWorks) {
    AlbaAny any(1234);

    any.saveContent<int>(5678);

    EXPECT_EQ(5678, any.getContentAs<int>());
}

TEST(AlbaAnyTest, ClearWorks) {
    AlbaAny any(1234);

    any.clear();

    EXPECT_FALSE(any.hasContent());
}

TEST(AlbaAnyTest, OutputStreamOperatorWorks) {
    stringstream ss;
    AlbaAny any(1234);

    ss << any;

    EXPECT_EQ(
        "hasContent: 1\n savedMemory: Decimal values: {210, 4, 0, 0, }\nHexadecimal values: {d2, 4, 0, 0, }\n",
        ss.str());
}

}  // namespace alba
