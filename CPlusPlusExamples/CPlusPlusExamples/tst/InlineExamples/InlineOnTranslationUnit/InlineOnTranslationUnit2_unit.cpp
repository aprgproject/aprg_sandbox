#include "CommonHeaderForInlineOnTranslationUnits.hpp"

#include <gtest/gtest.h>

// Inspired by: https://medium.com/pranayaggarwal25/unnamed-namespaces-Inline-f1498741c527

namespace alba {

namespace InlineOnTranslationUnits {

// constexpr int constInteger = 120;  // Error: redefinition of 'constInteger'
// int inlineIntegerWithDefinition = 220; // Error: redefinition of 'inlineIntegerWithDefinition'
// int inlineIntegerWithDeclaration = 320; // Error: redefinition of 'inlineIntegerWithDeclaration'
inline int externInlineInteger = 420;
// static inline int staticInlineInteger = 500; // Error: redefinition of 'staticInlineInteger'
// inline std::string inlineString{"620"}; // Error: redefinition of 'inlineString'
inline int inlineIntegerAtTranslationUnit = 720;
// int nonInlineAtTranslationUnit = 820; // conflicts with TranslationUnit1
// constexpr int SampleClassWithInline::constIntegerInClass = 1020; // Error: redefinition of 'constIntegerInClass'

int inlineFreeFunction() {
    // inline int sampleVariable=100; // Error: inline declaration of 'sampleVariable' not allowed in block scope
    return 2;
}

// Utilities for tests
void restoreInitialValuesForTranslationUnit2() {
    // constInteger = 120; // const so cannot change value
    inlineIntegerWithDefinition = 220;
    inlineIntegerWithDeclaration = 320;
    externInlineInteger = 420;
    staticInlineInteger = 520;
    inlineString = "620";
    inlineIntegerAtTranslationUnit = 720;
    // nonInlineAtTranslationUnit = 820; // conflicts with TranslationUnit1
    // SampleClassWithInline::constIntegerInClass = 1020; // const so cannot change value
}

TranslationUnitValues getValuesInTranslationUnit2() {
    return TranslationUnitValues{
        constInteger,
        inlineIntegerWithDefinition,
        inlineIntegerWithDeclaration,
        externInlineInteger,
        staticInlineInteger,
        inlineString,
        inlineIntegerAtTranslationUnit,
        0,  // nonInlineAtTranslationUnit, // conflicts with TranslationUnit1
        SampleClassWithInline::constIntegerInClass};
}

TEST(InlineOnTranslationUnit2Test, VariableValuesAreCorrect) {
    restoreInitialValuesForTranslationUnit2();
    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(220, inlineIntegerWithDefinition);
    EXPECT_EQ(320, inlineIntegerWithDeclaration);
    EXPECT_EQ(420, externInlineInteger);
    EXPECT_EQ(520, staticInlineInteger);
    EXPECT_EQ("620", inlineString);
    EXPECT_EQ(720, inlineIntegerAtTranslationUnit);
    // EXPECT_EQ(820, nonInlineAtTranslationUnit); // conflicts with TranslationUnit1
    EXPECT_EQ(1000, SampleClassWithInline::constIntegerInClass);
}

TEST(InlineOnTranslationUnit2Test, VariableValuesCanBeChanged) {
    restoreInitialValuesForTranslationUnit2();
    // constInteger = 121; // const so cannot change value
    inlineIntegerWithDefinition = 221;
    inlineIntegerWithDeclaration = 321;
    externInlineInteger = 421;
    staticInlineInteger = 521;
    inlineString = "621";
    inlineIntegerAtTranslationUnit = 721;
    // nonInlineAtTranslationUnit = 821; // conflicts with TranslationUnit1
    // SampleClassWithInline::constIntegerInClass = 1021; // const so cannot change value

    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(221, inlineIntegerWithDefinition);
    EXPECT_EQ(321, inlineIntegerWithDeclaration);
    EXPECT_EQ(421, externInlineInteger);
    EXPECT_EQ(521, staticInlineInteger);
    EXPECT_EQ("621", inlineString);
    EXPECT_EQ(721, inlineIntegerAtTranslationUnit);
    // EXPECT_EQ(822, nonInlineAtTranslationUnit); // conflicts with TranslationUnit1
    EXPECT_EQ(1000, SampleClassWithInline::constIntegerInClass);
    restoreInitialValuesForTranslationUnit2();
}

TEST(InlineOnTranslationUnit2Test, VariableValuesOnOtherTranslationUnit) {
    restoreInitialValuesForTranslationUnit1();
    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit1());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_EQ(210, otherTranslationUnitValues.inlineIntegerWithDefinition);
    EXPECT_EQ(310, otherTranslationUnitValues.inlineIntegerWithDeclaration);
    EXPECT_EQ(410, otherTranslationUnitValues.externInlineInteger);
    EXPECT_EQ(510, otherTranslationUnitValues.staticInlineInteger);  // static overrides inline
    EXPECT_EQ("610", otherTranslationUnitValues.inlineString);
    EXPECT_EQ(710, otherTranslationUnitValues.inlineIntegerAtTranslationUnit);
    EXPECT_EQ(810, otherTranslationUnitValues.nonInlineAtTranslationUnit);
    EXPECT_EQ(1000, SampleClassWithInline::constIntegerInClass);
}

TEST(InlineOnTranslationUnit2Test, VariableValuesAreChangedAndReflectedOnOtherTranslationUnit) {
    restoreInitialValuesForTranslationUnit1();
    restoreInitialValuesForTranslationUnit2();
    // constInteger = 122; // const so cannot change value
    inlineIntegerWithDefinition = 222;
    inlineIntegerWithDeclaration = 322;
    externInlineInteger = 422;
    staticInlineInteger = 522;
    inlineString = "622";
    inlineIntegerAtTranslationUnit = 722;
    // nonInlineAtTranslationUnit = 822; // conflicts with TranslationUnit1
    // SampleClassWithInline::constIntegerInClass = 1022; // const so cannot change value

    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit1());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_EQ(222, otherTranslationUnitValues.inlineIntegerWithDefinition);
    EXPECT_EQ(322, otherTranslationUnitValues.inlineIntegerWithDeclaration);
    EXPECT_EQ(422, otherTranslationUnitValues.externInlineInteger);
    EXPECT_EQ(510, otherTranslationUnitValues.staticInlineInteger);  // static overrides inline
    EXPECT_EQ("622", otherTranslationUnitValues.inlineString);
    EXPECT_EQ(722, otherTranslationUnitValues.inlineIntegerAtTranslationUnit);
    EXPECT_EQ(810, otherTranslationUnitValues.nonInlineAtTranslationUnit);
    EXPECT_EQ(1000, otherTranslationUnitValues.constIntegerInClass);
    restoreInitialValuesForTranslationUnit1();
    restoreInitialValuesForTranslationUnit2();
}

TEST(InlineOnTranslationUnit2Test, FunctionReturnValuesAreCorrect) {
    EXPECT_EQ(1, freeFunction());
    EXPECT_EQ(1, inlineFreeFunction());
}

}  // namespace InlineOnTranslationUnits

}  // namespace alba
