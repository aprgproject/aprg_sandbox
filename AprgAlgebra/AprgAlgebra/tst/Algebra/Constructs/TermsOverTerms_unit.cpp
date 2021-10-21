#include <Algebra/Constructs/TermsOverTerms.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(TermsOverTermsTest, ConstructionWorks)
{
    TermWithDetails termWithDetails(Term(10), TermAssociationType::Positive);
    TermsOverTerms termsOverTerms1;
    TermsOverTerms termsOverTerms2({termWithDetails, termWithDetails});
    TermsOverTerms termsOverTerms3({Term(5)}, {Term("x")});
    TermsOverTerms termsOverTerms4({termWithDetails}, {termWithDetails});

    EXPECT_TRUE(termsOverTerms1.getNumerators().empty());
    EXPECT_TRUE(termsOverTerms1.getDenominators().empty());
    Terms numeratorsToVerify2(termsOverTerms2.getNumerators());
    ASSERT_EQ(2U, numeratorsToVerify2.size());
    EXPECT_EQ(Term(10), numeratorsToVerify2.at(0));
    EXPECT_EQ(Term(10), numeratorsToVerify2.at(0));
    EXPECT_TRUE(termsOverTerms2.getDenominators().empty());
    Terms numeratorsToVerify3(termsOverTerms3.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify3.size());
    EXPECT_EQ(Term(5), numeratorsToVerify3.at(0));
    Terms denominatorsToVerify3(termsOverTerms3.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify3.size());
    EXPECT_EQ(Term("x"), denominatorsToVerify3.at(0));
    Terms numeratorsToVerify4(termsOverTerms4.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify4.size());
    EXPECT_EQ(Term(10), numeratorsToVerify4.at(0));
    Terms denominatorsToVerify4(termsOverTerms4.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify4.size());
    EXPECT_EQ(Term(10), denominatorsToVerify4.at(0));
}

