#include "TermListConstants.hpp"
#include "TermTranslator.hpp"

#include <AlbaLocalPathHandler.hpp>
#include <File/AlbaFileReader.hpp>
#include <String/AlbaStringHelper.hpp>

#include <algorithm>
#include <iostream>
#include <string>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace codeReview
{

constexpr char TermTranslator::QUOTATION_STRING[];
constexpr char TermTranslator::APOSTROPHE_STRING[];

TermTranslator::TermTranslator(string const& fileName, Findings& findings, DequeOfTerms& dequeOfTerms)
    : m_fileStream(fileName.c_str())
    , m_albaFileReader(m_fileStream)
    , m_isFileValid(false)
    , m_lineNumber(0)
    , m_findings(findings)
    , m_termBuilder(dequeOfTerms)
    , m_stringOfOperators{KEYWORD_OPERATORS, THREE_CHAR_OPERATORS, TWO_CHAR_OPERATORS, ONE_CHAR_OPERATORS}
    , m_stringOfKeywords{CPLUSPLUS_KEYWORDS}
    , m_stringOfPrimitiveTypes{PRIMITIVE_TYPES}
    , m_stringOfIgnorableIdentifiers{CPLUSPLUS_IGNORABLE_IDENTIFIERS}
{
    AlbaLocalPathHandler pathHandler;
    pathHandler.inputPath(fileName);
    if(pathHandler.isFoundInLocalSystem() && pathHandler.isFile())
    {
        if(m_fileStream.is_open())
        {
            m_isFileValid = true;
        }
        else
        {
            cout<<"TermTranslator::constructor| Cannot read cmake file: ["<<pathHandler.getFullPath()<<"]."<<endl;
            cout<<"TermTranslator::constructor| Problem in FileI/O!"<<endl;
        }
    }
    else
    {
        cout<<"TermTranslator::constructor| Cannot read cmake file: ["<<pathHandler.getFullPath()<<"]."<<endl;
        cout<<"TermTranslator::constructor| File does not exist!"<<endl;
    }
}

bool TermTranslator::isFileValid()
{
    return m_isFileValid;
}

void TermTranslator::readFile()
{
    if(m_isFileValid)
    {
        while(m_albaFileReader.isNotFinished())
        {
            string lineString(getLine());
            int index = lineString.find_first_not_of(WHITESPACE_STRING);
            if(isNotNpos(index))
            {
                while(getCPlusPlusTerm(lineString, index));
            }
            m_termBuilder.addNewLine();
        }
    }
}

bool TermTranslator::getCPlusPlusTerm(string& lineString, int & index)
{
    //optimize this think of findfirst and findfirst again
    string operatorString = fetchOperator(lineString, index);
    int length = lineString.length();
    bool continueProcessing = true;
    if(index >= length){continueProcessing = false;}
    else if( hasSingleLineComment(lineString, index) );
    else if( hasMultiLineComment(lineString, index) );
    else if( hasMacro(lineString, index) );
    else if( hasStringConstant(lineString, index) );
    else if( hasCharacterConstant(lineString, index) );
    else if( hasOperator(operatorString, index) );
    else if( hasWord(lineString, index) );
    else if( hasWhiteSpace(lineString, index) );
    else{
        m_termBuilder.addUnknown(lineString.substr(index));
        index = length;
        continueProcessing = false;
    }
    return continueProcessing;
}

bool TermTranslator::hasSingleLineComment(string& lineString, int& index)
{
    if(isEqualToFirstTwoCharacters(lineString, index, "//"))
    {
        m_termBuilder.addSingleLineComment(lineString.substr(index));
        index = lineString.length();
        return true;
    }
    return false;
}

bool TermTranslator::hasMultiLineComment(string& lineString, int& index)
{
    if(isEqualToFirstTwoCharacters(lineString, index, "/*"))
    {
        m_termBuilder.addMultiLineComment(readAndAccumulateUntilStringIfFound(lineString, index, "*/"));
        return true;
    }
    return false;
}

bool TermTranslator::hasMacro(string & lineString, int& index)
{
    int length = lineString.length();
    if(SHARP_CHAR == lineString[index])
    {
        index = lineString.find_first_not_of(WHITESPACE_STRING, index+1);
        if(isNotNpos(index))
        {
            int start = index;
            //stlalgorithm
            for (; index < length; index++)
            {
                if(!isLetter(lineString[index])) break;
            }
            m_termBuilder.addMacro(string("#")+lineString.substr(start, index-start));
            return true;
        }
    }
    return false;
}

bool TermTranslator::hasStringConstant(string & lineString, int& index)
{
    if(QUOTATION_CHAR == lineString[index])
    {
        string stringLiteral(QUOTATION_STRING);
        int slashCharacterIndex;
        int slashCount;
        index++;
        do
        {
            stringLiteral += readAndAccumulateUntilStringIfFound(lineString, index, QUOTATION_STRING);
            slashCharacterIndex = stringLiteral.length()-2;
            slashCount = 0;
            while(slashCharacterIndex>=0 && '\\'==stringLiteral[slashCharacterIndex])
            {
                slashCount++;
                slashCharacterIndex--;
            }
        }
        while(slashCount % 2);
        m_termBuilder.addConstantString(stringLiteral);
        return true;
    }
    return false;
}

bool TermTranslator::hasCharacterConstant(string & lineString, int& index)
{
    if(APOSTROPHE_CHAR == lineString[index])
    {
        string stringLiteral(APOSTROPHE_STRING);
        int slashCharacterIndex;
        int slashCount;
        index++;
        do
        {
            stringLiteral += readAndAccumulateUntilStringIfFound(lineString, index, APOSTROPHE_STRING);
            slashCharacterIndex = stringLiteral.length()-2;
            slashCount = 0;
            while(slashCharacterIndex>=0 && '\\'==stringLiteral[slashCharacterIndex])
            {
                slashCount++;
                slashCharacterIndex--;
            }
        }
        while(slashCount % 2);
        m_termBuilder.addConstantCharacter(stringLiteral);
        return true;
    }
    return false;
}

bool TermTranslator::hasOperator(string& operatorString, int& index)
{
    if(!operatorString.empty())
    {
        index = index + operatorString.length();
        m_termBuilder.addOperator(operatorString);
        return true;
    }
    return false;
}

bool TermTranslator::hasWord(string & lineString, int& index)
{
    int length = lineString.length();
    if(isLetterOrNumberOrUnderscore(lineString[index]))
    {
        int start = index;
        for (; index < length; index++)
        {
            if(!isLetterOrNumberOrUnderscore(lineString[index])) break;
        }

        string word(lineString.substr(start, index-start));
        if(isPrimitiveType(word))
        {
            m_termBuilder.addPrimitiveType(word);
        }
        else if(word == "true" || word == "false")
        {
            m_termBuilder.addConstantBoolean(word);
        }
        else if(isKeyword(word))
        {
            m_termBuilder.addKeyword(word);
        }
        else if(isNumber(word[0]))
        {
            m_termBuilder.addConstantNumber(word);
        }
        else if(isCPlusPlusIgnorableIdentifier(word))
        {
            m_termBuilder.addCPlusPlusIgnorableIdentifier(word);
        }
        else
        {
            m_termBuilder.addIdentifier(word);
        }

        return true;
    }
    return false;
}

bool TermTranslator::hasWhiteSpace(string & lineString, int& index)
{
    int length = lineString.length();
    if(isWhiteSpace(lineString[index]))
    {
        int start = index;
        index = lineString.find_first_not_of(WHITESPACE_STRING, index);
        if(isNpos(index))
        {
            index = length;
        }
        string whiteSpaceString = lineString.substr(start, index-start);
        m_termBuilder.addWhiteSpace();
        if(" "!=whiteSpaceString)
        {
            string locator = lineString.substr(0, start) +
                    "[" + lineString.substr(start, index-start) +
                    "]" + lineString.substr(index);
            m_findings.addFinding(m_lineNumber, constructFileLocator(__FILE__, __LINE__), "Extra white space found", locator);
        }
        return true;
    }
    return false;
}

string TermTranslator::getLine()
{
    m_lineNumber++;
    m_termBuilder.setLineNumber(m_lineNumber);
    return m_albaFileReader.getLine();
}

bool TermTranslator::isEqualToFirstTwoCharacters(string const& lineString, int& index, string const& stringToCheck)
{
    if(!isLessThanStringLength(lineString, index+1)) return false;
    return stringToCheck == lineString.substr(index, 2);
}

string TermTranslator::fetchOperator(string const& lineString, int& index)
{
    //switch or stl algorithm
    int lineLength = lineString.length();
    auto it = find_if(m_stringOfOperators.begin(), m_stringOfOperators.end(), [&](string& operatorString)
    {
        int operatorlength = operatorString.length();
        if(index+operatorlength-1 <lineLength)
        {
            return (operatorString == lineString.substr(index, operatorlength));
        }
        return false;
    });
    if(it == m_stringOfOperators.end())
    {
        return string("");
    }
    return *it;
}

bool TermTranslator::isKeyword(string const& word)
{
    return any_of(m_stringOfKeywords.begin(), m_stringOfKeywords.end(), [word](string& keyword)
    {
        return keyword == word;
    });
}

bool TermTranslator::isCPlusPlusIgnorableIdentifier(string const& word)
{
    return any_of(m_stringOfIgnorableIdentifiers.begin(), m_stringOfIgnorableIdentifiers.end(), [word](string& keyword)
    {
        return keyword == word;
    });
}

bool TermTranslator::isPrimitiveType(string const& word)
{
    return any_of(m_stringOfPrimitiveTypes.begin(), m_stringOfPrimitiveTypes.end(), [word](string& primitiveType)
    {
        return primitiveType == word;
    });
}

string TermTranslator::readAndAccumulateUntilStringIfFound(string & lineString, int & index, string const& stringToFind)
{
    //switch or stl algorithm
    string result;
    lineString = lineString.substr(index);
    while(m_fileStream.good())
    {
        index = lineString.find(stringToFind);
        if(isNotNpos(index))
        {
            int end =  index+stringToFind.length();
            result += lineString.substr(0, end);
            lineString.erase(0, end);
            index=0;
            return result;
        }
        result += lineString;
        result += "\n";
        lineString = getLine();
        index = 0;
    }
    return result;
}


}// namespace codeReview
