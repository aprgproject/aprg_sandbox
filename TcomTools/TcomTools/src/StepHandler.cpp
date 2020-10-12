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

void StepHandler::execute() const
{
    AlbaWindowsPathHandler currentPathHandler(m_configuration.inputFileOrDirectory);
    for(int step=1; step<4; step++)
    {
        currentPathHandler.reInput();
        if(!currentPathHandler.isFoundInLocalSystem())
        {
            cout << currentPathHandler.getFullPath() << " is not found in local system" << endl;            return;
        }
        if(1 == step && m_configuration.isExtractStepOn)
        {
            cout<<"Step "<<step<<" (Extract) start | CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
            executeExtractStep(currentPathHandler);
            cout<<"Step "<<step<<" (Extract) done | CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
        }
        else if(2 == step && m_configuration.isCombineAndSortStepOn)
        {
            cout<<"Step "<<step<<" (CombineAndSort) start | CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
            executeCombineAndSortStep(currentPathHandler);
            cout<<"Step "<<step<<" (CombineAndSort) done | CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
        }
        else if(3 == step)
        {
            if(m_configuration.isGrepStepOn)
            {
                cout<<"Step "<<step<<" (Grep) start | CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
                executeGrep(currentPathHandler);
                cout<<"Step "<<step<<" (Grep) done | CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
            }
            if(m_configuration.isCropStepOn)
            {

            }
        }
    }
}

void StepHandler::executeExtractStep(AlbaWindowsPathHandler & currentPathHandler) const
{
    cout<<"executeExtractStep "<<currentPathHandler.getFullPath()<<endl;
    AprgFileExtractor fileExtractor(m_configuration.extractGrepCondition);
    if(currentPathHandler.isDirectory())
    {
        fileExtractor.extractAllRelevantFiles(currentPathHandler.getFullPath());
    }
    else if(fileExtractor.isRecognizedCompressedFile(currentPathHandler.getExtension()))
    {
        fileExtractor.extractAllRelevantFiles(currentPathHandler.getFullPath());
        currentPathHandler.input(currentPathHandler.getDirectory() + R"(\)" + currentPathHandler.getFilenameOnly());
    }
    else
    {        cout<<"Extraction step did not proceed. CurrentPath: "<<currentPathHandler.getFullPath()<<endl;
    }
}

void StepHandler::executeCombineAndSortStep(AlbaWindowsPathHandler & currentPathHandler) const
{
    if(currentPathHandler.isDirectory())
    {
        m_configuration.btsLogSorterConfiguration.m_condition = m_configuration.acceptedFilesGrepCondition;
        tcomToolsBackend::BtsLogSorter btsLogSorter(m_configuration.btsLogSorterConfiguration);
        btsLogSorter.processDirectory(currentPathHandler.getDirectory());
        currentPathHandler.goUp();
        currentPathHandler.input(currentPathHandler.getDirectory() + R"(\sorted.log)");
        btsLogSorter.saveLogsToOutputFile(currentPathHandler.getFullPath());
    }
    else    {
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
        cout << "Grep this file: " << currentPathHandler.getFullPath() << endl;
        ifstream inputFileStream(currentPathHandler.getFullPath());
        currentPathHandler.input(currentPathHandler.getDirectory() + R"(\)" + m_configuration.getGrepFileName());
        ofstream outputFileStream(currentPathHandler.getFullPath());
        AlbaFileReader fileReader(inputFileStream);
        while(fileReader.isNotFinished())        {
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
