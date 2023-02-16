#include <Common/Container/AlbaAny.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaAnyTest, DefaultConstructorWorks)
{
    AlbaAny any;

    EXPECT_FALSE(any.hasContent());
}

TEST(AlbaAnyTest, CopyConstructorWorks)
{
    AlbaAny copiedAnyWithInteger(1234U);
    AlbaAny copiedAnyWithAny(copiedAnyWithInteger);

    EXPECT_EQ(1234U, copiedAnyWithInteger.getContentAs<unsigned int>());
    EXPECT_EQ(1234U, copiedAnyWithAny.getContentAs<unsigned int>());
}

TEST(AlbaAnyTest, CopyAssignmentWorks)
{
    AlbaAny originalAny(1234U);
    AlbaAny assignedAny = originalAny;

    EXPECT_EQ(1234U, originalAny.getContentAs<unsigned int>());
    EXPECT_EQ(1234U, assignedAny.getContentAs<unsigned int>());
}

TEST(AlbaAnyTest, BoolOperatorWorks)
{
    AlbaAny emptyAny;
    AlbaAny assignedAny(1234U);

    EXPECT_FALSE(static_cast<bool>(emptyAny));
    EXPECT_TRUE(static_cast<bool>(assignedAny));
}

TEST(AlbaAnyTest, HasContentWorks)
{
    AlbaAny emptyAny;
    AlbaAny assignedAny(1234U);

    EXPECT_FALSE(emptyAny.hasContent());
    EXPECT_TRUE(assignedAny.hasContent());
}

TEST(AlbaAnyTest, GetContentAsWorks)
{
    AlbaAny any(1234U);

    EXPECT_EQ(1234U, any.getContentAs<unsigned int>());
}

TEST(AlbaAnyTest, GetContentReferenceAsWorks)
{
    AlbaAny any(1234U);

    unsigned int & intReference = any.getContentReferenceAs<unsigned int>();
    intReference = 5678U;

    EXPECT_EQ(5678U, any.getContentAs<unsigned int>());
}

TEST(AlbaAnyTest, SaveContentWorks)
{
    AlbaAny any(1234U);

    any.saveContent<unsigned int>(5678U);

    EXPECT_EQ(5678U, any.getContentAs<unsigned int>());
}

TEST(AlbaAnyTest, ClearWorks)
{
    AlbaAny any(1234U);

    any.clear();

    EXPECT_FALSE(any.hasContent());
}

TEST(AlbaAnyTest, OutputStreamOperatorWorks)
{
    stringstream ss;
    AlbaAny any(1234U);

    ss<<any;

    EXPECT_EQ("hasContent: 1\n savedMemory: Decimal values: {210, 4, 0, 0, }\nHexadecimal values: {d2, 4, 0, 0, }\n",
              ss.str());
}


}
