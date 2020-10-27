#pragma once

#include "../Builder/TermBuilder.hpp"
#include "../Findings/Findings.hpp"
#include "../Term/Term.hpp"

#include <File/AlbaFileReader.hpp>

#include <fstream>
#include <string>
#include <vector>

using alba::AlbaFileReader;
using std::ifstream;
using std::string;
using std::vector;

namespace codeReview
{

class TermTranslator
{
public:
    explicit TermTranslator(string const& fileName, Findings& findings, DequeOfTerms& dequeOfTerms);
    bool isFileValid();
    void readFile();
private:
    bool getCPlusPlusTerm(string& lineString, int & index);
    bool hasSingleLineComment(string & lineString, int& index);
    bool hasMultiLineComment(string & lineString, int& index);
    bool hasMacro(string & lineString, int& index);
    bool hasStringConstant(string & lineString, int& index);
    bool hasCharacterConstant(string & lineString, int& index);
    bool hasOperator(string & operatorString, int& index);
    bool hasWord(string & lineString, int& index);
    bool hasWhiteSpace(string & lineString, int& index);

    string getLine();
    bool isEqualToFirstTwoCharacters(string const& lineString, int& index, string const& stringToCheck);
    string fetchOperator(string const& lineString, int& index);
    bool isKeyword(string const& word);
    bool isCPlusPlusIgnorableIdentifier(string const& word);
    bool isPrimitiveType(string const& word);
    string readAndAccumulateUntilStringIfFound(string& lineString, int& index, string const& stringToFind);

    static constexpr char QUOTATION_STRING[] = "\"";
    static constexpr char APOSTROPHE_STRING[] = "\'";
    static constexpr char QUOTATION_CHAR = '\"';
    static constexpr char APOSTROPHE_CHAR = '\'';
    static constexpr char SHARP_CHAR = '#';
    ifstream m_fileStream;
    AlbaFileReader m_albaFileReader;
    bool m_isFileValid;
    unsigned int m_lineNumber;
    Findings& m_findings;
    TermBuilder m_termBuilder;
    vector<string> m_stringOfOperators;
    vector<string> m_stringOfKeywords;
    vector<string> m_stringOfPrimitiveTypes;
    vector<string> m_stringOfIgnorableIdentifiers;
};

}// namespace codeReview
