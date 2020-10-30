#include "CPlusPlusFileFixer.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;
namespace alba
{
void CPlusPlusFileFixer::processDirectory(string const& path)
{
    set<string> listOfFiles;
    set<string> listOfDirectories;
    AlbaLocalPathHandler(path).findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& filePath : listOfFiles)
    {
        AlbaLocalPathHandler filePathHandler(filePath);
        if(!isPathIgnored(filePath))
        {
            if("cpp" == filePathHandler.getExtension() || "hpp" == filePathHandler.getExtension())
            {
                processFile(filePathHandler.getFullPath());
            }
        }
    }
}

void CPlusPlusFileFixer::processFile(string const& path)
{
    //cout<<"ProcessFile: "<<path<<endl;
    clear();
    checkFile(path);
    //fix(path);
    //writeFile(path);
}

void CPlusPlusFileFixer::clear()
{
    m_linesAfterTheHeader.clear();
    m_headerListFromAngleBrackets.clear();
    m_headerListFromQuotations.clear();
    m_isPragmaOnceFound = false;
}

void CPlusPlusFileFixer::checkFile(string const& path)
{
    readContentsFromFile(path);
    //notifyIfIostreamHeaderExistInProductionCode(path);
    //notifyIfCAssertHeaderExistInProductionCode(path);
    notifyIfMoreThanLoopsAreCascaded(path);
}

void CPlusPlusFileFixer::readContentsFromFile(string const& path)
{
    AlbaLocalPathHandler filePathHandler(path);
    ifstream inputLogFileStream(filePathHandler.getFullPath());
    AlbaFileReader fileReader(inputLogFileStream);    bool isOnHeaderPart(true);
    while(fileReader.isNotFinished())
    {
        string line(fileReader.getLine());        if(isOnHeaderPart)
        {
            if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "#include"))
            {
                notifyIfThereAreCommentsInHeader(path, line);
                string headerFromAngleBrackets(stringHelper::getStringInBetweenTwoStrings(line, R"(<)", R"(>)"));
                string headerFromQuotations(stringHelper::getStringInBetweenTwoStrings(line, R"(")", R"(")"));
                if(!headerFromAngleBrackets.empty())
                {
                    addHeaderFileFromAngleBrackets(headerFromAngleBrackets);
                }
                if(!headerFromQuotations.empty())
                {
                    addHeaderFileFromQuotations(headerFromQuotations);
                }
            }
            else if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "#pragma") && stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "once"))
            {
                m_isPragmaOnceFound = true;
            }
            else if(!stringHelper::isWhiteSpace(line))
            {
                m_linesAfterTheHeader.emplace_back(line);
                isOnHeaderPart=false;
            }
        }
        else
        {
            m_linesAfterTheHeader.emplace_back(line);
        }
    }
}

void CPlusPlusFileFixer::notifyIfThereAreCommentsInHeader(string const& path, std::string const& line) const
{
    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "//"))    {
        cout<<"CHECK THIS: Header comments on:["<<path<<"] in line:["<<line<<"]"<<endl;
    }
}
void CPlusPlusFileFixer::notifyIfIostreamHeaderExistInProductionCode(string const& path) const
{
    AlbaLocalPathHandler filePathHandler(path);
    bool isIostreamFound = (std::find(m_headerListFromAngleBrackets.cbegin(), m_headerListFromAngleBrackets.cend(), string("iostream")) != m_headerListFromAngleBrackets.end());
    bool isCpp = filePathHandler.getExtension() == "cpp";
    bool isUnitTest = stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(filePathHandler.getFile(), "_unit.cpp");
    if(isIostreamFound && !isCpp) // !isUnitTest)
    {
        cout<<"CHECK THIS: iostream found in:["<<path<<"]."<<endl;
    }
}

void CPlusPlusFileFixer::notifyIfCAssertHeaderExistInProductionCode(string const& path) const
{
    bool isCAssertFound = (std::find(m_headerListFromAngleBrackets.cbegin(), m_headerListFromAngleBrackets.cend(), string("cassert")) != m_headerListFromAngleBrackets.end());
    if(isCAssertFound)
    {
        cout<<"CHECK THIS: cassert found in:["<<path<<"]."<<endl;
    }
}