TEST(TermsOverTermsTest, GetNumeratorsAndGetDenominatorsWorks)
{
    TermsOverTerms termsOverTerms({Term(5)}, {Term("x")});

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term(5), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term("x"), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, GetNumeratorAndDenominatorAsTermWithDetailsWorks)
{
    TermsOverTerms termsOverTerms({Term(5)}, {Term("x")});

    TermsWithDetails termsWithDetails(termsOverTerms.getNumeratorAndDenominatorAsTermWithDetails());
    ASSERT_EQ(2U, termsWithDetails.size());
    EXPECT_EQ(Term(5), getTermConstReferenceFromSharedPointer(termsWithDetails.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termsWithDetails.at(0).association);
    EXPECT_EQ(Term("x"), getTermConstReferenceFromSharedPointer(termsWithDetails.at(1).baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termsWithDetails.at(1).association);
}

TEST(TermsOverTermsTest, GetNumeratorAndDenominatorAsTermWithDetailsWorksWhenBothNumeratorsAndDenominatorsAreEmpty)
{
    TermsOverTerms termsOverTerms(Terms{}, Terms{});

    TermsWithDetails termsWithDetails(termsOverTerms.getNumeratorAndDenominatorAsTermWithDetails());
    EXPECT_TRUE(termsWithDetails.empty());
}

TEST(TermsOverTermsTest, GetCombinedTermWorks)
{
    TermsOverTerms termsOverTerms({Term("x"), Term(56)}, {Term(7), Term("y")});

    Term expectedTerm(Term(Monomial(8, {{"x", 1}, {"y", -1}})));
    EXPECT_EQ(expectedTerm, termsOverTerms.getCombinedTerm());
}

TEST(TermsOverTermsTest, GetCombinedNumeratorWorks)
{
    TermsOverTerms termsOverTerms({Term("x"), Term(56)}, {Term(7), Term("y")});

    Term expectedTerm(Term(Monomial(56, {{"x", 1}})));
    EXPECT_EQ(expectedTerm, termsOverTerms.getCombinedNumerator());
}

TEST(TermsOverTermsTest, GetCombinedDenominatorWorks)
{
    TermsOverTerms termsOverTerms({Term("x"), Term(56)}, {Term(7), Term("y")});

    Term expectedTerm(Term(Monomial(7, {{"y", 1}})));
    EXPECT_EQ(expectedTerm, termsOverTerms.getCombinedDenominator());
}

TEST(TermsOverTermsTest, RetrievePolynomialAndNonPolynomialNumeratorsWorks)
{
    Term nonPolynomialTerm(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    TermsOverTerms termsOverTerms({Term(5), Term("x"), nonPolynomialTerm}, {Term(6), Term("y"), nonPolynomialTerm});

    Polynomial retrievedPolynomial;
    Terms retrievedTerms;
    termsOverTerms.retrievePolynomialAndNonPolynomialNumerators(retrievedPolynomial, retrievedTerms);

    Polynomial expectedPolynomial{Monomial(5, {{"x", 1}})};
    EXPECT_EQ(expectedPolynomial, retrievedPolynomial);
    ASSERT_EQ(1U, retrievedTerms.size());
    EXPECT_EQ(nonPolynomialTerm, retrievedTerms.at(0));
}

TEST(TermsOverTermsTest, RetrievePolynomialAndNonPolynomialDenominatorsWorks)
{
    Term nonPolynomialTerm(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    TermsOverTerms termsOverTerms({Term(5), Term("x"), nonPolynomialTerm}, {Term(6), Term("y"), nonPolynomialTerm});

    Polynomial retrievedPolynomial;
    Terms retrievedTerms;
    termsOverTerms.retrievePolynomialAndNonPolynomialsDenominators(retrievedPolynomial, retrievedTerms);

    Polynomial expectedPolynomial{Monomial(6, {{"y", 1}})};
    EXPECT_EQ(expectedPolynomial, retrievedPolynomial);
    ASSERT_EQ(1U, retrievedTerms.size());
    EXPECT_EQ(nonPolynomialTerm, retrievedTerms.at(0));
}

TEST(TermsOverTermsTest, RetrieveBaseToExponentMapWorks)
{
    TermsOverTerms termsOverTerms({Term("a"), Term("b")}, {Term("x"), Term("y")});

    TermsOverTerms::BaseToExponentMap baseToExponentMap;
    termsOverTerms.retrieveBaseToExponentMap(baseToExponentMap);

    ASSERT_EQ(4U, baseToExponentMap.size());
    TermsOverTerms::BaseToExponentMap::const_iterator itVerify=baseToExponentMap.cbegin();
    EXPECT_EQ(Term("a"), itVerify->first);
    EXPECT_EQ(AlbaNumber(1), itVerify->second);
    itVerify++;
    EXPECT_EQ(Term("b"), itVerify->first);
    EXPECT_EQ(AlbaNumber(1), itVerify->second);
    itVerify++;
    EXPECT_EQ(Term("x"), itVerify->first);
    EXPECT_EQ(AlbaNumber(-1), itVerify->second);
    itVerify++;
    EXPECT_EQ(Term("y"), itVerify->first);
    EXPECT_EQ(AlbaNumber(-1), itVerify->second);
}

TEST(TermsOverTermsTest, FlipWorks)
{
    TermsOverTerms termsOverTerms({Term("a"), Term("b")}, {Term("x"), Term("y")});

    termsOverTerms.flip();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(2U, numeratorsToVerify.size());    EXPECT_EQ(Term("x"), numeratorsToVerify.at(0));
    EXPECT_EQ(Term("y"), numeratorsToVerify.at(1));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(2U, denominatorsToVerify.size());
    EXPECT_EQ(Term("a"), denominatorsToVerify.at(0));
    EXPECT_EQ(Term("b"), denominatorsToVerify.at(1));
}

TEST(TermsOverTermsTest, SaveBaseToExponentMapWorks)
{
    TermsOverTerms::BaseToExponentMap baseToExponentMap{{Term("x"), AlbaNumber(5)}, {Term("y"), AlbaNumber(-10)}};
    TermsOverTerms termsOverTerms;
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.saveBaseToExponentMap(baseToExponentMap);

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term(createExpressionIfPossible({Term("x"), Term("^"), Term(5)})), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(createExpressionIfPossible({Term("y"), Term("^"), Term(10)})), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksAndRemovesTermsThatHasNoEffect)
{
    TermsOverTerms numeratorHasTermsNoEffect({Term(), Term(1)}, {});
    TermsOverTerms denominatorHasTermsNoEffect({}, {Term(), Term(1)});

    numeratorHasTermsNoEffect.simplify();
    denominatorHasTermsNoEffect.simplify();

    Terms numeratorsToVerify1(numeratorHasTermsNoEffect.getNumerators());
    Terms denominatorsToVerify1(numeratorHasTermsNoEffect.getDenominators());
    EXPECT_TRUE(numeratorsToVerify1.empty());
    EXPECT_TRUE(denominatorsToVerify1.empty());
    Terms numeratorsToVerify2(denominatorHasTermsNoEffect.getNumerators());
    Terms denominatorsToVerify2(denominatorHasTermsNoEffect.getDenominators());
    EXPECT_TRUE(numeratorsToVerify2.empty());
    EXPECT_TRUE(denominatorsToVerify2.empty());
}

TEST(TermsOverTermsTest, SimplifyWorksAndDoesNotCancelsZerosInNumeratorAndDenominator)
{
    TermsOverTerms termsOverTerms({Term(Constant(0))}, {Term(Constant(0))});

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_TRUE(isNotANumber(numeratorsToVerify.at(0)));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_TRUE(denominatorsToVerify.empty());
}

TEST(TermsOverTermsTest, SimplifyWorksAndRemovesOnSamePolynomialInNumeratorAndDenominator)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(11, {})};
    Polynomial polynomial2{Monomial(1, {{"y", 1}}), Monomial(13, {})};
    Polynomial polynomial3{Monomial(1, {{"z", 1}}), Monomial(17, {})};
    TermsOverTerms termsOverTerms({Term(polynomial2), Term(polynomial1)}, {Term(polynomial1), Term(polynomial3)});

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term(polynomial2), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(polynomial3), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksAndRemovesOnSameFactorsInNumeratorAndDenominator)
{
    Polynomial polynomial1{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 2}}), Monomial(-1, {})};
    TermsOverTerms termsOverTerms({Term(polynomial1)}, {Term(polynomial2)});

    termsOverTerms.simplify();

    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term(polynomialToExpect1), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(polynomialToExpect2), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksAndRemovesOnSameFactorsFirstBeforeCombining)
{
    Polynomial polynomial1{Monomial(12, {{"x", 1}}), Monomial(-15, {})};
    Polynomial polynomial2{Monomial(6, {{"x", 1}}), Monomial(7, {})};
    Polynomial polynomial3{Monomial(8, {{"x", 1}}), Monomial(9, {})};
    Polynomial polynomial4{Monomial(11, {{"x", 1}}), Monomial(-13, {})};
    Polynomial polynomial5{Monomial(8, {{"x", 1}}), Monomial(-10, {})};
    Terms numerators{Term(polynomial1), Term(polynomial2), Term(polynomial3), Term(polynomial4)};
    Terms denominators{Term(polynomial2), Term(polynomial5)};
    TermsOverTerms termsOverTerms(numerators, denominators);

    termsOverTerms.simplify();

    Polynomial polynomialToExpect{Monomial(264, {{"x", 2}}), Monomial(-15, {{"x", 1}}), Monomial(-351, {})};
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term(polynomialToExpect), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(2), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksAsCombiningPolynomialsOnNumeratorAndDenominatorSeparately)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Terms numerators{Term(polynomial1), Term(polynomial1)};
    Terms denominators{Term(polynomial2), Term(polynomial2)};
    TermsOverTerms termsOverTerms(numerators, denominators);

    termsOverTerms.simplify();

    Polynomial polynomialToExpect1{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 2}}), Monomial(4, {{"x", 1}}), Monomial(4, {})};
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term(polynomialToExpect1), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(polynomialToExpect2), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksWithPolynomialsWithNegativeExponents)
{
    Polynomial polynomial1{Monomial(1, {{"a", 1}, {"b", -1}}), Monomial(1, {{"c", 1}, {"b", -2}})};
    Polynomial polynomial2{Monomial(1, {{"b", 1}})};
    Polynomial polynomial3{Monomial(1, {{"a", 1}, {"b", 1}}), Monomial(1, {{"c", 1}})};
    Terms numerators{Term(polynomial1)};
    Terms denominators{Term(polynomial2), Term(polynomial3)};
    TermsOverTerms termsOverTerms(numerators, denominators);

    termsOverTerms.simplify();

    Monomial monomialToExpect(1, {{"b", 3}});
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    EXPECT_TRUE(numeratorsToVerify.empty());
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(monomialToExpect), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksAndRemovesOnSameExpressionInNumeratorAndDenominator)
{
    Expression expression1(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    Expression expression2(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression expression3(createExpressionIfPossible({Term("z"), Term("^"), Term("z")}));
    TermsOverTerms termsOverTerms({Term(expression2), Term(expression1)}, {Term(expression1), Term(expression3)});

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term(expression2), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(expression3), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksAndPutNegativeExponentsOnTheOtherSide)
{
    Term polynomialTerm1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(5, {})});
    Term polynomialTerm2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {})});
    Term expressionTerm1(createExpressionIfPossible({polynomialTerm1, Term("^"), Term(-1)}));
    Term expressionTerm2(createExpressionIfPossible({polynomialTerm2, Term("^"), Term(-1)}));
    TermsOverTerms termsOverTerms({expressionTerm1}, {expressionTerm2});

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(polynomialTerm2, numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(polynomialTerm1, denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksAndPutNegativeExponentsOnTheOtherSideAndCanCancelled)
{
    Term polynomialTerm1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(5, {})});
    Term expressionTerm1(createExpressionIfPossible({polynomialTerm1, Term("^"), Term(-1)}));
    TermsOverTerms termsOverTerms({polynomialTerm1, expressionTerm1}, {Term(1)});

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    EXPECT_TRUE(numeratorsToVerify.empty());
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    EXPECT_TRUE(denominatorsToVerify.empty());
}

