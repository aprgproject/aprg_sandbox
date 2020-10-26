#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp>

#include <functional>
#include <stack>
#include <string>
#include <vector>

namespace alba
{

class AlbaGrepStringEvaluator
{
    typedef std::stack <AlbaGrepStringEvaluatorTerm> StackOfTerms;
    typedef std::vector <AlbaGrepStringEvaluatorTerm> VectorOfTerms;
public:
    AlbaGrepStringEvaluator(std::string const& condition);
    bool evaluate(std::string const& stringToEvaluate) const;
    bool isInvalid() const;
    std::string getErrorMessage() const;
private:
    void extractTerms(std::string const& condition);
    void extractTermsWhileOnString(bool& isOnString, std::string & stringToBuild, char const& currentCharacter);
    void extractTermsWhileNotOnString(bool& isOnString, char const& currentCharacter, int& parenthesisCount);
    void convertToPostFix();
    bool isEvaluationPossible() const;
    void transferStackContentsToVector(
            StackOfTerms& stackOfTerms,
            VectorOfTerms& vectorOfTerms,
            std::function<bool(StackOfTerms&)> loopCondition);
    void addOperator(char const currentCharacter);
    void addParenthesis(char const currentCharacter, int& parenthesisCount);
    bool isOperator(char const character) const;
    bool isParenthesis(char const character) const;
    bool performBiDirectionalOperation(AlbaGrepStringEvaluatorTermType const termType, bool const inputValue1, bool const inputValue2) const;
    bool performPrefixOperation(AlbaGrepStringEvaluatorTermType const termType, bool const inputValue) const;
    void setErrorMessage(std::string const& errorMessage);
    bool m_isEvaluatorInvalid;
    std::string m_errorMessage;
    VectorOfTerms m_terms;
};

}


