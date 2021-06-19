#pragma once

#include <Equation/Constructs/TermsOverTerms.hpp>
#include <Equation/Term/TermAssociationType.hpp>

#include <vector>
namespace alba
{

namespace equation
{

class AdditionAndSubtractionOfTermsOverTerms
{
public:
    AdditionAndSubtractionOfTermsOverTerms();

    void putAsAddOrSubtraction(TermsOverTerms const& item, TermAssociationType const associationType);
    void putAsAddition(TermsOverTerms const& addend);
    void putAsSubtraction(TermsOverTerms const& subtrahend);

    Expression getCombinedExpression() const;
    Terms getLcmOfDenominatorTerms() const;
    Terms getNewNumeratorTermsOnLcm(
            unsigned int numeratorIndex,
            Terms const& lcmOfDenominatorTerms) const;

private:
    std::vector<TermsOverTerms> m_items;
    std::vector<TermAssociationType> m_associations;
};

}

}
