#include "CMakeReader.hpp"

#include <File/AlbaFileReader.hpp>
#include <String/AlbaStringHelper.hpp>
#include <AlbaLocalPathHandler.hpp>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace alba;
using namespace alba::stringHelper;

namespace codeReview
{

CMakeReader::CMakeReader(string const& fileName, CMakeDatabase& fileDirectoryDatabase)
    : m_fileStream(fileName.c_str())
    , m_albaFileReader(m_fileStream)
    , m_fileDirectoryDatabase(fileDirectoryDatabase)
    , m_isFileValid(false)
{
    AlbaLocalPathHandler pathHandler;
    pathHandler.inputPath(fileName);
    if(pathHandler.isFoundInLocalSystem() && pathHandler.isFile())
    {
        if(m_fileStream.is_open())
        {
            m_fullPathOfFile = pathHandler.getFullPath();
            addVariable("CMAKE_CURRENT_SOURCE_DIR", pathHandler.getDirectory());
            m_fileDirectoryDatabase.setCMakeFileDirectoryPath(pathHandler.getFullPath());
            m_isFileValid = true;
        }
        else
        {
            cout<<"CMakeReader::constructor| Cannot read cmake file: ["<<pathHandler.getFullPath()<<"]."<<endl;
            cout<<"CMakeReader::constructor| Problem in FileI/O!"<<endl;
        }
    }
    else
    {
        cout<<"CMakeReader::constructor| Cannot read cmake file: ["<<pathHandler.getFullPath()<<"]."<<endl;
        cout<<"CMakeReader::constructor| File does not exist!"<<endl;
    }
}

bool CMakeReader::isFileValid()
{
    return m_isFileValid;
}

VariableMapType& CMakeReader::getVariableMapReference()
{
    return m_variableMap;
}

void CMakeReader::printVariables()
{
    //output iterator
    cout << "CMakeReader::printVariables| File:" << m_fullPathOfFile <<endl;
    cout << "CMakeReader::printVariables| Variables contains:" <<endl;
    for (auto& variableMap : m_variableMap)
    {
        cout << "CMakeReader::printVariables| VariableName: " << variableMap.first  <<endl;
        for (auto& value : variableMap.second)
        {
            cout << "CMakeReader::printVariables| Variable Values-> "<<value<<endl;
        }
    }
    cout << endl;
}

void CMakeReader::addVariable(string const& variableName, string const& contents)
{
    m_variableMap[variableName].emplace(
                getStringWithoutRedundantWhiteSpace(
                    getCorrectPathWithoutDoublePeriod<'\\'>(
                        getCorrectPathWithReplacedSlashCharacters<'\\'>(contents))));
}

void CMakeReader::clearVariable(string const& variableName)
{
    m_variableMap[variableName].clear();
}

void CMakeReader::copyVariableMap(VariableMapType const& inputVariableMap)
{
    //std::copy anyone?
    for (auto& variableMapPair : inputVariableMap)
    {
        for (auto& value : variableMapPair.second)
        {
            addVariable(variableMapPair.first, value);
        }
    }
}

void CMakeReader::copyVariableMapExceptCMakeDirectory(VariableMapType const& inputVariableMap)
{
    //std::copy_if anyone?
    for (auto& variableMapPair : inputVariableMap)
    {
        if(variableMapPair.first != "CMAKE_CURRENT_SOURCE_DIR")
        {
            for (auto& value : variableMapPair.second)
            {
                addVariable(variableMapPair.first, value);
            }
        }
    }
}

void CMakeReader::addToFilesAndDirectoriesDatabase(string const& filesAndDirectories)
{
    separateStringsUsingWhiteSpaceAndDoOperation(filesAndDirectories, [&](string stringWithoutWhiteSpace)
    {
        addCMakeDirectoryIfNeededAndDoOperation(stringWithoutWhiteSpace, [&](string stringWithCMakeDirectory)
        {
            m_fileDirectoryDatabase.addFileOrDirectory(stringWithCMakeDirectory);
        });
    });
}

void CMakeReader::readFile()
{
    if(m_isFileValid)
    {
        string lineString;
        while(m_albaFileReader.isNotFinished() || !lineString.empty())
        {
            int index=0;
            lineString = (lineString.empty()) ? m_albaFileReader.getLineAndIgnoreWhiteSpaces(): lineString;

            if(isIgnorable(lineString)) {lineString=string(""); continue;}

            string firstCommand = getStringWithCapitalLetters(getNextCMakeIdentifier(lineString, index));
            if(firstCommand=="PROJECT"){ processProjectCommand(lineString, index); }
            else if(firstCommand=="SET"){ processSetCommand(lineString, index); }
            else if(firstCommand=="INCLUDE_DIRECTORIES"){  processIncludeDirectoriesCommand(lineString, index); }
            else if(firstCommand=="INCLUDE"){ processIncludeCommand(lineString, index); }
            else if(firstCommand=="ADD_SUBDIRECTORY"){ processAddSubDirectoryCommand(lineString, index); }
            else if(firstCommand=="ADD_EXECUTABLE"){ includeSecondArgumentToFilesAndDirectories(lineString, index); }
            else if(firstCommand=="ADD_LIBRARY"){ includeSecondArgumentToFilesAndDirectories(lineString, index); }
            else{ignoreEntireLine(lineString, index);} // CMAKE does not have line separators, its hard to assume

            lineString = (isNotNpos(index)) ? lineString.substr(index) : string("");
        }
    }
}

void CMakeReader::processProjectCommand(string& lineString, int& index)
{
    findOpeningParenthesisAndProceed(lineString, index);
    addVariable("PROJECT_NAME", getNextCMakeIdentifier(lineString, index));
}

void CMakeReader::processSetCommand(string& lineString, int& index)
{
    findOpeningParenthesisAndProceed(lineString, index);
    string variableName(getNextCMakeIdentifier(lineString, index));
    lineString = lineString.substr(index);
    index = 0;
    string contents(extractContentsUntilCloseParenthesis(lineString, index));
    VariableMapType tempVariableMap;
    replaceVariableWithRealValuesInStringAndDoOperation(m_variableMap.begin(), contents, [&](string stringWithRealValues)
    {
        tempVariableMap[variableName].emplace(getStringWithoutQuotations(getStringWithoutRedundantWhiteSpace(stringWithRealValues)));
    });

    copyVariableMap(tempVariableMap);
}

void CMakeReader::processIncludeDirectoriesCommand(string& lineString, int& index)
{
    findOpeningParenthesisAndProceed(lineString, index);
    lineString = lineString.substr(index);
    index = 0;
    string contents(extractContentsUntilCloseParenthesis(lineString, index));
    //cout << "CMakeReader::processIncludeDirectoriesCommand File:"<<m_fullPathOfFile<<" lineString:"<<"["<<lineString<<"]"<<endl;
    replaceVariableWithRealValuesInStringAndDoOperation(m_variableMap.begin(), contents, [&](string stringWithRealValues)
    {
        addToFilesAndDirectoriesDatabase(stringWithRealValues);
    });
}

void CMakeReader::processIncludeCommand(string& lineString, int& index)
{
    findOpeningParenthesisAndProceed(lineString, index);
    lineString = lineString.substr(index);
    index = 0;
    string contents(extractContentsUntilCloseParenthesis(lineString, index));

    set<string> listOfIncludeFiles;
    replaceVariableWithRealValuesInStringAndDoOperation(m_variableMap.begin(), contents, [&](string stringWithRealValues)
    {
        if(!hasCMakeVariables(stringWithRealValues))
        {
            separateStringsUsingWhiteSpaceAndDoOperation(stringWithRealValues, [&](string stringWithoutWhiteSpace)
            {
                addCMakeDirectoryIfNeededAndDoOperation(stringWithoutWhiteSpace, [&](string stringWithCMakeDirectory)
                {
                    listOfIncludeFiles.emplace(stringWithCMakeDirectory);
                });
            });
        }
    });

    for(auto& stringOfIncludeDirectory : listOfIncludeFiles)
    {
        CMakeReader reader(stringOfIncludeDirectory, m_fileDirectoryDatabase);
        if(reader.isFileValid())
        {
            reader.clearVariable("CMAKE_CURRENT_SOURCE_DIR");
            reader.copyVariableMap(m_variableMap);
            reader.readFile();
            copyVariableMap(reader.getVariableMapReference());
        }
    }
}

void CMakeReader::processAddSubDirectoryCommand(string& lineString, int& index)
{
    findOpeningParenthesisAndProceed(lineString, index);
    lineString = lineString.substr(index);
    index = 0;
    string contents(extractContentsUntilCloseParenthesis(lineString, index));

    set<string> listOfSubDirectories;
    replaceVariableWithRealValuesInStringAndDoOperation(m_variableMap.begin(), contents, [&](string stringWithRealValues)
    {
        if(!hasCMakeVariables(stringWithRealValues))
        {
            separateStringsUsingWhiteSpaceAndDoOperation(stringWithRealValues, [&](string stringWithoutWhiteSpace)
            {
                addCMakeDirectoryIfNeededAndDoOperation(stringWithoutWhiteSpace, [&](string stringWithCMakeDirectory)
                {
                    listOfSubDirectories.emplace(stringWithCMakeDirectory+"\\");
                });
            });
        }
    });

    for(auto& stringPathOfSubDirectory : listOfSubDirectories)
    {
        CMakeDatabase& subFileDirectoryDatabase = m_fileDirectoryDatabase.addCMakeSubDirectory();
        CMakeReader reader(stringPathOfSubDirectory+"CMakeLists.txt", subFileDirectoryDatabase);
        if(reader.isFileValid())
        {
            reader.copyVariableMapExceptCMakeDirectory(m_variableMap);
            reader.readFile();
        }
    }
}

void CMakeReader::includeSecondArgumentToFilesAndDirectories(string& lineString, int& index)
{
    findOpeningParenthesisAndProceed(lineString, index);
    getNextCMakeIdentifier(lineString, index);
    lineString = lineString.substr(index);
    index = 0;
    string contents(extractContentsUntilCloseParenthesis(lineString, index));
    //cout << "CMakeReader::includeSecondArgumentToFilesAndDirectories: File:"<<m_fullPathOfFile<<" lineString:"<<"["<<lineString<<"]"<<endl;
    replaceVariableWithRealValuesInStringAndDoOperation(m_variableMap.begin(), contents, [&](string stringWithRealValues)
    {
        addToFilesAndDirectoriesDatabase(stringWithRealValues);
    });
}


void CMakeReader::replaceVariableWithRealValuesInStringAndDoOperation(
        VariableMapIterator startIterator,
        string const& contents,
        function<void(string)> operationIfFound)
{
    bool found = false;
    //stl algorithm
    for (VariableMapIterator it = startIterator; it!=m_variableMap.end(); ++it)
    {
        auto& variableMap = *it;
        for (auto& variableValue : variableMap.second)
        {
            string contentsTemp (contents);
            if(transformReplaceStringIfFound(contentsTemp, "${" + variableMap.first + "}", variableValue))
            {
                VariableMapIterator nextVariableToCheck = it;
                nextVariableToCheck++;
                replaceVariableWithRealValuesInStringAndDoOperation(nextVariableToCheck, contentsTemp, operationIfFound);
                found = true;
            }
        }
        if(found){ break;}
    }
    if(!found)
    {
        operationIfFound(contents);
    }
}

void CMakeReader::separateStringsUsingWhiteSpaceAndDoOperation(
        string const& string1,
        function<void(string)> operationForEachString)
{
    string longString(getStringWithoutRedundantWhiteSpace(string1));
    int index=0;
    while(checkAndProceedIfCharacterIsFound(longString, WHITESPACE_STRING, index))
    {
        operationForEachString(longString.substr(0, index-1));
        longString = longString.substr(index);
        index=0;
    }
    if(!longString.empty()){operationForEachString(longString);}
}

void CMakeReader::addCMakeDirectoryIfNeededAndDoOperation(
        string const& string1,
        function<void(string)> operationForEachString)
{
    AlbaLocalPathHandler pathHandler;
    pathHandler.inputPath(string1);

    if(pathHandler.isRelativePath())
    {
        if(m_variableMap.find("CMAKE_CURRENT_SOURCE_DIR") != m_variableMap.end())
        {
            for(string cMakeFileDirectory : m_variableMap.at("CMAKE_CURRENT_SOURCE_DIR"))
            {
                AlbaLocalPathHandler pathHandlerWithCMake;
                pathHandlerWithCMake.inputPath(cMakeFileDirectory+"\\"+pathHandler.getFullPath());
                //check if path exists before adding
                operationForEachString(pathHandlerWithCMake.getFullPath());
            }
        }
        else
        {
            operationForEachString(pathHandler.getFullPath());
        }
    }
    else
    {
        operationForEachString(pathHandler.getFullPath());
    }
}

string CMakeReader::getNextCMakeIdentifier(string& lineString, int & index)
{
    //optimize this think of accumulate
    findAndProceedNotWhiteSpaceMultiLineSearch(lineString, index);
    if(isNpos(index)){return string("");}

    string command;
    int length = lineString.length();
    for (; index<length; index++)
    {
        if(isLetterOrNumberOrUnderscore(lineString[index]))
        {
            command += lineString[index];
        }
        else{break;}
    }
    return command;
}


void CMakeReader::findOpeningParenthesisAndProceed(string& lineString, int & index)
{
    bool continueSearching = true;
    while(continueSearching)
    {
        if(checkAndProceedIfCharacterIsFound(lineString, "(", index))
        {
            continueSearching = false;
            break;
        }
        else
        {
            continueSearching = readAnotherLineIfPossible(lineString, index);
        }
    }
}

string CMakeReader::extractContentsUntilCloseParenthesis(string& lineString, int & index)
{
    string contents;
    bool continueSearching = true;
    while(continueSearching)
    {
        if(checkIfCharacterIsFound(lineString, ")", index))
        {
            contents += lineString.substr(0,index);
            checkAndProceedIfCharacterIsFound(lineString, ")", index);
            continueSearching = false;
            break;
        }
        else
        {
            contents += lineString;
            contents += " ";
            continueSearching = readAnotherLineIfPossible(lineString, index);
        }
    }
    return contents;
}

void CMakeReader::findAndProceedNotWhiteSpaceMultiLineSearch(string& lineString, int& index)
{
    bool continueSearching = true;
    while(continueSearching)
    {
        index = lineString.find_first_not_of(WHITESPACE_STRING, index);
        if(isNpos(index))
        {
            continueSearching = readAnotherLineIfPossible(lineString, index);
        }
        else
        {
            continueSearching = false;
            break;
        }
    }
}

bool CMakeReader::readAnotherLineIfPossible(string& lineString, int& index)
{
    if(m_fileStream.good())
    {
        lineString = m_albaFileReader.getLineAndIgnoreWhiteSpaces();
        index = 0;
        return true;
    }
    return false;
}

bool CMakeReader::checkAndProceedIfCharacterIsFound(string const& string1, string const& characters, int& index){
    index = string1.find_first_of(characters, index);
    bool isFound = isNotNpos(index);
    index = string1.find_first_not_of(string(WHITESPACE_STRING) + characters, index);
    index = isNpos(index) ? string1.length() : index;
    return isFound;
}

bool CMakeReader::checkIfCharacterIsFound(string const& string1, string const& characters, int& index){
    index = string1.find_first_of(characters, index);
    bool isFound = isNotNpos(index);
    index = isNpos(index) ? string1.length() : index;
    return isFound;
}

void CMakeReader::ignoreEntireLine(string const& string1, int & index)
{
    index=string1.length();
}

bool CMakeReader::isIgnorable(string const& string1)
{
    int index = string1.find_first_not_of(WHITESPACE_STRING, 0);
    if(isNpos(index)) return false;
    return string1[index]=='#';
}

bool CMakeReader::hasCMakeVariables(string const& string1)
{
    int index = string1.find("${");
    if(isNpos(index)){ return false; }
    index = string1.find("}", index);
    return isNotNpos(index);
}

}// namespace codeReview

