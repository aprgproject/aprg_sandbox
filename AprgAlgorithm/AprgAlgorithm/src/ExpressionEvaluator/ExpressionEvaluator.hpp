#pragma once

#include <algorithm>
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
    ExpressionEvaluatorTerm(OperatorSyntaxType const& operatorSyntaxValue)
        : m_termType(TermType::Operator)
        , m_value()
        , m_operator()
        , m_operatorSyntaxType(operatorSyntaxValue)
        , m_operatorPriority(0)
    {}
    ExpressionEvaluatorTerm(OperatorTemplateType const& operatorValue, OperatorSyntaxType const& operatorSyntaxValue)
        : m_termType(TermType::Operator)
        , m_value()        , m_operator(operatorValue)
        , m_operatorSyntaxType(operatorSyntaxValue)
        , m_operatorPriority(0)
    {}    ExpressionEvaluatorTerm(OperatorTemplateType const& operatorValue, OperatorSyntaxType const& operatorSyntaxValue, unsigned int const operatorPriority)
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
    using TermStack = std::stack<Term>;
    using TermsStack = std::stack<Terms>;

    static PostfixEvaluator convertInfixToPostfix(InfixEvaluator const& infixEvaluator)
    {        PostfixEvaluator postfixEvaluator;
        Terms const& termsInInfix(infixEvaluator.m_terms);
        Terms & termsInPostfix(postfixEvaluator.m_terms);
        TermStack operatorStack;
        for(Term const& term : termsInInfix)
        {
            if (term.isStartGroupOperator())            {
                operatorStack.push(term);
            }
            else if (term.isEndGroupOperator())
            {
                transferTermStackToTerms(operatorStack, termsInPostfix, [term](TermStack& termStack)
                {
                    return !termStack.top().isStartGroupOperator();
                });
                if(!operatorStack.empty()) operatorStack.pop();
            }
            else if (term.isOperator())
            {
                transferTermStackToTerms(operatorStack, termsInPostfix, [term](TermStack& termStack)
                {
                    return term.getOperatorPriority() <= termStack.top().getOperatorPriority() && !termStack.top().isStartGroupOperator();
                });
                operatorStack.push(term);
            }            else
            {
                termsInPostfix.push_back(term);
            }
        }
        transferTermStackToTerms(operatorStack, termsInPostfix, [](TermStack&)
        {
            return true;
        });
        return postfixEvaluator;
    }
    static InfixEvaluator convertPostfixToInfix(PostfixEvaluator const& postfixEvaluator)
    {
        InfixEvaluator infixEvaluator;
        Terms const& termsInPostfix(postfixEvaluator.m_terms);
        Terms & termsInInfix(infixEvaluator.m_terms);
        TermsStack expressionsStack;
        for(Term const& term : termsInPostfix)
        {
            if (term.isValue())
            {
                expressionsStack.push({term});
            }
            else if (term.isOperator())
            {
                if(term.isPrefixUnaryOperator())
                {
                    Terms expressionOperand = popTermsStackAndReturnTopValue(expressionsStack);
                    Terms newExpression;
                    newExpression.emplace_back(term);
                    copyTermsAndPutGroupOperatorsIfNeeded(expressionOperand, newExpression);
                    expressionsStack.push(newExpression);
                }
                else if(term.isBinaryOperator())
                {
                    Terms expressionOperand1 = popTermsStackAndReturnTopValue(expressionsStack);
                    Terms expressionOperand2 = popTermsStackAndReturnTopValue(expressionsStack);
                    Terms newExpression;
                    copyTermsAndPutGroupOperatorsIfNeeded(expressionOperand1, newExpression);
                    newExpression.emplace_back(term);
                    copyTermsAndPutGroupOperatorsIfNeeded(expressionOperand2, newExpression);
                    expressionsStack.push(newExpression);
                }
            }
        }
        if(!expressionsStack.empty())
        {
            Terms finalExpression=expressionsStack.top();
            std::copy(finalExpression.cbegin(), finalExpression.cend(), std::back_inserter(termsInInfix));
        }
        return infixEvaluator;
    }
private:
    static void transferTermStackToTerms(
            TermStack& termStack,
            Terms& terms,
            std::function<bool(TermStack&)> loopCondition)
    {
        while (!termStack.empty() && loopCondition(termStack))
        {
            terms.push_back(termStack.top());
            termStack.pop();
        }
    }
    static Terms popTermsStackAndReturnTopValue(TermsStack& termsStack)
    {
        Terms terms;
        if(!termsStack.empty())
        {
            terms = termsStack.top();
            termsStack.pop();
        }
        return terms;
    }
    static void copyTermsAndPutGroupOperatorsIfNeeded(
            Terms const& inputTerms,
            Terms & outputTerms)
    {
        bool areGroupOperatorsNeeded = inputTerms.size() > 1;
        if(areGroupOperatorsNeeded)
        {
            outputTerms.emplace_back(Term::OperatorSyntaxType::StartGroup);
        }
        std::copy(inputTerms.cbegin(), inputTerms.cend(), std::back_inserter(outputTerms));
        if(areGroupOperatorsNeeded)
        {
            outputTerms.emplace_back(Term::OperatorSyntaxType::EndGroup);
        }
    }
};

}
}