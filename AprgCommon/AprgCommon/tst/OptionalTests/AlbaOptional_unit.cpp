#include <Optional/AlbaOptional.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(OptionalTest, OptionalCanBeContructedByConstructorWithContentTypeTest)
{
    // Given    AlbaOptional<int> integerOptional1(1111);

    // When
    // Then    EXPECT_TRUE((bool)integerOptional1);
    EXPECT_EQ(1111, (int)integerOptional1);
    EXPECT_EQ(1111, integerOptional1.get());
}

TEST(OptionalTest, OptionalSetValueTest)
{
    // Given
    AlbaOptional<int> integerOptional1;
    EXPECT_FALSE((bool)integerOptional1);

    // When
    integerOptional1.setValue(2222);

    // Then
    EXPECT_TRUE((bool)integerOptional1);
    EXPECT_EQ(2222, (int)integerOptional1);
    EXPECT_EQ(2222, integerOptional1.get());

    // When
    integerOptional1.setValue(222222);

    // Then
    EXPECT_TRUE((bool)integerOptional1);
    EXPECT_EQ(222222, (int)integerOptional1);
    EXPECT_EQ(222222, integerOptional1.get());
}

TEST(OptionalTest, OptionalGetReferenceTest)
{
    // Given
    AlbaOptional<int> integerOptional1(1111);

    // When
    // Then
    int& integerReference1 = integerOptional1.getReference();
    EXPECT_EQ(1111, integerReference1);

    // When
    integerReference1 = 3333;

    // Then
    EXPECT_EQ(3333, integerReference1);
    EXPECT_EQ(3333, integerOptional1.get());
}

TEST(OptionalTest, OptionalReferenceCanBeContructedByContructorWithContentTypeTest)
{
    // Given
    AlbaOptional<int> integerOptional1(3333);
    AlbaOptional<int&> integerOptional2(integerOptional1.getReference());

    // When
    // Then
    EXPECT_TRUE((bool)integerOptional2);
    EXPECT_EQ(3333, (int)integerOptional2);
    EXPECT_EQ(3333, integerOptional2.get());

    // When
    integerOptional2.setValue(4444);

    // Then
    EXPECT_EQ(4444, integerOptional2.get());
    EXPECT_EQ(4444, integerOptional1.get());
}

TEST(OptionalTest, OptionalReferenceSetReferenceTest)
{
    // Given
    AlbaOptional<int> integerOptional1(4444);
    AlbaOptional<int&> integerOptional2;
    EXPECT_FALSE((bool)integerOptional2);

    // When
    integerOptional2.setReference(integerOptional1.getReference());

    // Then
    EXPECT_TRUE((bool)integerOptional2);
    EXPECT_EQ(4444, (int)integerOptional2);
    EXPECT_EQ(4444, integerOptional1.get());

    // When
    integerOptional2.setValue(5555);

    // Then
    EXPECT_EQ(5555, integerOptional2.get());
    EXPECT_EQ(5555, integerOptional1.get());

}

TEST(OptionalTest, OptionalCanBeConstructedByDefaultTest)
{
    // Given
    AlbaOptional<int> integerOptional;
    EXPECT_FALSE((bool)integerOptional);

    // When
    integerOptional.createObjectUsingDefaultConstructor();

    // Then
    EXPECT_TRUE((bool)integerOptional);
}

TEST(OptionalTest, OptionalCanBeCopiedTest)
{
    // Given
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int> integerOptional2(integerOptional1);

    // When
    // Then
    EXPECT_EQ(1111, (int)integerOptional1);
    EXPECT_EQ(1111, integerOptional1.get());
    EXPECT_EQ(1111, (int)integerOptional2);    EXPECT_EQ(1111, integerOptional2.get());
}

TEST(OptionalTest, OptionalReferenceCanBeCopiedTest)
{
    // Given
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int&> integerOptional2(integerOptional1.getReference());
    AlbaOptional<int&> integerOptional3(integerOptional2);

    // When
    integerOptional3.setValue(2222);

    // Then
    EXPECT_EQ(2222, (int)integerOptional1);
    EXPECT_EQ(2222, integerOptional1.get());
    EXPECT_EQ(2222, (int)integerOptional2);    EXPECT_EQ(2222, integerOptional2.get());
    EXPECT_EQ(2222, (int)integerOptional3);
    EXPECT_EQ(2222, integerOptional3.get());
}

TEST(OptionalTest, OptionalCanBeAssignedTest)
{
    // Given
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int> integerOptional2;

    // When
    integerOptional2 = integerOptional1;

    // Then
    EXPECT_EQ(1111, (int)integerOptional1);
    EXPECT_EQ(1111, integerOptional1.get());
    EXPECT_EQ(1111, (int)integerOptional2);    EXPECT_EQ(1111, integerOptional2.get());
}

TEST(OptionalTest, OptionalReferenceCanBeAssignedTest)
{
    // Given
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int&> integerOptional2(integerOptional1.getReference());
    AlbaOptional<int&> integerOptional3;

    // When
    integerOptional3 = integerOptional2;
    integerOptional3.setValue(2222);

    // Then
    EXPECT_EQ(2222, (int)integerOptional1);
    EXPECT_EQ(2222, integerOptional1.get());
    EXPECT_EQ(2222, (int)integerOptional2);    EXPECT_EQ(2222, integerOptional2.get());
    EXPECT_EQ(2222, (int)integerOptional3);
    EXPECT_EQ(2222, integerOptional3.get());
}

TEST(OptionalTest, OptionalCanBeClearedTest)
{
    // Given
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int&> integerOptional2(integerOptional1.getReference());
    EXPECT_TRUE((bool)integerOptional1);
    EXPECT_TRUE((bool)integerOptional2);

    // When
    integerOptional1.clear();
    integerOptional2.clear();

    // Then
    EXPECT_FALSE((bool)integerOptional1);
    EXPECT_FALSE((bool)integerOptional2);
}

TEST(OptionalTest, OptionalCanBeMovedByMoveAssignmentOperatorTest)
{
    // Given
    AlbaOptional<int> integerOptional1(1111);
    AlbaOptional<int> integerOptional2;
    EXPECT_TRUE((bool)integerOptional1);
    EXPECT_FALSE((bool)integerOptional2);

    // When
    integerOptional2 = std::move(integerOptional1);

    // Then
    EXPECT_FALSE((bool)integerOptional1);
    EXPECT_TRUE((bool)integerOptional2);
    EXPECT_EQ(1111, integerOptional2.get());
}

TEST(OptionalTest, OptionalCanBeMovedByMoveContructorTest)
{
    // Given
    AlbaOptional<int> integerOptional1(1111);
    EXPECT_TRUE((bool)integerOptional1);

    // When
    AlbaOptional<int> integerOptional2(std::move(integerOptional1));

    // Then
    EXPECT_FALSE((bool)integerOptional1);
    EXPECT_TRUE((bool)integerOptional2);
    EXPECT_EQ(1111, integerOptional2.get());
}

}
