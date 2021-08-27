#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Math/Number/AlbaNumber.hpp>

namespace alba
{

namespace algebra
{

using BaseFirstCoefficientRetriever = BaseRetriever<AlbaNumber>;

class FirstCoefficientRetriever final : public BaseFirstCoefficientRetriever
{
public:
    FirstCoefficientRetriever();
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;

private:
    bool m_isValueSet;
};

}

}
