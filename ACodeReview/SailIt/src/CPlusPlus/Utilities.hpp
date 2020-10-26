#pragma once

#include "Term/Term.hpp"

#include <deque>
#include <ostream>
#include <set>
#include <string>
#include <vector>

using std::deque;
using std::vector;
using std::string;
using std::set;

namespace codeReview
{

typedef vector<string> VectorOfStrings;
typedef set<string> SetOfStrings;

typedef deque<Term> DequeOfTerms;
typedef deque<Term>::iterator TermsIterator;
typedef deque<Term>::reverse_iterator TermsReverseIterator;
typedef vector<Term> VectorOfTerms;
typedef vector<Term>::iterator ExpectedTermsIterator;

void printTerms(DequeOfTerms const& terms);
void printTerms(VectorOfTerms const& terms);
void printContentOfTerms(DequeOfTerms const& terms, std::ostream& fileStream);


}// namespace codeReview


