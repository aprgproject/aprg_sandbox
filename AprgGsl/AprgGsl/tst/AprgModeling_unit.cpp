#include <Modeling/AprgModeling.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

#define ALBA_MODELING_DATA_SET_FILE1 APRG_DIR R"(AprgGsl\AprgGsl\tst\ModelingDataSets\DataSet1.csv)"
#define ALBA_MODELING_DATA_SET_FILE2 APRG_DIR R"(AprgGsl\AprgGsl\tst\ModelingDataSets\DataSet2.csv)"

TEST(SampleTest, TestForDataSet)
{
    AprgModeling modeling;
    modeling.saveValuesFromFileToFileDataBuffer(ALBA_MODELING_DATA_SET_FILE1);
    modeling.fillSampleDataBufferFromFileDataBufferRandomly();
    modeling.divideSamplesToModelingAndValidation(50,50);
    modeling.model();
    AprgModeling::ValidationResult result =  modeling.validate();
    cout<<"totalSquareError: "<<std::setprecision(20)<<result.totalSquareError<<endl;
    cout<<"resultSize: "<<std::setprecision(20)<<result.resultSize<<endl;
    cout<<"meanSquareError: "<<std::setprecision(20)<<result.meanSquareError<<endl;
    cout<<"rootMeanSquareError: "<<std::setprecision(20)<<result.rootMeanSquareError<<endl;

    AprgModeling::Coefficients coefficients(modeling.getCoefficients());
    cout<<"Coefficients:"<<endl;
    unsigned int i=1;
    for(double coefficient: coefficients)
    {
        cout<<"["<<i++<<" -> "<<std::setprecision(20)<<coefficient<<"],"<<endl;
    }
}


