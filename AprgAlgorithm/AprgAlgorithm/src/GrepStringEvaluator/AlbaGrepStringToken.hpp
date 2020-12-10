#pragma once

#include <string>
#include <GrepStringEvaluator/AlbaGrepStringOperatorType.hpp>

namespace alba
{

class AlbaGrepStringToken
{
public:
    enum class TokenType
    {
        Dummy,
        Operator,
        StringToFind,
        Result,
    };
    AlbaGrepStringToken();
    AlbaGrepStringToken(std::string const& stringToFind);
    AlbaGrepStringToken(AlbaGrepStringOperatorType const operatorType);
    AlbaGrepStringToken(AlbaGrepStringOperatorType const operatorType, std::string const& operatorString);
    bool isToBeIgnored() const;
    bool isOperator() const;
    bool isClosingParenthesis() const;
    bool isOpeningParenthesis() const;
    bool isString() const;
    bool isBiDirectionalOperation() const;
    bool isPrefixOperation() const;
    TokenType getTokenType() const;
    AlbaGrepStringOperatorType getOperatorType() const;
    std::string getTokenTypeString() const;
    std::string getStringToFind() const;
    int getOperatorPriority() const;
    void appendToString(char const character);
    void setOperatorType(AlbaGrepStringOperatorType const type);
private:
    TokenType m_type;
    AlbaGrepStringOperatorType m_operatorType;
    std::string m_string;
};

}