void CPlusPlusFileFixer::notifyIfMoreThanLoopsAreCascaded(string const& path) const
{
    std::set<unsigned int> indentionsOfLoops;
    for(string const& line : m_linesAfterTheHeader)
    {
        if(isLineWithALoopStart(line))
        {
            indentionsOfLoops.emplace(stringHelper::getStringThatContainsWhiteSpaceIndention(line).size());
            if(indentionsOfLoops.size()>=2)
            {
                cout<<"CHECK THIS: More than 2 loops found in:["<<path<<"] in line:["<<line<<"]."<<endl;
            }
        }
        else if(isLineWithALoopEnd(line))
        {
            auto it = indentionsOfLoops.find(stringHelper::getStringThatContainsWhiteSpaceIndention(line).size());
            if(it!=indentionsOfLoops.end())
            {
                indentionsOfLoops.erase(it);
            }
        }
    }
}

void CPlusPlusFileFixer::fix(string const& path)
{
    fixHeaders(path);
    removeTrailingLinesInCode();
    fixNamespaces();
}

void CPlusPlusFileFixer::fixHeaders(string const& path)
{
    AlbaLocalPathHandler filePathHandler(path);    set<string> mainHeaders;
    set<string> cPlusPlusHeaders;
    set<string> otherLibraryHeaders;
    set<string> aprgFiles;    for(string const& header: m_headerListFromAngleBrackets)
    {
        if(isMainHeader(header, filePathHandler.getFullPath()))
        {
            mainHeaders.emplace(header);
        }
        else if(isCPlusPlusHeader(header))
        {
            cPlusPlusHeaders.emplace(header);
        }
        else if(isOtherLibraryHeaders(header))
        {
            otherLibraryHeaders.emplace(header);
        }
        else
        {
            aprgFiles.emplace(header);
        }
    }
    m_headerListFromAngleBrackets.clear();
    if(!mainHeaders.empty())
    {
        for(string const& header: mainHeaders)
        {
            addHeaderFileFromAngleBrackets(header);
        }
        addHeaderFileFromAngleBrackets("");
    }
    if(!aprgFiles.empty())
    {
        for(string const& header: aprgFiles)
        {
            addHeaderFileFromAngleBrackets(header);
        }
        addHeaderFileFromAngleBrackets("");
    }
    if(!otherLibraryHeaders.empty())
    {
        for(string const& header: otherLibraryHeaders)
        {
            addHeaderFileFromAngleBrackets(header);
        }
        addHeaderFileFromAngleBrackets("");
    }
    if(!cPlusPlusHeaders.empty())
    {
        for(string const& header: cPlusPlusHeaders)
        {
            addHeaderFileFromAngleBrackets(header);
        }
        addHeaderFileFromAngleBrackets("");
    }
}

void CPlusPlusFileFixer::removeTrailingLinesInCode()
{
    auto nonWhiteSpaceLineIterator = m_linesAfterTheHeader.rbegin();
    for(; nonWhiteSpaceLineIterator != m_linesAfterTheHeader.rend(); nonWhiteSpaceLineIterator++)
    {
        if(!stringHelper::isWhiteSpace(*nonWhiteSpaceLineIterator))
        {
            break;
        }
    }
    m_linesAfterTheHeader.erase(nonWhiteSpaceLineIterator.base(), m_linesAfterTheHeader.end());
}

void CPlusPlusFileFixer::fixNamespaces()
{
    for(string & line : m_linesAfterTheHeader)
    {
        string firstWord(stringHelper::getStringBeforeThisString(stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(line), " "));
        if("namespace" == firstWord)
        {
            stringHelper::transformReplaceStringIfFound(line, "{", "\n{");
        }
    }
}

void CPlusPlusFileFixer::addHeaderFileFromAngleBrackets(std::string const& header)
{
    AlbaPathHandler headerPathHandler(header, "/");
    m_headerListFromAngleBrackets.emplace_back(headerPathHandler.getFullPath());
}

void CPlusPlusFileFixer::addHeaderFileFromQuotations(std::string const& header)
{
    AlbaPathHandler headerPathHandler(header, "/");
    m_headerListFromQuotations.emplace(headerPathHandler.getFullPath());
}

void CPlusPlusFileFixer::writeFile(string const& path)
{
    AlbaLocalPathHandler filePathHandler(path);
    ofstream outputLogFileStream(filePathHandler.getFullPath());
    if(m_isPragmaOnceFound)
    {
        outputLogFileStream<<"#pragma once"<<endl;
        outputLogFileStream<<endl;
    }
    if(!m_headerListFromQuotations.empty())
    {
        writeHeadersWithQuotations(outputLogFileStream);
    }
    if(!m_headerListFromAngleBrackets.empty())
    {
        writeHeadersWithAngleBrackets(outputLogFileStream);
    }
    for(string const& line: m_linesAfterTheHeader)
    {
        outputLogFileStream<<line<<endl;
    }
}

