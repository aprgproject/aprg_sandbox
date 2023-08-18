#include "CommonHeaderForStaticOnTranslationUnits.hpp"

#include <gtest/gtest.h>

// Inspired by: https://medium.com/pranayaggarwal25/unnamed-namespaces-static-f1498741c527

namespace alba {

namespace StaticOnTranslationUnits {

// constexpr int constInteger = 120;  // Error: redefinition of 'constInteger'
// static int staticInteger = 220;    // Error: redefinition of 'staticInteger'

// int integer = 320;  // conflicts with TranslationUnit1
// explicitly extern (external linkage)
extern int externInteger;  // only a declaration (incomplete type)
// int externInteger = 420;   // conflicts with TranslationUnit1
// explicitly extern (external linkage)
extern const int externConstInteger;  // only a declaration (incomplete type)
// const int externConstInteger = 520;   // conflicts with TranslationUnit1

// int freeFunction() { return 2; } // conflicts with TranslationUnit1
int staticFreeFunction() { return 2; }
// if this is not defined, errors will occur because its used on this translation unit.

// Utilities for tests
void restoreInitialValuesForTranslationUnit2() {
    // constInteger = 120; // const so cannot change value
    staticInteger = 220;
    // integer = 320; // conflicts with TranslationUnit1
    externInteger = 420;
    // externConstInteger = 520;  // const so cannot change value
}

TranslationUnitValues getValuesInTranslationUnit2() {
    return TranslationUnitValues{constInteger, staticInteger, 0, externInteger, externConstInteger};
}

TEST(StaticOnTranslationUnit2Test, VariableValuesAreCorrect) {
    restoreInitialValuesForTranslationUnit2();
    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(220, staticInteger);
    // EXPECT_EQ(320, integer); // conflicts with TranslationUnit1
    EXPECT_EQ(420, externInteger);
    EXPECT_EQ(510, externConstInteger);
}

TEST(StaticOnTranslationUnit2Test, VariableValuesCanBeChanged) {
    restoreInitialValuesForTranslationUnit2();
    // constInteger = 121; // const so cannot change value
    staticInteger = 221;
    // integer = 321; // conflicts with TranslationUnit1
    externInteger = 421;
    // externConstInteger = 521; // const so cannot change value

    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(221, staticInteger);
    // EXPECT_EQ(321, integer); // conflicts with TranslationUnit1
    EXPECT_EQ(421, externInteger);
    EXPECT_EQ(510, externConstInteger);
    restoreInitialValuesForTranslationUnit2();
}

TEST(StaticOnTranslationUnit2Test, VariableValuesOnOtherTranslationUnit) {
    restoreInitialValuesForTranslationUnit1();
    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit1());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_EQ(210, otherTranslationUnitValues.staticInteger);
    EXPECT_EQ(310, otherTranslationUnitValues.integer);
    EXPECT_EQ(410, otherTranslationUnitValues.externInteger);
    EXPECT_EQ(510, otherTranslationUnitValues.externConstInteger);
}

TEST(StaticOnTranslationUnit2Test, VariableValuesAreChangedAndReflectedOnOtherTranslationUnit) {
    restoreInitialValuesForTranslationUnit1();
    restoreInitialValuesForTranslationUnit2();
    // constInteger = 122; // const so cannot change value
    staticInteger = 222;
    // integer = 322; // conflicts with TranslationUnit1
    externInteger = 422;
    // externConstInteger = 522; // const so cannot change value

    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit1());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_EQ(210, otherTranslationUnitValues.staticInteger);
    EXPECT_EQ(310, otherTranslationUnitValues.integer);
    EXPECT_EQ(422, otherTranslationUnitValues.externInteger);
    EXPECT_EQ(510, otherTranslationUnitValues.externConstInteger);
    restoreInitialValuesForTranslationUnit1();
    restoreInitialValuesForTranslationUnit2();
}

TEST(StaticOnTranslationUnit2Test, FunctionReturnValuesAreCorrect) {    EXPECT_EQ(1, freeFunction());
    EXPECT_EQ(2, staticFreeFunction());
}
}  // namespace StaticOnTranslationUnits

}  // namespace alba
