#include "AprgModeling.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <Randomizer/AlbaRandomizer.hpp>
#include <String/AlbaStringHelper.hpp>
#include <gsl/gsl_multifit.h>

#include <algorithm>
#include <iostream>

using namespace std;

namespace alba
{

AprgModeling::AprgModeling()
    : m_columnsForX(0)
    , m_numberOfSamples(0)
{}

void AprgModeling::clear()
{
    clearOtherData();
    clearDataBuffersForModeling();
    clearDataBuffersForValidation();
    clearRetrievedData();
}

unsigned int AprgModeling::getNumberOfSamples() const
{
    return m_numberOfSamples;
}

AprgModeling::Coefficients AprgModeling::getCoefficients() const
{
    return m_coefficients;
}

void AprgModeling::retrieveDataFromFileWithFileFormat1(string const& filePath)
{
    ifstream inputFile(filePath);
    AlbaFileReader fileReader(inputFile);
    fileReader.getLineAndIgnoreWhiteSpaces(); // Get Headers
    while(fileReader.isNotFinished())
    {
        string lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        stringHelper::strings itemsFound;
        stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(itemsFound, lineInFile, ",");

        if(!itemsFound.empty())
        {
            m_columnsForX = max(m_columnsForX, itemsFound.size()-1);
            stringHelper::strings::const_iterator it(itemsFound.begin());
            m_retrievedDataForY.emplace_back(stringHelper::convertStringToNumber<double>(*it));
            it++;
            for_each(it, itemsFound.cend(), [&](string const& item)
            {
                m_retrievedDataForX.emplace_back(stringHelper::convertStringToNumber<double>(item));
            });
            m_numberOfSamples++;
        }
    }
}

void AprgModeling::retrieveDataFromFileWithFileFormat2(string const& filePath)
{
    ifstream inputFile(filePath);
    AlbaFileReader fileReader(inputFile);
    fileReader.getLineAndIgnoreWhiteSpaces(); // Get Headers
    bool isLineWithYValues(true);
    DataBuffer reversedCoordinates;
    unsigned int reversedCoordinatesColumns(0);
    unsigned int reversedCoordinatesRows(0);
    while(fileReader.isNotFinished())
    {
        string lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        stringHelper::strings itemsFound;
        stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(itemsFound, lineInFile, ",");

        if(!itemsFound.empty())
        {
            if(isLineWithYValues)
            {
                stringHelper::strings::const_iterator it(itemsFound.begin());
                it++;
                for_each(it, itemsFound.cend(), [&](string const& item)
                {
                    m_retrievedDataForY.emplace_back(stringHelper::convertStringToNumber<double>(item));
                });
                isLineWithYValues=false;
            }
            else
            {
                reversedCoordinatesColumns = max(reversedCoordinatesColumns, itemsFound.size()-1);
                stringHelper::strings::const_iterator it(itemsFound.begin());
                it++;
                for_each(it, itemsFound.cend(), [&](string const& item)
                {
                    reversedCoordinates.emplace_back(stringHelper::convertStringToNumber<double>(item));
                });
                reversedCoordinatesRows++;
            }
        }
    }
    for(unsigned int i=0; i<reversedCoordinatesColumns; i++)
    {
        for(unsigned int j=0; j<reversedCoordinatesRows; j++)
        {
            m_retrievedDataForX.emplace_back(reversedCoordinates[getIndex(i,j, reversedCoordinatesColumns)]);
        }
    }
    m_columnsForX = reversedCoordinatesRows;
    m_numberOfSamples = reversedCoordinatesColumns;
}

void AprgModeling::saveRetrievedDataToModelingDataRandomly(unsigned int numberOfSamples)
{
    saveRetrievedDataToDataBufferRandomly(m_modelingDataForX, m_modelingDataForY, numberOfSamples);
}

void AprgModeling::saveRetrievedDataToValidationDataRandomly(unsigned int numberOfSamples)
{
    saveRetrievedDataToDataBufferRandomly(m_validationDataForX, m_validationDataForY, numberOfSamples);
}

void AprgModeling::saveAllRetrievedDataToModelingData(unsigned int numberOfSamples)
{
    saveAllRetrievedDataToDataBuffer(m_modelingDataForX, m_modelingDataForY, numberOfSamples);
}

void AprgModeling::saveAllRetrievedDataToValidationData(unsigned int numberOfSamples)
{
    saveAllRetrievedDataToDataBuffer(m_validationDataForX, m_validationDataForY, numberOfSamples);
}

void AprgModeling::model()
{
    calculateCoefficients();
}

AprgModeling::ValidationResult AprgModeling::validate()
{
    ValidationResult result;
    vector<double> calculationDataBuffer;

    unsigned int dataHeight = m_validationDataForY.size();
    unsigned int dataWidthForX = m_columnsForX-1;
    unsigned int index=0;
    for(unsigned int j=0; j<dataHeight; j++)
    {
        double yPredicted=0;
        for (unsigned int i=0; i < dataWidthForX; i++)
        {
            yPredicted += m_validationDataForX[index]*m_coefficients[i];
            index++;
        }
        calculationDataBuffer.emplace_back(yPredicted);
    }

    for(unsigned int j=0; j<dataHeight; j++)
    {
        calculationDataBuffer[j]=m_validationDataForY[j]-calculationDataBuffer[j];
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

void AprgModeling::printRetrievedData()
{
    printData(m_retrievedDataForX, m_retrievedDataForY);
}

void AprgModeling::printModelingData()
{
    printData(m_modelingDataForX, m_modelingDataForY);
}

void AprgModeling::printValidationData()
{
    printData(m_validationDataForX, m_validationDataForY);
}

void AprgModeling::printData(DataBuffer & dataBufferForX, DataBuffer & dataBufferForY)
{
    for(unsigned int j=0; j<dataBufferForY.size(); j++)
    {
        cout<<dataBufferForY[j]<<" || ";
        for(unsigned int i=0; i<m_columnsForX; i++)
        {
            cout<<dataBufferForX[getIndexForXData(i,j)]<<", ";
        }
        cout<<endl;
    }
}

void AprgModeling::saveRetrievedDataToDataBufferRandomly(DataBuffer & dataBufferForX, DataBuffer & dataBufferForY, unsigned int numberOfSamples)
{
    AlbaRandomizer randomizer;
    dataBufferForX.clear();
    dataBufferForY.clear();
    for(unsigned int j=0; j<numberOfSamples; j++)
    {
        int randomRow(randomizer.getRandomValueInUniformDistribution(0, m_numberOfSamples-1));
        dataBufferForY.emplace_back(m_retrievedDataForY[randomRow]);
        for(unsigned int i=0; i<m_columnsForX; i++)
        {
            dataBufferForX.emplace_back(m_retrievedDataForX[getIndexForXData(i,randomRow)]);
        }
    }
}

void AprgModeling::saveAllRetrievedDataToDataBuffer(DataBuffer & dataBufferForX, DataBuffer & dataBufferForY, unsigned int numberOfSamples)
{
    dataBufferForX.clear();
    dataBufferForY.clear();
    for(unsigned int j=0; j<numberOfSamples; j++)
    {
        dataBufferForY.emplace_back(m_retrievedDataForY[j]);
        for(unsigned int i=0; i<m_columnsForX; i++)
        {
            dataBufferForX.emplace_back(m_retrievedDataForX[getIndexForXData(i,j)]);
        }
    }
}

void AprgModeling::calculateCoefficients()
{
    int dataHeight = m_modelingDataForY.size();
    int dataWidth = m_columnsForX;
    double chisq;
    int j, i;

    gsl_matrix *xModelingData, *calculatedCovariance;
    gsl_vector *yModelingData, *calculatedCoefficients;

    xModelingData = gsl_matrix_alloc(dataHeight, dataWidth);
    yModelingData = gsl_vector_alloc(dataHeight);
    calculatedCoefficients = gsl_vector_alloc(dataWidth);
    calculatedCovariance = gsl_matrix_alloc(dataWidth, dataWidth);

    j=0;
    for(double currentValue:m_modelingDataForY)
    {
        gsl_vector_set(yModelingData, j, currentValue);
        j++;
    }

    j=0, i=0;
    for(double currentValue:m_modelingDataForX)
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
    m_modelingDataForX.clear();
    m_modelingDataForY.clear();
}

void AprgModeling::clearDataBuffersForValidation()
{
    m_validationDataForX.clear();
    m_validationDataForY.clear();
}

void AprgModeling::clearRetrievedData()
{
    m_retrievedDataForX.clear();
    m_retrievedDataForY.clear();
}

unsigned int AprgModeling::getIndexForXData(unsigned int const i, unsigned int const j) const
{
    return (j*m_columnsForX)+i;
}

unsigned int AprgModeling::getIndex(unsigned int const i, unsigned int const j, unsigned int const numberOfColumns) const
{
    return (j*numberOfColumns)+i;
}


void AprgModeling::clearOtherData()
{
    m_columnsForX=0;
    m_numberOfSamples=0;
}

}
