#include "CommonHeaderForStaticOnTranslationUnits.hpp"

#include <gtest/gtest.h>

// Inspired by: https://medium.com/pranayaggarwal25/unnamed-namespaces-static-f1498741c527

namespace alba {

namespace StaticOnTranslationUnits {

// constexpr int constInteger = 110;  // Error: redefinition of 'constInteger'
// static int staticInteger = 210;    // Error: redefinition of 'staticInteger'

int integer = 310;  // extern (external linkage) by default
// explicitly extern (external linkage)
extern int externInteger;  // only a declaration (incomplete type)
int externInteger = 410;   // definition (complete type)
// explicitly extern (external linkage)
extern const int externConstInteger;  // only a declaration (incomplete type)
const int externConstInteger = 510;   // definition (complete type)

int freeFunction() { return 1; }
int staticFreeFunction() { return 1; }

// Utilities for tests
void restoreInitialValuesForTranslationUnit1() {
    // constInteger = 110; // const so cannot change value
    staticInteger = 210;
    integer = 310;
    externInteger = 410;
    // externConstInteger = 510;  // const so cannot change value
}

TranslationUnitValues getValuesInTranslationUnit1() {
    return TranslationUnitValues{constInteger, staticInteger, integer, externInteger, externConstInteger};
}

TEST(StaticOnTranslationUnit1Test, VariableValuesAreCorrect) {
    restoreInitialValuesForTranslationUnit1();
    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(210, staticInteger);
    EXPECT_EQ(310, integer);
    EXPECT_EQ(410, externInteger);
    EXPECT_EQ(510, externConstInteger);
}

TEST(StaticOnTranslationUnit1Test, VariableValuesCanBeChanged) {
    restoreInitialValuesForTranslationUnit1();
    // constInteger = 111; // const so cannot change value
    staticInteger = 211;
    integer = 311;
    externInteger = 411;
    // externConstInteger = 511; // const so cannot change value

    EXPECT_EQ(100, constInteger);
    EXPECT_EQ(211, staticInteger);
    EXPECT_EQ(311, integer);
    EXPECT_EQ(411, externInteger);
    EXPECT_EQ(510, externConstInteger);
    restoreInitialValuesForTranslationUnit1();
}

TEST(StaticOnTranslationUnit1Test, VariableValuesOnOtherTranslationUnit) {
    restoreInitialValuesForTranslationUnit2();
    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit2());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_EQ(220, otherTranslationUnitValues.staticInteger);
    EXPECT_EQ(0, otherTranslationUnitValues.integer);  // does not exist TranslationUnit2
    EXPECT_EQ(420, otherTranslationUnitValues.externInteger);
    EXPECT_EQ(510, otherTranslationUnitValues.externConstInteger);
}

TEST(StaticOnTranslationUnit1Test, VariableValuesAreChangedAndReflectedOnOtherTranslationUnit) {
    restoreInitialValuesForTranslationUnit1();
    restoreInitialValuesForTranslationUnit2();
    // constInteger = 112; // const so cannot change value
    staticInteger = 212;
    integer = 312;
    externInteger = 412;
    // externConstInteger = 512; // const so cannot change value

    TranslationUnitValues otherTranslationUnitValues(getValuesInTranslationUnit2());
    EXPECT_EQ(100, otherTranslationUnitValues.constInteger);
    EXPECT_EQ(220, otherTranslationUnitValues.staticInteger);
    EXPECT_EQ(0, otherTranslationUnitValues.integer);  // does not exist TranslationUnit2
    EXPECT_EQ(412, otherTranslationUnitValues.externInteger);
    EXPECT_EQ(510, otherTranslationUnitValues.externConstInteger);
    restoreInitialValuesForTranslationUnit1();
    restoreInitialValuesForTranslationUnit2();
}

TEST(StaticOnTranslationUnit1Test, FunctionReturnValuesAreCorrect) {    EXPECT_EQ(1, freeFunction());
    EXPECT_EQ(1, staticFreeFunction());
}
}  // namespace StaticOnTranslationUnits

}  // namespace alba
