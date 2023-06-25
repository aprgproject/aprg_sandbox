#include <Algebra/Constructs/TermsAggregator.hpp>
#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableNonEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Simplification;
using namespace std;

namespace alba {

namespace algebra {

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample1) {
    SubstitutionOfVariablesToValues substitution({{"x", 8}});
    Term term(buildTermIfPossible("(x+2)*(x+2)*(x+2)*(x+2)"));
    EXPECT_EQ(Term(10000), substitution.performSubstitutionTo(term));
}

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample2) {
    SubstitutionOfVariablesToValues substitution({{"x", 3}});
    Term term(buildTermIfPossible("(4*x-5)*(6*x+7)*(8*x+9)"));
    EXPECT_EQ(Term(5775), substitution.performSubstitutionTo(term));
}

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample3) {
    SubstitutionOfVariablesToValues substitution({{"x", 2}});
    Term term(buildTermIfPossible("(4*x-5)*(6*x+7)*(8*x+9)*(11*x-13)"));
    EXPECT_EQ(Term(12825), substitution.performSubstitutionTo(term));
}

TEST(ComboTest, SimplifyToCommonDenominatorAndSubstitutionWorksUsingExample1) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SubstitutionOfVariablesToValues substitution({{"x", 2}});
    Term term(buildTermIfPossible("(((3*x)/(x-3))-((3*x+2)/(x^2-6*x+9)))*(((x+2)/(x+3))-((x)/(x^2+6*x+9)))"));
    Expression simplifiedTerm(term.getExpressionConstReference());
    simplifiedTerm.simplify();

    EXPECT_EQ(Term(AlbaNumber::createFraction(-252, 25)), substitution.performSubstitutionTo(simplifiedTerm));
}

TEST(ComboTest, OneVariableInequalityCanBeSolvedUsingExample1) {
    OneEquationOneVariableNonEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(buildEquationIfPossible("2+3*x < 5*x+8")));

    AlbaNumberIntervals acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(createOpenEndpoint(-3), acceptedIntervals.front().getLowerEndpoint());
    EXPECT_EQ(createPositiveInfinityOpenEndpoint(), acceptedIntervals.front().getHigherEndpoint());
}

TEST(ComboTest, OneVariableInequalityCanBeSolvedUsingExample2) {
    OneEquationOneVariableNonEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(buildEquationIfPossible("7/x > 2")));

    AlbaNumberIntervals acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(createOpenEndpoint(0), acceptedIntervals.front().getLowerEndpoint());
    EXPECT_EQ(createOpenEndpoint(AlbaNumber::createFraction(7, 2)), acceptedIntervals.front().getHigherEndpoint());
}

TEST(ComboTest, OneVariableInequalityCanBeSolvedUsingExample3) {
    OneEquationOneVariableNonEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(buildEquationIfPossible("abs(3*x+2) > 5")));

    AlbaNumberIntervals acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2U, acceptedIntervals.size());
    AlbaNumberInterval const& interval1(acceptedIntervals[0]);
    EXPECT_EQ(createNegativeInfinityOpenEndpoint(), interval1.getLowerEndpoint());
    EXPECT_EQ(createOpenEndpoint(AlbaNumber::createFraction(-7, 3)), interval1.getHigherEndpoint());
    AlbaNumberInterval const& interval2(acceptedIntervals[1]);
    EXPECT_EQ(createOpenEndpoint(1), interval2.getLowerEndpoint());
    EXPECT_EQ(createPositiveInfinityOpenEndpoint(), interval2.getHigherEndpoint());
}
TEST(ComboTest, OneVariableInequalityCanBeSolvedUsingExample4) {
    OneEquationOneVariableNonEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(buildEquationIfPossible("x^2+7*x+12 >= 0")));

    AlbaNumberIntervals acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2U, acceptedIntervals.size());
    AlbaNumberInterval const& interval1(acceptedIntervals[0]);
    EXPECT_EQ(createNegativeInfinityOpenEndpoint(), interval1.getLowerEndpoint());
    EXPECT_EQ(AlbaNumberIntervalEndpoint(createCloseEndpoint(-4)), interval1.getHigherEndpoint());
    AlbaNumberInterval const& interval2(acceptedIntervals[1]);
    EXPECT_EQ(AlbaNumberIntervalEndpoint(createCloseEndpoint(-3)), interval2.getLowerEndpoint());
    EXPECT_EQ(createPositiveInfinityOpenEndpoint(), interval2.getHigherEndpoint());
}
TEST(ComboTest, ImplicitDifferentiationAndIsolatingDerivativeWorks) {
    Differentiation differentiationForXWithY("x", {"y"});
    Term term1ForEquation(Polynomial{Monomial(3, {{"x", 4}, {"y", 2}}), Monomial(-7, {{"x", 1}, {"y", 3}})});    Term term2ForEquation(Polynomial{Monomial(4, {}), Monomial(-8, {{"y", 1}})});
    Equation equation(term1ForEquation, "=", term2ForEquation);
    Equation differentiatedEquation(differentiationForXWithY.differentiate(equation));
    IsolationOfOneVariableOnEqualityEquation isolation(differentiatedEquation);

    Polynomial numerator{Monomial(-12, {{"x", 3}, {"y", 2}}), Monomial(7, {{"y", 3}})};
    Polynomial denominator{Monomial(6, {{"x", 4}, {"y", 1}}), Monomial(-21, {{"x", 1}, {"y", 2}}), Monomial(8, {})};
    Term expectedIsolatedXLeftSide(createExpressionIfPossible({numerator, "/", denominator}));
    Term expectedIsolatedXRightSide("d[y]/d[x]");
    EXPECT_EQ(
        Equation(expectedIsolatedXLeftSide, "=", expectedIsolatedXRightSide),
        isolation.isolateTermWithVariableOnRightSideOfEquation("d[y]/d[x]"));
}

