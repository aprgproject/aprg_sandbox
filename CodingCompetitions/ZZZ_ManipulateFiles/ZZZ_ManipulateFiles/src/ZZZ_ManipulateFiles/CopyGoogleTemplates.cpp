#include "CopyGoogleTemplates.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <fstream>


#include <Common/Debug/AlbaDebug.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

void CopyGoogleTemplates::copyTemplatesForOneRound(
        string const& destinationPath,
        StringPairs const& replacePairs) const
{
    AlbaLocalPathHandler localPathHandler(m_googleTemplatesPath);
    ListOfPaths files;
    ListOfPaths directories;
    localPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for(auto const& originalFilePath : files)
    {
        AlbaLocalPathHandler originalFilePathHandler(originalFilePath);
        string newFile(originalFilePathHandler.getFile());
        for(auto const& replacePair : replacePairs)
        {
            transformReplaceStringIfFound(newFile, replacePair.first, replacePair.second);
        }
        if(!isStringFoundInsideTheOtherStringCaseSensitive(newFile, "SampleProblem"))
        {
            AlbaLocalPathHandler newFilePathHandler(destinationPath + "\\" + newFile);
            newFilePathHandler.createDirectoriesForNonExisitingDirectories();
            replaceStringWithStringOnFile(originalFilePath, newFilePathHandler.getFullPath(), replacePairs);
        }
    }
}

void CopyGoogleTemplates::replaceStringWithStringOnFile(
        string const& inputFilePath,
        string const& outputFilePath,
        StringPairs const& replacePairs) const
{
    AlbaLocalPathHandler outputFilePathHandler(outputFilePath);
    outputFilePathHandler.createDirectoriesForNonExisitingDirectories();
    ifstream inputFile(inputFilePath);
    ofstream outputFile(outputFilePath);
    if(inputFile.is_open())
    {
        AlbaFileReader inputFileReader(inputFile);
        while(inputFileReader.isNotFinished())
        {
            string line(inputFileReader.getLine());
            for(auto const& replacePair : replacePairs)
            {
                transformReplaceStringIfFound(line, replacePair.first, replacePair.second);
            }
            outputFile << line << "\n";
        }
    }
}

}
