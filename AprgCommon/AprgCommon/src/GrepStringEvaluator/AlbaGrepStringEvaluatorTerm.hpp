#pragma once

#include <string>

using std::string;

namespace alba
{

enum class AlbaGrepStringEvaluatorTermType
{
    AndOperator,
    ClosingParenthesis,
    Dummy,
    IgnoreOperator,
    NotOperator,
    OpeningParenthesis,
    OrOperator,
    XorOperator,
    XnorOperator,
    String
};

class AlbaGrepStringEvaluatorTerm
{
public:
    AlbaGrepStringEvaluatorTerm();
    AlbaGrepStringEvaluatorTerm(AlbaGrepStringEvaluatorTermType type);
    AlbaGrepStringEvaluatorTerm(AlbaGrepStringEvaluatorTermType type, string stringToFind);
    bool isToBeIgnored() const;
    bool isOperator() const;
    bool isClosingParenthesis() const;
    bool isOpeningParenthesis() const;
    bool isString() const;
    bool isBiDirectionalOperation() const;
    bool isPrefixOperation() const;
    AlbaGrepStringEvaluatorTermType getTermType() const;
    string getTermTypeString() const;
    string getString() const;
    int getPriorityScore() const;
    void appendToString(char const character);
    void setType(AlbaGrepStringEvaluatorTermType const type);
private:
    AlbaGrepStringEvaluatorTermType m_type;
    string m_stringToFind;
};

}
