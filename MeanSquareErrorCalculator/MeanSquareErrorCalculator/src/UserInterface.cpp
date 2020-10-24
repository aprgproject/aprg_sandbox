#include <UserInterface.hpp>

#include <AlbaStringHelper.hpp>
#include <iostream>
#include <MeanSquareErrorCalculator.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <vector>

using namespace alba;
using namespace std;

namespace mse
{

void UserInterface::execute()
{
    int mode(getModeInput());
    if(1 == mode)
    {
        executeRandomSubSampling();
    }
    else if(2 == mode)
    {
        executeKFold();
    }
}

void UserInterface::executeRandomSubSampling()
{
    while (1)
    {
        string filePath(getFilePathInput());
        cout<<"Number of iterations: ";
        int iterations(getNumberFromInput());

        MeanSquareErrorCalculator gsl;
        gsl.saveValuesFromFileToDatabase(filePath);

        int samples(gsl.getNumberOfRows());
        cout<<"Number of samples: "<<samples<<endl;

        cout<<"Number of samples for training: ";
        int trainingSamples(getNumberFromInput());

        if(trainingSamples>=samples)
        {
            cout<<"Number of samples for training is more than number of samples."<<endl;
            continue;
        }

        int validationSamples(samples-trainingSamples);
        cout<<"Number of samples for validation: "<<validationSamples<<endl;

        for(int i=0; i<iterations; i++)
        {
            gsl.randomizeSampleDatabase();
            gsl.retrieveTrainingSamples(0,trainingSamples);
            gsl.retrieveValidationSamples(trainingSamples, trainingSamples+validationSamples);
            gsl.performRegression();
        }
        gsl.printAverageOfSquareErrors();
    }
}

void UserInterface::executeKFold()
{
    while (1)
    {
        string filePath(getFilePathInput());
        cout<<"Number of folds: ";
        int folds(getNumberFromInput());

        MeanSquareErrorCalculator gsl;
        gsl.saveValuesFromFileToDatabase(filePath);

        int samples(gsl.getNumberOfRows());
        cout<<"Number of samples: "<<samples<<endl;

        vector<int> splitIndex;
        for(int i=0; i<folds; i++)
        {
            splitIndex.emplace_back(round(((double)i)*samples/folds));
        }
        splitIndex.emplace_back(samples);

        for(int i=0; i<folds; i++)
        {
            cout<<"Fold "<<i<<" Samples:["<<splitIndex[i]<<", "<<splitIndex[i+1]<<")"<<endl;
        }

        gsl.randomizeSampleDatabase();
        for(int i=0; i<folds; i++)
        {
            gsl.clearTrainingAndValidation();
            gsl.retrieveTrainingSamples(0,splitIndex[i]);
            gsl.retrieveValidationSamples(splitIndex[i],splitIndex[i+1]);
            gsl.retrieveTrainingSamples(splitIndex[i+1],samples);
            gsl.performRegression();
        }
        gsl.printAverageOfSquareErrors();
    }
}

int UserInterface::getModeInput()
{
    while (1)
    {
        cout<<"Enter mode (1-RandomSubSampling, 2->K-Fold)"<<endl;
        int mode(getNumberFromInput());
        if(1 == mode || 2 == mode)
        {
            return mode;
        }
        else
        {
            cout<<"Mode not recognized"<<endl;
        }
    }
}

string UserInterface::getFilePathInput()
{
    while (1)
    {
        cout<<"Input file path: ";
        cin.getline(buffer, bufferSize);
        string pathString(buffer);
        AlbaWindowsPathHandler filePath(pathString);
        if(filePath.isFoundInLocalSystem() && filePath.isFile())
        {
            return filePath.getFullPath();
        }
        else
        {
            cout<<"File not found"<<endl;
        }
    }
}

int UserInterface::getNumberFromInput()
{
    cin.getline(buffer, bufferSize);
    return stringHelper::convertStringToNumber<int>(string(buffer));
}

}
