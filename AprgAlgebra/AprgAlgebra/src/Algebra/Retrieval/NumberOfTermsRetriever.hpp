#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

namespace alba
{

namespace algebra
{

using BaseNumberOfTermsRetriever = BaseRetriever<unsigned int>;

class NumberOfTermsRetriever final : public BaseNumberOfTermsRetriever
{
public:
    NumberOfTermsRetriever();
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromPolynomial(Polynomial const& polynomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;
};

}

}