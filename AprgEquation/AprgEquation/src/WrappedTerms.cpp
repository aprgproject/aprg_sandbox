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

BaseTermSharedPointers & WrappedTerms::getBaseTermPointersReference()
{
    return m_baseTermPointers;
}

BaseTermSharedPointers const& WrappedTerms::getBaseTermPointersConstReference() const
{
    return m_baseTermPointers;
}

}

}