#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Math/AlbaNumber.hpp>

#include <functional>
#include <string>

namespace alba
{

namespace algebra
{

class Function : public BaseTermData // is there a need of multiple parameter functions?
{
public:
    using FunctionToPerform=std::function<AlbaNumber(AlbaNumber const&)>;

    Function();
    Function(
            std::string const& functionName,
            Expression const& expression,
            FunctionToPerform const& functionToPerform);

    bool operator==(Function const& second) const;
    bool operator!=(Function const& second) const;
    bool operator<(Function const& second) const;

    bool isInputExpressionAConstant() const;

    std::string getFunctionName() const;
    std::string getDisplayableString() const;
    std::string getDebugString() const;

    AlbaNumber performFunctionAndReturnResultIfPossible() const;
    Expression const& getInputExpressionConstReference() const;
    FunctionToPerform const& getFunctionToPerform() const;

    Expression & getInputExpressionReference();
    void simplify();

private:
    std::string m_functionName;
    Expression m_inputExpression;
    FunctionToPerform m_functionToPerform;
};

std::ostream & operator<<(std::ostream & out, Function const& functionAsParameter);

}

}