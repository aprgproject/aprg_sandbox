#include "SampleClassWithStatic.hpp"

#include <gtest/gtest.h>

namespace alba
{

TEST(SampleClassWithStaticTest, InitialValuesAreCorrect)
{
    SampleClassWithStatic object1;
    SampleClassWithStatic object2;

    EXPECT_EQ(100, object1.nonStaticData);
    EXPECT_EQ(100, object2.nonStaticData);
    EXPECT_EQ(200, SampleClassWithStatic::staticData);
    EXPECT_EQ(300, SampleClassWithStatic::staticConstData);
    EXPECT_EQ(400, SampleClassWithStatic::staticInlinedData);
}

TEST(SampleClassWithStaticTest, StaticDataCanBeReferedInSeveralWays)
{
    SampleClassWithStatic object;

    EXPECT_EQ(200, SampleClassWithStatic::staticData);
    EXPECT_EQ(300, SampleClassWithStatic::staticConstData);
    EXPECT_EQ(400, SampleClassWithStatic::staticInlinedData);

    EXPECT_EQ(200, object.staticData);
    EXPECT_EQ(300, object.staticConstData);
    EXPECT_EQ(400, object.staticInlinedData);
}

TEST(SampleClassWithStaticTest, ValuesCanBeChanged)
{
    SampleClassWithStatic object1;
    SampleClassWithStatic object2;

    object1.nonStaticData=101;
    SampleClassWithStatic::staticData=201;
    // SampleClassWithStatic::staticConstData=301; // can't be changed because its const
    SampleClassWithStatic::staticInlinedData=401;

    EXPECT_EQ(101, object1.nonStaticData);
    EXPECT_EQ(100, object2.nonStaticData);
    EXPECT_EQ(201, SampleClassWithStatic::staticData);
    EXPECT_EQ(300, SampleClassWithStatic::staticConstData);
    EXPECT_EQ(401, SampleClassWithStatic::staticInlinedData);
}

TEST(SampleClassWithStaticTest, ClassDeclaredFunctionsCanCalledWithChangedValues)
{
    SampleClassWithStatic object1;
    SampleClassWithStatic object2;

    object1.nonStaticData=101;
    SampleClassWithStatic::staticData=201;

    EXPECT_EQ(101, object1.nonStaticFunctionWithClassDeclaration());
    EXPECT_EQ(201, SampleClassWithStatic::staticFunctionWithClassDeclaration());
    EXPECT_EQ(100, object2.nonStaticFunctionWithClassDeclaration());
    EXPECT_EQ(201, object2.staticFunctionWithClassDeclaration());
}

TEST(SampleClassWithStaticTest, ClassDefinedFunctionsCanCalledWithChangedValues)
{
    SampleClassWithStatic object1;
    SampleClassWithStatic object2;

    object1.nonStaticData=101;
    SampleClassWithStatic::staticData=201;

    EXPECT_EQ(101, object1.nonStaticFunctionWithClassDefinition());
    EXPECT_EQ(201, SampleClassWithStatic::staticFunctionWithClassDefinition());
    EXPECT_EQ(100, object2.nonStaticFunctionWithClassDefinition());
    EXPECT_EQ(201, object2.staticFunctionWithClassDefinition());
}

}
