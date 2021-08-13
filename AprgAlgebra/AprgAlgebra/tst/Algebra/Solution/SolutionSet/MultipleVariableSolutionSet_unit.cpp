#include <Algebra/Solution/SolutionSet/MultipleVariableSolutionSet.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(MultipleVariableSolutionSetTest, ConstructorWorksAndEmpty)
{
    MultipleVariableSolutionSet solutionSet;

    EXPECT_TRUE(solutionSet.getVariableNameToSolutionSetMap().empty());
}

TEST(MultipleVariableSolutionSetTest, IsValueAcceptedForVariableWorks)
{
    MultipleVariableSolutionSet solutionSet;
    SolutionSet solutionSetForVariable;
    solutionSetForVariable.addAcceptedValue(AlbaNumber(58));
    solutionSet.addSolutionSetForVariable("a", solutionSetForVariable);
    solutionSet.addSolutionSetForVariable("b", solutionSetForVariable);

    EXPECT_TRUE(solutionSet.isValueAcceptedForVariable("a", 58));
    EXPECT_FALSE(solutionSet.isValueAcceptedForVariable("a", 59));
    EXPECT_TRUE(solutionSet.isValueAcceptedForVariable("b", 58));
    EXPECT_FALSE(solutionSet.isValueAcceptedForVariable("b", 59));
}

TEST(MultipleVariableSolutionSetTest, GetNumberOfVariablesWithSolutionsWorks)
{
    MultipleVariableSolutionSet solutionSet;
    SolutionSet solutionSetForVariable;
    solutionSetForVariable.addAcceptedValue(AlbaNumber(58));
    solutionSet.addSolutionSetForVariable("a", solutionSetForVariable);
    solutionSet.addSolutionSetForVariable("b", solutionSetForVariable);

    EXPECT_EQ(2u, solutionSet.getNumberOfVariablesWithSolutions());
}

TEST(MultipleVariableSolutionSetTest, GetDisplayableStringWorks)
{
    MultipleVariableSolutionSet solutionSet;
    SolutionSet solutionSetForVariable;
    solutionSetForVariable.addAcceptedValue(3.7);
    solutionSetForVariable.addAcceptedValue(5.6);
    solutionSetForVariable.addRejectedValue(6.5);
    solutionSetForVariable.addAcceptedInterval(AlbaNumberInterval(createOpenEndpoint(87), createOpenEndpoint(99)));
    solutionSet.addSolutionSetForVariable("a", solutionSetForVariable);
    solutionSet.addSolutionSetForVariable("b", solutionSetForVariable);

    EXPECT_EQ("Variable:{a} SolutionSet:{AcceptedValues:{3.7, 5.6} RejectedValues:{6.5} AcceptedInterval:{(87, 99)}} "
              "Variable:{b} SolutionSet:{AcceptedValues:{3.7, 5.6} RejectedValues:{6.5} AcceptedInterval:{(87, 99)}} ", solutionSet.getDisplayableString());
}

TEST(MultipleVariableSolutionSetTest, GetVariableNamesWorks)
{
    MultipleVariableSolutionSet solutionSet;
    SolutionSet solutionSetForVariable;
    solutionSetForVariable.addAcceptedValue(AlbaNumber(58));
    solutionSet.addSolutionSetForVariable("a", solutionSetForVariable);
    solutionSet.addSolutionSetForVariable("b", solutionSetForVariable);

    VariableNamesSet variableNames(solutionSet.getVariableNames());
    auto it = variableNames.cbegin();
    EXPECT_EQ("a", *(it++));
    EXPECT_EQ("b", *(it++));
}

TEST(MultipleVariableSolutionSetTest, GetSolutionSetForVariableWorks)
{
    MultipleVariableSolutionSet solutionSet;
    SolutionSet solutionSetForA;
    solutionSetForA.addAcceptedValue(AlbaNumber(58));
    solutionSet.addSolutionSetForVariable("a", solutionSetForA);

    AlbaNumbers const& acceptedValues(solutionSet.getSolutionSetForVariable("a").getAcceptedValues());

    ASSERT_EQ(1u, acceptedValues.size());
    EXPECT_EQ(AlbaNumber(58), acceptedValues.at(0));
}

TEST(MultipleVariableSolutionSetTest, AddSolutionSetForVariableWorks)
{
    MultipleVariableSolutionSet solutionSet;
    SolutionSet solutionSetForA;
    solutionSetForA.addAcceptedValue(AlbaNumber(58));

    solutionSet.addSolutionSetForVariable("a", solutionSetForA);

    MultipleVariableSolutionSet::VariableNameToSolutionSetMap expectedMap(solutionSet.getVariableNameToSolutionSetMap());
    ASSERT_EQ(1u, expectedMap.size());
    auto const it = expectedMap.cbegin();
    EXPECT_EQ("a", it->first);
    AlbaNumbers const& acceptedValues(it->second.getAcceptedValues());
    ASSERT_EQ(1u, acceptedValues.size());
    EXPECT_EQ(AlbaNumber(58), acceptedValues.at(0));
}

}

}
