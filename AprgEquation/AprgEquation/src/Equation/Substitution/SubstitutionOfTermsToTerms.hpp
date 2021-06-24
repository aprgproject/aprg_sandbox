#pragma once

#include <Equation/Term/Term.hpp>
#include <Equation/Term/TermsWithAssociation.hpp>

#include <string>

using namespace std;

namespace alba
{

namespace equation
{

using TermToTermMap = std::map<Term, Term>;
using TermTermPair = std::pair<Term, Term>;

class SubstitutionOfTermsToTerms
{
public:
    SubstitutionOfTermsToTerms();
    SubstitutionOfTermsToTerms(std::initializer_list<TermTermPair> const& variablesWithValues);
    SubstitutionOfTermsToTerms(TermToTermMap const& variablesWithValues);

    bool isTermFound(Term const& term) const;
    Term getTermForTerm(Term const& term) const;
    Term performSubstitutionTo(Expression const& expression) const;
    Term performSubstitutionTo(Function const& functionAsParameter) const;
    Term performSubstitutionTo(Term const& term) const;

    void putTermsToTermsMapping(std::initializer_list<TermTermPair> const& variablesWithValues);
    void putTermsToTermsMapping(TermToTermMap const& variablesWithValues);
    void putTermToTermMapping(Term const& term1, Term const& term2);

private:
    Expression performSubstitutionForExpression(Expression const& expression) const;
    Function performSubstitutionForFunction(Function const& functionAsParameter) const;
    void performSubstitutionForTermsWithAssociation(TermsWithAssociation & termsWithAssociation) const;
    TermToTermMap m_termsToTermsMap;
};

}

}
