#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>
#include <Common/Container/AlbaConfigurationHolder.hpp>

namespace alba
{

namespace booleanAlgebra
{

namespace Simplification
{

class SimplificationOfExpression
{
public:
    // is logarithm simplification needed?
    struct ConfigurationDetails
    {
        bool shouldSimplifyWithOuterOrAndInnerAnd;
        bool shouldSimplifyWithOuterAndAndInnerOr;
        bool shouldSimplifyByQuineMcKluskey;
    };
    class Configuration
            : public AlbaConfigurationHolder<ConfigurationDetails>
    {};
    class ScopeObject : public AlbaConfigurationScopeObject<ConfigurationDetails>
    {};

    SimplificationOfExpression();
    SimplificationOfExpression(Expression const& expression);

    static bool shouldSimplifyWithOuterOrAndInnerAnd();
    static bool shouldSimplifyWithOuterAndAndInnerOr();
    static bool shouldSimplifyByQuineMcKluskey();

    Expression getExpression() const;
    void setExpression(Expression const& expression);

    void simplify();
private:
    bool isChangeDetected(
            Expression const& expression1,
            Expression const& expression2) const;

    void simplifyExpressionUntilNoChange();
    void simplifyExpression(Expression & expression);

    void processTermsBaseOnOperatorLevel(
            Expression & expression,
            WrappedTerms const& termsToProcess,
            OperatorLevel const operatorLevel);
    void processAndSaveTermsForAndOperation(
            Expression & expression,
            WrappedTerms const& termsToProcess);
    void processAndSaveTermsForOrOperation(
            Expression & expression,
            WrappedTerms const& termsToProcess);

    Expression m_expression;
};

}

}

template <>
booleanAlgebra::Simplification::SimplificationOfExpression::ConfigurationDetails
getDefaultConfigurationDetails<booleanAlgebra::Simplification::SimplificationOfExpression::ConfigurationDetails>();

}
