#include <AlbaFileReader.hpp>
#include <AprgFileExtractor.hpp>
#include <BtsLogSorter.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <fstream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <StepHandler.hpp>
#include <string>

using namespace alba;
using namespace std;

namespace tcomToolsGui
{

StepHandler::StepHandler(TcomToolsConfiguration & configuration)
    : m_configuration(configuration)
{}

void StepHandler::executeSteps() const
{
    AlbaWindowsPathHandler currentPathHandler;
    currentPathHandler.inputPath(m_configuration.inputFileOrDirectory);
    for(int step=1; step<4; step++)
    {
        currentPathHandler.reInputPath();
        if(!currentPathHandler.isFoundInLocalSystem())
        {
            cout << currentPathHandler.getFullPath() << " is not found in local system" << endl;
            return;
        }
        cout<<"Step "<<step<<" start | CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
        if(1 == step && m_configuration.isExtractStepOn)
        {
            executeExtractStep(currentPathHandler);
        }
        else if(2 == step && m_configuration.isCombineAndSortStepOn)
        {
            executeCombineAndSortStep(currentPathHandler);
        }
        else if(3 == step)
        {
            if(m_configuration.isGrepStepOn)
            {
                executeGrep(currentPathHandler);
            }
            if(m_configuration.isCropStepOn)
            {

            }
        }
        cout<<"Step "<<step<<" done | CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
    }
}

void StepHandler::executeExtractStep(AlbaWindowsPathHandler & currentPathHandler) const
{
    AprgFileExtractor fileExtractor(m_configuration.extractGrepCondition);
    if(currentPathHandler.isDirectory())
    {
        fileExtractor.extractAllRelevantFiles(currentPathHandler.getFullPath());
    }
    else if(fileExtractor.isRecognizedCompressedFile(currentPathHandler.getExtension()))
    {
        fileExtractor.extractAllRelevantFiles(currentPathHandler.getFullPath());
        currentPathHandler.inputPath(currentPathHandler.getDirectory() + R"(\)" + currentPathHandler.getFilenameOnly());
    }
    else
    {
        cout<<"Extraction step did not proceed. CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
    }
}

void StepHandler::executeCombineAndSortStep(AlbaWindowsPathHandler & currentPathHandler) const
{
    if(currentPathHandler.isDirectory())
    {
        tcomToolsBackend::BtsLogSorter btsLogSorter(
                    m_configuration.acceptedFilesGrepCondition,
                    m_configuration.sorterConfigurationWithPcTime,
                    m_configuration.sorterConfigurationWithoutPcTime,
                    m_configuration.pathOfLogsWithoutPcTime);
        btsLogSorter.processDirectory(currentPathHandler.getDirectory());
        currentPathHandler.goUp();
        currentPathHandler.inputPath(currentPathHandler.getDirectory() + R"(\sorted.log)");
        btsLogSorter.saveAllToOutputFile(currentPathHandler.getFullPath());
    }
    else
    {
        cout<<"Combine and sort step did not proceed. CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
    }
}

void StepHandler::executeGrep(AlbaWindowsPathHandler & currentPathHandler) const
{
    AlbaGrepStringEvaluator evaluator(m_configuration.getGrepCondition());
    if(evaluator.isInvalid())
    {
        cout << "Grep condition is invalid. Grep condition: " << m_configuration.getGrepCondition() << " Error message: " << evaluator.getErrorMessage() << endl;
    }
    else if(currentPathHandler.isFile())
    {
        ifstream inputFileStream(currentPathHandler.getFullPath());
        currentPathHandler.inputPath(currentPathHandler.getDirectory() + R"(\)" + m_configuration.getGrepFileName());
        ofstream outputFileStream(currentPathHandler.getFullPath());
        AlbaFileReader fileReader(inputFileStream);
        while(fileReader.isNotFinished())
        {
            string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
            if(evaluator.evaluate(lineInLogs))
            {
                outputFileStream << lineInLogs << endl;
            }
        }
    }
    else
    {
        cout<<"Grep step did not proceed. CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
    }
}

}
