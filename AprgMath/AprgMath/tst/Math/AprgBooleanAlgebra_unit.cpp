#include <Math/AprgBooleanAlgebra.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace BooleanAlgebra
{

namespace
{

using NumberForTest = unsigned int;
using NumbersForTest = Container<NumberForTest>;
using PredicateForTest = Predicate<NumberForTest>;

NumbersForTest numbersWithNoEven{1, 3, 5};
NumbersForTest numbersWithOneEven{1, 2, 3, 5};
NumbersForTest numbersWithTwoEven{1, 2, 3, 4, 5};
NumbersForTest numbersWithAllEven{2, 4, 6};

PredicateForTest isEvenPredicate = [](NumberForTest const& number)
{
    return isEven(number);
};

}

TEST(AprgBooleanAlgebraTest, PredicateCanBeCreatedAndWorks)
{
    EXPECT_TRUE(isEvenPredicate(2U));
    EXPECT_FALSE(isEvenPredicate(1U));
}

TEST(AprgBooleanAlgebraTest, GetNegationWorks)
{
    EXPECT_TRUE(getNegation(false));
    EXPECT_FALSE(getNegation(true));
}

TEST(AprgBooleanAlgebraTest, GetConjunctionWorks)
{
    EXPECT_FALSE(getConjunction(false, false));
    EXPECT_FALSE(getConjunction(false, true));
    EXPECT_FALSE(getConjunction(true, false));
    EXPECT_TRUE(getConjunction(true, true));
}

TEST(AprgBooleanAlgebraTest, GetInclusiveDisjunctionWorks)
{
    EXPECT_FALSE(getInclusiveDisjunction(false, false));
    EXPECT_TRUE(getInclusiveDisjunction(false, true));
    EXPECT_TRUE(getInclusiveDisjunction(true, false));
    EXPECT_TRUE(getInclusiveDisjunction(true, true));
}

TEST(AprgBooleanAlgebraTest, GetExclusiveDisjunctionWorks)
{
    EXPECT_FALSE(getExclusiveDisjunction(false, false));
    EXPECT_TRUE(getExclusiveDisjunction(false, true));
    EXPECT_TRUE(getExclusiveDisjunction(true, false));
    EXPECT_FALSE(getExclusiveDisjunction(true, true));
}

TEST(AprgBooleanAlgebraTest, GetImplicationWorks)
{
    EXPECT_TRUE(getImplication(false, false));
    EXPECT_TRUE(getImplication(false, true));
    EXPECT_FALSE(getImplication(true, false));
    EXPECT_TRUE(getImplication(true, true));
}

TEST(AprgBooleanAlgebraTest, GetEquivalenceWorks)
{
    EXPECT_TRUE(getEquivalence(false, false));
    EXPECT_FALSE(getEquivalence(false, true));
    EXPECT_FALSE(getEquivalence(true, false));
    EXPECT_TRUE(getEquivalence(true, true));
}

TEST(AprgBooleanAlgebraTest, GetUniversalQuantificationWorks)
{
    EXPECT_FALSE(getUniversalQuantification(numbersWithNoEven, isEvenPredicate));
    EXPECT_FALSE(getUniversalQuantification(numbersWithOneEven, isEvenPredicate));
    EXPECT_FALSE(getUniversalQuantification(numbersWithTwoEven, isEvenPredicate));
    EXPECT_TRUE(getUniversalQuantification(numbersWithAllEven, isEvenPredicate));
}

TEST(AprgBooleanAlgebraTest, GetExistentialQuantificationWorks)
{
    EXPECT_FALSE(getExistentialQuantification(numbersWithNoEven, isEvenPredicate));
    EXPECT_TRUE(getExistentialQuantification(numbersWithOneEven, isEvenPredicate));
    EXPECT_TRUE(getExistentialQuantification(numbersWithTwoEven, isEvenPredicate));
    EXPECT_TRUE(getExistentialQuantification(numbersWithAllEven, isEvenPredicate));
}

TEST(AprgBooleanAlgebraTest, GetUniquenessQuantificationWorks)
{
    EXPECT_FALSE(getUniquenessQuantification(numbersWithNoEven, isEvenPredicate));
    EXPECT_TRUE(getUniquenessQuantification(numbersWithOneEven, isEvenPredicate));
    EXPECT_FALSE(getUniquenessQuantification(numbersWithTwoEven, isEvenPredicate));
    EXPECT_FALSE(getUniquenessQuantification(numbersWithAllEven, isEvenPredicate));
}

TEST(AprgBooleanAlgebraTest, GetTautologyWorks)
{
    auto tautologyToTest(getTautology<NumberForTest>());

    EXPECT_TRUE(tautologyToTest(1));
    EXPECT_TRUE(tautologyToTest(23));
    EXPECT_TRUE(tautologyToTest(518));
}

TEST(AprgBooleanAlgebraTest, GetContradictionWorks)
{
    auto contradictionToTest(getContradiction<NumberForTest>());

    EXPECT_FALSE(contradictionToTest(1));
    EXPECT_FALSE(contradictionToTest(23));
    EXPECT_FALSE(contradictionToTest(518));
}

}

}
