#pragma once

#include <string>
#include <vector>
#include <random>

namespace mse
{

class MeanSquareErrorCalculator
{
public:
    MeanSquareErrorCalculator();
    void clearModelingAndValidation();
    void clear();
    void saveValuesFromFileToDatabase(std::string const& filePath);
    void randomizeSampleDatabase();
    void performModelingAndValidation();
    int getNumberOfRows() const;
    void printDatabase() const;
    void printVectorOfDoubles(std::vector<double> const & doubles) const;
    void printAverageOfSquareErrors() const;
    void retrieveModelingSamples(int start, int end);
    void retrieveValidationSamples(int start, int end);
private:
    void calculateCoefficients(std::vector<double> & coefficients) const;    int getDatabaseIndex(int const x, int const y) const;
    int m_columns;
    int m_rows;
    double m_meanSquareTotalForRuns;
    double m_rootMeanSquareTotalForRuns;
    int m_runCount;
    std::vector<double> m_modelingForXData;
    std::vector<double> m_modelingForYData;
    std::vector<double> m_validationForXData;
    std::vector<double> m_validationForYData;
    std::vector<double> m_sampleDatabase;    std::vector<double> m_fileDatabase;
};

}