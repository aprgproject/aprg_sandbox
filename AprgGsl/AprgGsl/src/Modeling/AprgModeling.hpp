#pragma once

#include <string>
#include <vector>

namespace alba
{


class AprgModeling
{
public:
    struct ValidationResult
    {
        double totalSquareError;
        double resultSize;
        double meanSquareError;
        double rootMeanSquareError;
    };
    using Coefficients = std::vector<double>;
    using DataBuffer = std::vector<double>;
    AprgModeling();
    unsigned int getNumberOfSamples() const;
    Coefficients getCoefficients() const;
    void clear();
    void retrieveDataFromFileWithFileFormat1(std::string const& filePath);
    void retrieveDataFromFileWithFileFormat2(std::string const& filePath);
    void saveRetrievedDataToModelingDataRandomly(unsigned int numberOfSamples);
    void saveRetrievedDataToValidationDataRandomly(unsigned int numberOfSamples);
    void saveAllRetrievedDataToModelingData(unsigned int numberOfSamples);
    void saveAllRetrievedDataToValidationData(unsigned int numberOfSamples);
    void printRetrievedData();
    void printModelingData();
    void printValidationData();
    void model();
    ValidationResult validate();
private:
    void printData(DataBuffer & dataBufferForX, DataBuffer & dataBufferForY);
    void saveRetrievedDataToDataBufferRandomly(DataBuffer & dataBufferForX, DataBuffer & dataBufferForY, unsigned int numberOfSamples);
    void saveAllRetrievedDataToDataBuffer(DataBuffer & dataBufferForX, DataBuffer & dataBufferForY, unsigned int numberOfSamples);
    void calculateCoefficients();
    void clearDataBuffersForModeling();
    void clearDataBuffersForValidation();
    void clearRetrievedData();
    void clearOtherData();
    unsigned int getIndexForXData(unsigned int const x, unsigned int const y) const;
    unsigned int getIndex(unsigned int const i, unsigned int const j, unsigned int const numberOfColumns) const;
    unsigned int m_columnsForX;
    unsigned int m_numberOfSamples;
    Coefficients m_coefficients;
    DataBuffer m_modelingDataForX;
    DataBuffer m_modelingDataForY;
    DataBuffer m_validationDataForX;
    DataBuffer m_validationDataForY;
    DataBuffer m_retrievedDataForX;
    DataBuffer m_retrievedDataForY;
};

}