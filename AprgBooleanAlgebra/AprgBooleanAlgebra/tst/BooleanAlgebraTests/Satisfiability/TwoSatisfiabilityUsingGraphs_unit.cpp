#include <BooleanAlgebra/Satisfiability/TwoSatisfiabilityUsingGraphs.hpp>
#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;

namespace alba {

namespace booleanAlgebra {

TEST(TwoSatisfiabilityUsingGraphsTest, ExampleWithCompleteSolution) {
    Term termToTest(buildTermIfPossible("(x2|~x1)&(~x1|~x2)&(x1|x3)&(~x2|~x3)&(x1|x4)"));
    SatisfiabilityTerms satTermsToTest(getSatisfiabilityTerms(termToTest));
    TwoSatisfiabilityUsingGraphs twoSat(satTermsToTest);

    EXPECT_TRUE(twoSat.hasSolution());
    EXPECT_EQ("(x1'&x2'&x3&x4)", convertToString(twoSat.getSolution()));
}

TEST(TwoSatisfiabilityUsingGraphsTest, ExampleWithIncompleteSolution) {
    Term termToTest(buildTermIfPossible("(x1|x2)&(~x1|~x2)"));
    SatisfiabilityTerms satTermsToTest(getSatisfiabilityTerms(termToTest));
    TwoSatisfiabilityUsingGraphs twoSat(satTermsToTest);

    EXPECT_TRUE(twoSat.hasSolution());
    EXPECT_EQ("(x1&x2')", convertToString(twoSat.getSolution()));
}

TEST(TwoSatisfiabilityUsingGraphsTest, ExampleWithNoSolution) {
    Term termToTest(buildTermIfPossible("(x1|x2)^(x1|~x2)^(~x1|x3)^(~x1|~x3)"));
    SatisfiabilityTerms satTermsToTest(getSatisfiabilityTerms(termToTest));
    TwoSatisfiabilityUsingGraphs twoSat(satTermsToTest);

    EXPECT_TRUE(twoSat.hasSolution());
    EXPECT_TRUE(twoSat.getSolution().isEmpty());
}

}  // namespace booleanAlgebra

}  // namespace alba
