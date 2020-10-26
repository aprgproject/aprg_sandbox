#include "Utilities.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

namespace codeReview
{

void printTerms(DequeOfTerms const& terms)
{
    std::copy(terms.begin(), terms.end(), std::ostream_iterator<Term>(std::cout, "\n"));
}

void printTerms(VectorOfTerms const& terms)
{
    std::copy(terms.begin(), terms.end(), std::ostream_iterator<Term>(std::cout, "\n"));
}

void printContentOfTerms(DequeOfTerms const& terms, ostream& outStream)
{
    for(Term const& term : terms)
    {
        outStream<<term.getString();
    }
}

}// namespace codeReview


