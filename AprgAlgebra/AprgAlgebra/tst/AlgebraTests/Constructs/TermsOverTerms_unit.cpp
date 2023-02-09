#include <Algebra/Constructs/TermsOverTerms.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
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
    TermsOverTerms termsOverTerms3({5}, {"x"});

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
}

TEST(TermsOverTermsTest, GetNumeratorsAndGetDenominatorsWorks)
{
    TermsOverTerms termsOverTerms({5}, {"x"});

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term(5), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term("x"), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, GetNumeratorAndDenominatorAsTermWithDetailsWorks)
{
    TermsOverTerms termsOverTerms({5}, {"x"});

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
    TermsOverTerms termsOverTerms({"x", 56}, {7, "y"});

    Term expectedTerm(Monomial(8, {{"x", 1}, {"y", -1}}));
    EXPECT_EQ(expectedTerm, termsOverTerms.getCombinedTerm());
}

TEST(TermsOverTermsTest, GetCombinedNumeratorWorks)
{
    TermsOverTerms termsOverTerms({"x", 56}, {7, "y"});

    Term expectedTerm(Monomial(56, {{"x", 1}}));
    EXPECT_EQ(expectedTerm, termsOverTerms.getCombinedNumerator());
}

TEST(TermsOverTermsTest, GetCombinedDenominatorWorks)
{
    TermsOverTerms termsOverTerms({"x", 56}, {7, "y"});

    Term expectedTerm(Monomial(7, {{"y", 1}}));
    EXPECT_EQ(expectedTerm, termsOverTerms.getCombinedDenominator());
}

TEST(TermsOverTermsTest, RetrievePolynomialAndNonPolynomialNumeratorsWorks)
{
    Term nonPolynomialTerm(createExpressionIfPossible({"x", "^", "x"}));
    TermsOverTerms termsOverTerms({5, "x", nonPolynomialTerm}, {6, "y", nonPolynomialTerm});

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
    Term nonPolynomialTerm(createExpressionIfPossible({"x", "^", "x"}));
    TermsOverTerms termsOverTerms({5, "x", nonPolynomialTerm}, {6, "y", nonPolynomialTerm});

    Polynomial retrievedPolynomial;
    Terms retrievedTerms;
    termsOverTerms.retrievePolynomialAndNonPolynomialsDenominators(retrievedPolynomial, retrievedTerms);

    Polynomial expectedPolynomial{Monomial(6, {{"y", 1}})};
    EXPECT_EQ(expectedPolynomial, retrievedPolynomial);
    ASSERT_EQ(1U, retrievedTerms.size());
    EXPECT_EQ(nonPolynomialTerm, retrievedTerms.at(0));
}

TEST(TermsOverTermsTest, GetTermsRaiseToNumbersWorks)
{
    TermsOverTerms termsOverTerms({"a", "b"}, {"x", "y"});

    TermsRaiseToNumbers termsRaiseToNumbers(termsOverTerms.getTermsRaiseToNumbers());

    TermsRaiseToNumbers::BaseToExponentMap const& baseToExponentMap(termsRaiseToNumbers.getBaseToExponentMap());
    ASSERT_EQ(4U, baseToExponentMap.size());
    auto itVerify=baseToExponentMap.cbegin();
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
    TermsOverTerms termsOverTerms({"a", "b"}, {"x", "y"});

    termsOverTerms.flip();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(2U, numeratorsToVerify.size());
    EXPECT_EQ(Term("x"), numeratorsToVerify.at(0));
    EXPECT_EQ(Term("y"), numeratorsToVerify.at(1));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(2U, denominatorsToVerify.size());
    EXPECT_EQ(Term("a"), denominatorsToVerify.at(0));
    EXPECT_EQ(Term("b"), denominatorsToVerify.at(1));
}

TEST(TermsOverTermsTest, SimplifyWorksAndRemovesTermsThatHasNoEffect)
{
    TermsOverTerms numeratorHasTermsNoEffect({Term(), 1}, {});
    TermsOverTerms denominatorHasTermsNoEffect({}, {Term(), 1});

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
    TermsOverTerms termsOverTerms({0}, {0});

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_TRUE(isNan(numeratorsToVerify.at(0)));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_TRUE(denominatorsToVerify.empty());
}

TEST(TermsOverTermsTest, SimplifyWorksWithSimplifyingToFactorsWithZeroInNumerator)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Terms numerators{polynomial1, polynomial1, 0};
    Terms denominators{polynomial2, polynomial2};
    TermsOverTerms termsOverTerms(numerators, denominators);
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(Term(0), numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    EXPECT_TRUE(denominatorsToVerify.empty());
}

