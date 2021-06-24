#include <Equation/Factorization/FactorizationUsingPatterns.hpp>
#include <Equation/Term/Term.hpp>
#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{

TEST(FactorizationTest, FactorizeDifferenceOfSquaresWorksWhenItCannotBeFactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfSquares(polynomialToTest));

    ASSERT_EQ(1u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
}

TEST(FactorizationTest, FactorizeDifferenceOfSquaresWorksWhenItCanBeFactored)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfSquares(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, FactorizeDifferenceOfCubesWorksWhenItCannotBeFactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfCubes(polynomialToTest));

    ASSERT_EQ(1u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
}

TEST(FactorizationTest, FactorizeDifferenceOfCubesWorksWhenItCanBeFactored)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfCubes(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, FactorizeSumOfCubesWorksWorksWhenItCannotBeFactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeSumOfCubes(polynomialToTest));

    ASSERT_EQ(1u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
}

TEST(FactorizationTest, FactorizeSumOfCubesWorksWorksWhenItCanBeFactored)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeSumOfCubes(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, FactorizeDifferenceOfSquaresIfPossible_IsEmptyWhenItCannotBeRefactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfSquaresIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationTest, FactorizeDifferenceOfSquaresIfPossible_WorksWhenFirstMonomialIsPositive)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfSquaresIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, FactorizeDifferenceOfSquaresIfPossible_WorksWhenFirstMonomialIsNegative)
{
    Polynomial polynomialToTest{Monomial(-9, {{"x", 8}, {"y", 2}}), Monomial(16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfSquaresIfPossible(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, FactorizeDifferenceOfCubesIfPossible_IsEmptyWhenItCannotBeRefactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfCubesIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationTest, FactorizeDifferenceOfCubesIfPossible_WorksWhenFirstMonomialIsPositive)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfCubesIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, FactorizeDifferenceOfCubesIfPossible_WorksWhenFirstMonomialIsNegative)
{
    Polynomial polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfCubesIfPossible(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, FactorizeSumOfCubesIfPossible_IsEmptyWhenItCannotBeRefactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeSumOfCubesIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationTest, FactorizeSumOfCubesIfPossible_WorksWhenBothMonomialsArePositive)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeSumOfCubesIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, FactorizeSumOfCubesIfPossible_WorksWhenBothMonomialsAreNegative)
{
    Polynomial polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeSumOfCubesIfPossible(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, AddFactorsOfDifferenceOfSquaresWorks)
{
    Polynomial polynomial1{Monomial(9, {{"x", 4}}), Monomial(-16, {{"y", 2}})};
    Polynomial polynomial2{Monomial(-9, {{"x", 4}}), Monomial(16, {{"y", 2}})};

    Polynomials polynomialsToVerify1;
    Polynomials polynomialsToVerify2;
    addFactorsOfDifferenceOfSquares(polynomialsToVerify1, polynomial1);
    addFactorsOfDifferenceOfSquares(polynomialsToVerify2, polynomial2);

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

TEST(FactorizationTest, AddFactorsOfDifferenceOfCubesWorks)
{
    Polynomial polynomial1{Monomial(27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial2{Monomial(-27, {{"x", 6}}), Monomial(64, {{"y", 3}})};

    Polynomials polynomialsToVerify1;
    Polynomials polynomialsToVerify2;
    addFactorsOfDifferenceOfCubes(polynomialsToVerify1, polynomial1);
    addFactorsOfDifferenceOfCubes(polynomialsToVerify2, polynomial2);

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

TEST(FactorizationTest, AddFactorsOfSumOfCubesWorks)
{
    Polynomial polynomial1{Monomial(27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial polynomial2{Monomial(-27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};

    Polynomials polynomialsToVerify1;
    Polynomials polynomialsToVerify2;
    addFactorsOfSumOfCubes(polynomialsToVerify1, polynomial1);
    addFactorsOfSumOfCubes(polynomialsToVerify2, polynomial2);

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

TEST(FactorizationTest, IsDifferenceOfSquaresWorks)
{
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(9, {{"x", 4}}), Monomial(16, {{"y", 2}})};
    Polynomial polynomial3{Monomial(-9, {{"x", 4}}), Monomial(16, {{"y", 2}})};
    Polynomial polynomial4{Monomial(9, {{"x", 4}}), Monomial(-16, {{"y", 2}})};
    Polynomial polynomial5{Monomial(-9, {{"x", 4}}), Monomial(-16, {{"y", 2}})};
    Polynomial polynomial6{Monomial(10, {{"x", 4}}), Monomial(-16, {{"y", 2}})};
    Polynomial polynomial7{Monomial(9, {{"x", 4}}), Monomial(-15, {{"y", 2}})};
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

TEST(FactorizationTest, IsDifferenceOfCubesWorks)
{
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial polynomial3{Monomial(-27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial polynomial4{Monomial(27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial5{Monomial(-27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial6{Monomial(28, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial7{Monomial(27, {{"x", 6}}), Monomial(-63, {{"y", 3}})};
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

TEST(FactorizationTest, IsSumOfCubesWorks)
{
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial polynomial3{Monomial(-27, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial polynomial4{Monomial(27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial5{Monomial(-27, {{"x", 6}}), Monomial(-64, {{"y", 3}})};
    Polynomial polynomial6{Monomial(28, {{"x", 6}}), Monomial(64, {{"y", 3}})};
    Polynomial polynomial7{Monomial(27, {{"x", 6}}), Monomial(63, {{"y", 3}})};
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
