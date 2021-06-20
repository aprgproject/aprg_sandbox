#pragma once

#include <Equation/Term/BaseTerm.hpp>

#include <memory>
#include <vector>

namespace alba
{

namespace equation
{

using BaseTermSharedPointer = std::shared_ptr<BaseTerm>;
using BaseTermUniquePointer = std::unique_ptr<BaseTerm>;
using BaseTermSharedPointers = std::vector<BaseTermSharedPointer>;

}

}
