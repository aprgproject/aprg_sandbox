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
    EXPECT_EQ(58, acceptedValues.back().getInteger());
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
    EXPECT_EQ(58, acceptedValues.back().getInteger());
}

}

}
