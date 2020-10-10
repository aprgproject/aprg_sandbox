#pragma once

#include <functional>
#include <GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp>
#include <string>
#include <stack>
#include <vector>

using std::function;
using std::string;
using std::stack;
using std::vector;

namespace alba
{

class AlbaGrepStringEvaluator
{
    typedef stack <AlbaGrepStringEvaluatorTerm> StackOfTerms;
    typedef vector <AlbaGrepStringEvaluatorTerm> VectorOfTerms;
public:
    AlbaGrepStringEvaluator(string const& condition);
    bool evaluate(string const& stringToEvaluate) const;
    bool isInvalid() const;
    string getErrorMessage() const;
private:
    void extractTerms(string const& condition);
    void extractTermsWhileOnString(bool& isOnString, string& stringToBuild, char const& currentCharacter);
    void extractTermsWhileNotOnString(bool& isOnString, char const& currentCharacter, int& parenthesisCount);
    void convertToPostFix();
    bool isEvaluationPossible() const;
    void transferStackContentsToVector(
            StackOfTerms& stackOfTerms,
            VectorOfTerms& vectorOfTerms,
            function<bool(StackOfTerms&)> loopCondition);
    void addOperator(char const currentCharacter);
    void addParenthesis(char const currentCharacter, int& parenthesisCount);
    bool isOperator(char const character) const;
    bool isParenthesis(char const character) const;
    bool performBiDirectionalOperation(AlbaGrepStringEvaluatorTermType const termType, bool const inputValue1, bool const inputValue2) const;
    bool performPrefixOperation(AlbaGrepStringEvaluatorTermType const termType, bool const inputValue) const;
    void setErrorMessage(string const& errorMessage);
    bool m_isEvaluatorInvalid;
    string m_errorMessage;
    VectorOfTerms m_terms;
};

}
