#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermPointers.hpp>

#include <string>
#include <vector>

namespace alba
{

namespace booleanAlgebra
{

struct WrappedTerm
{
    WrappedTerm(BaseTerm const& baseTerm);
    WrappedTerm(WrappedTerm const& wrappedTerm);
    bool operator==(WrappedTerm const& second) const;
    bool operator!=(WrappedTerm const& second) const;
    bool operator<(WrappedTerm const& second) const;
    void clear();

    friend std::ostream & operator<<(std::ostream & out, WrappedTerm const& wrappedTerm);

    BaseTermSharedPointer baseTermSharedPointer;
};

using WrappedTerms=std::vector<WrappedTerm>;

}

}