#include "AlbaGrepStringEvaluator.hpp"

#include <String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

AlbaGrepStringEvaluator::AlbaGrepStringEvaluator(string const& condition)
    : m_isEvaluatorInvalid(false)
    , m_errorMessage()
{
    extractTokens(condition);
    generateExpressionEvaluatorPostfix();

    if(!isEvaluationPossible())
    {
        setErrorMessage("Evaluation is not possible (Logic error).");
    }
}

bool AlbaGrepStringEvaluator::evaluate(string const& stringToEvaluate)
{
    bool result(false);
    if(!isInvalid())
    {
        AlbaGrepStringEvaluatorTerm::setMainString(stringToEvaluate);
        result = m_postfixEvaluator.evaluate().getResult();
    }
    return result;
}

bool AlbaGrepStringEvaluator::isInvalid() const
{
    return m_isEvaluatorInvalid;
}

string AlbaGrepStringEvaluator::getErrorMessage() const
{
    return m_errorMessage;
}

void AlbaGrepStringEvaluator::extractTokens(string const& condition)
{
    m_tokens.emplace_back();
    bool isOnString(false);
    int parenthesisCount(0);
    string stringToBuild;
    for(char const currentCharacter:condition)
    {
        if(isOnString)
        {
            extractTokensWhileOnString(isOnString, stringToBuild, currentCharacter);
        }
        else
        {
            extractTokensWhileNotOnString(isOnString, currentCharacter, parenthesisCount);
        }
        if(m_isEvaluatorInvalid){return;}
    }

    m_tokens.erase(remove_if(m_tokens.begin(), m_tokens.end(), [](AlbaGrepStringToken const& token){return token.isToBeIgnored();}), m_tokens.end());

    if(m_tokens.size() == 0)
    {
        setErrorMessage("There are no contents");
    }
    else if(isOnString)
    {
        setErrorMessage("Incomplete '[' ']' found");
    }
    else if(parenthesisCount != 0)
    {
        setErrorMessage("Incomplete '(' ')' found");
    }
}

void AlbaGrepStringEvaluator::extractTokensWhileOnString(bool& isOnString, string & stringToBuild, char const& currentCharacter)
{
    if(']' == currentCharacter)
    {
        m_tokens.emplace_back(stringToBuild);
        stringToBuild.clear();
        isOnString = false;
    }
    else
    {
        stringToBuild += ::toupper(currentCharacter);
    }
}

void AlbaGrepStringEvaluator::extractTokensWhileNotOnString(bool& isOnString, char const& currentCharacter, int& parenthesisCount)
{
    if('[' == currentCharacter)
    {
        isOnString = true;
    }
    else if(isOperator(currentCharacter))
    {
        addOperator(currentCharacter);
    }
    else if(isParenthesis(currentCharacter))
    {
        addParenthesis(currentCharacter, parenthesisCount);
    }
}

void AlbaGrepStringEvaluator::generateExpressionEvaluatorPostfix()
{
    InfixEvaluator infixEvaluator;

    for (AlbaGrepStringToken const& token : m_tokens)
    {
        if(token.isOperator())
        {
            if(token.isPrefixOperation())
            {
                infixEvaluator.addTerm(InfixEvaluator::Term(token.getOperatorType(), EvaluatorTerm::OperatorSyntaxType::PrefixUnary, token.getOperatorPriority()));
            }
            else if(token.isBiDirectionalOperation())
            {
                infixEvaluator.addTerm(InfixEvaluator::Term(token.getOperatorType(), EvaluatorTerm::OperatorSyntaxType::Binary, token.getOperatorPriority()));
            }
            else if(token.isOpeningParenthesis())
            {
                infixEvaluator.addTerm(InfixEvaluator::Term(token.getOperatorType(), EvaluatorTerm::OperatorSyntaxType::StartGroup, token.getOperatorPriority()));
            }
            else if(token.isClosingParenthesis())
            {
                infixEvaluator.addTerm(InfixEvaluator::Term(token.getOperatorType(), EvaluatorTerm::OperatorSyntaxType::EndGroup, token.getOperatorPriority()));
            }
        }
        else if(token.isString())
        {
            infixEvaluator.addTerm(InfixEvaluator::Term(AlbaGrepStringEvaluatorTerm(token.getStringToFind())));
        }
    }
    m_postfixEvaluator = EvaluatorConverter::convertInfixToPostfix(infixEvaluator);
}

