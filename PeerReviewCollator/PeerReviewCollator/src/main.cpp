#include <AlbaWindowsPathHandler.hpp>
#include <PeerReviewCollator.hpp>
#include <iostream>
#include <string>

using namespace alba;
using namespace std;

bool isDirectoryNotValid(string const& directoryPath)
{
    AlbaWindowsPathHandler directoryPathHandler;
    directoryPathHandler.inputPath(directoryPath);
    if(!directoryPathHandler.isFoundInLocalSystem())
    {
        cout<<"Directory: ["<<directoryPath<<"] is not found in local system"<<endl;
        return true;
    }
    if(!directoryPathHandler.isDirectory())
    {
        cout<<"Directory: ["<<directoryPath<<"] is not a directory"<<endl;
        return true;
    }
    return false;
}

int main()
{
    constexpr int bufferSize = 1000;
    char buffer[bufferSize];
    string inputDirectory, outputDirectory;

    cout<<"PeerReviewCollator"<<endl<<endl;
    cout<<"Enter input directory(directory which contains all input csv files): "<<endl;
    cin.getline(buffer, bufferSize);
    inputDirectory = buffer;
    if(isDirectoryNotValid(inputDirectory))
    {
        return 1;
    }

    cout<<"Enter output directory(directory which will contain all output csv files): "<<endl;
    cin.getline(buffer, bufferSize);
    outputDirectory = buffer;
    if(isDirectoryNotValid(outputDirectory))
    {
        return 1;
    }

    cout<<endl;
    PeerReviewCollator collator;
    collator.processDirectory(inputDirectory);
    collator.generateOutput(outputDirectory);
    return 0;
}
