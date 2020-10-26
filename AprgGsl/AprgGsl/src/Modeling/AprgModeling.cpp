#include "AprgModeling.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <Randomizer/AlbaRandomizer.hpp>
#include <String/AlbaStringHelper.hpp>
#include <gsl/gsl_multifit.h>

#include <windows.h>

#include <algorithm>

using namespace std;

namespace alba
{

AprgModeling::AprgModeling()
    : m_columns(0)
    , m_rows(0)
{}

void AprgModeling::clear()
{
    clearOtherData();
    clearDataBuffersForModeling();
    clearDataBuffersForValidation();
    clearDataBufferForSamples();
    clearDataBufferFromFile();
}

unsigned int AprgModeling::getNumberOfRows() const
{
    return m_rows;
}

AprgModeling::Coefficients AprgModeling::getCoefficients() const
{
    return m_coefficients;
}

void AprgModeling::saveValuesFromFileToFileDataBuffer(string const& filePath)
{
    ifstream inputFile(filePath);
    AlbaFileReader fileReader(inputFile);
    fileReader.getLineAndIgnoreWhiteSpaces(); // Get Headers
    while(fileReader.isNotFinished())
    {
        string lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        if(!lineInFile.empty())
        {
            stringHelper::strings itemsFound;
            stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(itemsFound, lineInFile, ",");
            if(m_columns==0)
            {
                m_columns = itemsFound.size();
            }
            for_each(itemsFound.begin(), itemsFound.end(), [&](string const& item)
            {
                m_dataBufferFromFile.emplace_back(stringHelper::convertStringToNumber<double>(item));
            });
            m_rows++;
        }
    }
}

void AprgModeling::fillSampleDataBufferFromFileDataBufferRandomly()
{
    AlbaRandomizer randomizer;
    m_dataBufferForSamples.clear();
    for(unsigned int j=0; j<m_rows; j++)
    {
        int row(randomizer.getRandomValueInUniformDistribution(0, m_rows-1));
        for(unsigned int i=0; i<m_columns; i++)
        {
            m_dataBufferForSamples.emplace_back(m_dataBufferFromFile[getIndex(i,row)]);
        }
    }
}

void AprgModeling::divideSamplesToModelingAndValidation(unsigned int modelingSamplesPercentage, unsigned validationSamplesPercentage)
{
     unsigned int modelingSamples = (unsigned int)(((double)modelingSamplesPercentage*getNumberOfRows())/(modelingSamplesPercentage+validationSamplesPercentage));
     fillModelingDataBufferFromSamplesDataBuffer(0, modelingSamples);
     fillValidationDataBufferFromSamplesDataBuffer(modelingSamples, getNumberOfRows());
}

void AprgModeling::model()
{
    calculateCoefficients();
}

AprgModeling::ValidationResult AprgModeling::validate()
{
    ValidationResult result;
    vector<double> calculationDataBuffer;

    unsigned int dataHeight = m_dataBufferForValidationForY.size();
    unsigned int dataWidthForX = m_columns-1;
    unsigned int index=0;
    for(unsigned int j=0; j<dataHeight; j++)
    {
        double yPredicted=0;
        for (unsigned int i=0; i < dataWidthForX; i++)
        {
            yPredicted += m_dataBufferForValidationForX[index]*m_coefficients[i];
            index++;
        }
        calculationDataBuffer.emplace_back(yPredicted);
    }

    for(unsigned int j=0; j<dataHeight; j++)
    {
        calculationDataBuffer[j]=m_dataBufferForValidationForY[j]-calculationDataBuffer[j];
    }

    for(unsigned int j=0; j<dataHeight; j++)
    {
        calculationDataBuffer[j] = pow(calculationDataBuffer[j], 2);
    }

    double totalSquareError(0);
    for(unsigned int j=0; j<dataHeight; j++)
    {
        totalSquareError += calculationDataBuffer[j];
    }

    double meanSquareError=totalSquareError/calculationDataBuffer.size();
    double rootMeanSquareError=pow(meanSquareError, 0.5);

    result.totalSquareError = totalSquareError;
    result.resultSize = calculationDataBuffer.size();
    result.meanSquareError = meanSquareError;
    result.rootMeanSquareError = rootMeanSquareError;
    return result;
}

void AprgModeling::fillModelingDataBufferFromSamplesDataBuffer(unsigned int start, unsigned int end)
{
    unsigned int dataWidthForX = m_columns-1;
    for(unsigned int j=start; j<end; j++)
    {
        m_dataBufferForModelingForY.emplace_back(m_dataBufferForSamples[getIndex(0,j)]);
        for(unsigned int i=0; i<dataWidthForX; i++)
        {
            m_dataBufferForModelingForX.emplace_back(m_dataBufferForSamples[getIndex(i+1, j)]);
        }
    }
}

void AprgModeling::fillValidationDataBufferFromSamplesDataBuffer(unsigned int start, unsigned int end)
{
    unsigned int dataWidthForX = m_columns-1;
    for(unsigned int j=start; j<end; j++)
    {
        m_dataBufferForValidationForY.emplace_back(m_dataBufferForSamples[getIndex(0,j)]);
        for(unsigned int i=0; i<dataWidthForX; i++)
        {
            m_dataBufferForValidationForX.emplace_back(m_dataBufferForSamples[getIndex(i+1, j)]);
        }
    }
}

void AprgModeling::calculateCoefficients()
{
    int dataHeight = m_dataBufferForModelingForY.size();
    int dataWidth = m_columns-1;
    double chisq;
    int j, i;

    gsl_matrix *xModelingData, *calculatedCovariance;
    gsl_vector *yModelingData, *calculatedCoefficients;

    xModelingData = gsl_matrix_alloc(dataHeight, dataWidth);
    yModelingData = gsl_vector_alloc(dataHeight);
    calculatedCoefficients = gsl_vector_alloc(dataWidth);
    calculatedCovariance = gsl_matrix_alloc(dataWidth, dataWidth);

    j=0;
    for(double currentValue:m_dataBufferForModelingForY)
    {
        gsl_vector_set(yModelingData, j, currentValue);
        j++;
    }

    j=0, i=0;
    for(double currentValue:m_dataBufferForModelingForX)
    {
        gsl_matrix_set(xModelingData, j, i, currentValue);
        i++;
        if(i>=dataWidth) { j++; i=0; }
    }

    gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc(dataHeight, dataWidth);
    gsl_multifit_linear(xModelingData, yModelingData, calculatedCoefficients, calculatedCovariance, &chisq, work);

    for(i=0; i<dataWidth; i++)
    {
        m_coefficients.emplace_back(gsl_vector_get(calculatedCoefficients, i));
    }

    gsl_multifit_linear_free(work);
    gsl_matrix_free(calculatedCovariance);
    gsl_vector_free(calculatedCoefficients);
    gsl_vector_free(yModelingData);
    gsl_matrix_free(xModelingData);
}

void AprgModeling::clearDataBuffersForModeling()
{
    m_dataBufferForModelingForX.clear();
    m_dataBufferForModelingForY.clear();
}

void AprgModeling::clearDataBuffersForValidation()
{
    m_dataBufferForValidationForX.clear();
    m_dataBufferForValidationForY.clear();
}

void AprgModeling::clearDataBufferForSamples()
{
    m_dataBufferForSamples.clear();
}

void AprgModeling::clearDataBufferFromFile()
{
    m_dataBufferFromFile.clear();
}

unsigned int AprgModeling::getIndex(unsigned int const x, unsigned int const y) const
{
    return (y*m_columns)+x;
}

void AprgModeling::clearOtherData()
{
    m_columns=0;
    m_rows=0;
}

}


