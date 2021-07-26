#pragma once

#include <Algebra/Term/TermTypes/BaseTerm.hpp>

#include <memory>
#include <vector>

namespace alba
{

namespace algebra
{

using BaseTermSharedPointer = std::shared_ptr<BaseTerm>;
using BaseTermUniquePointer = std::unique_ptr<BaseTerm>;
using BaseTermSharedPointers = std::vector<BaseTermSharedPointer>;

}

}
