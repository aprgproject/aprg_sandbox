#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTerm.hpp>

#include <memory>
#include <vector>

namespace alba
{

namespace booleanAlgebra
{

using BaseTermSharedPointer = std::shared_ptr<BaseTerm>;
using BaseTermUniquePointer = std::unique_ptr<BaseTerm>;
using BaseTermSharedPointers = std::vector<BaseTermSharedPointer>;

}

}
