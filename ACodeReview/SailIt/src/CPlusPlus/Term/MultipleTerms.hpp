#pragma once

#include <initializer_list>
#include "Term.hpp"
#include <vector>

using std::vector;
using std::initializer_list;

namespace codeReview
{

class MultipleTerms
{
public:
    explicit MultipleTerms(initializer_list<Term> initializerList);
    bool isEqualToAnyOfTheTerms(Term const& termToCompare) const;

private:
    vector<Term> m_terms;
};

}// namespace codeReview
