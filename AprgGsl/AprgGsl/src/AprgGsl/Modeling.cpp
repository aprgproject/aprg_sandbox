#include "Modeling.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <gsl/gsl_multifit.h>

#include <algorithm>
#include <iostream>

using namespace alba::matrix;
using namespace std;

namespace alba {

Modeling::Modeling() {}

unsigned int Modeling::getNumberOfSamples() const { return m_retrievedDataForY.getNumberOfRows(); }

Modeling::MatrixOfDoubles Modeling::getCoefficients() const { return m_coefficients; }

void Modeling::retrieveDataFromFileWithFileFormat1(string const& filePath) {
    VectorOfDoubles retrievedDataForX, retrievedDataForY;
    unsigned int columnsForX = 0, numberOfSamples = 0;
    ifstream inputFile(filePath);
    AlbaFileReader fileReader(inputFile);
    fileReader.getLineAndIgnoreWhiteSpaces();  // Get Headers
    while (fileReader.isNotFinished()) {
        string lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        stringHelper::strings itemsFound;
        stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(itemsFound, lineInFile, ",");

        if (!itemsFound.empty()) {
            columnsForX = max(columnsForX, static_cast<unsigned int>(itemsFound.size() - 1));
            stringHelper::strings::const_iterator it(itemsFound.begin());
            retrievedDataForY.emplace_back(stringHelper::convertStringToNumber<double>(*it));
            it++;
            for_each(it, itemsFound.cend(), [&](string const& item) {
                retrievedDataForX.emplace_back(stringHelper::convertStringToNumber<double>(item));
            });
            numberOfSamples++;
        }
    }
    saveRetrievedDataForXAndY(columnsForX, numberOfSamples, retrievedDataForX, retrievedDataForY);
}

void Modeling::retrieveDataFromFileWithFileFormat2(string const& filePath) {
    VectorOfDoubles retrievedDataForX, retrievedDataForY;
    unsigned int columnsForX = 0, numberOfSamples = 0;
    bool isLineWithYValues(true);
    VectorOfDoubles reversedCoordinates;
    unsigned int reversedCoordinatesColumns(0);
    unsigned int reversedCoordinatesRows(0);

    ifstream inputFile(filePath);
    AlbaFileReader fileReader(inputFile);
    fileReader.getLineAndIgnoreWhiteSpaces();  // Get Headers
    while (fileReader.isNotFinished()) {
        string lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        stringHelper::strings itemsFound;
        stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters>(itemsFound, lineInFile, ",");

        if (!itemsFound.empty()) {
            if (isLineWithYValues) {
                stringHelper::strings::const_iterator it(itemsFound.begin());
                it++;
                for_each(it, itemsFound.cend(), [&](string const& item) {
                    retrievedDataForY.emplace_back(stringHelper::convertStringToNumber<double>(item));
                });
                isLineWithYValues = false;
            } else {
                reversedCoordinatesColumns =
                    max(reversedCoordinatesColumns, static_cast<unsigned int>(itemsFound.size() - 1));
                stringHelper::strings::const_iterator it(itemsFound.begin());
                it++;
                for_each(it, itemsFound.cend(), [&](string const& item) {
                    reversedCoordinates.emplace_back(stringHelper::convertStringToNumber<double>(item));
                });
                reversedCoordinatesRows++;
            }
        }
    }
    for (unsigned int i = 0; i < reversedCoordinatesColumns; i++) {
        for (unsigned int j = 0; j < reversedCoordinatesRows; j++) {
            retrievedDataForX.emplace_back(reversedCoordinates[getIndex(i, j, reversedCoordinatesColumns)]);
        }
    }
    columnsForX = reversedCoordinatesRows;
    numberOfSamples = reversedCoordinatesColumns;
    saveRetrievedDataForXAndY(columnsForX, numberOfSamples, retrievedDataForX, retrievedDataForY);
}

void Modeling::saveRetrievedDataForXAndY(
    unsigned int numberOfIndicators, unsigned int numberOfSamples, VectorOfDoubles const& retrievedDataForX,
    VectorOfDoubles const& retrievedDataForY) {
    copyVectorToMatrix(numberOfIndicators, numberOfSamples, retrievedDataForX, m_retrievedDataForX);
    copyVectorToMatrix(1, numberOfSamples, retrievedDataForY, m_retrievedDataForY);
}

void Modeling::saveRetrievedDataToModelingDataRandomly(unsigned int numberOfSamples) {
    saveRetrievedDataToMatrixRandomly(m_modelingDataForX, m_modelingDataForY, numberOfSamples);
}

void Modeling::saveRetrievedDataToValidationDataRandomly(unsigned int numberOfSamples) {
    saveRetrievedDataToMatrixRandomly(m_validationDataForX, m_validationDataForY, numberOfSamples);
}

void Modeling::saveRetrievedDataToModelingData(unsigned int numberOfSamples) {
    saveRetrievedDataToMatrix(m_modelingDataForX, m_modelingDataForY, numberOfSamples);
}

void Modeling::saveRetrievedDataToValidationData(unsigned int numberOfSamples) {
    saveRetrievedDataToMatrix(m_validationDataForX, m_validationDataForY, numberOfSamples);
}

void Modeling::modelUsingLeastSquares() { calculateCoefficientsUsingLeastSquares(); }

Modeling::ValidationResult Modeling::validate() {
    ValidationResult result;
    vector<double> calculationDataBuffer;

    unsigned int dataHeight = m_validationDataForY.getNumberOfRows();
    unsigned int dataWidthForX = m_validationDataForX.getNumberOfColumns();
    unsigned int index = 0;

    for (unsigned int j = 0; j < dataHeight; j++) {
        double yPredicted = 0;
        for (unsigned int i = 0; i < dataWidthForX; i++) {
            yPredicted += m_validationDataForX.getEntry(i, j) * m_coefficients.getEntry(i, 0);
            index++;
        }
        calculationDataBuffer.emplace_back(yPredicted);
    }

    for (unsigned int j = 0; j < dataHeight; j++) {
        calculationDataBuffer[j] = m_validationDataForY.getEntry(0, j) - calculationDataBuffer[j];
    }

    for (unsigned int j = 0; j < dataHeight; j++) {
        calculationDataBuffer[j] = pow(calculationDataBuffer[j], 2);
    }

    double totalSquareError(0);
    for (unsigned int j = 0; j < dataHeight; j++) {
        totalSquareError += calculationDataBuffer[j];
    }

    double meanSquareError = totalSquareError / calculationDataBuffer.size();
    double rootMeanSquareError = pow(meanSquareError, 0.5);

    result.totalSquareError = totalSquareError;
    result.resultSize = calculationDataBuffer.size();
    result.meanSquareError = meanSquareError;
    result.rootMeanSquareError = rootMeanSquareError;
    return result;
}

void Modeling::printRetrievedData() {
    cout << "RetrievedData:\n";
    printData(m_retrievedDataForX, m_retrievedDataForY);
}

void Modeling::printModelingData() {
    cout << "ModelingData:\n";
    printData(m_modelingDataForX, m_modelingDataForY);
}

void Modeling::printValidationData() {
    cout << "ValidationData:\n";
    printData(m_validationDataForX, m_validationDataForY);
}

void Modeling::printData(MatrixOfDoubles& matrixInX, MatrixOfDoubles& matrixInY) {
    for (unsigned int j = 0; j < matrixInY.getNumberOfRows(); j++) {
        cout << matrixInY.getEntry(0, j) << " <- ";
        for (unsigned int i = 0; i < matrixInX.getNumberOfColumns(); i++) {
            cout << matrixInX.getEntry(i, j) << ", ";
        }
        cout << "\n";
    }
}

void Modeling::copyVectorToMatrix(
    unsigned int const numberOfColumns, unsigned int const numberOfRows, VectorOfDoubles const& retrievedDataForX,
    MatrixOfDoubles& matrixOfDoubles) {
    matrixOfDoubles.clearAndResize(numberOfColumns, numberOfRows);
    unsigned int x = 0, y = 0;
    for (double const value : retrievedDataForX) {
        matrixOfDoubles.setEntry(x, y, value);
        x++;
        if (x >= numberOfColumns) {
            x = 0;
            y++;
        }
    }
}

void Modeling::saveRetrievedDataToMatrixRandomly(
    MatrixOfDoubles& matrixInX, MatrixOfDoubles& matrixInY, unsigned int numberOfSamples) {
    matrixInX.clearAndResize(m_retrievedDataForX.getNumberOfColumns(), numberOfSamples);
    matrixInY.clearAndResize(1, numberOfSamples);
    AlbaUniformNonDeterministicRandomizer<unsigned int> randomizer(0, m_retrievedDataForY.getNumberOfRows() - 1);
    for (unsigned int j = 0; j < numberOfSamples; j++) {
        unsigned int randomRow(randomizer.getRandomValue());
        matrixInY.setEntry(0, j, m_retrievedDataForY.getEntry(0, randomRow));
        for (unsigned int i = 0; i < m_retrievedDataForX.getNumberOfColumns(); i++) {
            matrixInX.setEntry(i, j, m_retrievedDataForX.getEntry(i, randomRow));
        }
    }
}

void Modeling::saveRetrievedDataToMatrix(
    MatrixOfDoubles& matrixInX, MatrixOfDoubles& matrixInY, unsigned int numberOfSamples) {
    matrixInX.clearAndResize(m_retrievedDataForX.getNumberOfColumns(), numberOfSamples);
    matrixInY.clearAndResize(1, numberOfSamples);
    for (unsigned int j = 0; j < numberOfSamples; j++) {
        matrixInY.setEntry(0, j, m_retrievedDataForY.getEntry(0, j));
        for (unsigned int i = 0; i < m_retrievedDataForX.getNumberOfColumns(); i++) {
            matrixInX.setEntry(i, j, m_retrievedDataForX.getEntry(i, j));
        }
    }
}

void Modeling::calculateCoefficientsUsingLeastSquares() {
    unsigned int dataHeight = m_modelingDataForY.getNumberOfRows();
    unsigned int dataWidth = m_modelingDataForX.getNumberOfColumns();
    double chisq;

    gsl_matrix *xModelingData, *calculatedCovariance;
    gsl_vector *yModelingData, *calculatedCoefficients;

    xModelingData = gsl_matrix_alloc(dataHeight, dataWidth);
    yModelingData = gsl_vector_alloc(dataHeight);
    calculatedCoefficients = gsl_vector_alloc(dataWidth);
    calculatedCovariance = gsl_matrix_alloc(dataWidth, dataWidth);

    for (unsigned int y = 0; y < m_modelingDataForY.getNumberOfRows(); y++) {
        for (unsigned int x = 1; x < m_modelingDataForY.getNumberOfColumns(); x++) {
            gsl_vector_set(yModelingData, y, m_modelingDataForY.getEntry(x, y));
        }
    }
    for (unsigned int x = 1; x < m_modelingDataForX.getNumberOfColumns(); x++) {
        for (unsigned int y = 0; y < m_modelingDataForX.getNumberOfRows(); y++) {
            gsl_matrix_set(xModelingData, y, x, m_modelingDataForX.getEntry(x, y));
        }
    }

    gsl_multifit_linear_workspace* work = gsl_multifit_linear_alloc(dataHeight, dataWidth);
    auto multifitError =
        gsl_multifit_linear(xModelingData, yModelingData, calculatedCoefficients, calculatedCovariance, &chisq, work);

    cout << "Error status is [" << multifitError << "] which means: [" << gsl_strerror(multifitError) << "]\n";

    m_coefficients.clearAndResize(dataWidth, 1);
    for (unsigned int i = 0; i < dataWidth; i++) {
        m_coefficients.setEntry(i, 0, gsl_vector_get(calculatedCoefficients, i));
    }

    gsl_multifit_linear_free(work);

    gsl_matrix_free(calculatedCovariance);
    gsl_vector_free(calculatedCoefficients);
    gsl_vector_free(yModelingData);
    gsl_matrix_free(xModelingData);
}

unsigned int Modeling::getIndex(unsigned int const i, unsigned int const j, unsigned int const numberOfColumns) const {
    return (j * numberOfColumns) + i;
}

}  // namespace alba
