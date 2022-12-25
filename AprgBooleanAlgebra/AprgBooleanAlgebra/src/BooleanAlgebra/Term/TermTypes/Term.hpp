#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTerm.hpp>
#include <BooleanAlgebra/Term/TermTypes/Constant.hpp>
#include <BooleanAlgebra/Term/TermTypes/Expression.hpp>
#include <BooleanAlgebra/Term/TermTypes/Operator.hpp>
#include <BooleanAlgebra/Term/TermTypes/TermType.hpp>
#include <BooleanAlgebra/Term/TermTypes/VariableTerm.hpp>

#include <memory>
#include <string>
#include <vector>

namespace alba
{

namespace booleanAlgebra
{

class Term : public BaseTerm
{
public:
    Term();
    Term(Term const& term);
    Term(bool const boolValue);
    Term(char const* const characterString);
    Term(std::string const& stringAsParameter);    Term(Constant const& constant);
    Term(VariableTerm const& variableTerm);
    Term(Operator const& operatorTerm);
    Term(Expression const& expression);

    Term & operator=(Term const& term);

    bool operator==(Term const& second) const;
    bool operator!=(Term const& second) const;    bool operator<(Term const& second) const;

    Term operator~() const;
    bool isEmpty() const;
    bool isConstant() const;
    bool isVariableTerm() const;
    bool isOperator() const;
    bool isExpression() const;
    bool isSimplified() const;

    TermType getTermType() const;
    Constant const& getConstantConstReference() const;
    VariableTerm const& getVariableTermConstReference() const;
    Operator const& getOperatorConstReference() const;
    Expression const& getExpressionConstReference() const;
    bool getBooleanValue() const;
    std::string getDisplayableString() const;
    std::string getDebugString() const;

    Constant & getConstantReference();
    VariableTerm & getVariableTermReference();
    Operator & getOperatorReference();
    Expression & getExpressionReference();

    void clear();
    void simplify();
    void sort();    void negate();

    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();

private:
    void resetBaseDataTermPointerBasedFromTerm(Term const& term);
    void initializeBasedOnString(std::string const& stringAsParameter);

    friend std::ostream & operator<<(std::ostream & out, Term const& term);
    TermType m_type;
    bool m_isSimplified;
    std::unique_ptr<BaseTermData> m_baseTermDataPointer;
};

using Terms = std::vector<Term>;
}

}