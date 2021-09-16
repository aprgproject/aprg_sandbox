#pragma once

#include <Algebra/Term/TermTypes/Expression.hpp>

namespace alba
{

namespace algebra
{

namespace Simplification
{

bool simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(Expression & expression);
bool tryToAddSubtractTermsOverTermsAndReturnIfChanged(Expression & addSubtractExpression);
void simplifyTermsWithDetailsInExpressionToACommonDenominator(Expression & expression);

void simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
        TermsWithDetails & termsToUpdate,
        OperatorLevel & mainOperatorLevel,
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
