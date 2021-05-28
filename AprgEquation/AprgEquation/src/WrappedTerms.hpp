#pragma once

#include <BaseTerm.hpp>

#include <memory>
#include <vector>

namespace alba
{

namespace equation
{

class WrappedTerms
{
public:
    using BaseTermPointers = std::vector<std::shared_ptr<BaseTerm>>;

    WrappedTerms();
    ~WrappedTerms();

    BaseTermPointers & getBaseTermPointersReference();
    BaseTermPointers const& getBaseTermPointersConstReference() const;

private:
     BaseTermPointers m_baseTermPointers;
};

}

}
