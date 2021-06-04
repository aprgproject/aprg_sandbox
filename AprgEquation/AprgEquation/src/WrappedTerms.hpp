#pragma once

#include <BaseTerm.hpp>
#include <BaseTermPointers.hpp>

#include <memory>
#include <vector>
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