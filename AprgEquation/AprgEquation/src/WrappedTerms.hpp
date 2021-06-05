#pragma once

#include <BaseTermPointers.hpp>

namespace alba
{

namespace equation
{

class WrappedTerms
{
public:

    WrappedTerms();
    ~WrappedTerms();

    BaseTermSharedPointers & getBaseTermPointersReference();
    BaseTermSharedPointers const& getBaseTermPointersConstReference() const;

private:
     BaseTermSharedPointers m_baseTermPointers;
};

}

}
