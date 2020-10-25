#include <Optional/AlbaOptional.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(AlbaOptionalTest, IntegerTest)
{
    AlbaOptional<int> integerOptional1(1111);
    EXPECT_TRUE((bool)integerOptional1);
    EXPECT_EQ(1111, (int)integerOptional1);
    EXPECT_EQ(1111, integerOptional1.get());

    AlbaOptional<int> integerOptional2;
    EXPECT_FALSE((bool)integerOptional2);
    integerOptional2.setValue(2222);
    EXPECT_TRUE((bool)integerOptional2);
    EXPECT_EQ(2222, (int)integerOptional2);
    EXPECT_EQ(2222, integerOptional2.get());
    integerOptional2.setValue(222222);
    EXPECT_TRUE((bool)integerOptional2);
    EXPECT_EQ(222222, (int)integerOptional2);
    EXPECT_EQ(222222, integerOptional2.get());

    int & integerReference1 = integerOptional1.getReference();
    EXPECT_EQ(1111, integerReference1);
    integerReference1 = 3333;
    EXPECT_EQ(3333, integerReference1);
    EXPECT_EQ(3333, integerOptional1.get());

    AlbaOptional<int&> integerOptional3(integerOptional1.getReference());
    EXPECT_TRUE((bool)integerOptional3);
    EXPECT_EQ(3333, (int)integerOptional3);
    EXPECT_EQ(3333, integerOptional3.get());

    integerOptional3.setValue(4444);
    EXPECT_EQ(4444, integerOptional3.get());
    EXPECT_EQ(4444, integerOptional1.get());

    AlbaOptional<int&> integerOptional4;
    EXPECT_FALSE((bool)integerOptional4);
    integerOptional4.setReference(integerOptional1.getReference());
    EXPECT_TRUE((bool)integerOptional4);
    EXPECT_EQ(4444, (int)integerOptional4);
    EXPECT_EQ(4444, integerOptional1.get());

    integerOptional4.setValue(5555);
    EXPECT_EQ(5555, integerOptional4.get());
    EXPECT_EQ(5555, integerOptional1.get());
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
    EXPECT_EQ(1111, (int)integerOptional1);
    EXPECT_EQ(1111, integerOptional1.get());
    EXPECT_EQ(1111, (int)integerOptional2);
    EXPECT_EQ(1111, integerOptional2.get());
}

TEST(AlbaOptionalTest, AlbaOptionalCanBeCopiedReferenceTest)
{
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int&> integerOptional2(integerOptional1.getReference());
    AlbaOptional<int&> integerOptional3(integerOptional2);
    integerOptional3.setValue(2222);
    EXPECT_EQ(2222, (int)integerOptional1);
    EXPECT_EQ(2222, integerOptional1.get());
    EXPECT_EQ(2222, (int)integerOptional2);
    EXPECT_EQ(2222, integerOptional2.get());
    EXPECT_EQ(2222, (int)integerOptional3);
    EXPECT_EQ(2222, integerOptional3.get());
}

TEST(AlbaOptionalTest, AlbaOptionalCanBeAssignedTest)
{
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int> integerOptional2;
    integerOptional2 = integerOptional1;
    EXPECT_EQ(1111, (int)integerOptional1);
    EXPECT_EQ(1111, integerOptional1.get());
    EXPECT_EQ(1111, (int)integerOptional2);
    EXPECT_EQ(1111, integerOptional2.get());
}

TEST(AlbaOptionalTest, AlbaOptionalCanBeAssignedReferenceTest)
{
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int&> integerOptional2(integerOptional1.getReference());
    AlbaOptional<int&> integerOptional3;
    integerOptional3 = integerOptional2;
    integerOptional3.setValue(2222);
    EXPECT_EQ(2222, (int)integerOptional1);
    EXPECT_EQ(2222, integerOptional1.get());
    EXPECT_EQ(2222, (int)integerOptional2);
    EXPECT_EQ(2222, integerOptional2.get());
    EXPECT_EQ(2222, (int)integerOptional3);
    EXPECT_EQ(2222, integerOptional3.get());
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
