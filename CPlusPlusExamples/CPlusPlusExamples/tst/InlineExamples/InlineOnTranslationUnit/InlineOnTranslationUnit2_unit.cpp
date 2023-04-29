#include "CommonHeaderForInlineOnTranslationUnits.hpp"

#include <gtest/gtest.h>

// Inspired by: https://medium.com/pranayaggarwal25/unnamed-namespaces-Inline-f1498741c527

namespace alba {

namespace InlineOnTranslationUnits {

// int inlineIntegerWithDeclaration=300; // Error: redefinition of 'inlineIntegerWithDeclaration'
inline int inlineIntegerAtTranslationUnit = 420;  // different definition (results in undefined behavior)
// int nonInlineAtTranslationUnit=500; // Linker error: multiple definition of
// 'alba::InlineOnTranslationUnits::nonInlineAtTranslationUnit'
inline int externInlineInteger =
    620;  // definition (complete type), different definition (results in undefined behavior)

int inlineFreeFunction()  // different definition (results in undefined behavior)
{
    // inline int sampleVariable=100; // Error: inline declaration of 'sampleVariable' not allowed in block scope
    return 2;
}

// Utilities for tests
TranslationUnitValues getValuesInTranslationUnit2() {
    return TranslationUnitValues{
        constInteger,
        inlineIntegerWithDefinition,
        inlineIntegerWithDeclaration,
        inlineIntegerAtTranslationUnit,
        0,
        externInlineInteger,
        staticInlineInteger,
        inlineString};
}

TEST(InlineOnTranslationUnit2Test, DISABLED_VariableValuesAreCorrect)  // Flaky test
{
    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(200, inlineIntegerWithDefinition);
    EXPECT_EQ(0, inlineIntegerWithDeclaration);
    EXPECT_EQ(410, inlineIntegerAtTranslationUnit);
    // Undefined behavior really but in this case in takes the implementation from TranslationUnit1
    // EXPECT_EQ(0, nonInlineAtTranslationUnit); // conflicts with TranslationUnit1
    EXPECT_EQ(610, externInlineInteger);
    EXPECT_EQ(700, staticInlineInteger);
    EXPECT_EQ("800", inlineString);
    EXPECT_EQ(1000, SampleClassWithInline::constIntegerInClass);
}

TEST(InlineOnTranslationUnit2Test, VariableValuesCanBeChanged) {
    // constInteger = 101; // Const cannot change
    inlineIntegerWithDefinition = 201;
    inlineIntegerWithDeclaration = 301;
    inlineIntegerAtTranslationUnit = 411;
    externInlineInteger = 611;
    staticInlineInteger = 711;
    inlineString = "801";

    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(201, inlineIntegerWithDefinition);
    EXPECT_EQ(301, inlineIntegerWithDeclaration);
    EXPECT_EQ(411, inlineIntegerAtTranslationUnit);
    // EXPECT_EQ(0, nonInlineAtTranslationUnit); // conflicts with TranslationUnit1
    EXPECT_EQ(611, externInlineInteger);
    EXPECT_EQ(711, staticInlineInteger);
    EXPECT_EQ("801", inlineString);
}

TEST(InlineOnTranslationUnit2Test, VariableValuesAreChangedAndReflectedOnOtherTranslationUnit) {
    // constInteger = 103; // Const cannot change
    inlineIntegerWithDefinition = 203;
    inlineIntegerWithDeclaration = 303;
    inlineIntegerAtTranslationUnit = 413;
    // nonInlineAtTranslationUnit = 503; // no "nonInlineAtTranslationUnit" here because it conflicts with
    // TranslationUnit1
    externInlineInteger = 613;
    staticInlineInteger = 713;
    inlineString = "803";

    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit1());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_EQ(203, otherTranslationUnitValues.inlineIntegerWithDefinition);
    EXPECT_EQ(303, otherTranslationUnitValues.inlineIntegerWithDeclaration);
    EXPECT_EQ(413, otherTranslationUnitValues.inlineIntegerAtTranslationUnit);
    EXPECT_EQ(500, otherTranslationUnitValues.nonInlineAtTranslationUnit);
    EXPECT_EQ(613, otherTranslationUnitValues.externInlineInteger);
    EXPECT_EQ(700, otherTranslationUnitValues.staticInlineInteger);  // static overrides inline
    EXPECT_EQ("803", otherTranslationUnitValues.inlineString);
}

TEST(InlineOnTranslationUnit2Test, FunctionReturnValuesAreCorrect) {
    EXPECT_EQ(1, freeFunction());
    // EXPECT_EQ(1, inlineFreeFunction()); // Undefined behavior really but in this case in takes the implementation
    // from TranslationUnit1
}

}  // namespace InlineOnTranslationUnits

}  // namespace alba
