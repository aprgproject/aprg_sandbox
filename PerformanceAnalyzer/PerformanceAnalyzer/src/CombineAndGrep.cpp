#include "CombineAndGrep.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>
using namespace std;

namespace alba{

CombineAndGrep::CombineAndGrep(string const& outputFilePath, string const& grepString)
    : m_outputFileStream(AlbaLocalPathHandler(outputFilePath).getFullPath())
    , m_grepString(grepString)
{}

void CombineAndGrep::processDirectory(string const& inputDirectoryPath)
{
    AlbaLocalPathHandler inputDirectoryPathHandler(inputDirectoryPath);
    cout << "processDirectory() inputDirectoryPath:" << inputDirectoryPath << endl;
    AlbaLocalPathHandler::ListOfPaths files;
    AlbaLocalPathHandler::ListOfPaths directories;
    inputDirectoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for(string const& file: files)
    {
        processFile(file);
    }
}

void CombineAndGrep::processFile(string const& inputFilePath)
{
    AlbaLocalPathHandler inputFilePathHandler(inputFilePath);
    cout << "processFile() inputFilePath:" << inputFilePath << endl;
    ifstream inputFileStream(inputFilePathHandler.getFullPath());
    AlbaFileReader fileToRead(inputFileStream);
    while(fileToRead.isNotFinished())
    {
        string lineFromFile(fileToRead.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineFromFile, m_grepString))
        {
            m_outputFileStream << lineFromFile << endl;
        }
    }
}

}
