#include "DerivativeVariableName.hpp"

#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{
namespace algebra
{

DerivativeVariableName::DerivativeVariableName(
        unsigned int const differentiationLevel,
        string const& baseVariable,
        string const& dependentVariable)
    : m_isValid(true)
    , m_differentiationLevel(differentiationLevel)
    , m_baseVariable(baseVariable)
    , m_dependentVariable(dependentVariable)
{}

DerivativeVariableName::DerivativeVariableName(
        string const& derivativeVariableInLeibnizNotation)
    : m_isValid(false)
    , m_differentiationLevel(0U)
{
    string numerator = getStringBeforeThisString(derivativeVariableInLeibnizNotation, "/");
    string denominator = getStringAfterThisString(derivativeVariableInLeibnizNotation, "/");
    processNumerator(numerator);
    if(isValid())
    {
        processDenominator(denominator);
    }
}

bool DerivativeVariableName::isValid() const
{
    return m_isValid;
}

unsigned int DerivativeVariableName::getDifferentiationLevel() const
{
    return m_differentiationLevel;
}

string const& DerivativeVariableName::getBaseVariable() const
{
    return m_baseVariable;
}

string const& DerivativeVariableName::getDependentVariable() const
{
    return m_dependentVariable;
}

string DerivativeVariableName::getNameInLeibnizNotation() const
{
    stringstream ss;
    if(m_differentiationLevel == 1)
    {
        ss << "d[" << m_dependentVariable << "]";
        if(!m_baseVariable.empty())
        {
            ss <<"/d[" << m_baseVariable << "]";
        }
    }
    else
    {
        ss << "d" << m_differentiationLevel << "[" << m_dependentVariable << "]";
        if(!m_baseVariable.empty())
        {
            ss <<"/d[" << m_baseVariable << "]" << m_differentiationLevel;
        }
    }
    return ss.str();
}

void DerivativeVariableName::differentiate()
{
    m_differentiationLevel++;
}

void DerivativeVariableName::processNumerator(
        string const& numerator)
{
    enum class ProcessingState
    {
        Initial,
        AfterD,
        Number,
        VariableWithBrackets,
        LastState,
        Invalid
    };
    ProcessingState state = ProcessingState::Initial;
    string differentiationLevelString;
    string dependentVariable;
    for(char const c : numerator)
    {
        if(ProcessingState::Initial == state)
        {
            if(c=='d')
            {
                state = ProcessingState::AfterD;
            }
            else
            {
                break;
            }
        }
        else if(ProcessingState::AfterD == state)
        {
            if(isNumber(c))
            {
                differentiationLevelString += c;
                state = ProcessingState::Number;
            }
            else if(c=='[')
            {
                differentiationLevelString = "1";
                state = ProcessingState::VariableWithBrackets;
            }
            else
            {
                break;
            }
        }
        else if(ProcessingState::Number == state)
        {
            if(isNumber(c))
            {
                differentiationLevelString += c;
            }
            else if(c=='[')
            {
                state = ProcessingState::VariableWithBrackets;
            }
            else
            {
                break;
            }
        }
        else if(ProcessingState::VariableWithBrackets == state)
        {
            if(c==']')
            {
                state = ProcessingState::LastState;
            }
            else
            {
                dependentVariable += c;
            }
        }
        else if(ProcessingState::LastState == state)
        {
            state = ProcessingState::Invalid;
            break;
        }
    }
    if(ProcessingState::LastState == state)
    {
        m_isValid = true;
        m_dependentVariable = dependentVariable;
        m_differentiationLevel = convertStringToNumber<unsigned int>(differentiationLevelString);
    }
    else
    {
        m_isValid = false;
    }
}

void DerivativeVariableName::processDenominator(
        string const& denominator)
{
    enum class ProcessingState
    {
        Initial,
        AfterD,
        Number,
        VariableWithBrackets,
        VariableOnly,
        LastState,
        Invalid
    };
    ProcessingState state = ProcessingState::Initial;
    string differentiationLevelString;
    string baseVariable;
    for(char const c : denominator)
    {
        if(ProcessingState::Initial == state)
        {
            if(c=='d')
            {
                state = ProcessingState::AfterD;
            }
            else
            {
                break;
            }
        }
        else if(ProcessingState::AfterD == state)
        {
            if(c=='[')
            {
                state = ProcessingState::VariableWithBrackets;
            }
            else
            {
                break;
            }
        }
        else if(ProcessingState::VariableWithBrackets == state)
        {
            if(c==']')
            {
                state = ProcessingState::LastState;
            }
            else
            {
                baseVariable += c;
            }
        }
        else if(ProcessingState::LastState == state)
        {
            if(isNumber(c))
            {
                differentiationLevelString += c;
            }
            else
            {
                break;
            }
        }
    }
    if(ProcessingState::LastState == state)
    {
        if(differentiationLevelString.empty())
        {
            differentiationLevelString = "1";
        }
        unsigned int differentiationLevelInDenominator
                = convertStringToNumber<unsigned int>(differentiationLevelString);
        if(differentiationLevelInDenominator == m_differentiationLevel)
        {
            m_isValid = true;
            m_baseVariable = baseVariable;
        }
        else
        {
            m_isValid = false;
        }
    }
    else
    {
        m_isValid = false;
    }
}

}

}
