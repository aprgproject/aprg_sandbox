#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Geometry/ThreeDimensions/ThreeDimensionsUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>
#include <AprgGnuPlot/AprgGnuPlot3D.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra;
using namespace alba::algebra::Functions;
using namespace alba::algebra::ThreeDimensions;
using namespace std;

namespace alba
{

TEST(AprgAlgebraTest, ThreeDimensionsGeometricEquationCanBeShown)
{
    Equation generalEquation(getHyperbolicParaboloidEquation());
    SubstitutionOfVariablesToValues initialSubstitution;
    initialSubstitution.putVariableWithValue("a", 1);
    initialSubstitution.putVariableWithValue("b", 2);
    initialSubstitution.putVariableWithValue("c", 3);
    initialSubstitution.putVariableWithValue("x0", 1);
    initialSubstitution.putVariableWithValue("y0", 2);
    initialSubstitution.putVariableWithValue("z0", 3);
    Equation equationWithValues(initialSubstitution.performSubstitutionTo(generalEquation));
    AprgGnuPlot3D::PointsInGraph pointsOfEquation;
    for(double x=-100; x<=100; x+=5)
    {
        for(double y=-100; y<=100; y+=5)
        {
            SubstitutionOfVariablesToValues substitution{{"x", x}, {"y", y}};
            Equation equationWithZ(substitution.performSubstitutionTo(equationWithValues));
            OneEquationOneVariableEqualitySolver solver;
            SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equationWithZ));
            AlbaNumbers zAcceptedValues(solutionSet.getAcceptedValues());
            for(AlbaNumber const& zNumber : zAcceptedValues)
            {
                pointsOfEquation.emplace_back(AprgGnuPlot3D::getPoint(x, y, zNumber.getDouble()));
            }
        }
    }

    AprgGnuPlot3D gnuPlot3D;
    gnuPlot3D.setTitle("Three Dimensions Geometric Equation", R"("font ",22")");
    gnuPlot3D.setXAxis("X", R"("font ",15")");
    gnuPlot3D.setYAxis("Y", R"("font ",15")");
    gnuPlot3D.setZAxis("Z", R"("font ",15")");
    gnuPlot3D.doGraphs([&]()
    {
        gnuPlot3D.graph(pointsOfEquation, "equation", "with points palette pointsize 1 pointtype 1");
    });
}

TEST(AprgAlgebraTest, DISABLED_EquationCanBeShown){
    Term leftHandSize(Polynomial({Monomial(2, {{"x", 4}}), Monomial(1, {{"y", 2}}), Monomial(-1, {{"x", 2}}), Monomial(-2, {{"y", 1}})}));
    Term rightHandSize(z);
    Equation equation(leftHandSize, "=", rightHandSize);
    AprgGnuPlot3D::PointsInGraph pointsOfEquation;
    for(double x=-2; x<=2; x+=0.1)
    {
        for(double y=-2; y<=2; y+=0.1)
        {
            SubstitutionOfVariablesToValues substitution{{"x", x}, {"y", y}};
            Equation equationWithZ(substitution.performSubstitutionTo(equation));
            OneEquationOneVariableEqualitySolver solver;
            SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equationWithZ));
            AlbaNumbers zAcceptedValues(solutionSet.getAcceptedValues());
            for(AlbaNumber const& zNumber : zAcceptedValues)
            {
                pointsOfEquation.emplace_back(AprgGnuPlot3D::getPoint(x, y, zNumber.getDouble()));
            }
        }
    }

    AprgGnuPlot3D gnuPlot3D;
    gnuPlot3D.setTitle("Equation", R"("font ",22")");
    gnuPlot3D.setXAxis("X", R"("font ",15")");
    gnuPlot3D.setYAxis("Y", R"("font ",15")");
    gnuPlot3D.setZAxis("Z", R"("font ",15")");
    gnuPlot3D.doGraphs([&]()
    {
        gnuPlot3D.graph(pointsOfEquation, "equation", "with points palette pointsize 1 pointtype 1");
        gnuPlot3D.graph({AprgGnuPlot3D::getPoint(-0.5, 1, static_cast<double>(-9)/8)}, "point1", "with points palette pointsize 2 pointtype 2");
        gnuPlot3D.graph({AprgGnuPlot3D::getPoint(0, 1, -1)}, "point3", "with points palette pointsize 2 pointtype 3");
        gnuPlot3D.graph({AprgGnuPlot3D::getPoint(0.5, 1, static_cast<double>(-9)/8)}, "point4", "with points palette pointsize 2 pointtype 4");
    });
}

}