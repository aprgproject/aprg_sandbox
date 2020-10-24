#include <File/AlbaFileReader.hpp>
#include <AprgFileExtractor.hpp>
#include <String/AlbaStringHelper.hpp>
#include <BtsLogSorter.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <fstream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <StepHandler.hpp>
#include <string>

namespace alba
{
namespace ProgressCounters
{
extern int grepProcessProgress;
extern int cropProcessProgress;
extern int numberOfStepsEnabled;
extern void resetProgressCounters();
}
}

using namespace alba;
using namespace std;

namespace tcomToolsGui
{

StepHandler::StepHandler()
{}

void StepHandler::execute(TcomToolsConfiguration const& configuration) const
{
    AlbaWindowsPathHandler currentPathHandler(configuration.inputFileOrDirectory);
    ProgressCounters::resetProgressCounters();
    ProgressCounters::numberOfStepsEnabled = configuration.isExtractStepOn + configuration.isCombineAndSortStepOn + configuration.isGrepStepOn + configuration.isCropStepOn;
    for(int step=1; step<5; step++)
    {
        currentPathHandler.reInput();
        if(!currentPathHandler.isFoundInLocalSystem())
        {
            cout << currentPathHandler.getFullPath() << " is not found in local system" << endl;
            return;
        }
        if(1 == step && configuration.isExtractStepOn)
        {
            currentPathHandler.input(executeExtractStep(configuration, currentPathHandler.getFullPath()));
        }
        else if(2 == step && configuration.isCombineAndSortStepOn)
        {
            currentPathHandler.input(executeCombineAndSortStep(configuration, currentPathHandler.getFullPath()));
        }
        else if(3 == step && configuration.isGrepStepOn)
        {
            currentPathHandler.input(executeGrepStep(configuration, currentPathHandler.getFullPath()));
        }
        else if(4 == step && configuration.isCropStepOn)
        {
            currentPathHandler.input(executeCropStep(configuration, currentPathHandler.getFullPath()));
        }
    }
}

string StepHandler::executeExtractStep(TcomToolsConfiguration const& configuration, string const& inputPath) const
{
    cout<<" (Extract) start | Input path: "<<inputPath<<endl;
    AprgFileExtractor fileExtractor(configuration.extractGrepCondition);
    AlbaWindowsPathHandler pathHandler(inputPath);
    string outputPath(inputPath);
    if(pathHandler.isDirectory())
    {
        fileExtractor.extractAllRelevantFiles(pathHandler.getFullPath());
    }
    else if(fileExtractor.isRecognizedCompressedFile(pathHandler.getExtension()))
    {
        fileExtractor.extractAllRelevantFiles(pathHandler.getFullPath());
        pathHandler.input(pathHandler.getDirectory() + R"(\)" + pathHandler.getFilenameOnly());
        outputPath = pathHandler.getFullPath();
    }
    else
    {
        cout<<"Extraction step did not proceed. Current path: "<<pathHandler.getFullPath()<<endl;
    }
    cout<<" (Extract) done | Output path: "<<outputPath<<endl;
    return outputPath;
}

string StepHandler::executeCombineAndSortStep(TcomToolsConfiguration const& configuration, string const& inputPath) const
{
    cout<<" (CombineAndSort) start | Input path: "<<inputPath<<endl;
    AlbaWindowsPathHandler pathHandler(inputPath);
    string outputPath(inputPath);
    if(pathHandler.isDirectory())
    {
        tcomToolsBackend::BtsLogSorterConfiguration sorterConfiguration(configuration.btsLogSorterConfiguration);
        sorterConfiguration.m_condition = configuration.acceptedFilesGrepCondition;
        tcomToolsBackend::BtsLogSorter btsLogSorter(sorterConfiguration);
        btsLogSorter.processDirectory(pathHandler.getDirectory());
        pathHandler.goUp();
        pathHandler.input(pathHandler.getDirectory() + R"(\sorted.log)");
        outputPath = pathHandler.getFullPath();
        btsLogSorter.saveLogsToOutputFile(outputPath);
    }
    else
    {
        cout<<"Combine and sort step did not proceed. Current path: "<<pathHandler.getFullPath()<<endl;
    }
    cout<<" (CombineAndSort) done | Output path: "<<inputPath<<endl;
    return outputPath;
}

string StepHandler::executeGrepStep(TcomToolsConfiguration const& configuration, string const& inputPath) const
{
    cout<<" (Grep) start | Input path: "<<inputPath<<endl;
    AlbaWindowsPathHandler pathHandler(inputPath);
    string outputPath(inputPath);
    AlbaGrepStringEvaluator evaluator(configuration.getGrepCondition());
    if(evaluator.isInvalid())
    {
        cout << "Grep condition is invalid. Grep condition: " << configuration.getGrepCondition() << " Error message: " << evaluator.getErrorMessage() << endl;
    }
    else if(pathHandler.isFile())
    {
        outputPath = grepFile(configuration, pathHandler.getFullPath());
    }
    else
    {
        cout<<"Grep step did not proceed. Current path: "<<pathHandler.getFullPath()<<endl;
    }
    cout<<" (Grep) done | Output path: "<<outputPath<<endl;
    return outputPath;
}

string StepHandler::grepFile(TcomToolsConfiguration const& configuration, string const& inputPath) const
{
    AlbaGrepStringEvaluator evaluator(configuration.getGrepCondition());
    AlbaWindowsPathHandler pathHandler(inputPath);
    ifstream inputFileStream(pathHandler.getFullPath());
    pathHandler.input(pathHandler.getDirectory() + R"(\)" + configuration.getGrepFileName());
    ofstream outputFileStream(pathHandler.getFullPath());
    AlbaFileReader fileReader(inputFileStream);
    double sizeOfFile = fileReader.getFileSize();
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(evaluator.evaluate(lineInLogs))
        {
            outputFileStream << lineInLogs << endl;
        }
        ProgressCounters::grepProcessProgress = fileReader.getCurrentLocation()*100/sizeOfFile;
    }
    ProgressCounters::grepProcessProgress = 100;
    return pathHandler.getFullPath();
}

