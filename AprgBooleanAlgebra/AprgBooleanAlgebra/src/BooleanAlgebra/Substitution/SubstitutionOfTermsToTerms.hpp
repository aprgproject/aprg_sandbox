#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

#include <map>

namespace alba {

namespace booleanAlgebra {

using TermToTermMap = std::map<Term, Term>;
using TermTermPair = std::pair<Term, Term>;

class SubstitutionOfTermsToTerms {
public:
    SubstitutionOfTermsToTerms() = default;
    SubstitutionOfTermsToTerms(std::initializer_list<TermTermPair> const& variablesWithValues);
    SubstitutionOfTermsToTerms(TermToTermMap const& variablesWithValues);

    bool isEmpty() const;
    bool isTermFound(Term const& term) const;
    int getSize() const;
    Term getTermForTerm(Term const& term) const;
    Term performSubstitutionTo(Expression const& expression) const;
    Term performSubstitutionTo(Term const& term) const;

    Expression performSubstitutionForExpression(Expression const& expression) const;

    void putTermsToTermsMapping(std::initializer_list<TermTermPair> const& variablesWithValues);
    void putTermsToTermsMapping(TermToTermMap const& variablesWithValues);
    void putTermToTermMapping(Term const& term1, Term const& term2);

private:
    void performSubstitutionForWrappedTerms(WrappedTerms& wrappedTerms) const;
    TermToTermMap m_termsToTermsMap;
};

}  // namespace booleanAlgebra

}  // namespace alba
