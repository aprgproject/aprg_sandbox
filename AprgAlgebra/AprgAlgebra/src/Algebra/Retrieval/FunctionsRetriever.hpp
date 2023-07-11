#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

#include <functional>

namespace alba {

namespace algebra {

class FunctionsRetriever final : public BaseRetriever {
public:
    using FunctionCondition = std::function<bool(Function const&)>;

    FunctionsRetriever(FunctionCondition const& isFunctionIncluded);

    FunctionsSet const& getFunctions() const;

    void retrieveFromPolynomial(Polynomial const&) override;
    void retrieveFromFunction(Function const& functionObject) override;

private:
    FunctionCondition m_isFunctionIncluded;
    FunctionsSet m_functions;
};

}  // namespace algebra

}  // namespace alba
