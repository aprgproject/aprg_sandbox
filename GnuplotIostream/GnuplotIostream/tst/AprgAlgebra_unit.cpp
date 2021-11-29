#include "gnuplot-iostream.h"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Geometry/ThreeDimensions/ThreeDimensionsUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::algebra;
using namespace alba::algebra::Functions;
using namespace alba::algebra::ThreeDimensions;
using namespace std;

namespace alba
{

TEST(AprgAlgebraTest, DISABLED_ThreeDimensionsGeometricEquationCanBeShown)
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

    string nameOfGraph("Three Dimensions Geometric Equation");
    Gnuplot gp;
    gp << "splot ";
    vector<pair<pair<double, double>, double>> pts;
    for(double x=-100; x<=100; x+=5)
    {
        for(double y=-100; y<=100; y+=5)
        {
            SubstitutionOfVariablesToValues substitution{{"x", x}, {"y", y}};
            Equation equationWithZ(substitution.performSubstitutionTo(equationWithValues));
            OneEquationOneVariableEqualitySolver solver;
            SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equationWithZ));
            AlbaNumbers zValues(solutionSet.getAcceptedValues());
            for(AlbaNumber const& z : zValues)
            {
                pts.emplace_back(make_pair(make_pair(x, y), z.getDouble()));
            }
        }
    }
    gp << gp.binFile1d(pts, "record") << "with points palette pointsize 1 pointtype 1 title '"<< nameOfGraph <<"'";
    gp << ", ";
    gp << endl;
}

TEST(AprgAlgebraTest, DISABLED_EquationCanBeShown)
{
    Term leftHandSize(Polynomial({Monomial(2, {{"x", 4}}), Monomial(1, {{"y", 2}}), Monomial(-1, {{"x", 2}}), Monomial(-2, {{"y", 1}})}));
    Term rightHandSize(z);
    Equation equation(leftHandSize, "=", rightHandSize);

    string nameOfGraph("Equation");
    Gnuplot gp;
    gp << "splot ";
    vector<pair<pair<double, double>, double>> pts;
    for(double x=-2; x<=2; x+=0.1)
    {
        for(double y=-2; y<=2; y+=0.1)
        {
            SubstitutionOfVariablesToValues substitution{{"x", x}, {"y", y}};
            Equation equationWithZ(substitution.performSubstitutionTo(equation));
            OneEquationOneVariableEqualitySolver solver;
            SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equationWithZ));
            AlbaNumbers zValues(solutionSet.getAcceptedValues());
            for(AlbaNumber const& z : zValues)
            {
                pts.emplace_back(make_pair(make_pair(x, y), z.getDouble()));
            }
        }
    }
    gp << gp.binFile1d(pts, "record") << "with points palette pointsize 1 pointtype 1 title '"<< nameOfGraph <<"'";
    gp << ", ";


    {
        // put points
        vector<pair<pair<double, double>, double>> pts;
        pts.emplace_back(make_pair(make_pair(-0.5, 1), static_cast<double>(-9)/8));
        pts.emplace_back(make_pair(make_pair(0, 1), -1));
        pts.emplace_back(make_pair(make_pair(0.5, 1), static_cast<double>(-9)/8));
        gp << gp.binFile1d(pts, "record") << "with points palette pointsize 2 pointtype 2 title '"<< nameOfGraph <<"'";
        gp << ", ";
    }

    gp << endl;
}

}
