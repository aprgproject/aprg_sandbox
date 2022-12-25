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

    // rule of five or six
    ~WrappedTerm() = default;
    WrappedTerm(WrappedTerm const& termWithDetails);
    WrappedTerm & operator=(WrappedTerm const& termWithDetails);
    WrappedTerm(WrappedTerm && termWithDetails) = default;
    WrappedTerm & operator=(WrappedTerm && termWithDetails) = default;

    bool operator==(WrappedTerm const& second) const;
    bool operator!=(WrappedTerm const& second) const;
    bool operator<(WrappedTerm const& second) const;

    void clear();

    friend std::ostream & operator<<(std::ostream & out, WrappedTerm const& wrappedTerm);

    BaseTermUniquePointer baseTermPointer;
};

using WrappedTerms=std::vector<WrappedTerm>;
}

}