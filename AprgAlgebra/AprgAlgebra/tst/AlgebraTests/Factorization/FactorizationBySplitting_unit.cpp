#include <Algebra/Factorization/FactorizationBySplitting.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algebra {

namespace Factorization {

TEST(FactorizationBySplittingTest, FactorizeBySplittingSmallerPolynomialsWorksWhenItCannotBeFactored) {
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeBySplittingToSmallerPolynomials(polynomialToTest));

    ASSERT_EQ(1U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
}

TEST(FactorizationBySplittingTest, FactorizeBySplittingSmallerPolynomialsWorksWhenItCanBeFactored) {    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"c", 1}, {"x", 2}}), Monomial(1, {{"a", 1}, {"d", 1}, {"x", 1}}),
        Monomial(1, {{"b", 1}, {"c", 1}, {"x", 1}}), Monomial(1, {{"b", 1}, {"d", 1}})};
    Polynomials polynomialsToVerify(factorizeBySplittingToSmallerPolynomials(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"c", 1}, {"x", 1}}), Monomial(1, {{"d", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, FactorizeBySplittingToSmallerPolynomialsIfPossible_IsEmptyWhenItCannotBeFactored) {    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify;
    factorizeBySplittingToSmallerPolynomialsIfPossible(polynomialsToVerify, polynomialToTest);
    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(
    FactorizationBySplittingTest,
    FactorizeBySplittingToSmallerPolynomialsIfPossible_WorksBySplittingByPolynomialDegree) {
    Polynomial polynomialToTest{Monomial(25, {{"x", 2}}), Monomial(30, {{"x", 1}, {"y", 1}}),
                                Monomial(9, {{"y", 2}}),  Monomial(15, {{"x", 1}}),
                                Monomial(9, {{"y", 1}}),  Monomial(2, {})};

    Polynomials polynomialsToVerify;
    factorizeBySplittingToSmallerPolynomialsIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(2, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(    FactorizationBySplittingTest,
    FactorizeBySplittingToSmallerPolynomialsIfPossible_WorksBySplittingByDivisibilityOfExponents) {
    Polynomial polynomialToTest{
        Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(-1, {{"z", 2}}),        Monomial(-2, {{"y", 1}, {"z", 1}})};

    Polynomials polynomialsToVerify;
    factorizeBySplittingToSmallerPolynomialsIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(1, {{"z", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {{"z", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, FactorizeBySplittingToSmallerPolynomialsIfPossible_WorksBySplittingByFirstVariable) {    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(-1, {{"a", 1}, {"y", 1}}), Monomial(-1, {{"b", 1}, {"y", 1}}),
        Monomial(1, {{"b", 1}, {"x", 1}})};
    Polynomials polynomialsToVerify;
    factorizeBySplittingToSmallerPolynomialsIfPossible(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(    FactorizationBySplittingTest,
    FactorizeBySplittingToSmallerPolynomialsIfPossible_IsEmptyWhenFactorsAreOnlyConstants) {
    Polynomial polynomialToTest{
        Monomial(-18, {{"dy/dx", 1}, {"y", 5}}), Monomial(-5, {{"dy/dx", 1}, {"y", 4}}), Monomial(6, {{"x", 5}}),        Monomial(2, {{"dy/dx", 1}, {"y", 1}}), Monomial(-2, {})};

    Polynomials polynomialsToVerify;
    factorizeBySplittingToSmallerPolynomialsIfPossible(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationBySplittingTest, FactorizeIfPossibleBySplittingByPolynomialDegree_IsEmptyWhenItCannotBeFactored) {
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify;
    factorizeIfPossibleBySplittingByPolynomialDegree(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationBySplittingTest, FactorizeIfPossibleBySplittingByPolynomialDegree_Works) {
    Polynomial polynomialToTest{Monomial(25, {{"x", 2}}), Monomial(30, {{"x", 1}, {"y", 1}}),
                                Monomial(9, {{"y", 2}}),  Monomial(15, {{"x", 1}}),
                                Monomial(9, {{"y", 1}}),  Monomial(2, {})};

    Polynomials polynomialsToVerify;
    factorizeIfPossibleBySplittingByPolynomialDegree(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(2, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(    FactorizationBySplittingTest,
    FactorizeIfPossibleBySplittingByDivisibilityOfExponents_IsEmptyWhenItCannotBeFactored) {
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};
    Polynomials polynomialsToVerify;
    factorizeIfPossibleBySplittingByDivisibilityOfExponents(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationBySplittingTest, FactorizeIfPossibleBySplittingByDivisibilityOfExponents_Works) {
    Polynomial polynomialToTest{
        Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(-1, {{"z", 2}}),
        Monomial(-2, {{"y", 1}, {"z", 1}})};

    Polynomials polynomialsToVerify;
    factorizeIfPossibleBySplittingByDivisibilityOfExponents(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(1, {{"z", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {{"z", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, FactorizeIfPossibleBySplittingByFirstVariable_IsEmptyWhenItCannotBeFactored) {    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify;
    factorizeIfPossibleBySplittingByFirstVariable(polynomialsToVerify, polynomialToTest);
    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(
    FactorizationBySplittingTest, FactorizeIfPossibleBySplittingByFirstVariable_IsEmptyWhenPolynomialCannotBeSplitted) {
    Polynomial polynomialToTest{Monomial(1, {{"x", 3}}), Monomial(13, {{"x", 7}})};

    Polynomials polynomialsToVerify;
    factorizeIfPossibleBySplittingByFirstVariable(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(
    FactorizationBySplittingTest,
    FactorizeIfPossibleBySplittingByFirstVariable_IsEmptyWhenNoCommonFactorsCanBeFoundAfterSplit) {
    Polynomial polynomialToTest{Monomial(1, {{"a", 3}}), Monomial(13, {{"b", 7}})};

    Polynomials polynomialsToVerify;
    factorizeIfPossibleBySplittingByFirstVariable(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationBySplittingTest, FactorizeIfPossibleBySplittingByFirstVariable_WorksOnAXPlusBTimesCXPlusD) {
    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"c", 1}, {"x", 2}}), Monomial(1, {{"a", 1}, {"d", 1}, {"x", 1}}),
        Monomial(1, {{"b", 1}, {"c", 1}, {"x", 1}}), Monomial(1, {{"b", 1}, {"d", 1}})};

    Polynomials polynomialsToVerify;
    factorizeIfPossibleBySplittingByFirstVariable(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"c", 1}, {"x", 1}}), Monomial(1, {{"d", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, FactorizeIfPossibleBySplittingByFirstVariable_WorksOnExample1) {    Polynomial polynomialToTest{
        Monomial(15, {{"a", 1}, {"b", 1}}), Monomial(-20, {{"a", 1}}), Monomial(-21, {{"b", 1}}), Monomial(28, {})};

    Polynomials polynomialsToVerify;    factorizeIfPossibleBySplittingByFirstVariable(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(5, {{"a", 1}}), Monomial(-7, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"b", 1}}), Monomial(-4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, FactorizeIfPossibleBySplittingByFirstVariable_WorksOnExample2) {    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(-1, {{"a", 1}, {"y", 1}}), Monomial(-1, {{"b", 1}, {"y", 1}}),
        Monomial(1, {{"b", 1}, {"x", 1}})};
    Polynomials polynomialsToVerify;
    factorizeIfPossibleBySplittingByFirstVariable(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, SplitPolynomialsByPolynomialDegree_Works) {    Polynomial polynomialToTest{Monomial(25, {{"x", 2}}), Monomial(30, {{"x", 1}, {"y", 1}}),
                                Monomial(9, {{"y", 2}}),  Monomial(15, {{"x", 1}}),
                                Monomial(9, {{"y", 1}}),  Monomial(2, {})};
    Polynomials polynomialsToVerify;
    splitPolynomialsByPolynomialDegree(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{
        Monomial(25, {{"x", 2}}), Monomial(30, {{"x", 1}, {"y", 1}}), Monomial(9, {{"y", 2}})};
    Polynomial polynomialToExpect2{Monomial(15, {{"x", 1}}), Monomial(9, {{"y", 1}})};
    Polynomial polynomialToExpect3{Monomial(2, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationBySplittingTest, SplitPolynomialsByDivisibilityOfExponents_Works) {    Polynomial polynomialToTest{
        Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(-1, {{"z", 2}}),
        Monomial(-2, {{"y", 1}, {"z", 1}})};
    Polynomials polynomialsToVerify;
    splitPolynomialsByDivisibilityOfExponents(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 2}}), Monomial(-1, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 1}, {"y", 1}}), Monomial(-2, {{"y", 1}, {"z", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, SplitPolynomialsByFirstVariable_Works) {    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"a", 1}, {"y", 1}}), Monomial(1, {{"b", 1}, {"x", 1}}),
        Monomial(1, {{"b", 1}, {"y", 1}})};
    Polynomials polynomialsToVerify;
    splitPolynomialsByFirstVariable(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"a", 1}, {"y", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"b", 1}, {"x", 1}}), Monomial(1, {{"b", 1}, {"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, factorizeSmallerPolynomials_WorksByFactoringOutCommonFactors) {    Polynomial polynomial1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"a", 1}, {"y", 1}})};
    Polynomial polynomial2{Monomial(1, {{"b", 1}, {"x", 1}}), Monomial(1, {{"b", 1}, {"y", 1}})};
    Polynomials polynomialsToTest{polynomial1, polynomial2};
    Polynomials polynomialsToVerify;
    factorizeSmallerPolynomials(polynomialsToVerify, polynomialsToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, FactorizeSmallerPolynomials_WorksBySubstitutingCommonFactorsToVariables) {    Polynomial polynomial1{Monomial(25, {{"x", 2}}), Monomial(30, {{"x", 1}, {"y", 1}}), Monomial(9, {{"y", 2}})};
    Polynomial polynomial2{Monomial(15, {{"x", 1}}), Monomial(9, {{"y", 1}})};
    Polynomial polynomial3{Monomial(2, {})};
    Polynomials polynomialsToTest{polynomial1, polynomial2, polynomial3};
    Polynomials polynomialsToVerify;
    factorizeSmallerPolynomials(polynomialsToVerify, polynomialsToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(2, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, FactorizeSmallerPolynomialsByFactoringOutCommonFactorsWorks) {    Polynomial polynomial1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"a", 1}, {"y", 1}})};
    Polynomial polynomial2{Monomial(1, {{"b", 1}, {"x", 1}}), Monomial(1, {{"b", 1}, {"y", 1}})};
    Polynomials polynomialsToTest{polynomial1, polynomial2};
    Polynomials polynomialsToVerify;
    factorizeSmallerPolynomialsByFactoringOutCommonFactors(polynomialsToVerify, polynomialsToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, FactorizeSmallerPolynomialsBySubstitutingCommonFactorsToVariablesWorks) {    Polynomial polynomial1{Monomial(25, {{"x", 2}}), Monomial(30, {{"x", 1}, {"y", 1}}), Monomial(9, {{"y", 2}})};
    Polynomial polynomial2{Monomial(15, {{"x", 1}}), Monomial(9, {{"y", 1}})};
    Polynomial polynomial3{Monomial(2, {})};
    Polynomials polynomialsToTest{polynomial1, polynomial2, polynomial3};
    Polynomials polynomialsToVerify;
    factorizeSmallerPolynomialsBySubstitutingCommonFactorsToNewVariables(polynomialsToVerify, polynomialsToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(2, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, FactorizePolynomialWithVariablesWorks) {    Polynomial polynomialsToTest{Monomial(1, {{"x+1", 2}}), Monomial(2, {{"x+1", 1}}), Monomial(1, {})};
    SubstitutionOfVariablesToTerms variableSubstitution(
        {{"x+1", Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})})}});
    Polynomials polynomialsToVerify;
    factorizePolynomialWithNewVariables(polynomialsToVerify, polynomialsToTest, variableSubstitution);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, GetCommonFactorsInThesePolynomialsWorks) {    Polynomial polynomial1{Monomial(12, {{"x", 3}}), Monomial(24, {{"x", 2}}), Monomial(12, {{"x", 1}})};
    Polynomial polynomial2{Monomial(6, {{"x", 4}}), Monomial(-6, {{"x", 2}})};
    Polynomial polynomial3{Monomial(4, {{"x", 4}}), Monomial(4, {{"x", 3}})};
    Polynomials polynomialsToTest{polynomial1, polynomial2, polynomial3};
    Polynomials polynomialsToVerify;
    getCommonFactorsInThesePolynomials(polynomialsToVerify, polynomialsToTest);

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(2, {{"x", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
}

TEST(FactorizationBySplittingTest, GetNewPolynomialWithVariablesWorks) {    SubstitutionOfVariablesToTerms variableSubstitution;
    Polynomial polynomial1{Monomial(25, {{"x", 2}}), Monomial(30, {{"x", 1}, {"y", 1}}), Monomial(9, {{"y", 2}})};
    Polynomial polynomial2{Monomial(15, {{"x", 1}}), Monomial(9, {{"y", 1}})};
    Polynomial polynomial3{Monomial(2, {})};    Polynomials polynomialsToTest{polynomial1, polynomial2, polynomial3};

    Polynomial polynomia1ToVerify(getNewPolynomialWithNewVariables(variableSubstitution, polynomialsToTest));

    ASSERT_EQ(1, variableSubstitution.getSize());
    Term termToExpect(Polynomial{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}})});
    EXPECT_EQ(termToExpect, variableSubstitution.getTermForVariable("{(5[x] + 3[y])}"));
    Polynomial polynomialToExpect{
        Monomial(1, {{"{(5[x] + 3[y])}", 2}}), Monomial(3, {{"{(5[x] + 3[y])}", 1}}), Monomial(2, {})};
    EXPECT_EQ(polynomialToExpect, polynomia1ToVerify);
}

TEST(FactorizationBySplittingTest, RemoveCommonFactorsInPolynomialsWorks) {
    Polynomial polynomial1{Monomial(12, {{"x", 3}}), Monomial(24, {{"x", 2}}), Monomial(12, {{"x", 1}})};
    Polynomial polynomial2{Monomial(6, {{"x", 4}}), Monomial(-6, {{"x", 2}})};
    Polynomial polynomial3{Monomial(4, {{"x", 4}}), Monomial(4, {{"x", 3}})};
    Polynomial polynomial4{Monomial(2, {{"x", 1}})};
    Polynomial polynomial5{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomials polynomialsWithFactors{polynomial1, polynomial2, polynomial3};
    Polynomials commonFactors{polynomial4, polynomial5};

    Polynomials polynomialsToVerify;
    getPolynomialsWithRemovedCommonFactors(polynomialsToVerify, polynomialsWithFactors, commonFactors);

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(6, {{"x", 1}}), Monomial(6, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 2}}), Monomial(-3, {{"x", 1}})};
    Polynomial polynomialToExpect3{Monomial(2, {{"x", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify[0]);
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify[1]);
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify[2]);
}

TEST(FactorizationBySplittingTest, UpdateToGetSubsetOfFactorsWorks) {    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Polynomial polynomial3{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    Polynomials commonFactors1{polynomial1, polynomial2};    Polynomials commonFactors2{polynomial1, polynomial3};

    updateToGetSubsetOfFactors(commonFactors1, commonFactors2);

    ASSERT_EQ(1U, commonFactors1.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    EXPECT_EQ(polynomialToExpect1, commonFactors1[0]);
}

TEST(FactorizationBySplittingTest, CombinePolynomialsByAdditionAndEmplaceBackWorks) {    Polynomial polynomial1{Monomial(1, {{"x", 1}})};
    Polynomial polynomial2{Monomial(2, {{"x", 1}}), Monomial(3, {})};
    Polynomial polynomial3{Monomial(4, {})};
    Polynomials polynomials{polynomial1, polynomial2, polynomial3};
    Polynomials polynomialsToVerify;
    combinePolynomialsByAdditionThenEmplaceFactoredPolynomialIfNeeded(polynomialsToVerify, polynomials);

    ASSERT_EQ(1U, polynomialsToVerify.size());
    Polynomial polynomialToExpect{Monomial(3, {{"x", 1}}), Monomial(7, {})};
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify[0]);
}

}  // namespace Factorization
}  // namespace algebra

}  // namespace alba