TEST(ComboTest, ImplicitDifferentiationAndIsolatingDerivativeUsingSecondDerivativeWorks) {
    Differentiation differentiationForXWithY("x", {"y"});
    Term term1ForEquation(Polynomial{Monomial(4, {{"x", 2}}), Monomial(9, {{"y", 2}})});
    Term term2ForEquation(36);
    Equation equation(term1ForEquation, "=", term2ForEquation);
    Equation differentiatedEquation(differentiationForXWithY.differentiate(equation));
    IsolationOfOneVariableOnEqualityEquation isolation1(differentiatedEquation);
    Equation isolatedFirstDerivativeEquation(isolation1.isolateTermWithVariableOnRightSideOfEquation("d[y]/d[x]"));
    Equation secondDifferentiatedEquation(differentiationForXWithY.differentiate(isolatedFirstDerivativeEquation));
    SubstitutionOfVariablesToTerms substitution({{"d[y]/d[x]", isolatedFirstDerivativeEquation.getLeftHandTerm()}});
    Equation secondDifferentiatedSimplifiedEquation(substitution.performSubstitutionTo(secondDifferentiatedEquation));
    IsolationOfOneVariableOnEqualityEquation isolation2(secondDifferentiatedSimplifiedEquation);
    Equation isolatedSecondDerivativeEquation(isolation2.isolateTermWithVariableOnRightSideOfEquation("d2[y]/d[x]2"));

    Polynomial expectedPolynomial{
        Monomial(AlbaNumber::createFraction(-16, 81), {{"x", 2}, {"y", -3}}),
        Monomial(AlbaNumber::createFraction(-4, 9), {{"y", -1}})};
    Term expectedIsolatedXLeftSide(expectedPolynomial);
    Term expectedIsolatedXRightSide("d2[y]/d[x]2");
    EXPECT_EQ(Equation(expectedIsolatedXLeftSide, "=", expectedIsolatedXRightSide), isolatedSecondDerivativeEquation);
}

TEST(ComboTest, DifferentiationRelatedRatesConeWaterExampleTest) {
    // A tank is in the form of an inverted cone having an altitude of 16m and a radius of 4m.
    // Water is flowing into the tank at the rate of 2m3/min.
    // How fast is the water level rising when the water is 5m deep?

    // Solution: V = (1/3)*pi*r^2*h, 4*r = h -> V = (1/48)*pi*h^3

    Term term1ForEquation(Monomial(AlbaNumber::createFraction(1, 48U), {{"pi", 1}, {"h", 3}}));
    Term term2ForEquation(Monomial(1, {{"V", 1}}));
    Equation equation(term1ForEquation, "=", term2ForEquation);
    Differentiation differentiation("t", {"V", "h"});
    Equation differentiatedEquation(differentiation.differentiate(equation));
    SubstitutionOfVariablesToValues substitution({{"d[V]/d[t]", 2}, {"h", 5}, {"pi", ALBA_NUMBER_PI}});
    Equation solutionEquation(substitution.performSubstitutionTo(differentiatedEquation));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(solutionEquation));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ(AlbaNumbers{0.4074366543152521}, solutionSet.getAcceptedValues());
}

}  // namespace algebra

}  // namespace alba
