#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

namespace Simplification
{

void simplifyTermToACommonDenominator(Term & term);
void simplifyTermByCombiningRadicals(Term & term);
void simplifyTermByFactoringToNonDoubleFactors(Term & term);

bool simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(Expression & expression);
bool tryToAddSubtractTermsOverTermsAndReturnIfChanged(Expression & addSubtractExpression);void simplifyTermsWithDetailsInExpressionToACommonDenominator(Expression & expression);

void simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
        TermsWithDetails & termsToUpdate,        OperatorLevel & mainOperatorLevel,
        TermsWithDetails const& termsToCheck);
void simplifyAndCopyTermsFromAnExpressionAndChangeOperatorLevelIfNeeded(
        TermsWithDetails & termsToUpdate,
        OperatorLevel & mainOperatorLevel,
        Expression const& expression,
        TermAssociationType const association);
TermsWithAssociation getTermsWithAssociationAndReverseIfNeeded(
        Expression const& expression,
        TermAssociationType const overallAssociation);

}

}

}
