#include <TwoDimensions/Polynomial.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(PolynomialTest, PolynomialCanBeCreated)
{
    Polynomial<3> polynomial{3,2,1};
}

}

}