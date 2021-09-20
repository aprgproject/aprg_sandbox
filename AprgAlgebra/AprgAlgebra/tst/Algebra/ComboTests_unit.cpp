#include <Algebra/Constructs/TermsAggregator.hpp>
#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableNonEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Simplification;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample1)
{
    SubstitutionOfVariablesToValues substitution({{"x", 8}});
    Term term(buildTermIfPossible("(x+2)*(x+2)*(x+2)*(x+2)"));
    EXPECT_EQ(Term(10000), substitution.performSubstitutionTo(term));
}

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample2)
{
    SubstitutionOfVariablesToValues substitution({{"x", 3}});
    Term term(buildTermIfPossible("(4*x-5)*(6*x+7)*(8*x+9)"));
    EXPECT_EQ(Term(5775), substitution.performSubstitutionTo(term));
}

TEST(ComboTest, SimplifyAndSubstitutionWorksUsingExample3)
{
    SubstitutionOfVariablesToValues substitution({{"x", 2}});
    Term term(buildTermIfPossible("(4*x-5)*(6*x+7)*(8*x+9)*(11*x-13)"));
    EXPECT_EQ(Term(12825), substitution.performSubstitutionTo(term));
}

TEST(ComboTest, SimplifyToCommonDenominatorAndSubstitutionWorksUsingExample1)
{
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

TEST(ComboTest, OneVariableInequalityCanBeSolvedUsingExample1)
{
    OneEquationOneVariableNonEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(buildEquationIfPossible("2+3*x < 5*x+8")));

    AlbaNumberIntervals acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(createOpenEndpoint(-3), acceptedIntervals.front().getLowerEndpoint());
    EXPECT_EQ(createPositiveInfinityOpenEndpoint(), acceptedIntervals.front().getHigherEndpoint());
}

TEST(ComboTest, OneVariableInequalityCanBeSolvedUsingExample2)
{
    OneEquationOneVariableNonEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(buildEquationIfPossible("7/x > 2")));

    AlbaNumberIntervals acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(createOpenEndpoint(0), acceptedIntervals.front().getLowerEndpoint());
    EXPECT_EQ(createOpenEndpoint(AlbaNumber::createFraction(7, 2)), acceptedIntervals.front().getHigherEndpoint());
}

TEST(ComboTest, OneVariableInequalityCanBeSolvedUsingExample3)
{
    OneEquationOneVariableNonEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(buildEquationIfPossible("abs(3*x+2) > 5")));

    AlbaNumberIntervals acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2U, acceptedIntervals.size());
    AlbaNumberInterval const& interval1(acceptedIntervals.at(0));
    EXPECT_EQ(createNegativeInfinityOpenEndpoint(), interval1.getLowerEndpoint());
    EXPECT_EQ(createOpenEndpoint(AlbaNumber::createFraction(-7, 3)), interval1.getHigherEndpoint());
    AlbaNumberInterval const& interval2(acceptedIntervals.at(1));
    EXPECT_EQ(createOpenEndpoint(1), interval2.getLowerEndpoint());
    EXPECT_EQ(createPositiveInfinityOpenEndpoint(), interval2.getHigherEndpoint());
}

TEST(ComboTest, OneVariableInequalityCanBeSolvedUsingExample4)
{
    OneEquationOneVariableNonEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(buildEquationIfPossible("x^2+7*x+12 >= 0")));

    AlbaNumberIntervals acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2U, acceptedIntervals.size());
    AlbaNumberInterval const& interval1(acceptedIntervals.at(0));
    EXPECT_EQ(createNegativeInfinityOpenEndpoint(), interval1.getLowerEndpoint());
    EXPECT_EQ(AlbaNumberIntervalEndpoint(createCloseEndpoint(-4)), interval1.getHigherEndpoint());
    AlbaNumberInterval const& interval2(acceptedIntervals.at(1));
    EXPECT_EQ(AlbaNumberIntervalEndpoint(createCloseEndpoint(-3)), interval2.getLowerEndpoint());
    EXPECT_EQ(createPositiveInfinityOpenEndpoint(), interval2.getHigherEndpoint());
}

}

}
