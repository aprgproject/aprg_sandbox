#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

using TermToTermMap = std::map<Term, Term>;
using TermTermPair = std::pair<Term, Term>;

class SubstitutionOfTermsToTerms {
public:
    SubstitutionOfTermsToTerms();
    SubstitutionOfTermsToTerms(std::initializer_list<TermTermPair> const& variablesWithValues);
    SubstitutionOfTermsToTerms(TermToTermMap const& variablesWithValues);

    bool isEmpty() const;
    bool isTermFound(Term const& term) const;
    unsigned int getSize() const;
    Term getTermForTerm(Term const& term) const;
    Term performSubstitutionTo(Expression const& expression) const;
    Term performSubstitutionTo(Function const& functionObject) const;
    Term performSubstitutionTo(Term const& term) const;
    Equation performSubstitutionTo(Equation const& equation) const;

    Expression performSubstitutionForExpression(Expression const& expression) const;
    Function performSubstitutionForFunction(Function const& functionObject) const;

    void putTermsToTermsMapping(std::initializer_list<TermTermPair> const& variablesWithValues);
    void putTermsToTermsMapping(TermToTermMap const& variablesWithValues);
    void putTermToTermMapping(Term const& term1, Term const& term2);

private:
    void performSubstitutionForTermsWithAssociation(TermsWithAssociation& termsWithAssociation) const;
    TermToTermMap m_termsToTermsMap;
};

}  // namespace algebra

}  // namespace alba
