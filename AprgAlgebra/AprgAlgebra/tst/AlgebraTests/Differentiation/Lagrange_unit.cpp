#include <Algebra/Differentiation/Lagrange.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

TEST(LagrangeTest, GetLagrangeMultipliersWorks) {
    // Let x units be the length of the base of a box, y units be the width of the base of the box, z units be the depth
    // of the box The box has a constant volume V. Calculate the dimensions so that it will have the least amount of
    // material to manufacture. Surface area = xy + 2xz + 2yz Volume  = xyz

    Term termToTest(Polynomial{
        Monomial(1, {{"x", 1}, {"y", 1}}), Monomial(2, {{"x", 1}, {"z", 1}}), Monomial(2, {{"y", 1}, {"z", 1}})});
    Term lagrangeFunction(Polynomial{Monomial(1, {{"x", 1}, {"y", 1}, {"z", 1}}), Monomial(-1, {{"V", 1}})});

    Terms langrangeMultipliers(getLagrangeMultipliers(termToTest, {"x", "y", "z"}, {lagrangeFunction}));

    ASSERT_EQ(1U, langrangeMultipliers.size());
    string stringToExpect("-2[z^-1]");
    EXPECT_EQ(stringToExpect, convertToString(langrangeMultipliers[0]));

    // using lagrange multipler as -2/z, we can use that to calculate the other values.
}

TEST(LagrangeTest, GetLagrangeMultipliersWorksUsingExample1) {
    // Find the relative extrema of the f if f(x,y,z) = xz+yz
    // and the point (x,y,z) lies on the intersection of the surfaces x^2+y^2=2 and yz=2

    Term termToTest(Polynomial{Monomial(1, {{"x", 1}, {"z", 1}}), Monomial(1, {{"y", 1}, {"z", 1}})});
    Term lagrangeFunction1(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(-2, {})});
    Term lagrangeFunction2(Polynomial{Monomial(1, {{"y", 1}, {"z", 1}}), Monomial(-2, {})});

    Terms langrangeMultipliers(
        getLagrangeMultipliers(termToTest, {"x", "y", "z"}, {lagrangeFunction1, lagrangeFunction2}));

    ASSERT_EQ(2U, langrangeMultipliers.size());
    string stringToExpect1("(((1/32)[z^6] + (-1/16)[z^4])^(1/2))");
    string stringToExpect2("{EmptyTerm}");
    EXPECT_EQ(stringToExpect1, convertToString(langrangeMultipliers[0]));
    EXPECT_EQ(stringToExpect2, convertToString(langrangeMultipliers[1]));
}

}  // namespace algebra

}  // namespace alba
