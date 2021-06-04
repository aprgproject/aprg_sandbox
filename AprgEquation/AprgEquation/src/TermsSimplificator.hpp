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

    void simplify();
    void simplify(unsigned int const index);
    void simplifyThreeTerms(unsigned int const index);

    AlbaOptional<Term> getNewTermFromThreeTerms(
            Term const& term1,
            Term const& term2,
            Term const& term3) const;

    AlbaOptional<Term> combineConstantOperatorConstant(
            Constant const& constant1,
            Operator const& operatorTerm,
            Constant const& constant2) const;
    AlbaOptional<Term> combineConstantOperatorVariable(
            Constant const& constant,
            Operator const& operatorTerm,
            Variable const& variable) const;
    AlbaOptional<Term> combineVariableOperatorConstant(
            Variable const& variable,
            Operator const& operatorTerm,
            Constant const& constant) const;
    AlbaOptional<Term> combineVariableOperatorVariable(
            Variable const& variable1,
            Operator const& operatorTerm,
            Variable const& variable2) const;
    AlbaOptional<Term> combineVariableOperatorVariableSameVariable(
            Variable const& variable,
            Operator const& operatorTerm) const;
    AlbaOptional<Term> combineVariableOperatorVariableDifferentVariable(
            Variable const& variable1,
            Operator const& operatorTerm,
            Variable const& variable2) const;
    AlbaOptional<Term> combineMonomialOperatorConstant(
            Monomial const& monomial,
            Operator const& operatorTerm,
            Constant const& constant) const;
    AlbaOptional<Term> combineMonomialOperatorVariable(
            Monomial const& monomial,
            Operator const& operatorTerm,
            Variable const& variable) const;
    AlbaOptional<Term> combineMonomialOperatorVariableSameMonomialVariable(
            Monomial const& monomial,
            Operator const& operatorTerm,
            Variable const& variable) const;
    AlbaOptional<Term> combineMonomialOperatorVariableDifferentMonomialVariable(
            Monomial const& monomial,
            Operator const& operatorTerm,
            Variable const& variable) const;
    AlbaOptional<Term> combineConstantOperatorMonomial(
            Constant const& constant,
            Operator const& operatorTerm,
            Monomial const& monomial) const;
    AlbaOptional<Term> combineVariableOperatorMonomial(
            Variable const& variable,
            Operator const& operatorTerm,
            Monomial const& monomial) const;
    AlbaOptional<Term> combineVariableOperatorMonomialSameMonomialVariable(
            Variable const& variable,
            Operator const& operatorTerm,
            Monomial const& monomial) const;
    AlbaOptional<Term> combineVariableOperatorMonomialDifferentMonomialVariable(
            Variable const& variable,
            Operator const& operatorTerm,
            Monomial const& monomial) const;

    void eraseTermsInclusive(
            unsigned int const firstIndex,            unsigned int const secondIndex);
    void insertTerm(
            unsigned int const index,
            Term const& term);

private:
    Terms m_terms;
};

}

}
