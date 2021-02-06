#include <Modeling/AprgModeling.hpp>

#include <Container/AlbaRange.hpp>
#include <gtest/gtest.h>

using namespace alba;
using namespace std;


#define ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT1_FILE1 APRG_DIR "AprgGsl\\AprgGsl\\tst\\ModelingDataSets\\DataSet1.csv"
#define ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT1_FILE2 APRG_DIR "AprgGsl\\AprgGsl\\tst\\ModelingDataSets\\DataSet2.csv"
#define ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT2_FILE3 APRG_DIR "AprgGsl\\AprgGsl\\tst\\ModelingDataSets\\DataSet3_FileFormat2.csv"

TEST(SampleTest, TestForDataSet)
{
    AprgModeling modeling;
    modeling.retrieveDataFromFileWithFileFormat1(ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT1_FILE1);
    modeling.printRetrievedData();
    unsigned int numberOfSamples (modeling.getNumberOfSamples());
    modeling.saveRetrievedDataToModelingDataRandomly(numberOfSamples/2);
    modeling.saveRetrievedDataToValidationDataRandomly(numberOfSamples/2);
    modeling.modelUsingLeastSquares();
    modeling.printModelingData();
    modeling.printValidationData();
    AprgModeling::ValidationResult result =  modeling.validate();
    cout<<"totalSquareError: "<<std::setprecision(20)<<result.totalSquareError<<endl;
    cout<<"resultSize: "<<std::setprecision(20)<<result.resultSize<<endl;
    cout<<"meanSquareError: "<<std::setprecision(20)<<result.meanSquareError<<endl;
    cout<<"rootMeanSquareError: "<<std::setprecision(20)<<result.rootMeanSquareError<<endl;

    AprgModeling::MatrixOfDoubles coefficients(modeling.getCoefficients());
    cout<<"Coefficients:"<<endl;
    coefficients.traverse([&](unsigned int const x, unsigned int const, double const value)
    {
        cout<<"["<<x+1<<" -> "<<std::setprecision(20)<<value<<"],"<<endl;
    });
}

TEST(SampleTest, DISABLED_TestForDataSet3_FileFormat2)
{
    AprgModeling modeling;
    modeling.retrieveDataFromFileWithFileFormat2(ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT2_FILE3);
    modeling.printRetrievedData();
    unsigned int numberOfSamples (modeling.getNumberOfSamples());
    modeling.saveRetrievedDataToModelingData(numberOfSamples);
    modeling.saveRetrievedDataToValidationData(numberOfSamples);
    modeling.modelUsingLeastSquares();
    modeling.printModelingData();
    modeling.printValidationData();
    AprgModeling::ValidationResult result =  modeling.validate();
    cout<<"totalSquareError: "<<std::setprecision(20)<<result.totalSquareError<<endl;
    cout<<"resultSize: "<<std::setprecision(20)<<result.resultSize<<endl;
    cout<<"meanSquareError: "<<std::setprecision(20)<<result.meanSquareError<<endl;
    cout<<"rootMeanSquareError: "<<std::setprecision(20)<<result.rootMeanSquareError<<endl;

    AprgModeling::MatrixOfDoubles coefficients(modeling.getCoefficients());
    cout<<"Coefficients:"<<endl;
    coefficients.traverse([&](unsigned int const x, unsigned int const, double const value)
    {
        cout<<"["<<x+1<<" -> "<<std::setprecision(20)<<value<<"],"<<endl;
    });
}