void CPlusPlusFileFixer::writeHeadersWithQuotations(ofstream & outputLogFileStream) const
{
    for(string const& header: m_headerListFromQuotations)
    {
        if(!header.empty())
        {
            outputLogFileStream<<R"(#include ")"<<header<<R"(")"<<endl;
        }
        else
        {
            outputLogFileStream<<endl;
        }
    }
    outputLogFileStream<<endl;
}

void CPlusPlusFileFixer::writeHeadersWithAngleBrackets(ofstream & outputLogFileStream) const
{
    for(string const& header: m_headerListFromAngleBrackets)
    {
        if(!header.empty())
        {
            outputLogFileStream<<R"(#include <)"<<header<<R"(>)"<<endl;
        }
        else
        {
            outputLogFileStream<<endl;
        }
    }
}

bool CPlusPlusFileFixer::isLineWithALoopStart(string const& line) const
{
    bool result(false);
    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "for(") ||
            stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "while("))
    {
        result=true;
    }
    return result;
}

bool CPlusPlusFileFixer::isLineWithALoopEnd(string const& line) const
{
    bool result(false);
    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "}") &&
            !stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "{"))
    {
        result=true;
    }
    return result;
}


bool CPlusPlusFileFixer::isPathIgnored(string const& path) const
{
    bool result(false);    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(path, "ACodeReview") ||
            stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(path, "AprgCMakeHelpers") ||
            stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(path, "CImg") ||
            stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(path, "curl-7.38.0") ||            stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(path, "CurlCpp") ||
            stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(path, "gsl1.8") ||
            stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(path, "gtest-1.7.0") ||
            stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(path, "plantumlqeditor") ||
            stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(path, "zlib128"))
    {
        result=true;
    }
    return result;
}

bool CPlusPlusFileFixer::isCPlusPlusHeader(string const& header) const
{
    bool result(false);
    if("cstdlib" == header || "csignal" == header || "csetjmp" == header || "cstdarg" == header || "typeinfo" == header || "typeindex" == header || "type_traits" == header ||
            "bitset" == header || "functional" == header || "utility" == header || "ctime" == header || "chrono" == header || "cstddef" == header || "initializer_list" == header ||
            "tuple" == header || "any" == header || "optional" == header || "variant" == header || "new" == header || "memory" == header || "scoped_allocator" == header ||
            "memory_resource" == header || "climits" == header || "cfloat" == header || "cstdint" == header || "cinttypes" == header || "limits" == header || "exception" == header ||
            "stdexcept" == header || "cassert" == header || "system_error" == header || "cerrno" == header || "cctype" == header || "cwctype" == header || "cstring" == header || "cwchar" == header ||
            "cuchar" == header || "string" == header || "string_view" == header || "array" == header || "vector" == header || "deque" == header || "list" == header || "forward_list" == header ||
            "set" == header || "map" == header || "unordered_set" == header || "unordered_map" == header || "stack" == header || "queue" == header || "algorithm" == header ||
            "execution" == header || "iterator" == header || "cmath" == header || "complex" == header || "valarray" == header || "random" == header || "numeric" == header ||
            "ratio" == header || "cfenv" == header || "iosfwd" == header || "ios" == header || "istream" == header || "ostream" == header || "iostream" == header || "fstream" == header ||
            "sstream" == header || "strstream" == header || "iomanip" == header || "streambuf" == header || "cstdio" == header || "locale" == header || "clocale" == header ||
            "codecvt" == header || "regex" == header || "atomic" == header || "thread" == header || "mutex" == header || "shared_mutex" == header || "future" == header ||
            "condition_variable" == header || "filesystem" == header)
    {
        result=true;
    }
    return result;
}

bool CPlusPlusFileFixer::isQtHeader(string const& header) const
{
    bool result(false);
    AlbaLocalPathHandler headerFileHandler(header);
    if(header.length()>=2)
    {
        if('Q' == header[0] && ('t' == header[1] || stringHelper::isCapitalLetter(header[1])) && headerFileHandler.getExtension().empty())
        {
            result = true;
        }
    }
    return result;
}

bool CPlusPlusFileFixer::isOtherLibraryHeaders(string const& header) const
{
    bool result(false);
    if("windows.h" == header || stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(header, "gtest") || isQtHeader(header))
    {
        result=true;
    }
    return result;
}

bool CPlusPlusFileFixer::isMainHeader(string const& headerFoundInFile, string const& filePath) const
{
    bool result(false);
    AlbaLocalPathHandler headerFileHandler(headerFoundInFile);
    AlbaLocalPathHandler filePathHandler(filePath);
    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(headerFileHandler.getFilenameOnly(), filePathHandler.getFilenameOnly()))
    {
        result=true;
    }
    return result;
}


}
