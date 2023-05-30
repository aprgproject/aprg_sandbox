#include <Algebra/Solution/SolutionSet/MultipleVariableSolutionSet.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

TEST(MultipleVariableSolutionSetTest, ConstructorWorksAndEmpty) {
    MultipleVariableSolutionSet solutionSet;

    EXPECT_TRUE(solutionSet.getVariableNameToSolutionSetMap().empty());
}

TEST(MultipleVariableSolutionSetTest, IsValueAcceptedForVariableWorks) {
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

TEST(MultipleVariableSolutionSetTest, GetNumberOfVariablesWithSolutionsWorks) {
    MultipleVariableSolutionSet solutionSet;
    SolutionSet solutionSetForVariable;
    solutionSetForVariable.addAcceptedValue(AlbaNumber(58));
    solutionSet.addSolutionSetForVariable("a", solutionSetForVariable);
    solutionSet.addSolutionSetForVariable("b", solutionSetForVariable);

    EXPECT_EQ(2, solutionSet.getNumberOfVariablesWithSolutions());
}

TEST(MultipleVariableSolutionSetTest, GetVariableNamesWorks) {
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

TEST(MultipleVariableSolutionSetTest, GetSolutionSetForVariableWorks) {
    MultipleVariableSolutionSet solutionSet;
    SolutionSet solutionSetForA;
    solutionSetForA.addAcceptedValue(AlbaNumber(58));
    solutionSet.addSolutionSetForVariable("a", solutionSetForA);

    SolutionSet solutionSetToVerify(solutionSet.getSolutionSetForVariable("a"));

    EXPECT_EQ(AlbaNumbers{58}, solutionSetToVerify.getAcceptedValues());
}

TEST(MultipleVariableSolutionSetTest, AddSolutionSetForVariableWorks) {
    MultipleVariableSolutionSet solutionSet;
    SolutionSet solutionSetForA;
    solutionSetForA.addAcceptedValue(AlbaNumber(58));

    solutionSet.addSolutionSetForVariable("a", solutionSetForA);

    MultipleVariableSolutionSet::VariableNameToSolutionSetMap expectedMap(
        solutionSet.getVariableNameToSolutionSetMap());
    ASSERT_EQ(1U, expectedMap.size());
    auto const it = expectedMap.cbegin();
    EXPECT_EQ("a", it->first);
    EXPECT_EQ(AlbaNumbers{58}, it->second.getAcceptedValues());
}

TEST(MultipleVariableSolutionSetTest, OutputStreamOperatorWorks) {
    MultipleVariableSolutionSet solutionSet;
    SolutionSet solutionSetForVariable;
    solutionSetForVariable.addAcceptedValue(3.7);
    solutionSetForVariable.addAcceptedValue(5.6);
    solutionSetForVariable.addRejectedValue(6.5);
    solutionSetForVariable.addAcceptedInterval(AlbaNumberInterval(createOpenEndpoint(87), createOpenEndpoint(99)));
    solutionSet.addSolutionSetForVariable("a", solutionSetForVariable);
    solutionSet.addSolutionSetForVariable("b", solutionSetForVariable);

    EXPECT_EQ(
        "Variable:{a} SolutionSet:{AcceptedValues: : [{size: 2 | 3.7, 5.6, }] RejectedValues: : [{size: 1 | 6.5, }] "
        "AcceptedIntervals: : [{size: 1 | (87, 99), }]}\n"
        "Variable:{b} SolutionSet:{AcceptedValues: : [{size: 2 | 3.7, 5.6, }] RejectedValues: : [{size: 1 | 6.5, }] "
        "AcceptedIntervals: : [{size: 1 | (87, 99), }]}\n",
        convertToString(solutionSet));
}

}  // namespace algebra

}  // namespace alba
