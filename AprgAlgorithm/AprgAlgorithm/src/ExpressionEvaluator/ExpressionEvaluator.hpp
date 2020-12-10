#pragma once

#include <functional>
#include <stack>
#include <vector>

namespace alba
{

namespace ExpressionEvaluator
{

template <typename ValueTemplateType, typename OperatorTemplateType>
class ExpressionEvaluatorConverter;

template <typename ValueTemplateType, typename OperatorTemplateType>
class ExpressionEvaluatorTerm
{
public:
    enum class TermType
    {
        Value,
        Operator
    };
    enum class OperatorSyntaxType
    {
        Unknown,
        PrefixUnary,
        Binary,
        StartGroup,
        EndGroup
    };
    ExpressionEvaluatorTerm(ValueTemplateType const& value)
        : m_termType(TermType::Value)
        , m_value(value)
        , m_operator()
        , m_operatorSyntaxType(OperatorSyntaxType::Unknown)
        , m_operatorPriority(0)
    {}
    ExpressionEvaluatorTerm(OperatorTemplateType const& operatorValue, OperatorSyntaxType const& operatorSyntaxValue)
        : m_termType(TermType::Operator)
        , m_value()
        , m_operator(operatorValue)
        , m_operatorSyntaxType(operatorSyntaxValue)
        , m_operatorPriority(0)
    {}
    ExpressionEvaluatorTerm(OperatorTemplateType const& operatorValue, OperatorSyntaxType const& operatorSyntaxValue, unsigned int const operatorPriority)
        : m_termType(TermType::Operator)
        , m_value()
        , m_operator(operatorValue)
        , m_operatorSyntaxType(operatorSyntaxValue)
        , m_operatorPriority(operatorPriority)
    {}
    bool isOperator() const
    {
        return m_termType == TermType::Operator;
    }
    bool isValue() const
    {
        return m_termType == TermType::Value;
    }
    bool isStartGroupOperator() const
    {
        return m_operatorSyntaxType == OperatorSyntaxType::StartGroup;
    }
    bool isEndGroupOperator() const
    {
        return m_operatorSyntaxType == OperatorSyntaxType::EndGroup;
    }
    bool isPrefixUnaryOperator() const
    {
        return m_operatorSyntaxType == OperatorSyntaxType::PrefixUnary;
    }
    bool isBinaryOperator() const
    {
        return m_operatorSyntaxType == OperatorSyntaxType::Binary;
    }
    ValueTemplateType getValue() const
    {
        return m_value;
    }
    ValueTemplateType& getReferenceOfValue()
    {
        return m_value;
    }
    OperatorTemplateType getOperator() const
    {
        return m_operator;
    }
    unsigned int getOperatorPriority() const
    {
        return m_operatorPriority;
    }
private:
    TermType m_termType;
    ValueTemplateType m_value;
    OperatorTemplateType m_operator;
    OperatorSyntaxType m_operatorSyntaxType;
    unsigned int m_operatorPriority;
};

template <typename ValueTemplateType, typename OperatorTemplateType>
class ExpressionInfixEvaluator
{
public:
    using Term = ExpressionEvaluatorTerm<ValueTemplateType, OperatorTemplateType>;
    using Terms = std::vector<Term>;
    using ValueStack = std::stack<ValueTemplateType>;
    using OperatorStack = std::stack<Term>;
    void addTerm(Term const& term)
    {
        m_terms.emplace_back(term);
    }
    ValueTemplateType evaluate()
    {
        ValueTemplateType result;
        ValueStack valueStack;
        OperatorStack operatorStack;
        traverseAllTermsForEvaluation(valueStack, operatorStack);
        while(!operatorStack.empty())
        {
            performOperationWithStacks(valueStack, operatorStack);
        }
        if(valueStack.size()==1)
        {
            result = valueStack.top();
        }
        return result;
    }
    Terms getTerms() const
    {
        return m_terms;
    }
    Terms& getTermsReference()
    {
        return m_terms;
    }
private:
    void traverseAllTermsForEvaluation(ValueStack & valueStack, OperatorStack & operatorStack)
    {
        for(Term const& term : m_terms)
        {
            if(term.isOperator())
            {
                if(term.isStartGroupOperator())
                {
                    continue;
                }
                else if(term.isEndGroupOperator())
                {
                    performOperationWithStacks(valueStack, operatorStack);
                }
                else
                {
                    while(!operatorStack.empty() && term.getOperatorPriority()<operatorStack.top().getOperatorPriority())
                    {
                        performOperationWithStacks(valueStack, operatorStack);
                    }
                    operatorStack.push(term);
                }
            }
            else if(term.isValue())
            {
                valueStack.push(term.getValue());
            }
        }
    }
    void performOperationWithStacks(ValueStack & valueStack, OperatorStack & operatorStack)
    {
        if(!operatorStack.empty())
        {
            Term& operatorTerm(operatorStack.top());
            operatorStack.pop();
            if(operatorTerm.isPrefixUnaryOperator() && !valueStack.empty())
            {
                ValueTemplateType const& value(valueStack.top());
                valueStack.pop();
                valueStack.push(performUnaryOperation(operatorTerm.getOperator(), value));
            }
            else if(operatorTerm.isBinaryOperator() && valueStack.size()>=2)
            {
                ValueTemplateType const& value1(valueStack.top());
                valueStack.pop();
                ValueTemplateType const& value2(valueStack.top());
                valueStack.pop();
                valueStack.push(performBinaryOperation(value1, operatorTerm.getOperator(), value2));
            }
        }
    }
    Terms m_terms;
    friend class ExpressionEvaluatorConverter<ValueTemplateType, OperatorTemplateType>;
};

template <typename ValueTemplateType, typename OperatorTemplateType>
class ExpressionPostfixEvaluator // prefix is reverse postfix, so no prefix needed
{
public:
    using Term = ExpressionEvaluatorTerm<ValueTemplateType, OperatorTemplateType>;
    using Terms = std::vector<Term>;
    using ValueStack = std::stack<ValueTemplateType>;
    void addTerm(Term const& term)
    {
        m_terms.emplace_back(term);
    }
    ValueTemplateType evaluate()
    {
        ValueTemplateType result;
        ValueStack valueStack;
        traverseAllTermsForEvaluation(valueStack);
        if(valueStack.size()==1)
        {
            result = valueStack.top();
        }
        return result;
    }
    Terms getTerms() const
    {
        return m_terms;
    }
    Terms& getTermsReference()
    {
        return m_terms;
    }
    bool isEvaluationPossible() const
    {
        int resultStackSize(0);
        for (Term const& term : m_terms)
        {
            if(term.isValue())
            {
                resultStackSize++;
            }
            else if(term.isPrefixUnaryOperator())
            {
                if(resultStackSize<=0)
                {
                    return false;
                }
            }
            else if(term.isBinaryOperator())
            {
                resultStackSize--;
                if(resultStackSize<=0)
                {
                    return false;
                }
            }
        }
        if(resultStackSize!=1)
        {
            return false;
        }
        return true;
    }
private:
    void traverseAllTermsForEvaluation(ValueStack & valueStack)
    {
        for(Term const& term : m_terms)
        {
            if(term.isOperator())
            {
                performOperationWithValueStack(valueStack, term);
            }
            else if(term.isValue())
            {
                valueStack.push(term.getValue());
            }
        }
    }
    void performOperationWithValueStack(ValueStack & valueStack, Term const& operatorTerm)
    {
        if(operatorTerm.isPrefixUnaryOperator() && !valueStack.empty())
        {
            ValueTemplateType value(valueStack.top());
            valueStack.pop();
            valueStack.push(performUnaryOperation(operatorTerm.getOperator(), value));
        }
        else if(operatorTerm.isBinaryOperator() && valueStack.size()>=2)
        {
            ValueTemplateType value1(valueStack.top());
            valueStack.pop();
            ValueTemplateType value2(valueStack.top());
            valueStack.pop();
            valueStack.push(performBinaryOperation(value1, operatorTerm.getOperator(), value2));
        }
    }
    Terms m_terms;
    friend class ExpressionEvaluatorConverter<ValueTemplateType, OperatorTemplateType>;
};

template <typename ValueTemplateType, typename OperatorTemplateType>
class ExpressionEvaluatorConverter
{
public:
    using PostfixEvaluator = ExpressionPostfixEvaluator<ValueTemplateType, OperatorTemplateType>;
    using InfixEvaluator = ExpressionInfixEvaluator<ValueTemplateType, OperatorTemplateType>;
    using Term = ExpressionEvaluatorTerm<ValueTemplateType, OperatorTemplateType>;
    using Terms = std::vector<Term>;
    using TermsStack = std::stack<Term>;

