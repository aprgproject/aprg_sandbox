#pragma once

#include "../Term/Term.hpp"
#include "../Utilities.hpp"

namespace codeReview
{

class TermBuilder
{
public:
    TermBuilder(DequeOfTerms& dequeOfTerms);
    DequeOfTerms& getTermsReference();

    void setLineNumber(unsigned int const lineNumber);
    void addNewLine();
    void addWhiteSpace();
    void addSemiColon();
    void addSingleLineComment(string const& content);
    void addConstantBoolean(string const& content);
    void addConstantNumber(string const& content);
    void addConstantString(string const& content);
    void addConstantCharacter(string const& content);
    void addIdentifier(string const& content);
    void addMultiLineComment(string const& content);
    void addKeyword(string const& content);
    void addCPlusPlusIgnorableIdentifier(string const& content);
    void addPrimitiveType(string const& content);
    void addMacro(string const& content);
    void addOperator(string const& content);
    void addUnknown(string const& content);
    void addIgnorable(string const& content);
    void addTerm(Term const& term);
    Term& getLastTermReference();

private:
    DequeOfTerms& m_terms;
    unsigned int m_lineNumber;
};

}


