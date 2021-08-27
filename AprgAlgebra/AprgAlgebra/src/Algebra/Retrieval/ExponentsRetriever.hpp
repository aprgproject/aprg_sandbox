#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

namespace alba
{

namespace algebra
{

using BaseExponentsRetriever = BaseRetriever<AlbaNumbersSet>;

class ExponentsRetriever final : public BaseExponentsRetriever
{
public:
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
};

}

}
