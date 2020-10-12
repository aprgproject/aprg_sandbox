#include "AlbaGrepStringEvaluator.hpp"

#include <AlbaStringHelper.hpp>
#include <algorithm>

using namespace std;
using alba::stringHelper::isStringFoundInsideTheOtherStringCaseSensitive;

namespace alba
{

AlbaGrepStringEvaluator::AlbaGrepStringEvaluator(string const& condition)
    : m_isEvaluatorInvalid(false)
    , m_errorMessage()
{
    extractTerms(condition);
    convertToPostFix();
    if(!isEvaluationPossible())
    {
        setErrorMessage("Evaluation is not possible (Logic error).");
    }
}

bool AlbaGrepStringEvaluator::evaluate(string const& stringToEvaluate) const
{
    if(m_isEvaluatorInvalid){return false;}

    string evaluateStringWithCapitalLetters(alba::stringHelper::getStringWithCapitalLetters(stringToEvaluate));
    stack <bool> resultsStack;

    for (AlbaGrepStringEvaluatorTerm const& term : m_terms)
    {
        if(term.isString())
        {
            resultsStack.push(isStringFoundInsideTheOtherStringCaseSensitive(evaluateStringWithCapitalLetters, term.getString()));
        }
        else if(term.isPrefixOperation())
        {
            bool inputValue = resultsStack.top();
            resultsStack.pop();
            resultsStack.push(performPrefixOperation(term.getTermType(), inputValue));
        }
        else if(term.isBiDirectionalOperation())
        {
            bool inputValue1 = resultsStack.top();
            resultsStack.pop();
            bool inputValue2 = resultsStack.top();
            resultsStack.pop();
            resultsStack.push(performBiDirectionalOperation(term.getTermType(), inputValue1, inputValue2));
        }
    }

    if(!resultsStack.empty())
    {
        return resultsStack.top();
    }
    return false;
}

bool AlbaGrepStringEvaluator::isInvalid() const
{
    return m_isEvaluatorInvalid;
}

string AlbaGrepStringEvaluator::getErrorMessage() const
{
    return m_errorMessage;
}

void AlbaGrepStringEvaluator::extractTerms(string const& condition)
{
    m_terms.emplace_back(AlbaGrepStringEvaluatorTermType::Dummy);
    bool isOnString(false);
    int parenthesisCount(0);
    string stringToBuild;
    for(char const currentCharacter:condition)
    {
        if(isOnString)
        {
            extractTermsWhileOnString(isOnString, stringToBuild, currentCharacter);
        }
        else
        {
            extractTermsWhileNotOnString(isOnString, currentCharacter, parenthesisCount);
        }
        if(m_isEvaluatorInvalid){return;}
    }

    m_terms.erase(remove_if(m_terms.begin(), m_terms.end(), [](AlbaGrepStringEvaluatorTerm const& term){return term.isToBeIgnored();}), m_terms.end());

    if(m_terms.size() == 0)
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

void AlbaGrepStringEvaluator::extractTermsWhileOnString(bool& isOnString, string & stringToBuild, char const& currentCharacter)
{
    if(']' == currentCharacter)
    {
        m_terms.emplace_back(AlbaGrepStringEvaluatorTermType::String, stringToBuild);
        stringToBuild.clear();
        isOnString = false;
    }
    else
    {
        stringToBuild += ::toupper(currentCharacter);
    }
}

void AlbaGrepStringEvaluator::extractTermsWhileNotOnString(bool& isOnString, char const& currentCharacter, int& parenthesisCount)
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

void AlbaGrepStringEvaluator::convertToPostFix()
{
    StackOfTerms operatorStack;
    VectorOfTerms termsInPostFixOrder;

    for (AlbaGrepStringEvaluatorTerm const& term : m_terms)
    {
        if (term.isOperator())
        {
            transferStackContentsToVector(operatorStack, termsInPostFixOrder, [term](StackOfTerms& stackOfTerms)
            {
                return term.getPriorityScore() <= stackOfTerms.top().getPriorityScore();
            });
            operatorStack.push(term);
        }
        else if (term.isOpeningParenthesis())
        {
            operatorStack.push(term);
        }
        else if (term.isClosingParenthesis())
        {
            transferStackContentsToVector(operatorStack, termsInPostFixOrder, [term](StackOfTerms& stackOfTerms)
            {
                return !stackOfTerms.top().isOpeningParenthesis();
            });
            if(!operatorStack.empty()) operatorStack.pop();
        }
        else
        {
            termsInPostFixOrder.push_back(term);
        }
    }
    transferStackContentsToVector(operatorStack, termsInPostFixOrder, [](StackOfTerms&){return true;});

    m_terms.resize(termsInPostFixOrder.size());
    copy(termsInPostFixOrder.begin(), termsInPostFixOrder.end(), m_terms.begin());
}

bool AlbaGrepStringEvaluator::isEvaluationPossible() const
{
    int resultStackSize(0);
    for (AlbaGrepStringEvaluatorTerm const& term : m_terms)
    {
        if(term.isString())
        {
            resultStackSize++;
        }
        else if(term.isPrefixOperation())
        {
            if(resultStackSize<=0)
            {
                return false;
            }
        }
        else if(term.isBiDirectionalOperation())
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

void AlbaGrepStringEvaluator::transferStackContentsToVector(
        StackOfTerms& stackOfTerms,
        VectorOfTerms& vectorOfTerms,
        function<bool(StackOfTerms&)> loopCondition)
{
    while (!stackOfTerms.empty() && loopCondition(stackOfTerms))
    {
        vectorOfTerms.push_back(stackOfTerms.top());
        stackOfTerms.pop();
    }
}

void AlbaGrepStringEvaluator::addOperator(char const currentCharacter)
{
    bool invalidOperator(false);
    AlbaGrepStringEvaluatorTerm & previousTerm(m_terms.back());
    char const characterToCheck = ('~' == currentCharacter) ? '!' : currentCharacter;

    switch(previousTerm.getTermType())
    {
    case AlbaGrepStringEvaluatorTermType::AndOperator:
        switch(characterToCheck)
        {
        case '&': previousTerm.appendToString(characterToCheck); break;
        case '!': m_terms.emplace_back(AlbaGrepStringEvaluatorTermType::NotOperator, string("")+characterToCheck); break;
        default: invalidOperator = true; break;
        }
        break;
    case AlbaGrepStringEvaluatorTermType::NotOperator:
        switch(characterToCheck)
        {
        case '^':
            previousTerm.appendToString(characterToCheck);
            previousTerm.setType(AlbaGrepStringEvaluatorTermType::XnorOperator);
            break;
        case '!': previousTerm.setType(AlbaGrepStringEvaluatorTermType::IgnoreOperator); break;
        default: invalidOperator = true; break;
        }
        break;
    case AlbaGrepStringEvaluatorTermType::OrOperator:
        switch(characterToCheck)
        {
        case '|': previousTerm.appendToString(characterToCheck); break;
        case '!': m_terms.emplace_back(AlbaGrepStringEvaluatorTermType::NotOperator, string("")+characterToCheck); break;
        default: invalidOperator = true; break;
        }
        break;
    case AlbaGrepStringEvaluatorTermType::XorOperator:
        switch(characterToCheck)
        {
        case '!':
            previousTerm.appendToString(characterToCheck);
            previousTerm.setType(AlbaGrepStringEvaluatorTermType::XnorOperator);
            break;
        default: invalidOperator = true; break;
        }
        break;
    case AlbaGrepStringEvaluatorTermType::XnorOperator:
        switch(characterToCheck)
        {
        case '!': m_terms.emplace_back(AlbaGrepStringEvaluatorTermType::NotOperator, string("")+characterToCheck); break;
        default: invalidOperator = true; break;
        }
        break;
    default:
        switch(characterToCheck)
        {
        case '!': m_terms.emplace_back(AlbaGrepStringEvaluatorTermType::NotOperator, string("")+characterToCheck); break;
        case '&': m_terms.emplace_back(AlbaGrepStringEvaluatorTermType::AndOperator, string("")+characterToCheck); break;
        case '|': m_terms.emplace_back(AlbaGrepStringEvaluatorTermType::OrOperator, string("")+characterToCheck); break;
        case '^': m_terms.emplace_back(AlbaGrepStringEvaluatorTermType::XorOperator, string("")+characterToCheck); break;
        default: break;
        }
        break;
    }
    if(invalidOperator)
    {
        previousTerm.appendToString(characterToCheck);
        setErrorMessage("Invalid operator : [" + previousTerm.getString() + "]");
    }
}

void AlbaGrepStringEvaluator::addParenthesis(char const currentCharacter, int& parenthesisCount)
{
    switch(currentCharacter)
    {
    case '(':
        m_terms.emplace_back(AlbaGrepStringEvaluatorTermType::OpeningParenthesis);
        parenthesisCount++;
        break;
    case ')':
        m_terms.emplace_back(AlbaGrepStringEvaluatorTermType::ClosingParenthesis);
        parenthesisCount--;
        break;
    default:
        break;
    }
}

bool AlbaGrepStringEvaluator::isOperator(char const character) const
{
    return '!' == character || '~' == character || '&' == character || '|' == character || '^' == character;
}

bool AlbaGrepStringEvaluator::isParenthesis(char const character) const
{
    return '(' == character || ')' == character;
}

bool AlbaGrepStringEvaluator::performBiDirectionalOperation(
        AlbaGrepStringEvaluatorTermType const termType,
        bool const inputValue1,
        bool const inputValue2) const
{
    bool outputValue(false);
    switch (termType)
    {
    case AlbaGrepStringEvaluatorTermType::AndOperator:
        outputValue = inputValue1 && inputValue2;
        break;
    case AlbaGrepStringEvaluatorTermType::OrOperator:
        outputValue = inputValue1 || inputValue2;
        break;
    case AlbaGrepStringEvaluatorTermType::XorOperator:
        outputValue = (inputValue1 && (!inputValue2)) || ((!inputValue1) && inputValue2);
        break;
    case AlbaGrepStringEvaluatorTermType::XnorOperator:
        outputValue = ((!inputValue1) && (!inputValue2)) || (inputValue1 && inputValue2);
        break;
    default:
        break;
    }
    return outputValue;
}

bool AlbaGrepStringEvaluator::performPrefixOperation(
        AlbaGrepStringEvaluatorTermType const termType,
        bool const inputValue) const
{
    bool outputValue(false);
    switch (termType)
    {
    case AlbaGrepStringEvaluatorTermType::NotOperator:
        outputValue = !inputValue;
        break;
    default:
        break;
    }
    return outputValue;
}

void AlbaGrepStringEvaluator::setErrorMessage(string const& errorMessage)
{
    m_isEvaluatorInvalid = true;
    m_errorMessage = errorMessage;
}

}

