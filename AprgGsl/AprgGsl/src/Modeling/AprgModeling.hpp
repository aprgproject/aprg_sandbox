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
    unsigned int getNumberOfRows() const;
    Coefficients getCoefficients() const;
    void clear();
    void saveValuesFromFileToFileDataBuffer(std::string const& filePath);
    void fillSampleDataBufferFromFileDataBufferRandomly();
    void divideSamplesToModelingAndValidation(unsigned int modelingSamplesPercentage, unsigned validationSamplesPercentage);
    void model();
    ValidationResult validate();
private:
    void fillModelingDataBufferFromSamplesDataBuffer(unsigned int start, unsigned int end);
    void fillValidationDataBufferFromSamplesDataBuffer(unsigned int start, unsigned int end);
    void calculateCoefficients();
    void clearDataBuffersForModeling();
    void clearDataBuffersForValidation();
    void clearDataBufferForSamples();
    void clearDataBufferFromFile();
    void clearOtherData();
    unsigned int getIndex(unsigned int const x, unsigned int const y) const;
    unsigned int m_columns;
    unsigned int m_rows;
    Coefficients m_coefficients;
    DataBuffer m_dataBufferForModelingForX;
    DataBuffer m_dataBufferForModelingForY;
    DataBuffer m_dataBufferForValidationForX;
    DataBuffer m_dataBufferForValidationForY;
    DataBuffer m_dataBufferForSamples;
    DataBuffer m_dataBufferFromFile;
};

}
