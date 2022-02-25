#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <string>
#include <vector>

namespace alba
{

class Modeling
{
public:
    struct ValidationResult
    {
        double totalSquareError;
        double resultSize;
        double meanSquareError;
        double rootMeanSquareError;
    };
    using VectorOfDoubles = std::vector<double>;
    using MatrixOfDoubles = matrix::AlbaMatrix<double>;
    Modeling();
    unsigned int getNumberOfSamples() const;
    MatrixOfDoubles getCoefficients() const;
    void retrieveDataFromFileWithFileFormat1(std::string const& filePath);
    void retrieveDataFromFileWithFileFormat2(std::string const& filePath);
    void saveRetrievedDataForXAndY(
            unsigned int numberOfIndicators,
            unsigned int numberOfSamples,
            VectorOfDoubles const& retrievedDataForX,
            VectorOfDoubles const& retrievedDataForY);
    void saveRetrievedDataToModelingDataRandomly(unsigned int numberOfSamples);
    void saveRetrievedDataToValidationDataRandomly(unsigned int numberOfSamples);
    void saveRetrievedDataToModelingData(unsigned int numberOfSamples);
    void saveRetrievedDataToValidationData(unsigned int numberOfSamples);
    void printRetrievedData();
    void printModelingData();
    void printValidationData();
    void modelUsingLeastSquares();
    ValidationResult validate();

private:
    void copyVectorToMatrix(unsigned int const numberOfColumns, unsigned int const numberOfRows, VectorOfDoubles const& retrievedDataForX, MatrixOfDoubles & matrixOfDoubles);
    void printData(MatrixOfDoubles & matrixInX, MatrixOfDoubles & matrixInY);
    void saveRetrievedDataToMatrixRandomly(MatrixOfDoubles & matrixInX, MatrixOfDoubles & matrixInY, unsigned int numberOfSamples);
    void saveRetrievedDataToMatrix(MatrixOfDoubles & matrixInX, MatrixOfDoubles & matrixInY, unsigned int numberOfSamples);
    void calculateCoefficientsUsingLeastSquares();
    unsigned int getIndex(unsigned int const i, unsigned int const j, unsigned int const numberOfColumns) const;
    MatrixOfDoubles m_coefficients;
    MatrixOfDoubles m_modelingDataForX;
    MatrixOfDoubles m_modelingDataForY;
    MatrixOfDoubles m_validationDataForX;
    MatrixOfDoubles m_validationDataForY;
    MatrixOfDoubles m_retrievedDataForX;
    MatrixOfDoubles m_retrievedDataForY;
};

}
