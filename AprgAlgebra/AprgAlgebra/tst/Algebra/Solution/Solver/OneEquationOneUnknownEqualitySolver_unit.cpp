#include <Algebra/Solution/Solver/OneEquationOneUnknownEqualitySolver.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(OneEquationOneUnknownEqualitySolverTest, ConstructionWorks)
{
    OneEquationOneUnknownEqualitySolver(Equation(Term("x"), "=", Term("y")));
}

}

}
