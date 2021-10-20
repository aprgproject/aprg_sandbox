#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

namespace Simplification
{

class SimplificationOfFunctionToTerm
{
public:
    struct ConfigurationDetails
    {
        bool shouldSimplifyTrigonometricFunctionsToSinAndCos;
        bool shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel;
    };

    class Configuration
            : public AlbaConfigurationHolder<ConfigurationDetails>
    {};

    class ScopeObject : public AlbaConfigurationScopeObject<ConfigurationDetails>
    {};

    SimplificationOfFunctionToTerm();

    static bool shouldSimplifyTrigonometricFunctionsToSinAndCos();
    static bool shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel();

    Term simplifyToTerm(Function const& functionObject);

private:
    Term simplifyTrigometricFunctionToExpression(Function const& functionObject);
    Term simplifyLogarithmicFunctionToExpression(Function const& functionObject);
    Term getLogarithmicOfTermBasedFromName(Term const& term, std::string const& functionName) const;

};

}

}

template <>
algebra::Simplification::SimplificationOfFunctionToTerm::ConfigurationDetails
getDefaultConfigurationDetails<alba::algebra::Simplification::SimplificationOfFunctionToTerm::ConfigurationDetails>();

}
