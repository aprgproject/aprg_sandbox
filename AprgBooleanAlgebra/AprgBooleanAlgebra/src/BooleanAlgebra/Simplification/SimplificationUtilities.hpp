#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

namespace Simplification
{

void simplifyByQuineMcKluskey(Term & term);

void simplifyTermByPriorityAndOperationThenOrOperation(Term & term);

void simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
        WrappedTerms & newWrappedTerms,
        OperatorLevel & mainOperatorLevel,
        WrappedTerms const& oldWrappedTerms);

void simplifyAndCopyTermsFromAnExpressionAndChangeOperatorLevelIfNeeded(
        WrappedTerms & newWrappedTerms,
        OperatorLevel & mainOperatorLevel,
        Expression const& subExpression);

Terms createUniqueTerms(
        WrappedTerms const& terms);

void combineComplementaryTerms(
        Terms & termsToCombine,
        OperatorLevel const operatorLevel);

void combineTermsByCheckingTheCommonFactor(
        Terms & termsToCombine,
        OperatorLevel const operatorLevel);

void combineUniqueTermsAndCommonFactorIfPossible(
        Term & outputTerm,
        Term const& term1,
        Term const& term2,
        OperatorLevel const operatorLevel);

Terms getTermOrSubTerms(Term const& term);

OperatorLevel getSubOperatorLevel(
        Term const& term1,
        Term const& term2);

void distributeTermsIfNeeded(
        Term & outputTerm,
        Terms const& inputTerms,
        OperatorLevel const outerOperation,
        OperatorLevel const innerOperation);

void distributeTermsWithRecursion(
        Term & outputTerm,
        Terms & innerTermsCombinations,
        Expressions const& innerExpressions,
        Term const& outerFactor,
        OperatorLevel const outerOperation,
        OperatorLevel const innerOperation,
        unsigned int const index);

}

}

}
