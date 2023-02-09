#pragma once

#include "../Database/CPlusPlusType.hpp"

#include <optional>

#include <ostream>
#include <string>

using std::string;
using std::ostream;
using std::optional;

namespace codeReview
{

enum class TermType
{
    Class,
    Comment,
    Constant_Boolean,
    Constant_Character,
    Constant_Number,
    Constant_String,
    CPlusPlusIgnorableIdentifier,
    Empty,
    FunctionName,
    Identifier,
    Keyword,
    Macro,
    MultiLine_Comment,
    MultiLine_ElseClause,
    MultiLine_ElseIfClause,
    MultiLine_IfElseIfStartChain_Ignorable,
    Namespace,
    NewLine,
    Operator,
    ProcessedTerm,
    SingleLine_Comment,
    Type,
    Unknown,
    Value_LValue,
    Value_RValue,
    Value_RValue_CanBeALine,
    Variable,
    VariableDeclaration,
    WhiteSpace
};

class Term
{
public:
    explicit Term(TermType termType, unsigned int const lineNumber=0);
    explicit Term(TermType termType, string const& content, unsigned int const lineNumber=0);

    friend ostream& operator<<(ostream & out, Term const& term);
    bool operator==(Term const& termToCompare) const;
    bool operator==(string const& content) const;
    friend bool operator==(string const& content, Term const& term);
    bool operator!=(Term const& termToCompare) const;
    bool operator!=(string const& content) const;
    friend bool operator!=(string const& content, Term const& term);

    string getString() const;
    bool hasValueType() const;
    CPlusPlusType getValueType() const;
    CPlusPlusType& getValueTypeReference() const;
    string getPrintableString() const;
    string getTermTypeString() const;
    TermType getTermType() const;
    unsigned int getLineNumber() const;

    void clearValueType();
    void setString(string const & string1);
    void setTermType(TermType termType);
    void setValueType(CPlusPlusType const& cPlusPlusType);
    void setLineNumber(unsigned int lineNumber);

private:
    bool hasNoContentString() const;
    bool m_hasContentString;
    TermType m_termType;
    string m_content;
    string m_valueType;
    unsigned int m_lineNumber;
    std::Optional<CPlusPlusType> m_ValueTypeOptional;

};

}