string StepHandler::executeCropStep(TcomToolsConfiguration const& configuration, string const& inputPath) const
{
    cout<<" (Crop) start | Input path: "<<inputPath<<endl;
    AlbaWindowsPathHandler pathHandler(inputPath);
    string outputPath(inputPath);
    if(pathHandler.isFile())
    {
        double foundLocation(getLocationOfPriotizedPrint(configuration, inputPath));
        if(-1 != foundLocation)
        {
            outputPath = cropFile(configuration, pathHandler.getFullPath(), foundLocation);
        }
        else
        {
            cout<<"Crop step did not proceed. Prioritized log print not found: "<<configuration.prioritizedLogPrint<<endl;
        }
    }
    else
    {
        cout<<"Crop step did not proceed. Current path: "<<pathHandler.getFullPath()<<endl;
    }
    cout<<" (Crop) done | Output path: "<<outputPath<<endl;
    return outputPath;
}

string StepHandler::cropFile(TcomToolsConfiguration const& configuration, string const& inputPath, double foundLocation) const
{
    LocationsInFile locations(getLocationsInFile(configuration, foundLocation));
    AlbaWindowsPathHandler pathHandler(inputPath);
    ifstream inputFileStream(pathHandler.getFullPath());
    pathHandler.input(pathHandler.getDirectory() + R"(\)" + pathHandler.getFilenameOnly() + "Cropped.log");
    ofstream outputFileStream(pathHandler.getFullPath());
    AlbaFileReader fileReader(inputFileStream);
    fileReader.moveLocation(locations.startLocation);
    fileReader.getLineAndIgnoreWhiteSpaces();
    double locationDifference = locations.endLocation-locations.startLocation;
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        double currentLocation = fileReader.getCurrentLocation();
        if(currentLocation < locations.endLocation)
        {
            outputFileStream << lineInLogs << endl;
        }
        else
        {
            break;
        }
        ProgressCounters::cropProcessProgress = 50 + (currentLocation-locations.startLocation)*50/locationDifference;
    }
    ProgressCounters::cropProcessProgress = 100;
    return pathHandler.getFullPath();
}

double StepHandler::getLocationOfPriotizedPrint(TcomToolsConfiguration const& configuration, string const& inputPath) const
{
    double foundLocation(-1);
    AlbaWindowsPathHandler pathHandler(inputPath);
    ifstream inputFileStream(pathHandler.getFullPath());
    AlbaFileReader fileReader(inputFileStream);
    double sizeOfFile = fileReader.getFileSize();
    while(fileReader.isNotFinished())
    {
        string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInLogs, configuration.prioritizedLogPrint))
        {
            cout<<"Found prioritized log print in input file. Log print: "<<lineInLogs<<endl;
            foundLocation = fileReader.getCurrentLocation();
            break;
        }
        ProgressCounters::cropProcessProgress = fileReader.getCurrentLocation()*50/sizeOfFile;
    }
    ProgressCounters::cropProcessProgress = 50;
    return foundLocation;
}

StepHandler::LocationsInFile StepHandler::getLocationsInFile(TcomToolsConfiguration const& configuration, double foundLocation) const
{
    LocationsInFile locations;
    double outputSize = 1000000 * configuration.cropSize;
    double startingLocation = foundLocation - (outputSize/2);
    locations.startLocation = (startingLocation<0) ? 0 : startingLocation;
    locations.endLocation = startingLocation + outputSize;
    return locations;
}

}
