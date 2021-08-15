#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumber.hpp>

#include <string>

namespace alba
{

namespace algebra
{

class ProofByInduction
{
public:
    using FunctionToCheck=std::function<AlbaNumber(AlbaNumber const&)>;

    ProofByInduction(
            std::string const variableNameInExpression,
            Term const& algebraicExpressionToCheck,
            FunctionToCheck const& functionToCheck);

    bool isVerificationOnASpecificValueSuccessful(AlbaNumber const& value) const;
    bool isVerificationOnInductionStepSuccessful(
            Term const& firstTerm,
            Term const& secondTerm,
            Term const& expectedDifferenceOfFirstAndSecondTerm) const;

    std::string m_variableNameInExpression;
    Term m_algebraicExpressionToCheck;
    FunctionToCheck m_functionToCheck;
};

}

}
