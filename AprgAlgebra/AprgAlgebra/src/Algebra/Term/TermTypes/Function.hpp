#pragma once

#include <Algebra/Term/TermTypes/BaseTerm.hpp>
#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/BaseTermPointers.hpp>
#include <Math/Number/AlbaNumber.hpp>

#include <functional>
#include <string>
namespace alba
{
namespace algebra
{

class Function : public BaseTermData
{
public:
    using FunctionToPerform=std::function<AlbaNumber(AlbaNumber const&)>;

    Function();
    Function(Function const& functionObject);
    Function(
            std::string const& functionName,
            BaseTerm const& baseTerm,
            FunctionToPerform const& functionToPerform);

    Function & operator=(Function const& functionObject);

    bool operator==(Function const& second) const;
    bool operator!=(Function const& second) const;
    bool operator<(Function const& second) const;

    bool isInputAConstant() const;

    std::string getFunctionName() const;
    std::string getDisplayableString() const;
    std::string getDebugString() const;

    AlbaNumber performFunctionAndReturnResultIfPossible() const;
    BaseTerm const& getInputTermConstReference() const;
    FunctionToPerform const& getFunctionToPerform() const;

    BaseTerm & getInputTermReference();
    void simplify();

private:
    std::string m_functionName;
    BaseTermUniquePointer m_inputTermPointer;
    FunctionToPerform m_functionToPerform;
};

std::ostream & operator<<(std::ostream & out, Function const& functionAsParameter);

}

}
