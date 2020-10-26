#include "CPlusPlusFileFixer.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <fstream>
#include <iostream>

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
        if("cpp" == filePathHandler.getExtension() || "hpp" == filePathHandler.getExtension())
        {
            processFile(filePathHandler.getFullPath());
        }
    }
}
void CPlusPlusFileFixer::processFile(string const& path)
{
    cout<<"ProcessFile: "<<path<<endl;
    clear();
    checkFile(path);
    fix(path);
    writeFile(path);
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
    AlbaLocalPathHandler filePathHandler(path);
    ifstream inputLogFileStream(filePathHandler.getFullPath());
    AlbaFileReader fileReader(inputLogFileStream);
    bool isOnHeaderPart(true);
    while(fileReader.isNotFinished())
    {
        string line(fileReader.getLine());
        if(isOnHeaderPart)
        {
            if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "#include"))
            {
                if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "//"))
                {
                    cout<<"Please check header commented on path:"<<path<<" line:"<<line<<endl;
                }
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
            else if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "#pragma") && stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(line, "once"))            {
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
void CPlusPlusFileFixer::fix(string const& path)
{
    fixHeaders(path);

    removeTrailingLinesInCode();
    fixNamespaces();
}

void CPlusPlusFileFixer::fixHeaders(string const& path)
{
    AlbaLocalPathHandler filePathHandler(path);
    set<string> mainHeaders;
    set<string> cPlusPlusHeaders;    set<string> otherLibraryHeaders;
    set<string> aprgFiles;
    for(string const& header: m_headerListFromAngleBrackets)
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

void CPlusPlusFileFixer::writeFile(string const& path)
{
    AlbaLocalPathHandler filePathHandler(path);    ofstream outputLogFileStream(filePathHandler.getFullPath());
    if(m_isPragmaOnceFound)
    {
        outputLogFileStream<<"#pragma once"<<endl;
        outputLogFileStream<<endl;
    }
    if(!m_headerListFromQuotations.empty())
    {
        for(string const& header: m_headerListFromQuotations)
        {
            if(!header.empty())
            {                outputLogFileStream<<R"(#include ")"<<header<<R"(")"<<endl;
            }
            else
            {
                outputLogFileStream<<endl;
            }
        }
        outputLogFileStream<<endl;
    }
    if(!m_headerListFromAngleBrackets.empty())
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
    for(string const& line: m_linesAfterTheHeader)
    {
        outputLogFileStream<<line<<endl;
    }
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

bool CPlusPlusFileFixer::isOtherLibraryHeaders(string const& headerFoundInFile) const
{
    bool result(false);
    if("windows.h" == headerFoundInFile || stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(headerFoundInFile, "gtest"))
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
    }    return result;
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


}

