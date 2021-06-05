#pragma once

#include <Term.hpp>
#include <Optional/AlbaOptional.hpp>

namespace alba
{

namespace equation
{

class TermsSimplificator
{
public:
    TermsSimplificator(Terms const& terms);

    Terms const& getTermsConstReference() const;

    void buildExpressionFromTerms();
    void simplifyTerms();

private:
    AlbaOptional<unsigned int> getNextOperatorIndexToPerform() const;

    bool buildExpressionWithBinaryOperationAndReturnIfBuilt(unsigned int const index);
    bool buildExpressionWithUnaryOperationAndReturnIfBuilt(unsigned int const index);
    bool simplifyBinaryOperationAndReturnIfSimplified(unsigned int const index);
    bool simplifyUnaryOperationAndReturnIfSimplified(unsigned int const index);

    void eraseTermsInclusive(
            unsigned int const firstIndex,
            unsigned int const secondIndex);
    void insertTerm(
            unsigned int const index,
            Term const& term);

    Terms m_terms;
};

}

}
