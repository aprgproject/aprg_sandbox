#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba
{
namespace algebra
{
using BaseExponentsRetriever = BaseRetriever<AlbaNumbersSet>;

class ExponentsRetriever final : public BaseExponentsRetriever
{
public:
    void retrieveFromMonomial(Monomial const& monomial) override;
};

}

}
