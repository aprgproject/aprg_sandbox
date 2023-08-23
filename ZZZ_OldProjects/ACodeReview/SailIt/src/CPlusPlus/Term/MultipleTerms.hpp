#pragma once

#include "Term.hpp"

#include <initializer_list>
#include <vector>

using std::initializer_list;
using std::vector;

namespace codeReview {

class MultipleTerms {
public:
    explicit MultipleTerms(initializer_list<Term> const& initializerList);
    bool isEqualToAnyOfTheTerms(Term const& termToCompare) const;

private:
    vector<Term> m_terms;
};

}  // namespace codeReview
