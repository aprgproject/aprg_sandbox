#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

namespace Simplification {

void simplifyTermToACommonDenominator(Term& term);
void simplifyTermByCombiningRadicals(Term& term);
void simplifyTermByFactoringToNonDoubleFactors(Term& term);
void simplifyTermByFactoringToNonDoubleFactorsToACommonDenominator(Term& term);

bool simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(
    Expression& expression);
bool tryToAddSubtractTermsOverTermsAndReturnIfChanged(Expression& addSubtractExpression);
void simplifyTermsWithDetailsInExpressionToACommonDenominator(Expression& expression);

void simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
    TermsWithDetails& newTermsWithDetails, OperatorLevel& mainOperatorLevel,
    TermsWithDetails const& oldTermsWithDetails);
void simplifyAndCopyTermsFromAnExpressionAndChangeOperatorLevelIfNeeded(
    TermsWithDetails& newTermsWithDetails, OperatorLevel& mainOperatorLevel, Expression const& subExpression,
    TermAssociationType const subExpressionAssociation);
TermsWithAssociation getTermsWithAssociationAndReverseIfNeeded(
    Expression const& expression, TermAssociationType const overallAssociation);

}  // namespace Simplification

}  // namespace algebra

}  // namespace alba
