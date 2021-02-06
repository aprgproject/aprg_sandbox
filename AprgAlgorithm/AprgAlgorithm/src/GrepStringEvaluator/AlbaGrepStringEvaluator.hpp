#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluatorPerformOperations.hpp> //this needs to be before ExpressionEvaluator
#include <ExpressionEvaluator/ExpressionEvaluator.hpp>
#include <GrepStringEvaluator/AlbaGrepStringOperatorType.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp>
#include <GrepStringEvaluator/AlbaGrepStringToken.hpp>

#include <functional>
#include <stack>
#include <string>
#include <vector>

namespace alba
{

class AlbaGrepStringEvaluator
{
    using VectorOfTokens = std::vector<AlbaGrepStringToken>;
    using InfixEvaluator = ExpressionEvaluator::ExpressionInfixEvaluator<AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;
    using PostfixEvaluator = ExpressionEvaluator::ExpressionPostfixEvaluator<AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;
    using EvaluatorTerm = ExpressionEvaluator::ExpressionEvaluatorTerm<AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;
    using EvaluatorConverter = ExpressionEvaluator::ExpressionEvaluatorConverter<AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;

public:
    AlbaGrepStringEvaluator(std::string const& condition);
    bool evaluate(std::string const& stringToEvaluate);
    bool isInvalid() const;
    std::string getErrorMessage() const;
private:
    void extractTokens(std::string const& condition);
    void extractTokensWhileOnString(bool& isOnString, std::string & stringToBuild, char const& currentCharacter);
    void extractTokensWhileNotOnString(bool& isOnString, char const& currentCharacter, int& parenthesisCount);
    void generateExpressionEvaluatorPostfix();
    bool isEvaluationPossible() const;
    void addOperator(char const currentCharacter);
    void addParenthesis(char const currentCharacter, int& parenthesisCount);
    bool isOperator(char const character) const;
    bool isParenthesis(char const character) const;
    void setErrorMessage(std::string const& errorMessage);
    bool m_isEvaluatorInvalid;
    std::string m_errorMessage;
    VectorOfTokens m_tokens;
    PostfixEvaluator m_postfixEvaluator;
};

}
