#include "MeanSquareErrorCalculator.hpp"

#include <File/AlbaFileReader.hpp>
#include <Randomizer/AlbaRandomizer.hpp>
#include <String/AlbaStringHelper.hpp>
#include <algorithm>
#include <gsl/gsl_multifit.h>
#include <iomanip>
#include <iostream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <windows.h>

using namespace alba;
using namespace std;

namespace mse
{

MeanSquareErrorCalculator::MeanSquareErrorCalculator()
    : m_columns(0)
    , m_rows(0)
    , m_meanSquareTotalForRuns(0)
    , m_rootMeanSquareTotalForRuns(0)
    , m_runCount(0)
{}

void MeanSquareErrorCalculator::clearTrainingAndValidation()
{
    m_trainingForXData.clear();
    m_trainingForYData.clear();
    m_validationForXData.clear();
    m_validationForYData.clear();
}

void MeanSquareErrorCalculator::clear()
{
    m_columns=0;
    m_rows=0;
    m_meanSquareTotalForRuns=0;
    m_rootMeanSquareTotalForRuns=0;
    m_runCount=0;
    clearTrainingAndValidation();
    m_sampleDatabase.clear();
    m_fileDatabase.clear();
}

void MeanSquareErrorCalculator::saveValuesFromFileToDatabase(string const& filePath)
{
    clear();
    AlbaWindowsPathHandler pathHandler(filePath);
    cout<<"processFile -> Processing File: "<<pathHandler.getFile()<<endl;
    ifstream inputFile(filePath);
    AlbaFileReader fileReader(inputFile);
    string firstLine(fileReader.getLineAndIgnoreWhiteSpaces());
    cout<<"Headers: "<<firstLine<<endl;
    while(fileReader.isNotFinished())
    {
        string lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        if(!lineInFile.empty())
        {
            stringHelper::strings itemsFound;
            stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(itemsFound, lineInFile, ",");
            if(m_columns==0)
            {
                m_columns = itemsFound.size();            }
            for_each(itemsFound.begin(), itemsFound.end(), [&](string const& item)
            {
                m_fileDatabase.emplace_back(stringHelper::convertStringToNumber<double>(item));            });
            m_rows++;
        }
    }
}

void MeanSquareErrorCalculator::randomizeSampleDatabase()
{
    AlbaRandomizer randomizer;
    m_sampleDatabase.clear();
    for(int j=0; j<m_rows; j++)
    {
        int row(randomizer.getRandomValueInUniformDistribution(0, m_rows-1));
        for(int i=0; i<m_columns; i++)
        {
            m_sampleDatabase.emplace_back(m_fileDatabase[getDatabaseIndex(i,row)]);
        }
    }
}

void MeanSquareErrorCalculator::performModelingAndValidation()
{
    vector<double> coefficients;
    vector<double> calculationResult;
    calculateCoefficients(coefficients);

    cout<<"coefficients: "<<endl;    printVectorOfDoubles(coefficients);

    int dataHeight = m_validationForYData.size();
    int dataWidthForX = m_columns-1;
    int index=0;
    for(int j=0; j<dataHeight; j++)
    {
        double yPredicted=0;
        for (int i=0; i < dataWidthForX; i++)
        {
            yPredicted += m_validationForXData[index]*coefficients[i];
            index++;
        }
        calculationResult.emplace_back(yPredicted);
    }

    //cout<<"yValidationData: "<<endl;
    //printVectorOfDoubles(m_validationForYData);

    //cout<<"yPredicted: "<<endl;
    //printVectorOfDoubles(calculationResult);

    for(int j=0; j<dataHeight; j++)
    {
        calculationResult[j]=m_validationForYData[j]-calculationResult[j];
    }

    //cout<<"residual: "<<endl;
    //printVectorOfDoubles(calculationResult);

    for(int j=0; j<dataHeight; j++)
    {
        calculationResult[j] = pow(calculationResult[j], 2);
    }

    //cout<<"residual squared: "<<endl;
    //printVectorOfDoubles(calculationResult);

    double totalSquareError(0);
    for(int j=0; j<dataHeight; j++)
    {
        totalSquareError += calculationResult[j];
    }

    double meanSquareError=totalSquareError/calculationResult.size();
    double rootMeanSquareError=pow(meanSquareError, 0.5);

    cout<<"totalSquareError: "<<std::setprecision(20)<<totalSquareError<<endl;
    cout<<"partialResultSize: "<<std::setprecision(20)<<calculationResult.size()<<endl;
    cout<<"meanSquareError: "<<std::setprecision(20)<<meanSquareError<<endl;
    cout<<"rootMeanSquareError: "<<std::setprecision(20)<<rootMeanSquareError<<endl;

    m_meanSquareTotalForRuns += meanSquareError;
    m_rootMeanSquareTotalForRuns += rootMeanSquareError;
    m_runCount++;
}

int MeanSquareErrorCalculator::getNumberOfRows() const
{
    return m_rows;
}

void MeanSquareErrorCalculator::printDatabase() const
{
    for(int j=0; j<m_rows; j++)
    {
        for(int i=0; i<m_columns; i++)
        {
            cout<<"["<<m_sampleDatabase[getDatabaseIndex(i,j)]<<"]";
        }
        cout<<endl;
    }
}

void MeanSquareErrorCalculator::printVectorOfDoubles(vector<double> const & doubles) const
{
    cout.precision(5);
    for(double value : doubles)
    {
        cout<<"["<<value<<"]";
    }
    cout<<endl;
}


void MeanSquareErrorCalculator::printAverageOfSquareErrors() const
{
    cout<<endl;
    cout<<"runCount: "<<m_runCount<<endl;
    cout<<"meanSquareAverageForRuns: "<<std::setprecision(20)<<m_meanSquareTotalForRuns/m_runCount<<endl;
    cout<<"rootMeanSquareAverageForRuns: "<<std::setprecision(20)<<m_rootMeanSquareTotalForRuns/m_runCount<<endl;
}

void MeanSquareErrorCalculator::retrieveTrainingSamples(int start, int end)
{
    int dataWidthForX = m_columns-1;
    for(int j=start; j<end; j++)
    {
        m_trainingForYData.emplace_back(m_sampleDatabase[getDatabaseIndex(0,j)]);
        for(int i=0; i<dataWidthForX; i++)
        {
            m_trainingForXData.emplace_back(m_sampleDatabase[getDatabaseIndex(i+1, j)]);
        }
    }
}

void MeanSquareErrorCalculator::retrieveValidationSamples(int start, int end)
{
    int dataWidthForX = m_columns-1;
    for(int j=start; j<end; j++)
    {
        m_validationForYData.emplace_back(m_sampleDatabase[getDatabaseIndex(0,j)]);
        for(int i=0; i<dataWidthForX; i++)
        {
            m_validationForXData.emplace_back(m_sampleDatabase[getDatabaseIndex(i+1, j)]);
        }
    }
}
void MeanSquareErrorCalculator::calculateCoefficients(vector<double> & coefficients) const
{
    int dataHeight = m_trainingForYData.size();
    int dataWidth = m_columns-1;
    double chisq;
    int j, i;

    gsl_matrix *xTrainingData, *calculatedCovariance;
    gsl_vector *yTrainingData, *calculatedCoefficients;

    xTrainingData = gsl_matrix_alloc(dataHeight, dataWidth);
    yTrainingData = gsl_vector_alloc(dataHeight);
    calculatedCoefficients = gsl_vector_alloc(dataWidth);
    calculatedCovariance = gsl_matrix_alloc(dataWidth, dataWidth);

    j=0;
    for(double currentValue:m_trainingForYData)
    {
        gsl_vector_set(yTrainingData, j, currentValue);
        j++;
    }

    j=0, i=0;
    for(double currentValue:m_trainingForXData)
    {
        gsl_matrix_set(xTrainingData, j, i, currentValue);
        i++;
        if(i>=dataWidth) { j++; i=0; }
    }

    gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc(dataHeight, dataWidth);
    gsl_multifit_linear(xTrainingData, yTrainingData, calculatedCoefficients, calculatedCovariance, &chisq, work);

    for(i=0; i<dataWidth; i++)
    {
        coefficients.emplace_back(gsl_vector_get(calculatedCoefficients, i));
    }

    gsl_multifit_linear_free(work);
    gsl_matrix_free(calculatedCovariance);
    gsl_vector_free(calculatedCoefficients);
    gsl_vector_free(yTrainingData);
    gsl_matrix_free(xTrainingData);
}

int MeanSquareErrorCalculator::getDatabaseIndex(int const x, int const y) const
{
    return (y*m_columns)+x;
}

}
