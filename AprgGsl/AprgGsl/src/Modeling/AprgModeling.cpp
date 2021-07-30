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
{}

unsigned int AprgModeling::getNumberOfSamples() const
{
    return m_retrievedDataForY.getRows();
}

AprgModeling::MatrixOfDoubles AprgModeling::getCoefficients() const
{
    return m_coefficients;
}

void AprgModeling::retrieveDataFromFileWithFileFormat1(string const& filePath)
{
    VectorOfDoubles retrievedDataForX, retrievedDataForY;
    unsigned int columnsForX = 0, numberOfSamples = 0;
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
            columnsForX = max(columnsForX, itemsFound.size()-1);
            stringHelper::strings::const_iterator it(itemsFound.begin());
            retrievedDataForY.emplace_back(stringHelper::convertStringToNumber<double>(*it));
            it++;
            for_each(it, itemsFound.cend(), [&](string const& item)
            {
                retrievedDataForX.emplace_back(stringHelper::convertStringToNumber<double>(item));
            });
            numberOfSamples++;
        }
    }
    saveRetrievedDataForXAndY(columnsForX, numberOfSamples, retrievedDataForX, retrievedDataForY);
}

void AprgModeling::retrieveDataFromFileWithFileFormat2(string const& filePath)
{
    VectorOfDoubles retrievedDataForX, retrievedDataForY;
    unsigned int columnsForX = 0, numberOfSamples = 0;
    bool isLineWithYValues(true);
    VectorOfDoubles reversedCoordinates;
    unsigned int reversedCoordinatesColumns(0);
    unsigned int reversedCoordinatesRows(0);

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
            if(isLineWithYValues)
            {
                stringHelper::strings::const_iterator it(itemsFound.begin());
                it++;
                for_each(it, itemsFound.cend(), [&](string const& item)
                {
                    retrievedDataForY.emplace_back(stringHelper::convertStringToNumber<double>(item));
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
            retrievedDataForX.emplace_back(reversedCoordinates[getIndex(i,j, reversedCoordinatesColumns)]);
        }
    }
    columnsForX = reversedCoordinatesRows;
    numberOfSamples = reversedCoordinatesColumns;
    saveRetrievedDataForXAndY(columnsForX, numberOfSamples, retrievedDataForX, retrievedDataForY);
}

void AprgModeling::saveRetrievedDataForXAndY(
        unsigned int numberOfIndicators,
        unsigned int numberOfSamples,
        VectorOfDoubles const& retrievedDataForX,
        VectorOfDoubles const& retrievedDataForY)
{
    copyVectorToMatrix(numberOfIndicators, numberOfSamples, retrievedDataForX, m_retrievedDataForX);
    copyVectorToMatrix(1, numberOfSamples, retrievedDataForY, m_retrievedDataForY);
}

void AprgModeling::saveRetrievedDataToModelingDataRandomly(unsigned int numberOfSamples)
{
    saveRetrievedDataToMatrixRandomly(m_modelingDataForX, m_modelingDataForY, numberOfSamples);
}

void AprgModeling::saveRetrievedDataToValidationDataRandomly(unsigned int numberOfSamples)
{
    saveRetrievedDataToMatrixRandomly(m_validationDataForX, m_validationDataForY, numberOfSamples);
}

void AprgModeling::saveRetrievedDataToModelingData(unsigned int numberOfSamples)
{
    saveRetrievedDataToMatrix(m_modelingDataForX, m_modelingDataForY, numberOfSamples);
}

void AprgModeling::saveRetrievedDataToValidationData(unsigned int numberOfSamples)
{
    saveRetrievedDataToMatrix(m_validationDataForX, m_validationDataForY, numberOfSamples);
}

void AprgModeling::modelUsingLeastSquares()
{
    calculateCoefficientsUsingLeastSquares();
}

AprgModeling::ValidationResult AprgModeling::validate()
{
    ValidationResult result;
    vector<double> calculationDataBuffer;

    unsigned int dataHeight = m_validationDataForY.getRows();
    unsigned int dataWidthForX = m_validationDataForX.getColumns();//why minus 1 lets remove it
    unsigned int index=0;
    for(unsigned int j=0; j<dataHeight; j++)
    {
        double yPredicted=0;
        for (unsigned int i=0; i < dataWidthForX; i++)
        {
            yPredicted += m_validationDataForX.get(i, j)*m_coefficients.get(i, 0);
            index++;
        }
        calculationDataBuffer.emplace_back(yPredicted);
    }

    for(unsigned int j=0; j<dataHeight; j++)
    {
        calculationDataBuffer[j]=m_validationDataForY.get(0, j)-calculationDataBuffer[j];
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
    cout<<"RetrievedData:"<<endl;
    printData(m_retrievedDataForX, m_retrievedDataForY);
}

void AprgModeling::printModelingData()
{
    cout<<"ModelingData:"<<endl;
    printData(m_modelingDataForX, m_modelingDataForY);
}

void AprgModeling::printValidationData()
{
    cout<<"ValidationData:"<<endl;
    printData(m_validationDataForX, m_validationDataForY);
}

void AprgModeling::printData(MatrixOfDoubles & matrixInX, MatrixOfDoubles & matrixInY)
{
    for(unsigned int j=0; j<matrixInY.getRows(); j++)
    {
        cout<<matrixInY.get(0, j)<<" <- ";
        for(unsigned int i=0; i<matrixInX.getColumns(); i++)
        {
            cout<<matrixInX.get(i, j)<<", ";
        }
        cout<<endl;
    }
}

void AprgModeling::copyVectorToMatrix(unsigned int const numberOfColumns, unsigned int const numberOfRows, VectorOfDoubles const& retrievedDataForX, MatrixOfDoubles & matrixOfDoubles)
{
    matrixOfDoubles.clearAndResize(numberOfColumns, numberOfRows);
    unsigned int x=0, y=0;
    for(double const value : retrievedDataForX)
    {
        matrixOfDoubles.set(x, y, value);
        x++;
        if(x>=numberOfColumns)
        {
            x=0;
            y++;
        }
    }
}

void AprgModeling::saveRetrievedDataToMatrixRandomly(MatrixOfDoubles & matrixInX, MatrixOfDoubles & matrixInY, unsigned int numberOfSamples)
{
    matrixInX.clearAndResize(m_retrievedDataForX.getColumns(), numberOfSamples);
    matrixInY.clearAndResize(1, numberOfSamples);
    AlbaRandomizer randomizer;
    for(unsigned int j=0; j<numberOfSamples; j++)
    {
        unsigned int randomRow((unsigned int)randomizer.getRandomValueInUniformDistribution(0, m_retrievedDataForY.getRows()-1));
        matrixInY.set(0, j, m_retrievedDataForY.get(0, randomRow));
        for(unsigned int i=0; i<m_retrievedDataForX.getColumns(); i++)
        {
            matrixInX.set(i, j, m_retrievedDataForX.get(i, randomRow));
        }
    }
}

void AprgModeling::saveRetrievedDataToMatrix(MatrixOfDoubles & matrixInX, MatrixOfDoubles & matrixInY, unsigned int numberOfSamples)
{
    matrixInX.clearAndResize(m_retrievedDataForX.getColumns(), numberOfSamples);
    matrixInY.clearAndResize(1, numberOfSamples);
    for(unsigned int j=0; j<numberOfSamples; j++)
    {
        matrixInY.set(0, j, m_retrievedDataForY.get(0, j));
        for(unsigned int i=0; i<m_retrievedDataForX.getColumns(); i++)
        {
            matrixInX.set(i, j, m_retrievedDataForX.get(i,j));
        }
    }
}

void AprgModeling::calculateCoefficientsUsingLeastSquares()
{
    unsigned int dataHeight = m_modelingDataForY.getRows();
    unsigned int dataWidth = m_modelingDataForX.getColumns();
    double chisq;

    gsl_matrix *xModelingData, *calculatedCovariance;
    gsl_vector *yModelingData, *calculatedCoefficients;

    xModelingData = gsl_matrix_alloc(dataHeight, dataWidth);
    yModelingData = gsl_vector_alloc(dataHeight);
    calculatedCoefficients = gsl_vector_alloc(dataWidth);
    calculatedCovariance = gsl_matrix_alloc(dataWidth, dataWidth);

    for(unsigned int y=0; y<m_modelingDataForY.getRows(); y++)
    {
        for(unsigned int x=1; x<m_modelingDataForY.getColumns(); x++)
        {
            gsl_vector_set(yModelingData, y, m_modelingDataForY.get(x, y));
        }
    }
    for(unsigned int x=1; x<m_modelingDataForX.getColumns(); x++)
    {
        for(unsigned int y=0; y<m_modelingDataForX.getRows(); y++)
        {
            gsl_matrix_set(xModelingData, y, x, m_modelingDataForX.get(x, y));
        }
    }

    gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc(dataHeight, dataWidth);
    gsl_multifit_linear(xModelingData, yModelingData, calculatedCoefficients, calculatedCovariance, &chisq, work);

    m_coefficients.clearAndResize(dataWidth, 1);
    for(unsigned int i=0; i<dataWidth; i++)
    {
        m_coefficients.set(i, 0, gsl_vector_get(calculatedCoefficients, i));
    }

    gsl_multifit_linear_free(work);
    gsl_matrix_free(calculatedCovariance);
    gsl_vector_free(calculatedCoefficients);
    gsl_vector_free(yModelingData);
    gsl_matrix_free(xModelingData);
}

unsigned int AprgModeling::getIndex(unsigned int const i, unsigned int const j, unsigned int const numberOfColumns) const
{
    return (j*numberOfColumns)+i;
}

}