    static PostfixEvaluator convertInfixToPostfix(InfixEvaluator const& infixEvaluator)
    {
        PostfixEvaluator postfixEvaluator;
        Terms const& termsInInfix(infixEvaluator.m_terms);
        Terms & termsInPostfix(postfixEvaluator.m_terms);
        TermsStack operatorStack;
        for(Term const& term : termsInInfix)
        {
            if (term.isStartGroupOperator())
            {
                operatorStack.push(term);
            }
            else if (term.isEndGroupOperator())
            {
                transferTermsStackToTerms(operatorStack, termsInPostfix, [term](TermsStack& termsStack)
                {
                    return !termsStack.top().isStartGroupOperator();
                });
                if(!operatorStack.empty()) operatorStack.pop();
            }
            else if (term.isOperator())
            {
                transferTermsStackToTerms(operatorStack, termsInPostfix, [term](TermsStack& termsStack)
                {
                    return term.getOperatorPriority() <= termsStack.top().getOperatorPriority() && !termsStack.top().isStartGroupOperator();
                });
                operatorStack.push(term);
            }
            else
            {
                termsInPostfix.push_back(term);
            }
        }
        transferTermsStackToTerms(operatorStack, termsInPostfix, [](TermsStack&)
        {
            return true;
        });
        return postfixEvaluator;
    }
    //convertPostfixToInfix
private:
    static void transferTermsStackToTerms(
            TermsStack& termsStack,
            Terms& terms,
            std::function<bool(TermsStack&)> loopCondition)
    {
        while (!termsStack.empty() && loopCondition(termsStack))
        {
            terms.push_back(termsStack.top());
            termsStack.pop();
        }
    }
};

}

}
