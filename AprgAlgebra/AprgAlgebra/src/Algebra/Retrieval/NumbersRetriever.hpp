#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba {

namespace algebra {

class NumbersRetriever final : public BaseRetriever {
public:
    AlbaNumbersSet const& getNumbers() const;

    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;

private:
    AlbaNumbersSet m_numbers;
};

}  // namespace algebra

}  // namespace alba
