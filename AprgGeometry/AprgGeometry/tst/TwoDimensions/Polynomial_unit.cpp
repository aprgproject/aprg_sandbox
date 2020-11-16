#include <TwoDimensions/Polynomial.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;

TEST(PolynomialTest, PolynomialCanBeCreated)
{
    Polynomial<3> polynomial{3,2,1};
}
