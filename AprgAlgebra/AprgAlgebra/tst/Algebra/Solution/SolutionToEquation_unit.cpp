#include <Algebra/Solution/SolutionToEquation.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SolutionToEquationTest, ConstructionWorks)
{
    SolutionToEquation(Equation(Term("x"), "=", Term("y")));
}

}
}