bool AlbaGrepStringEvaluator::isEvaluationPossible() const
{
    return m_postfixEvaluator.isEvaluationPossible();
}

void AlbaGrepStringEvaluator::addOperator(char const characterOperator)
{
    bool invalidOperator(false);
    AlbaGrepStringToken & previousToken(m_tokens.back());
    char const currentCharacter = convertTildeToExclamationPointIfNeeded(characterOperator);

    switch(previousToken.getOperatorType())
    {
    case AlbaGrepStringOperatorType::AndOperator:
        switch(currentCharacter)
        {
        case '&': previousToken.appendToString(currentCharacter); break;
        case '!': m_tokens.emplace_back(AlbaGrepStringOperatorType::NotOperator, string("")+currentCharacter); break;
        default: invalidOperator = true; break;
        }
        break;
    case AlbaGrepStringOperatorType::NotOperator:
        switch(currentCharacter)
        {
        case '^':
            previousToken.appendToString(currentCharacter);
            previousToken.setOperatorType(AlbaGrepStringOperatorType::XnorOperator);
            break;
        case '!': previousToken.setOperatorType(AlbaGrepStringOperatorType::IgnoreOperator); break;        default: invalidOperator = true; break;
        }
        break;
    case AlbaGrepStringOperatorType::OrOperator:
        switch(currentCharacter)
        {
        case '|': previousToken.appendToString(currentCharacter); break;
        case '!': m_tokens.emplace_back(AlbaGrepStringOperatorType::NotOperator, string("")+currentCharacter); break;
        default: invalidOperator = true; break;
        }
        break;
    case AlbaGrepStringOperatorType::XorOperator:
        switch(currentCharacter)
        {
        case '!':
            previousToken.appendToString(currentCharacter);
            previousToken.setOperatorType(AlbaGrepStringOperatorType::XnorOperator);
            break;
        default: invalidOperator = true; break;        }
        break;
    case AlbaGrepStringOperatorType::XnorOperator:
        switch(currentCharacter)
        {
        case '!': m_tokens.emplace_back(AlbaGrepStringOperatorType::NotOperator, string("")+currentCharacter); break;
        default: invalidOperator = true; break;
        }
        break;
    default:
        switch(currentCharacter)
        {
        case '!': m_tokens.emplace_back(AlbaGrepStringOperatorType::NotOperator, string("")+currentCharacter); break;
        case '&': m_tokens.emplace_back(AlbaGrepStringOperatorType::AndOperator, string("")+currentCharacter); break;
        case '|': m_tokens.emplace_back(AlbaGrepStringOperatorType::OrOperator, string("")+currentCharacter); break;
        case '^': m_tokens.emplace_back(AlbaGrepStringOperatorType::XorOperator, string("")+currentCharacter); break;
        default: break;
        }
        break;    }
    if(invalidOperator)
    {
        previousToken.appendToString(currentCharacter);
        setErrorMessage("Invalid operator : [" + previousToken.getStringToFind() + "]");
    }
}
void AlbaGrepStringEvaluator::addParenthesis(char const currentCharacter, int& parenthesisCount)
{
    switch(currentCharacter)    {
    case '(':
        m_tokens.emplace_back(AlbaGrepStringOperatorType::OpeningParenthesis);
        parenthesisCount++;
        break;
    case ')':
        m_tokens.emplace_back(AlbaGrepStringOperatorType::ClosingParenthesis);
        parenthesisCount--;
        break;
    default:
        break;
    }
}

char AlbaGrepStringEvaluator::convertTildeToExclamationPointIfNeeded(char const character)
{
    return ('~' == character) ? '!' : character;
}

bool AlbaGrepStringEvaluator::isOperator(char const character) const
{
    return '!' == character || '~' == character || '&' == character || '|' == character || '^' == character;}

bool AlbaGrepStringEvaluator::isParenthesis(char const character) const
{
    return '(' == character || ')' == character;}

void AlbaGrepStringEvaluator::setErrorMessage(string const& errorMessage)
{
    m_isEvaluatorInvalid = true;
    m_errorMessage = errorMessage;
}

}
