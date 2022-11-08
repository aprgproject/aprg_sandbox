#include <Geometry/TwoDimensions/Constructs/Polynomial.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(PolynomialTest, PolynomialCanBeCreated)
{
    Polynomial<3>{1,2,3};
}

TEST(PolynomialTest, CalculateOutputFromInputWorks)
{
    Polynomial<3> polynomial{1,2,3};

    EXPECT_DOUBLE_EQ(38, polynomial.calculateOutputFromInput(5));
}

TEST(PolynomialTest, GetValueOfFirstDerivativeWorks)
{
    Polynomial<3> polynomial{1,2,3};

    EXPECT_DOUBLE_EQ(12, polynomial.getValueOfFirstDerivative(5));
}

}

}
