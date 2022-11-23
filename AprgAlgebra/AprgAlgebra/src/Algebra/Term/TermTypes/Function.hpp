#pragma once

#include <Algebra/Term/TermTypes/BaseTerm.hpp>
#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/BaseTermPointers.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <functional>
#include <string>

namespace alba
{

namespace algebra
{

class Function : public BaseTermData
{
public:
    using EvaluationFunction=std::function<AlbaNumber(AlbaNumber const&)>;

    Function();
    Function(Function const& functionObject);
    Function(
            std::string const& functionName,
            BaseTerm const& baseTerm,
            EvaluationFunction const& evaluationFunction);

    Function & operator=(Function const& functionObject);

    bool operator==(Function const& second) const;
    bool operator!=(Function const& second) const;
    bool operator<(Function const& second) const;
    bool isSimplified() const;

    std::string getFunctionName() const;
    std::string getDebugString() const;
    AlbaNumber performFunctionAndReturnResultIfPossible() const;
    BaseTerm const& getInputTermConstReference() const;    EvaluationFunction const& getEvaluationFunction() const;

    BaseTerm & getInputTermReference();
    void simplify();

    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();

private:
    friend std::ostream & operator<<(std::ostream & out, Function const& functionObject);

    std::string m_functionName;
    BaseTermUniquePointer m_inputTermPointer;
    EvaluationFunction m_evaluationFunction;
    bool m_isSimplified;
};

}

}