#include <AprgGsl/Modeling.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

#define ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT1_FILE1 APRG_DIR R"(\AprgGsl\FilesForTests\DataSets\DataSet1.csv)"
#define ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT1_FILE2 APRG_DIR R"(\AprgGsl\FilesForTests\DataSets\DataSet2.csv)"
#define ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT2_FILE3 APRG_DIR R"(\AprgGsl\FilesForTests\DataSets\DataSet3_FileFormat2.csv)"

namespace alba
{

TEST(SampleTest, TestForDataSet)
{
    AlbaLocalPathHandler testFilePath(ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT1_FILE1);
    Modeling modeling;
    modeling.retrieveDataFromFileWithFileFormat1(testFilePath.getFullPath());
    modeling.printRetrievedData();
    unsigned int numberOfSamples (modeling.getNumberOfSamples());
    modeling.saveRetrievedDataToModelingDataRandomly(numberOfSamples/2);
    modeling.saveRetrievedDataToValidationDataRandomly(numberOfSamples/2);
    modeling.modelUsingLeastSquares();
    modeling.printModelingData();
    modeling.printValidationData();
    Modeling::ValidationResult result =  modeling.validate();
    cout<<"totalSquareError: "<<std::setprecision(20)<<result.totalSquareError<<endl;
    cout<<"resultSize: "<<std::setprecision(20)<<result.resultSize<<endl;
    cout<<"meanSquareError: "<<std::setprecision(20)<<result.meanSquareError<<endl;
    cout<<"rootMeanSquareError: "<<std::setprecision(20)<<result.rootMeanSquareError<<endl;

    Modeling::MatrixOfDoubles coefficients(modeling.getCoefficients());
    cout<<"Coefficients:"<<endl;
    cout<<coefficients<<endl;
}

TEST(SampleTest, DISABLED_TestForDataSet3_FileFormat2)
{
    AlbaLocalPathHandler testFilePath(ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT2_FILE3);
    Modeling modeling;
    modeling.retrieveDataFromFileWithFileFormat2(testFilePath.getFullPath());
    modeling.printRetrievedData();
    unsigned int numberOfSamples (modeling.getNumberOfSamples());
    modeling.saveRetrievedDataToModelingData(numberOfSamples);
    modeling.saveRetrievedDataToValidationData(numberOfSamples);
    modeling.modelUsingLeastSquares();
    modeling.printModelingData();
    modeling.printValidationData();
    Modeling::ValidationResult result =  modeling.validate();
    cout<<"totalSquareError: "<<std::setprecision(20)<<result.totalSquareError<<endl;
    cout<<"resultSize: "<<std::setprecision(20)<<result.resultSize<<endl;
    cout<<"meanSquareError: "<<std::setprecision(20)<<result.meanSquareError<<endl;
    cout<<"rootMeanSquareError: "<<std::setprecision(20)<<result.rootMeanSquareError<<endl;

    Modeling::MatrixOfDoubles coefficients(modeling.getCoefficients());
    cout<<"Coefficients:"<<endl;
    cout<<coefficients<<endl;
}

}
