#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algebra {

TEST(SeriesBasedOnSummationTest, ConstructionWorks) { SeriesBasedOnSummation("n", "n"); }

TEST(SeriesBasedOnSummationTest, IsConvergentWorksWhenSummationModelIsValid) {
    Term exponent(Polynomial{Monomial(1, {}), Monomial(-1, {{"n", 1}})});
    Term formula(createExpressionIfPossible({2, "^", exponent}));
    SeriesBasedOnSummation series(formula, "n");

    EXPECT_TRUE(series.isSummationModelValid());
    EXPECT_TRUE(series.isConvergent());
}

TEST(SeriesBasedOnSummationTest, IsConvergentWorksWhenSummationModelIsInvalid) {
    Term numerator(Polynomial{Monomial(1, {{"n", 2}}), Monomial(1, {})});
    Term denominator(Monomial(1, {{"n", 2}}));
    Term formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation series(formula, "n");

    EXPECT_FALSE(series.isSummationModelValid());
    EXPECT_FALSE(series.isConvergent());
}

TEST(SeriesBasedOnSummationTest, IsAbsolutelyConvergentWorksWhenSummationModelIsValid) {
    Term exponent(Polynomial{Monomial(1, {}), Monomial(-1, {{"n", 1}})});
    Term formula(createExpressionIfPossible({2, "^", exponent}));
    SeriesBasedOnSummation series(formula, "n");

    EXPECT_TRUE(series.isSummationModelValid());
    EXPECT_TRUE(series.isAbsolutelyConvergent());
}

TEST(SeriesBasedOnSummationTest, IsAbsolutelyConvergentWorksWhenSummationModelIsInvalid) {
    Term numerator(Polynomial{Monomial(1, {{"n", 2}}), Monomial(1, {})});
    Term denominator(Monomial(1, {{"n", 2}}));
    Term formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation series(formula, "n");

    EXPECT_FALSE(series.isSummationModelValid());
    EXPECT_FALSE(series.isAbsolutelyConvergent());
}

TEST(SeriesBasedOnSummationTest, IsConditionallyConvergentWorksWhenSummationModelIsValid) {
    Term exponent(Polynomial{Monomial(1, {}), Monomial(-1, {{"n", 1}})});
    Term formula(createExpressionIfPossible({2, "^", exponent}));
    SeriesBasedOnSummation series(formula, "n");

    EXPECT_TRUE(series.isSummationModelValid());
    EXPECT_TRUE(series.isConditionallyConvergent());
}

TEST(SeriesBasedOnSummationTest, IsConditionallyConvergentWorksWhenSummationModelIsInvalid) {
    Term numerator(Polynomial{Monomial(1, {{"n", 2}}), Monomial(1, {})});
    Term denominator(Monomial(1, {{"n", 2}}));
    Term formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation series(formula, "n");

    EXPECT_FALSE(series.isSummationModelValid());
    EXPECT_TRUE(series.isConditionallyConvergent());
}

}  // namespace algebra

}  // namespace alba
