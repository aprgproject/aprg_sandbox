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
    std::string getDisplayableString() const;
    void clear();
    BaseTermSharedPointer baseTermSharedPointer;
};

using WrappedTerms=std::vector<WrappedTerm>;

std::ostream & operator<<(std::ostream & out, WrappedTerm const& wrappedTerm);

}

}