TEST(TermsOverTermsTest, SimplifyWorksOnExample1)
{
    Polynomial polynomialNumerator{Monomial(3, {{"x", 4}}), Monomial(-32, {{"x", 2}}), Monomial(-80, {{"x", 1}}), Monomial(-12, {})};
    Polynomial polynomialDenominator{Monomial(1, {{"x", 4}}), Monomial(-18, {{"x", 2}}), Monomial(81, {})};
    TermsOverTerms termsOverTerms({Term(polynomialNumerator)}, {Term(polynomialDenominator)});

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term(polynomialNumerator), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(polynomialDenominator), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksWithSimplifyingToFactorsAndDoesNotCombinePolynomials)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Terms numerators{Term(polynomial1), Term(polynomial1)};
    Terms denominators{Term(polynomial2), Term(polynomial2)};
    TermsOverTerms termsOverTerms(numerators, denominators);
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.simplify();

    Term expectedNumerator(createExpressionIfPossible({Term(polynomial1), Term("^"), Term(2)}));
    Term expectedDenominator(createExpressionIfPossible({Term(polynomial2), Term("^"), Term(2)}));
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term(expectedNumerator), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(expectedDenominator), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksWithSimplifyingToFactorsWithPolynomialsWithNegativeExponents)
{
    Polynomial polynomial1{Monomial(1, {{"a", 1}, {"b", -1}}), Monomial(1, {{"c", 1}, {"b", -2}})};
    Polynomial polynomial2{Monomial(1, {{"b", 1}})};
    Polynomial polynomial3{Monomial(1, {{"a", 1}, {"b", 1}}), Monomial(1, {{"c", 1}})};
    Terms numerators{Term(polynomial1)};
    Terms denominators{Term(polynomial2), Term(polynomial3)};
    TermsOverTerms termsOverTerms(numerators, denominators);
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.simplify();

    Monomial monomialToExpect(1, {{"b", 3}});
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    EXPECT_TRUE(numeratorsToVerify.empty());
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(monomialToExpect), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksWithSimplifyingToFactorsWithExample1)
{
    Polynomial polynomial1{Monomial(1, {{"a", 1}}), Monomial(-1, {{"a", -1}})};
    Polynomial polynomial2{Monomial(1, {{"a", 1}}), Monomial(-1, {{"a", -2}})};
    Terms numerators{Term(polynomial1)};
    Terms denominators{Term(polynomial2)};
    TermsOverTerms termsOverTerms(numerators, denominators);
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.simplify();

    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"a", 2}}), Monomial(1, {{"a", 1}}), Monomial(1, {})};
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(2U, numeratorsToVerify.size());
    EXPECT_EQ(Term("a"), numeratorsToVerify.at(0));
    EXPECT_EQ(Term(polynomialToExpect1), numeratorsToVerify.at(1));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(polynomialToExpect2), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksWithSimplifyingToFactorsAndPutNegativeExponentsOnTheOtherSide)
{
    Term polynomialTerm1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(5, {})});
    Term polynomialTerm2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {})});
    Term expressionTerm1(createExpressionIfPossible({polynomialTerm1, Term("^"), Term(-1)}));
    Term expressionTerm2(createExpressionIfPossible({polynomialTerm2, Term("^"), Term(-1)}));
    TermsOverTerms termsOverTerms({expressionTerm1}, {expressionTerm2});
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(polynomialTerm2, numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(polynomialTerm1, denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksWithSimplifyingToFactorsAndPutNegativeExponentsOnTheOtherSideAndCanCancelled)
{
    Term polynomialTerm1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(5, {})});
    Term expressionTerm1(createExpressionIfPossible({polynomialTerm1, Term("^"), Term(-1)}));
    TermsOverTerms termsOverTerms({polynomialTerm1, expressionTerm1}, {Term(1)});
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    EXPECT_TRUE(numeratorsToVerify.empty());
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    EXPECT_TRUE(denominatorsToVerify.empty());
}

