#pragma once

#include "CMakeDatabase.hpp"

#include <AlbaFileReader.hpp>
#include <functional>
#include <fstream>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>

using std::string;
using std::ifstream;
using std::unordered_map;
using std::vector;
using std::set;
using std::function;

using alba::AlbaFileReader;

namespace codeReview
{
typedef unordered_map<string, set<string>> VariableMapType;
typedef unordered_map<string, set<string>>::iterator VariableMapIterator;

class CMakeReader
{
public:
    explicit CMakeReader(string const& fileName, CMakeDatabase& fileDirectoryDatabase);
    bool isFileValid();
    VariableMapType& getVariableMapReference();
    void printVariables();
    void addVariable(string const& variableName, string const& contents);
    void clearVariable(string const& variableName);
    void copyVariableMap(VariableMapType const& inputVariableMap);
    void copyVariableMapExceptCMakeDirectory(VariableMapType const& inputVariableMap);
    void addToFilesAndDirectoriesDatabase(string const& filesAndDirectories);
    void readFile();
private:
    void processProjectCommand(string& lineString, int& index);
    void processSetCommand(string& lineString, int& index);
    void processIncludeDirectoriesCommand(string& lineString, int& index);
    void processIncludeCommand(string& lineString, int& index);
    void processAddSubDirectoryCommand(string& lineString, int& index);
    void includeSecondArgumentToFilesAndDirectories(string& lineString, int& index);
    void replaceVariableWithRealValuesInStringAndDoOperation(
            VariableMapIterator startIterator,
            string const& contents,
            function<void(string)> operationIfFound);
    void separateStringsUsingWhiteSpaceAndDoOperation(
            string const& string1,
            function<void(string)> operationForEachString);
    void addCMakeDirectoryIfNeededAndDoOperation(
            string const& string1,
            function<void(string)> operationForEachString);
    string getNextCMakeIdentifier(string& lineString, int& index);
    void findOpeningParenthesisAndProceed(string& lineString, int& index);
    string extractContentsUntilCloseParenthesis(string& lineString, int& index);
    void findAndProceedNotWhiteSpaceMultiLineSearch(string& lineString, int& index);
    bool readAnotherLineIfPossible(string& lineString, int& index);
    bool checkAndProceedIfCharacterIsFound(string const& string1, string const& characters, int& index);
    bool checkIfCharacterIsFound(string const& string1, string const& characters, int& index);
    void ignoreEntireLine(string const& string1, int& index);
    bool isIgnorable(string const& string1);
    bool hasCMakeVariables(string const& string1);
    ifstream m_fileStream;
    AlbaFileReader m_albaFileReader;
    CMakeDatabase& m_fileDirectoryDatabase;
    VariableMapType m_variableMap;
    string m_fullPathOfFile;
    bool m_isFileValid;
};

}// namespace codeReview
