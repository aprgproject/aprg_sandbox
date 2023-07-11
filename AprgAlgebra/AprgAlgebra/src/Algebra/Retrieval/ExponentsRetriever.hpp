#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba {

namespace algebra {

class ExponentsRetriever final : public BaseRetriever {
public:
    AlbaNumbersSet const& getExponents() const;

    void retrieveFromMonomial(Monomial const& monomial) override;

private:
    AlbaNumbersSet m_exponents;
};

}  // namespace algebra

}  // namespace alba
