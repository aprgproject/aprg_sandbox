#include "../Utilities.hpp"
#include "TermBuilder.hpp"

#include <iostream>

using namespace std;

namespace codeReview
{

TermBuilder::TermBuilder(DequeOfTerms& dequeOfTerms)
    : m_terms(dequeOfTerms)
    , m_lineNumber(0)
{}

DequeOfTerms& TermBuilder::getTermsReference()
{
    return m_terms;
}

void TermBuilder::setLineNumber(unsigned int const lineNumber)
{
    m_lineNumber = lineNumber;
}

void TermBuilder::addNewLine()
{
    m_terms.emplace_back(TermType::NewLine, "\n", m_lineNumber);
}

void TermBuilder::addWhiteSpace()
{
    m_terms.emplace_back(TermType::WhiteSpace, " ", m_lineNumber);
}

void TermBuilder::addSemiColon()
{
    m_terms.emplace_back(TermType::Operator, ";", m_lineNumber);
}

void TermBuilder::addSingleLineComment(string const& content)
{
    m_terms.emplace_back(TermType::SingleLine_Comment, content, m_lineNumber);
}

void TermBuilder::addConstantBoolean(string const& content)
{
     m_terms.emplace_back(TermType::Constant_Boolean, content, m_lineNumber);
     m_terms.back().setValueType(CPlusPlusType("bool", CPlusPlusTypeType::Primitive));
}

void TermBuilder::addConstantNumber(string const& content)
{
     m_terms.emplace_back(TermType::Constant_Number, content, m_lineNumber);
     m_terms.back().setValueType(CPlusPlusType("ConstantNumber", CPlusPlusTypeType::ConstantNumber));
}

void TermBuilder::addConstantString(string const& content)
{
     m_terms.emplace_back(TermType::Constant_String, content, m_lineNumber);
     m_terms.back().setValueType(CPlusPlusType("string", CPlusPlusTypeType::Primitive));
}

void TermBuilder::addConstantCharacter(string const& content)
{
     m_terms.emplace_back(TermType::Constant_Character, content, m_lineNumber);
     m_terms.back().setValueType(CPlusPlusType("char", CPlusPlusTypeType::Primitive));
}

void TermBuilder::addIdentifier(string const& content)
{
    m_terms.emplace_back(TermType::Identifier, content, m_lineNumber);
}

void TermBuilder::addMultiLineComment(string const& content)
{
    m_terms.emplace_back(TermType::MultiLine_Comment, content, m_lineNumber);
}

void TermBuilder::addKeyword(string const& content)
{
    m_terms.emplace_back(TermType::Keyword, content, m_lineNumber);
}

void TermBuilder::addCPlusPlusIgnorableIdentifier(string const& content)
{
    m_terms.emplace_back(TermType::CPlusPlusIgnorableIdentifier, content, m_lineNumber);
}

void TermBuilder::addPrimitiveType(string const& content)
{
    m_terms.emplace_back(TermType::Type, content, m_lineNumber);
    m_terms.back().setValueType(CPlusPlusType(content, CPlusPlusTypeType::Primitive));
}

void TermBuilder::addMacro(string const& content)
{
    m_terms.emplace_back(TermType::Macro, content, m_lineNumber);
}

void TermBuilder::addOperator(string const& content)
{
    m_terms.emplace_back(TermType::Operator, content, m_lineNumber);
}

void TermBuilder::addUnknown(string const& content)
{
    m_terms.emplace_back(TermType::Unknown, content, m_lineNumber);
}

void TermBuilder::addIgnorable(string const& content)
{
    m_terms.emplace_back(TermType::ProcessedTerm, content, m_lineNumber);
}

void TermBuilder::addTerm(Term const& term)
{
    m_terms.emplace_back(term);
}

Term& TermBuilder::getLastTermReference()
{
    return m_terms.back();
}

}


