#include "CommonHeaderForInlineOnTranslationUnits.hpp"

#include <gtest/gtest.h>

// Inspired by: https://medium.com/pranayaggarwal25/unnamed-namespaces-Inline-f1498741c527

namespace alba
{

namespace InlineOnTranslationUnits
{

//int inlineIntegerWithDeclaration=300; // Error: redefinition of 'inlineIntegerWithDeclaration'
inline int inlineIntegerAtTranslationUnit=410;
int nonInlineAtTranslationUnit=500;
//inline int nonInlineAtTranslationUnit=500; // Error: inline declaration of 'nonInlineAtTranslationUnit' follows non-inline definition
inline int externInlineInteger=610; // definition (complete type), different definition (results in undefined behavior)

int inlineFreeFunction()
{
    return 1;
}



// Utilities for tests
TranslationUnitValues getValuesInTranslationUnit1()
{
    return TranslationUnitValues{
        constInteger,
                inlineIntegerWithDefinition,
                inlineIntegerWithDeclaration,
                inlineIntegerAtTranslationUnit,
                nonInlineAtTranslationUnit,
                externInlineInteger,
                inlineString};
}

TEST(InlineOnTranslationUnit1Test, DISABLED_VariableValuesAreCorrect) // Flaky test
{
    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(200, inlineIntegerWithDefinition);
    EXPECT_EQ(0, inlineIntegerWithDeclaration);
    EXPECT_EQ(410, inlineIntegerAtTranslationUnit);
    EXPECT_EQ(500, nonInlineAtTranslationUnit);
    EXPECT_EQ(610, externInlineInteger);
    EXPECT_EQ("700", inlineString);
    EXPECT_EQ(1000, SampleClassWithInline::constIntegerInClass);
}

TEST(InlineOnTranslationUnit1Test, VariableValuesCanBeChanged)
{
    //constInteger = 101; // Const cannot change
    inlineIntegerWithDefinition = 201;
    inlineIntegerWithDeclaration = 301;
    inlineIntegerAtTranslationUnit = 411;
    nonInlineAtTranslationUnit = 501;
    externInlineInteger = 611;
    inlineString = "701";

    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(201, inlineIntegerWithDefinition);
    EXPECT_EQ(301, inlineIntegerWithDeclaration);
    EXPECT_EQ(411, inlineIntegerAtTranslationUnit);
    EXPECT_EQ(501, nonInlineAtTranslationUnit);
    EXPECT_EQ(611, externInlineInteger);
    EXPECT_EQ("701", inlineString);
}

TEST(InlineOnTranslationUnit1Test, VariableValuesAreChangedAndReflectedOnOtherTranslationUnit)
{
    //constInteger = 102; // Const cannot change
    inlineIntegerWithDefinition = 202;
    inlineIntegerWithDeclaration = 302;
    inlineIntegerAtTranslationUnit = 412;
    nonInlineAtTranslationUnit = 502;
    externInlineInteger = 612;
    inlineString = "702";

    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit2());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_EQ(202, otherTranslationUnitValues.inlineIntegerWithDefinition);
    EXPECT_EQ(302, otherTranslationUnitValues.inlineIntegerWithDeclaration);
    EXPECT_EQ(412, otherTranslationUnitValues.inlineIntegerAtTranslationUnit);
    EXPECT_EQ(0, otherTranslationUnitValues.nonInlineAtTranslationUnit); // no "nonInlineAtTranslationUnit" on Translation Unit 2
    EXPECT_EQ(612, otherTranslationUnitValues.externInlineInteger);
    EXPECT_EQ("702", otherTranslationUnitValues.inlineString);
}

TEST(InlineOnTranslationUnit1Test, FunctionReturnValuesAreCorrect)
{
    EXPECT_EQ(1, freeFunction());
    EXPECT_EQ(1, inlineFreeFunction());
}

}

}
