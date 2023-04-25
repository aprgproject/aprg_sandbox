#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba {

namespace algebra {

using BaseNumbersRetriever = BaseRetriever<AlbaNumbersSet>;

class NumbersRetriever final : public BaseNumbersRetriever {
public:
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
};

}  // namespace algebra

}  // namespace alba
