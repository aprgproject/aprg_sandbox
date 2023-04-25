#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

#include <functional>

namespace alba {

namespace algebra {

using BaseFunctionsRetriever = BaseRetriever<FunctionsSet>;

class FunctionsRetriever final : public BaseFunctionsRetriever {
public:
    using FunctionCondition = std::function<bool(Function const&)>;

    FunctionsRetriever(FunctionCondition const& isFunctionIncluded);
    void retrieveFromPolynomial(Polynomial const&) override;
    void retrieveFromFunction(Function const& functionObject) override;

private:
    FunctionCondition m_isFunctionIncluded;
};

}  // namespace algebra

}  // namespace alba
