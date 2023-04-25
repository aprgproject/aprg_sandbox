#include <BooleanAlgebra/Simplification/SimplificationUtilities.hpp>
#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::booleanAlgebra::Simplification;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace booleanAlgebra {

TEST(ComboTest, Example1) {
    Term termToTest(buildTermIfPossible("(x2|~x1)&(~x1|~x2)&(x1|x3)&(~x2|~x3)&(x1|x4)"));

    simplifyTermWithOuterOrAndInnerAnd(termToTest);

    string stringToVerify(convertToString(termToTest));
    string stringToExpect("(x1'&x2'&x3&x4)");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

TEST(ComboTest, Example2) {
    Term termToTest(buildTermIfPossible("(x1|x2)&(~x1|~x2)"));

    simplifyTermWithOuterOrAndInnerAnd(termToTest);

    string stringToVerify(convertToString(termToTest));
    string stringToExpect("((x1&x2')|(x1'&x2))");
    EXPECT_EQ(stringToExpect, stringToVerify);
}

}  // namespace booleanAlgebra

}  // namespace alba
