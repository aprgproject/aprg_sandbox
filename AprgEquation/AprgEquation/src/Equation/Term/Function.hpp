#pragma once

#include <Equation/Term/BaseTermData.hpp>
#include <Equation/Term/Constant.hpp>
#include <Equation/Term/Expression.hpp>

#include <functional>
#include <string>

namespace alba
{

namespace equation
{

class Function : public BaseTermData // is there a need of multiple parameter functions?
{
    friend std::ostream & operator<<(std::ostream & out, Function const& term);
public:
    using FunctionToPerform=std::function<Constant(Constant const&)>;

    Function();
    Function(
            std::string const& functionName,
            Expression const& expression,
            FunctionToPerform const& functionToPerform);

    bool operator==(Function const& second) const;
    bool operator!=(Function const& second) const;
    bool operator<(Function const& second) const;

    bool isInputExpressionAConstant() const;

    std::string getFunctionName() const;    std::string getDisplayableString() const;
    std::string getDebugString() const;

    Constant performFunctionAndReturnResultIfPossible() const;
    Expression const& getInputExpressionConstReference() const;

    Expression & getInputExpressionReference();
    void simplify();

private:    std::string m_functionName;
    Expression m_inputExpression;
    FunctionToPerform m_functionToPerform;
};

std::ostream & operator<<(std::ostream & out, Function const& functionAsParameter);

}

}
