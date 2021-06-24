#include <Equation/Factorization/FactorizationUsingPatterns.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace equation
{

namespace Factorization
{

TEST(FactorizationUsingPatternsTest, FactorizeUsingPatternsWorksWhenItCannotBeFactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeUsingPatterns(polynomialToTest));

    ASSERT_EQ(1u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(polynomialToTest);    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
}

TEST(FactorizationUsingPatternsTest, FactorizeUsingPatternsWorksWhenItCanBeFactored)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeUsingPatterns(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationUsingPatternsTest, FactorizeUsingPatternsIfPossibleWorksWhenItCannotBeFactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeUsingPatternsIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUsingPatternsTest, FactorizeUsingPatternsIfPossibleWorksWhenItCanBeFactored)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeUsingPatternsIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfSquaresIfPossible_IsEmptyWhenItCannotBeRefactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};
    Polynomials polynomialsToVerify(factorizeDifferenceOfSquaresIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfSquaresIfPossible_WorksWhenFirstMonomialIsPositive)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};
    Polynomials polynomialsToVerify(factorizeDifferenceOfSquaresIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfSquaresIfPossible_WorksWhenFirstMonomialIsNegative)
{
    Polynomial polynomialToTest{Monomial(-9, {{"x", 8}, {"y", 2}}), Monomial(16, {{"z", 4}})};
    Polynomials polynomialsToVerify(factorizeDifferenceOfSquaresIfPossible(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfCubesIfPossible_IsEmptyWhenItCannotBeRefactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};
    Polynomials polynomialsToVerify(factorizeDifferenceOfCubesIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfCubesIfPossible_WorksWhenFirstMonomialIsPositive)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};
    Polynomials polynomialsToVerify(factorizeDifferenceOfCubesIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationUsingPatternsTest, FactorizeDifferenceOfCubesIfPossible_WorksWhenFirstMonomialIsNegative)
{
    Polynomial polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};
    Polynomials polynomialsToVerify(factorizeDifferenceOfCubesIfPossible(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationUsingPatternsTest, FactorizeSumOfCubesIfPossible_IsEmptyWhenItCannotBeRefactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};
    Polynomials polynomialsToVerify(factorizeSumOfCubesIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUsingPatternsTest, FactorizeSumOfCubesIfPossible_WorksWhenBothMonomialsArePositive)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};
    Polynomials polynomialsToVerify(factorizeSumOfCubesIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationUsingPatternsTest, FactorizeSumOfCubesIfPossible_WorksWhenBothMonomialsAreNegative)
{
    Polynomial polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};
    Polynomials polynomialsToVerify(factorizeSumOfCubesIfPossible(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationUsingPatternsTest, AddFactorsOfDifferenceOfSquaresWorks)
{
    Polynomial polynomial1{Monomial(9, {{"x", 4}}), Monomial(-16, {{"y", 2}})};
    Polynomial polynomial2{Monomial(-9, {{"x", 4}}), Monomial(16, {{"y", 2}})};
    Polynomials polynomialsToVerify1;
    Polynomials polynomialsToVerify2;
    addFactorsOfDifferenceOfSquares(polynomialsToVerify1, polynomial1);    addFactorsOfDifferenceOfSquares(polynomialsToVerify2, polynomial2);

    ASSERT_EQ(2u, polynomialsToVerify1.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 2}}), Monomial(4, {{"y", 1}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 2}}), Monomial(-4, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify1.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify1.at(1));
    ASSERT_EQ(3u, polynomialsToVerify2.size());
    Polynomial polynomialToExpect3{Monomial(-1, {})};
    Polynomial polynomialToExpect4{Monomial(3, {{"x", 2}}), Monomial(4, {{"y", 1}})};
    Polynomial polynomialToExpect5{Monomial(3, {{"x", 2}}), Monomial(-4, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify2.at(0));
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify2.at(1));
    EXPECT_EQ(polynomialToExpect5, polynomialsToVerify2.at(2));
}

