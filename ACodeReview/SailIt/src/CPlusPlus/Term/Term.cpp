#include "Term.hpp"

#include <String/AlbaStringHelper.hpp>
#include <iostream>
#include <utility>
#include <string>
using namespace std;
using namespace alba::stringHelper;
namespace codeReview
{

Term::Term(TermType termType, unsigned int const lineNumber)
    : m_hasContentString(false)
    , m_termType(termType)
    , m_content()
    , m_lineNumber(lineNumber)
{}

Term::Term(TermType termType, string const& content, unsigned int const lineNumber)
    : m_hasContentString(true)
    , m_termType(termType)
    , m_content(content)
    , m_lineNumber(lineNumber)
{}

ostream& operator<<(ostream & out, Term const& term)
{
    out << "Line:" << term.m_lineNumber << " " <<
           term.getTermTypeString() <<
           " content:[" << term.getPrintableString() << "]";
    if(term.hasValueType())
    {
        out << " valueType:[" << term.getValueType() << "]";
    }
    return out;
}

bool Term::operator==(Term const& termToCompare) const
{
    if(m_termType == termToCompare.getTermType())
    {
        if(hasNoContentString() || termToCompare.hasNoContentString())
        {
            return true;
        }
        return getString()==termToCompare.getString();
    }
    return false;
}

bool Term::operator==(string const& content) const
{
    return getString()==content;
}

bool operator==(string const& content, Term const& term)
{
    return term.getString()==content;
}

bool Term::operator!=(Term const& termToCompare) const
{
    return !(*this == termToCompare);
}

bool Term::operator!=(string const& content) const
{
    return getString()!=content;
}

bool operator!=(string const& content, Term const& term)
{
    return term.getString()!=content;
}

string Term::getString() const
{
    return m_content;
}

bool Term::hasValueType() const
{
    return m_ValueTypeOptional;
}

CPlusPlusType Term::getValueType() const
{
    if(m_ValueTypeOptional)
    {
        return m_ValueTypeOptional.getReference();
    }
    return CPlusPlusType();
}

CPlusPlusType& Term::getValueTypeReference() const
{
    return m_ValueTypeOptional.getReference();
}

string Term::getPrintableString() const
{
    string replacedString(m_content);
    while(transformReplaceStringIfFound(replacedString, "\n", "(\\n)"));
    return replacedString;
}

string Term::getTermTypeString() const
{

#define GET_ENUM_STRING(en) \
    case en: \
    return #en;

    switch(m_termType)
    {
    GET_ENUM_STRING(TermType::Class)
            GET_ENUM_STRING(TermType::Comment)
            GET_ENUM_STRING(TermType::Constant_Boolean)
            GET_ENUM_STRING(TermType::Constant_Character)
            GET_ENUM_STRING(TermType::Constant_Number)
            GET_ENUM_STRING(TermType::Constant_String)
            GET_ENUM_STRING(TermType::CPlusPlusIgnorableIdentifier)
            GET_ENUM_STRING(TermType::Empty)
            GET_ENUM_STRING(TermType::FunctionName)
            GET_ENUM_STRING(TermType::Identifier)
            GET_ENUM_STRING(TermType::Keyword)
            GET_ENUM_STRING(TermType::Macro)
            GET_ENUM_STRING(TermType::MultiLine_Comment)
            GET_ENUM_STRING(TermType::MultiLine_ElseClause)
            GET_ENUM_STRING(TermType::MultiLine_ElseIfClause)
            GET_ENUM_STRING(TermType::MultiLine_IfElseIfStartChain_Ignorable)
            GET_ENUM_STRING(TermType::Namespace)
            GET_ENUM_STRING(TermType::NewLine)
            GET_ENUM_STRING(TermType::Operator)
            GET_ENUM_STRING(TermType::ProcessedTerm)
            GET_ENUM_STRING(TermType::SingleLine_Comment)
            GET_ENUM_STRING(TermType::Type)
            GET_ENUM_STRING(TermType::Unknown)
            GET_ENUM_STRING(TermType::Value_LValue)
            GET_ENUM_STRING(TermType::Value_RValue)
            GET_ENUM_STRING(TermType::Value_RValue_CanBeALine)
            GET_ENUM_STRING(TermType::Variable)
            GET_ENUM_STRING(TermType::VariableDeclaration)
            GET_ENUM_STRING(TermType::WhiteSpace)
    }
    return string("");
}

TermType Term::getTermType() const
{
    return m_termType;
}

unsigned int Term::getLineNumber() const
{
    return m_lineNumber;
}

void Term::clearValueType()
{
    return m_ValueTypeOptional.clear();
}

void Term::setString(string const & string1)
{
    m_content = string1;
}

void Term::setValueType(CPlusPlusType const& cPlusPlusType)
{
    m_ValueTypeOptional.setValue(cPlusPlusType);
}

void Term::setTermType(TermType termType)
{
    m_termType = termType;
}

void Term::setLineNumber(unsigned int lineNumber)
{
    m_lineNumber = lineNumber;
}

bool Term::hasNoContentString() const
{
    return !m_hasContentString;
}

}
