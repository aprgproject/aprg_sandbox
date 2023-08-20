#include "CommonHeaderForInlineOnTranslationUnits.hpp"

#include <gtest/gtest.h>

// Inspired by: https://medium.com/pranayaggarwal25/unnamed-namespaces-Inline-f1498741c527

namespace alba {

namespace InlineOnTranslationUnits {

// constexpr int constInteger = 110;  // Error: redefinition of 'constInteger'
// int inlineIntegerWithDefinition = 210; // Error: redefinition of 'inlineIntegerWithDefinition'
// int inlineIntegerWithDeclaration = 310; // Error: redefinition of 'inlineIntegerWithDeclaration'
inline int externInlineInteger = 410;
// static inline int staticInlineInteger = 500; // Error: redefinition of 'staticInlineInteger'
// inline std::string inlineString{"610"}; // Error: redefinition of 'inlineString'
inline int inlineIntegerAtTranslationUnit = 710;
int nonInlineAtTranslationUnit = 810;
// constexpr int SampleClassWithInline::constIntegerInClass = 1010; // Error: redefinition of 'constIntegerInClass'

int inlineFreeFunction() { return 1; }

// Utilities for tests
void restoreInitialValuesForTranslationUnit1() {
    // constInteger = 110; // const so cannot change value
    inlineIntegerWithDefinition = 210;
    inlineIntegerWithDeclaration = 310;
    externInlineInteger = 410;
    staticInlineInteger = 510;
    inlineString = "610";
    inlineIntegerAtTranslationUnit = 710;
    nonInlineAtTranslationUnit = 810;
    // SampleClassWithInline::constIntegerInClass = 1010; // const so cannot change value
}

TranslationUnitValues getValuesInTranslationUnit1() {
    return TranslationUnitValues{
        constInteger,
        inlineIntegerWithDefinition,
        inlineIntegerWithDeclaration,
        externInlineInteger,
        staticInlineInteger,
        inlineString,
        inlineIntegerAtTranslationUnit,
        nonInlineAtTranslationUnit,
        SampleClassWithInline::constIntegerInClass};
}

TEST(InlineOnTranslationUnit1Test, VariableValuesAreCorrect) {
    restoreInitialValuesForTranslationUnit1();
    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(210, inlineIntegerWithDefinition);
    EXPECT_EQ(310, inlineIntegerWithDeclaration);
    EXPECT_EQ(410, externInlineInteger);
    EXPECT_EQ(510, staticInlineInteger);
    EXPECT_EQ("610", inlineString);
    EXPECT_EQ(710, inlineIntegerAtTranslationUnit);
    EXPECT_EQ(810, nonInlineAtTranslationUnit);
    EXPECT_EQ(1000, SampleClassWithInline::constIntegerInClass);
}

TEST(InlineOnTranslationUnit1Test, VariableValuesCanBeChanged) {
    restoreInitialValuesForTranslationUnit1();
    // constInteger = 111; // const so cannot change value
    inlineIntegerWithDefinition = 211;
    inlineIntegerWithDeclaration = 311;
    externInlineInteger = 411;
    staticInlineInteger = 511;
    inlineString = "611";
    inlineIntegerAtTranslationUnit = 711;
    nonInlineAtTranslationUnit = 811;
    // SampleClassWithInline::constIntegerInClass = 1011; // const so cannot change value

    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(211, inlineIntegerWithDefinition);
    EXPECT_EQ(311, inlineIntegerWithDeclaration);
    EXPECT_EQ(411, externInlineInteger);
    EXPECT_EQ(511, staticInlineInteger);
    EXPECT_EQ("611", inlineString);
    EXPECT_EQ(711, inlineIntegerAtTranslationUnit);
    EXPECT_EQ(811, nonInlineAtTranslationUnit);
    EXPECT_EQ(1000, SampleClassWithInline::constIntegerInClass);
    restoreInitialValuesForTranslationUnit1();
}

TEST(InlineOnTranslationUnit1Test, VariableValuesOnOtherTranslationUnit) {
    restoreInitialValuesForTranslationUnit2();
    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit2());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_EQ(220, otherTranslationUnitValues.inlineIntegerWithDefinition);
    EXPECT_EQ(320, otherTranslationUnitValues.inlineIntegerWithDeclaration);
    EXPECT_EQ(420, otherTranslationUnitValues.externInlineInteger);
    EXPECT_EQ(520, otherTranslationUnitValues.staticInlineInteger);  // static overrides inline
    EXPECT_EQ("620", otherTranslationUnitValues.inlineString);
    EXPECT_EQ(720, otherTranslationUnitValues.inlineIntegerAtTranslationUnit);
    EXPECT_EQ(0, otherTranslationUnitValues.nonInlineAtTranslationUnit);  // does not exist TranslationUnit2
    EXPECT_EQ(1000, SampleClassWithInline::constIntegerInClass);
}

TEST(InlineOnTranslationUnit1Test, VariableValuesAreChangedAndReflectedOnOtherTranslationUnit) {
    restoreInitialValuesForTranslationUnit1();
    restoreInitialValuesForTranslationUnit2();
    // constInteger = 112; // const so cannot change value
    inlineIntegerWithDefinition = 212;
    inlineIntegerWithDeclaration = 312;
    externInlineInteger = 412;
    staticInlineInteger = 512;
    inlineString = "612";
    inlineIntegerAtTranslationUnit = 712;
    nonInlineAtTranslationUnit = 812;
    // SampleClassWithInline::constIntegerInClass = 1012; // const so cannot change value

    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit2());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_EQ(212, otherTranslationUnitValues.inlineIntegerWithDefinition);
    EXPECT_EQ(312, otherTranslationUnitValues.inlineIntegerWithDeclaration);
    EXPECT_EQ(412, otherTranslationUnitValues.externInlineInteger);
    EXPECT_EQ(520, otherTranslationUnitValues.staticInlineInteger);  // static overrides inline
    EXPECT_EQ("612", otherTranslationUnitValues.inlineString);
    EXPECT_EQ(712, otherTranslationUnitValues.inlineIntegerAtTranslationUnit);
    EXPECT_EQ(0, otherTranslationUnitValues.nonInlineAtTranslationUnit);  // does not exist TranslationUnit2
    EXPECT_EQ(1000, SampleClassWithInline::constIntegerInClass);
    restoreInitialValuesForTranslationUnit1();
    restoreInitialValuesForTranslationUnit2();
}

TEST(InlineOnTranslationUnit1Test, FunctionReturnValuesAreCorrect) {
    EXPECT_EQ(1, freeFunction());
    EXPECT_EQ(1, inlineFreeFunction());
}

}  // namespace InlineOnTranslationUnits

}  // namespace alba