TEST(FactorizationUsingPatternsTest, AddFactorsOfDifferenceOfCubesWorks)
{
    Polynomial polynomial1{Monomial(27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial2{Monomial(-27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomials polynomialsToVerify1;
    Polynomials polynomialsToVerify2;
    addFactorsOfDifferenceOfCubes(polynomialsToVerify1, polynomial1);    addFactorsOfDifferenceOfCubes(polynomialsToVerify2, polynomial2);

    ASSERT_EQ(2u, polynomialsToVerify1.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 2}}), Monomial(-4, {{"y", 1}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 4}}), Monomial(12, {{"x", 2}, {"y", 1}}), Monomial(16, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify1.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify1.at(1));
    ASSERT_EQ(3u, polynomialsToVerify2.size());
    Polynomial polynomialToExpect3{Monomial(-1, {})};
    Polynomial polynomialToExpect4{Monomial(3, {{"x", 2}}), Monomial(-4, {{"y", 1}})};
    Polynomial polynomialToExpect5{Monomial(9, {{"x", 4}}), Monomial(12, {{"x", 2}, {"y", 1}}), Monomial(16, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify2.at(0));
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify2.at(1));
    EXPECT_EQ(polynomialToExpect5, polynomialsToVerify2.at(2));
}

TEST(FactorizationUsingPatternsTest, AddFactorsOfSumOfCubesWorks)
{
    Polynomial polynomial1{Monomial(27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial polynomial2{Monomial(-27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomials polynomialsToVerify1;
    Polynomials polynomialsToVerify2;
    addFactorsOfSumOfCubes(polynomialsToVerify1, polynomial1);    addFactorsOfSumOfCubes(polynomialsToVerify2, polynomial2);

    ASSERT_EQ(2u, polynomialsToVerify1.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 2}}), Monomial(4, {{"y", 1}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 4}}), Monomial(-12, {{"x", 2}, {"y", 1}}), Monomial(16, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify1.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify1.at(1));
    ASSERT_EQ(3u, polynomialsToVerify2.size());
    Polynomial polynomialToExpect3{Monomial(-1, {})};
    Polynomial polynomialToExpect4{Monomial(3, {{"x", 2}}), Monomial(4, {{"y", 1}})};
    Polynomial polynomialToExpect5{Monomial(9, {{"x", 4}}), Monomial(-12, {{"x", 2}, {"y", 1}}), Monomial(16, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify2.at(0));
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify2.at(1));
    EXPECT_EQ(polynomialToExpect5, polynomialsToVerify2.at(2));
}

TEST(FactorizationUsingPatternsTest, IsDifferenceOfSquaresWorks)
{
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(9, {{"x", 4}}), Monomial(16, {{"y", 2}})};    Polynomial polynomial3{Monomial(-9, {{"x", 4}}), Monomial(16, {{"y", 2}})};
    Polynomial polynomial4{Monomial(9, {{"x", 4}}), Monomial(-16, {{"y", 2}})};
    Polynomial polynomial5{Monomial(-9, {{"x", 4}}), Monomial(-16, {{"y", 2}})};
    Polynomial polynomial6{Monomial(10, {{"x", 4}}), Monomial(-16, {{"y", 2}})};    Polynomial polynomial7{Monomial(9, {{"x", 4}}), Monomial(-15, {{"y", 2}})};
    Polynomial polynomial8{Monomial(9, {{"x", 5}}), Monomial(-16, {{"y", 2}})};
    Polynomial polynomial9{Monomial(9, {{"x", 4}}), Monomial(-16, {{"y", 3}})};

    EXPECT_FALSE(isDifferenceOfSquares(polynomial1));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial2));
    EXPECT_TRUE(isDifferenceOfSquares(polynomial3));
    EXPECT_TRUE(isDifferenceOfSquares(polynomial4));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial5));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial6));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial7));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial8));
    EXPECT_FALSE(isDifferenceOfSquares(polynomial9));
}

TEST(FactorizationUsingPatternsTest, IsDifferenceOfCubesWorks)
{
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(27, {{"x", 6}}), Monomial(64, {{"y", 3}})};    Polynomial polynomial3{Monomial(-27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial polynomial4{Monomial(27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial5{Monomial(-27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial6{Monomial(28, {{"x", 6}}), Monomial(-64, {{"y", 3}})};    Polynomial polynomial7{Monomial(27, {{"x", 6}}), Monomial(-63, {{"y", 3}})};
    Polynomial polynomial8{Monomial(27, {{"x", 7}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial9{Monomial(27, {{"x", 6}}), Monomial(-64, {{"y", 4}})};

    EXPECT_FALSE(isDifferenceOfCubes(polynomial1));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial2));
    EXPECT_TRUE(isDifferenceOfCubes(polynomial3));
    EXPECT_TRUE(isDifferenceOfCubes(polynomial4));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial5));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial6));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial7));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial8));
    EXPECT_FALSE(isDifferenceOfCubes(polynomial9));
}

TEST(FactorizationUsingPatternsTest, IsSumOfCubesWorks)
{
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(27, {{"x", 6}}), Monomial(64, {{"y", 3}})};    Polynomial polynomial3{Monomial(-27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial polynomial4{Monomial(27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial5{Monomial(-27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial6{Monomial(28, {{"x", 6}}), Monomial(64, {{"y", 3}})};    Polynomial polynomial7{Monomial(27, {{"x", 6}}), Monomial(63, {{"y", 3}})};
    Polynomial polynomial8{Monomial(27, {{"x", 7}}), Monomial(64, {{"y", 3}})};
    Polynomial polynomial9{Monomial(27, {{"x", 6}}), Monomial(64, {{"y", 4}})};

    EXPECT_FALSE(isSumOfCubes(polynomial1));
    EXPECT_TRUE(isSumOfCubes(polynomial2));
    EXPECT_FALSE(isSumOfCubes(polynomial3));
    EXPECT_FALSE(isSumOfCubes(polynomial4));
    EXPECT_TRUE(isSumOfCubes(polynomial5));
    EXPECT_FALSE(isSumOfCubes(polynomial6));
    EXPECT_FALSE(isSumOfCubes(polynomial7));
    EXPECT_FALSE(isSumOfCubes(polynomial8));
    EXPECT_FALSE(isSumOfCubes(polynomial9));
}

}

}

}