TEST(TermsOverTermsTest, SimplifyWorksWithSimplifyingToFactorsWithZeroInDenominator)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Terms numerators{polynomial1, polynomial1};
    Terms denominators{polynomial2, polynomial2, 0};
    TermsOverTerms termsOverTerms(numerators, denominators);
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.simplify();

    Term expectedNumerator(createExpressionIfPossible({polynomial1, "^", 2}));
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(expectedNumerator, numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term(0), denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksAndRemovesOnSamePolynomialInNumeratorAndDenominator)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(11, {})};
    Polynomial polynomial2{Monomial(1, {{"y", 1}}), Monomial(13, {})};
    Polynomial polynomial3{Monomial(1, {{"z", 1}}), Monomial(17, {})};
    TermsOverTerms termsOverTerms({polynomial2, polynomial1}, {polynomial1, polynomial3});

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
    TermsOverTerms termsOverTerms({polynomial1}, {polynomial2});

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
    Terms numerators{polynomial1, polynomial2, polynomial3, polynomial4};
    Terms denominators{polynomial2, polynomial5};
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
    Terms numerators{polynomial1, polynomial1};
    Terms denominators{polynomial2, polynomial2};
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
    Terms numerators{polynomial1};
    Terms denominators{polynomial2, polynomial3};
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
    Expression expression1(createExpressionIfPossible({"x", "^", "x"}));
    Expression expression2(createExpressionIfPossible({"y", "^", "y"}));
    Expression expression3(createExpressionIfPossible({"z", "^", "z"}));
    TermsOverTerms termsOverTerms({expression2, expression1}, {expression1, expression3});

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
    Term expressionTerm1(createExpressionIfPossible({polynomialTerm1, "^", -1}));
    Term expressionTerm2(createExpressionIfPossible({polynomialTerm2, "^", -1}));
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
    Term expressionTerm1(createExpressionIfPossible({polynomialTerm1, "^", -1}));
    TermsOverTerms termsOverTerms({polynomialTerm1, expressionTerm1}, {1});

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
    TermsOverTerms termsOverTerms({polynomialNumerator}, {polynomialDenominator});

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
    Terms numerators{polynomial1, polynomial1};
    Terms denominators{polynomial2, polynomial2};
    TermsOverTerms termsOverTerms(numerators, denominators);
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.simplify();

    Term expectedNumerator(createExpressionIfPossible({polynomial1, "^", 2}));
    Term expectedDenominator(createExpressionIfPossible({polynomial2, "^", 2}));
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(expectedNumerator, numeratorsToVerify.at(0));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(expectedDenominator, denominatorsToVerify.at(0));
}

TEST(TermsOverTermsTest, SimplifyWorksWithSimplifyingToFactorsWithPolynomialsWithNegativeExponents)
{
    Polynomial polynomial1{Monomial(1, {{"a", 1}, {"b", -1}}), Monomial(1, {{"c", 1}, {"b", -2}})};
    Polynomial polynomial2{Monomial(1, {{"b", 1}})};
    Polynomial polynomial3{Monomial(1, {{"a", 1}, {"b", 1}}), Monomial(1, {{"c", 1}})};
    Terms numerators{polynomial1};
    Terms denominators{polynomial2, polynomial3};
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
    Terms numerators{polynomial1};
    Terms denominators{polynomial2};
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
    Term expressionTerm1(createExpressionIfPossible({polynomialTerm1, "^", -1}));
    Term expressionTerm2(createExpressionIfPossible({polynomialTerm2, "^", -1}));
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
    Term expressionTerm1(createExpressionIfPossible({polynomialTerm1, "^", -1}));
    TermsOverTerms termsOverTerms({polynomialTerm1, expressionTerm1}, {1});
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
    Term numerator(createExpressionIfPossible({polynomialTerm, "^", 2}));
    Term denominator(createExpressionIfPossible({polynomialTerm, "^", 8}));
    TermsOverTerms termsOverTerms({numerator}, {denominator});
    termsOverTerms.setAsShouldSimplifyToFactors(true);

    termsOverTerms.simplify();

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    EXPECT_TRUE(numeratorsToVerify.empty());
    Term expectedDenominator(createExpressionIfPossible({polynomialTerm, "^", 6}));
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
    Factorization::ConfigurationDetails configurationDetails(
                Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    termsOverTerms.setFactorizationConfigurationDetails(configurationDetails);

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

TEST(TermsOverTermsTest, SimplifyWorksAndFactorizeTrigonometricFunctions)
{
    Term numerator(createExpressionIfPossible({sec("x"), "*", tan("x")}));
    Term denominatorPart1(createExpressionIfPossible({Monomial(1, {{"x", 2}}), "*", sec("x"), "*", tan("x")}));
    Term denominatorPart2(createExpressionIfPossible({Monomial(2, {{"x", 1}}), "*", sec("x")}));
    Term denominator(createExpressionIfPossible({denominatorPart1, "+", denominatorPart2}));
    TermsOverTerms termsOverTerms({numerator}, {denominator});
    termsOverTerms.setAsShouldSimplifyToFactors(true);
    Factorization::ConfigurationDetails configurationDetails(
                Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    termsOverTerms.setFactorizationConfigurationDetails(configurationDetails);

    termsOverTerms.simplify();

    Term expectedNumerator(tan("x"));
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(expectedNumerator, numeratorsToVerify.at(0));
    Term expectedDenominator1("x");
    Term expectedDenominator2(createExpressionIfPossible({2, "+", "x", "*", tan("x")}));
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(2U, denominatorsToVerify.size());
    EXPECT_EQ(expectedDenominator1, denominatorsToVerify.at(0));
    EXPECT_EQ(expectedDenominator2, denominatorsToVerify.at(1));
}

TEST(TermsOverTermsTest, SimplifyWorksOnDistributingTerms)
{
    Term lnOfX(ln("x"));
    Term sinOfLnOfX(sin(lnOfX));
    Term cosOfLnOfX(cos(lnOfX));
    Term numeratorPart(createExpressionIfPossible({cosOfLnOfX, "-", sinOfLnOfX}));
    Term numerator(createExpressionIfPossible({"x", "*", numeratorPart}));
    Term denominator(2);
    TermsOverTerms termsOverTerms({numerator}, {denominator});

    termsOverTerms.simplify();

    string stringToExpect("((x*cos(ln(x)))-(x*sin(ln(x))))");
    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(stringToExpect, convertToString(numeratorsToVerify.at(0)));
    Term expectedDenominator1(2);
    Terms denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(expectedDenominator1, denominatorsToVerify.at(0));
}

}

}