TEST(TermsOverTermsTest, SimplifyWorksWithSimplifyingToFactorsAndFactorsAreCancelledButExponentsFormIsRetainedAndFactorsAreNotPopulated)
{
    Term polynomialTerm(Polynomial{Monomial(7, {{"x", 3}}), Monomial(-1, {})});
    Term numerator(createExpressionIfPossible({polynomialTerm, Term("^"), Term(2)}));
    Term denominator(createExpressionIfPossible({polynomialTerm, Term("^"), Term(8)}));
    TermsOverTerms termsOverTerms({numerator}, {denominator});
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    EXPECT_TRUE(numeratorsToVerify.empty());
    Term expectedDenominator(createExpressionIfPossible({polynomialTerm, Term("^"), Term(6)}));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(expectedDenominator, denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksWhenShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValueIsDefault)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-5, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-7, {})});
    TermsOverTerms termsOverTerms({numerator}, {denominator});
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.simplify();

    Term expectedNumerator1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2.23606797749979, {})});
    Term expectedNumerator2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2.23606797749979, {})});
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(2U, numeratorsToVerify.size());
    EXPECT_EQ(expectedNumerator1, numeratorsToVerify.at(0));
    EXPECT_EQ(expectedNumerator2, numeratorsToVerify.at(1));
    Term expectedDenominator1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2.645751311064591, {})});
    Term expectedDenominator2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2.645751311064591, {})});
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(2U, denominatorsToVerify.size());
    EXPECT_EQ(expectedDenominator1, denominatorsToVerify.at(0));
    EXPECT_EQ(expectedDenominator2, denominatorsToVerify.at(1));
}

TEST(TermsOverTermsTest, SimplifyWorksWhenShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValueIsTrue)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-5, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-7, {})});
    TermsOverTerms termsOverTerms({numerator}, {denominator});
    termsOverTerms.setAsShouldSimplifyToFactors(true);
    termsOverTerms.setAsShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(true);

    termsOverTerms.simplify();

    Term expectedNumerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-5, {})});
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(expectedNumerator, numeratorsToVerify.at(0));
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-7, {})});
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(expectedDenominator, denominatorsToVerify.at(0));
}

}

}
