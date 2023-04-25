#pragma once

#include <Algorithm/ExpressionEvaluator/ExpressionEvaluator.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluatorPerformOperations.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp>
#include <GrepStringEvaluator/AlbaGrepStringOperatorType.hpp>
#include <GrepStringEvaluator/AlbaGrepStringToken.hpp>

#include <functional>
#include <stack>
#include <string>
#include <vector>

namespace alba {

class AlbaGrepStringEvaluator {
    using VectorOfTokens = std::vector<AlbaGrepStringToken>;
    using InfixEvaluator = algorithm::ExpressionEvaluator::ExpressionInfixEvaluator<
        AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;
    using PostfixEvaluator = algorithm::ExpressionEvaluator::ExpressionPostfixEvaluator<
        AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;
    using EvaluatorTerm = algorithm::ExpressionEvaluator::ExpressionEvaluatorTerm<
        AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;
    using EvaluatorConverter = algorithm::ExpressionEvaluator::ExpressionEvaluatorConverter<
        AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;

public:
    AlbaGrepStringEvaluator(std::string const& condition);
    bool evaluate(std::string const& stringToEvaluate);
    bool isInvalid() const;
    std::string getErrorMessage() const;

private:
    void extractTokens(std::string const& condition);
    void extractTokensWhileOnString(bool& isOnString, std::string& stringToBuild, char const& currentCharacter);
    void extractTokensWhileNotOnString(bool& isOnString, char const& currentCharacter, int& parenthesisCount);
    void generateExpressionEvaluatorPostfix();
    bool isEvaluationPossible() const;
    void addOperator(char const characterOperator);
    void addParenthesis(char const currentCharacter, int& parenthesisCount);
    char convertTildeToExclamationPointIfNeeded(char const character);
    bool isOperator(char const character) const;
    bool isParenthesis(char const character) const;
    void setErrorMessage(std::string const& errorMessage);
    bool m_isEvaluatorInvalid;
    std::string m_errorMessage;
    VectorOfTokens m_tokens;
    PostfixEvaluator m_postfixEvaluator;
};

}  // namespace alba
