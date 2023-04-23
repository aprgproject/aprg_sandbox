#include "CommonHeaderForStaticOnTranslationUnits.hpp"

#include <gtest/gtest.h>

// Inspired by: https://medium.com/pranayaggarwal25/unnamed-namespaces-static-f1498741c527

namespace alba
{

namespace StaticOnTranslationUnits
{

int integer=300; // extern(external linkage) by default
extern int externInteger;  // explicitly extern(external linkage), only a declaration (incomplete type) and not a definition
extern const int externConstInteger; // explicitly extern(external linkage), only a declaration (incomplete type) and not a definition

int externInteger = 400;  // definition (complete type)
const int externConstInteger = 500;  // definition (complete type)

int freeFunction()
{    return 1;
}

int staticFreeFunction(){
    return 1;
}


// Utilities for tests
TranslationUnitValues getValuesInTranslationUnit1()
{
    return TranslationUnitValues{constInteger, staticInteger, integer, externInteger, externConstInteger};
}

TEST(StaticOnTranslationUnit1Test, DISABLED_VariableValuesAreCorrect) // Flaky test
{
    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(200, staticInteger);    EXPECT_EQ(300, integer);
    EXPECT_EQ(400, externInteger);
    EXPECT_EQ(500, externConstInteger);
}

TEST(StaticOnTranslationUnit1Test, VariableValuesCanBeChanged)
{
    //constInteger = 101; // Const cannot change
    staticInteger = 201;    integer = 301;
    externInteger = 401;
    //externConstInteger = 501; // Const cannot change
    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(201, staticInteger);
    EXPECT_EQ(301, integer);
    EXPECT_EQ(401, externInteger);
    EXPECT_EQ(500, externConstInteger);
}

TEST(StaticOnTranslationUnit1Test, VariableValuesAreChangedAndReflectedOnOtherTranslationUnit)
{
    //constInteger = 102; // Const cannot change
    staticInteger = 202;    integer = 302;
    externInteger = 402;
    //externConstInteger = 502; // Const cannot change

    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit2());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_NE(202, otherTranslationUnitValues.staticInteger); // not equal
    EXPECT_EQ(0, otherTranslationUnitValues.integer); // no "integer" on Translation Unit 2
    EXPECT_EQ(402, otherTranslationUnitValues.externInteger);
    EXPECT_EQ(500, otherTranslationUnitValues.externConstInteger);
}

TEST(StaticOnTranslationUnit1Test, FunctionReturnValuesAreCorrect)
{
    EXPECT_EQ(1, freeFunction());
    EXPECT_EQ(1, staticFreeFunction());
}

}

}