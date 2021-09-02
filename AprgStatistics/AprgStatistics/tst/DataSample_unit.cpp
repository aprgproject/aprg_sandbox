#include <DataSample.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(DataSampleTest, DataSampleWithDefaultConstructorIsZero)
{
    DataSample<5> dataSample;
    EXPECT_EQ(0U, dataSample.getValueAt(0));
    EXPECT_EQ(0U, dataSample.getValueAt(1));
    EXPECT_EQ(0U, dataSample.getValueAt(2));
    EXPECT_EQ(0U, dataSample.getValueAt(3));
    EXPECT_EQ(0U, dataSample.getValueAt(4));
}

TEST(DataSampleTest, DataSampleWithInitializerListIsCorrectlyInitialized)
{
    DataSample<5> dataSample{10, 20, 30, 40, 50};
    EXPECT_EQ(10U, dataSample.getValueAt(0));
    EXPECT_EQ(20U, dataSample.getValueAt(1));
    EXPECT_EQ(30U, dataSample.getValueAt(2));
    EXPECT_EQ(40U, dataSample.getValueAt(3));
    EXPECT_EQ(50U, dataSample.getValueAt(4));
}

TEST(DataSampleTest, SumCanBeCalculated)
{
    DataSample<5> dataSample{10, 20, 30, 40, 50};
    EXPECT_EQ(150U, dataSample.getSum());
}

TEST(DataSampleTest, IndexCanBeChecked){
    DataSample<5> dataSample{10, 20, 30, 40, 50};
    EXPECT_TRUE(dataSample.isIndexValid(0));
    EXPECT_TRUE(dataSample.isIndexValid(1));    EXPECT_TRUE(dataSample.isIndexValid(2));
    EXPECT_TRUE(dataSample.isIndexValid(3));
    EXPECT_TRUE(dataSample.isIndexValid(4));
    EXPECT_FALSE(dataSample.isIndexValid(5));
    EXPECT_FALSE(dataSample.isIndexValid(-5));
}

TEST(DataSampleTest, GetValueAtInvalidIndexReturnsZero)
{
    DataSample<5> dataSample{10, 20, 30, 40, 50};
    EXPECT_EQ(0U, dataSample.getValueAt(5));
    EXPECT_EQ(0U, dataSample.getValueAt(-5));
}

TEST(DataSampleTest, DataSampleCanBeSet){
    DataSample<5> dataSample{10, 20, 30, 40, 50};
    dataSample.setValueAt(0, 500);
    dataSample.setValueAt(1, 400);
    dataSample.setValueAt(2, 300);
    dataSample.setValueAt(3, 200);
    dataSample.setValueAt(4, 100);
    EXPECT_EQ(500U, dataSample.getValueAt(0));
    EXPECT_EQ(400U, dataSample.getValueAt(1));
    EXPECT_EQ(300U, dataSample.getValueAt(2));
    EXPECT_EQ(200U, dataSample.getValueAt(3));
    EXPECT_EQ(100U, dataSample.getValueAt(4));
}

TEST(DataSampleTest, DataSampleCanBeCompared){
    DataSample<5> dataSample{10, 20, 30, 40, 50};
    DataSample<5> dataSample2{10, 20, 30, 40, 50};
    DataSample<5> dataSample3{10, 20, 25, 40, 50};    EXPECT_EQ(dataSample, dataSample2);
    EXPECT_NE(dataSample, dataSample3);
}

TEST(DataSampleTest, DataSamplesCanBeAddedTogether)
{
    DataSample<5> dataSample1{10, 20, 30, 40, 50};
    DataSample<5> dataSample2{10, 20, 30, 40, 50};
    DataSample<5> actualResult = dataSample1+dataSample2;
    EXPECT_EQ(20U, actualResult.getValueAt(0));
    EXPECT_EQ(40U, actualResult.getValueAt(1));
    EXPECT_EQ(60U, actualResult.getValueAt(2));
    EXPECT_EQ(80U, actualResult.getValueAt(3));
    EXPECT_EQ(100U, actualResult.getValueAt(4));
}

TEST(DataSampleTest, DataSamplesCanBeAddedWithSingleValue){
    DataSample<5> dataSample1{10, 20, 30, 40, 50};
    unsigned int singleValue = 1;
    DataSample<5> actualResult = dataSample1+singleValue;
    EXPECT_EQ(11U, actualResult.getValueAt(0));
    EXPECT_EQ(21U, actualResult.getValueAt(1));
    EXPECT_EQ(31U, actualResult.getValueAt(2));
    EXPECT_EQ(41U, actualResult.getValueAt(3));
    EXPECT_EQ(51U, actualResult.getValueAt(4));
}

}