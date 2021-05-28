#include "WrappedTerms.hpp"

#include <Term.hpp>

namespace alba
{

namespace equation
{

WrappedTerms::WrappedTerms()
{}

WrappedTerms::~WrappedTerms()
{}

WrappedTerms::BaseTermPointers & WrappedTerms::getBaseTermPointersReference()
{
    return m_baseTermPointers;
}

WrappedTerms::BaseTermPointers const& WrappedTerms::getBaseTermPointersConstReference() const
{
    return m_baseTermPointers;
}


}

}
