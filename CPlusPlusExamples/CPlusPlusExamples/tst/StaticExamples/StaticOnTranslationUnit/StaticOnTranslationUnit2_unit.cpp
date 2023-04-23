#include "CommonHeaderForStaticOnTranslationUnits.hpp"

#include <gtest/gtest.h>

// Inspired by: https://medium.com/pranayaggarwal25/unnamed-namespaces-static-f1498741c527

namespace alba
{

namespace StaticOnTranslationUnits
{

// int integer; // extern(external linkage) by default, cannot redefine here because it conflicts with TranslationUnit1
extern int externInteger;  // explicitly extern(external linkage), only a declaration and not a definitionextern const int externConstInteger; // explicitly extern(external linkage), only a declaration and not a definition

// Cannot redefine freeFunction because its already defined in TranslationUnit1
// int freeFunction()// {
//     return 2;
// }

int staticFreeFunction() // if this is not defined, errors will occur because its used on this translation unit.
{
    return 2;
}

// Utilities for tests
TranslationUnitValues getValuesInTranslationUnit2()
{
    return TranslationUnitValues{constInteger, staticInteger, 0, externInteger, externConstInteger};
}

TEST(StaticOnTranslationUnit2Test, DISABLED_VariableValuesAreCorrect) // Flaky test
{
    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(200, staticInteger);    //EXPECT_EQ(300, integer); // no "integer" here because it conflicts with TranslationUnit1
    EXPECT_EQ(400, externInteger);
    EXPECT_EQ(500, externConstInteger);
}

TEST(StaticOnTranslationUnit2Test, VariableValuesCanBeChanged)
{
    //constInteger = 101; // Const cannot change
    staticInteger = 201;    //integer = 301; // no "integer" here because it conflicts with TranslationUnit1
    externInteger = 401;
    //externConstInteger = 501; // Const cannot change
    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(201, staticInteger);
    //EXPECT_EQ(301, integer); // no "integer" here because it conflicts with TranslationUnit1
    EXPECT_EQ(401, externInteger);
    EXPECT_EQ(500, externConstInteger);
}

TEST(StaticOnTranslationUnit2Test, VariableValuesAreChangedAndReflectedOnOtherTranslationUnit)
{
    //constInteger = 103; // Const cannot change
    staticInteger = 203;    // integer = 303; // no "integer" here because it conflicts with TranslationUnit1
    externInteger = 403;
    //externConstInteger = 503; // Const cannot change
    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit1());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_NE(203, otherTranslationUnitValues.staticInteger); // not equal
    EXPECT_EQ(300, otherTranslationUnitValues.integer);
    EXPECT_EQ(403, otherTranslationUnitValues.externInteger);
    EXPECT_EQ(500, otherTranslationUnitValues.externConstInteger);
}

TEST(StaticOnTranslationUnit2Test, FunctionReturnValuesAreCorrect)
{
    EXPECT_EQ(1, freeFunction());
    EXPECT_EQ(2, staticFreeFunction());
}

}

}