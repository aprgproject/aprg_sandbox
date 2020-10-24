#include <Optional/AlbaOptional.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(AlbaOptionalTest, IntegerTest)
{
    AlbaOptional<int> integerOptional1(1111);
    EXPECT_TRUE((bool)integerOptional1);
    EXPECT_EQ((int)integerOptional1, 1111);
    EXPECT_EQ(integerOptional1.get(), 1111);

    AlbaOptional<int> integerOptional2;
    EXPECT_FALSE((bool)integerOptional2);
    integerOptional2.setValue(2222);
    EXPECT_TRUE((bool)integerOptional2);
    EXPECT_EQ((int)integerOptional2, 2222);
    EXPECT_EQ(integerOptional2.get(), 2222);
    integerOptional2.setValue(222222);
    EXPECT_TRUE((bool)integerOptional2);
    EXPECT_EQ((int)integerOptional2, 222222);
    EXPECT_EQ(integerOptional2.get(), 222222);

    int & integerReference1 = integerOptional1.getReference();
    EXPECT_EQ(integerReference1, 1111);
    integerReference1 = 3333;
    EXPECT_EQ(integerReference1, 3333);
    EXPECT_EQ(integerOptional1.get(), 3333);

    AlbaOptional<int&> integerOptional3(integerOptional1.getReference());
    EXPECT_TRUE((bool)integerOptional3);
    EXPECT_EQ((int)integerOptional3, 3333);
    EXPECT_EQ(integerOptional3.get(), 3333);

    integerOptional3.setValue(4444);
    EXPECT_EQ(integerOptional3.get(), 4444);
    EXPECT_EQ(integerOptional1.get(), 4444);

    AlbaOptional<int&> integerOptional4;
    EXPECT_FALSE((bool)integerOptional4);
    integerOptional4.setReference(integerOptional1.getReference());
    EXPECT_TRUE((bool)integerOptional4);
    EXPECT_EQ((int)integerOptional4, 4444);
    EXPECT_EQ(integerOptional1.get(), 4444);

    integerOptional4.setValue(5555);
    EXPECT_EQ(integerOptional4.get(), 5555);
    EXPECT_EQ(integerOptional1.get(), 5555);
}

TEST(AlbaOptionalTest, AlbaOptionalCanBeConstructedByDefault)
{
    AlbaOptional<int> integerOptional;
    EXPECT_FALSE((bool)integerOptional);
    integerOptional.createObjectUsingDefaultConstructor();
    EXPECT_TRUE((bool)integerOptional);
}

TEST(AlbaOptionalTest, AlbaOptionalCanBeCopiedTest)
{
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int> integerOptional2(integerOptional1);
    EXPECT_EQ((int)integerOptional1, 1111);
    EXPECT_EQ(integerOptional1.get(), 1111);
    EXPECT_EQ((int)integerOptional2, 1111);
    EXPECT_EQ(integerOptional2.get(), 1111);
}

TEST(AlbaOptionalTest, AlbaOptionalCanBeCopiedReferenceTest)
{
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int&> integerOptional2(integerOptional1.getReference());
    AlbaOptional<int&> integerOptional3(integerOptional2);
    integerOptional3.setValue(2222);
    EXPECT_EQ((int)integerOptional1, 2222);
    EXPECT_EQ(integerOptional1.get(), 2222);
    EXPECT_EQ((int)integerOptional2, 2222);
    EXPECT_EQ(integerOptional2.get(), 2222);
    EXPECT_EQ((int)integerOptional3, 2222);
    EXPECT_EQ(integerOptional3.get(), 2222);
}

TEST(AlbaOptionalTest, AlbaOptionalCanBeAssignedTest)
{
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int> integerOptional2;
    integerOptional2 = integerOptional1;
    EXPECT_EQ((int)integerOptional1, 1111);
    EXPECT_EQ(integerOptional1.get(), 1111);
    EXPECT_EQ((int)integerOptional2, 1111);
    EXPECT_EQ(integerOptional2.get(), 1111);
}

TEST(AlbaOptionalTest, AlbaOptionalCanBeAssignedReferenceTest)
{
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int&> integerOptional2(integerOptional1.getReference());
    AlbaOptional<int&> integerOptional3;
    integerOptional3 = integerOptional2;
    integerOptional3.setValue(2222);
    EXPECT_EQ((int)integerOptional1, 2222);
    EXPECT_EQ(integerOptional1.get(), 2222);
    EXPECT_EQ((int)integerOptional2, 2222);
    EXPECT_EQ(integerOptional2.get(), 2222);
    EXPECT_EQ((int)integerOptional3, 2222);
    EXPECT_EQ(integerOptional3.get(), 2222);
}

TEST(AlbaOptionalTest, AlbaOptionalCanBeClearedTest)
{
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int&> integerOptional2(integerOptional1.getReference());
    EXPECT_TRUE((bool)integerOptional1);
    EXPECT_TRUE((bool)integerOptional2);
    integerOptional1.clear();
    integerOptional2.clear();
    EXPECT_FALSE((bool)integerOptional1);
    EXPECT_FALSE((bool)integerOptional2);
}
