#include <Statistics/DataSample.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(DataSampleTest, DataSampleWithDefaultConstructorIsZero)
{
    DataSample<unsigned int, 5> dataSample;
    EXPECT_EQ(0u, dataSample.getValueAt(0));
    EXPECT_EQ(0u, dataSample.getValueAt(1));
    EXPECT_EQ(0u, dataSample.getValueAt(2));
    EXPECT_EQ(0u, dataSample.getValueAt(3));
    EXPECT_EQ(0u, dataSample.getValueAt(4));
}

TEST(DataSampleTest, DataSampleWithInitializerListIsCorrectlyInitialized)
{
    DataSample<unsigned int, 5> dataSample{10, 20, 30, 40, 50};
    EXPECT_EQ(10u, dataSample.getValueAt(0));
    EXPECT_EQ(20u, dataSample.getValueAt(1));
    EXPECT_EQ(30u, dataSample.getValueAt(2));
    EXPECT_EQ(40u, dataSample.getValueAt(3));
    EXPECT_EQ(50u, dataSample.getValueAt(4));
}

TEST(DataSampleTest, SumCanBeCalculated)
{
    DataSample<unsigned int, 5> dataSample{10, 20, 30, 40, 50};
    EXPECT_EQ(150u, dataSample.getSum());
}

TEST(DataSampleTest, IndexCanBeChecked)
{
    DataSample<unsigned int, 5> dataSample{10, 20, 30, 40, 50};
    EXPECT_TRUE(dataSample.isIndexValid(0));
    EXPECT_TRUE(dataSample.isIndexValid(1));
    EXPECT_TRUE(dataSample.isIndexValid(2));
    EXPECT_TRUE(dataSample.isIndexValid(3));
    EXPECT_TRUE(dataSample.isIndexValid(4));
    EXPECT_FALSE(dataSample.isIndexValid(5));
    EXPECT_FALSE(dataSample.isIndexValid(-5));
}

TEST(DataSampleTest, GetValueAtInvalidIndexReturnsZero)
{
    DataSample<unsigned int, 5> dataSample{10, 20, 30, 40, 50};
    EXPECT_EQ(0u, dataSample.getValueAt(5));
    EXPECT_EQ(0u, dataSample.getValueAt(-5));
}

TEST(DataSampleTest, DataSampleCanBeSet)
{
    DataSample<unsigned int, 5> dataSample{10, 20, 30, 40, 50};
    dataSample.setValueAt(0, 500);
    dataSample.setValueAt(1, 400);
    dataSample.setValueAt(2, 300);
    dataSample.setValueAt(3, 200);
    dataSample.setValueAt(4, 100);
    EXPECT_EQ(500u, dataSample.getValueAt(0));
    EXPECT_EQ(400u, dataSample.getValueAt(1));
    EXPECT_EQ(300u, dataSample.getValueAt(2));
    EXPECT_EQ(200u, dataSample.getValueAt(3));
    EXPECT_EQ(100u, dataSample.getValueAt(4));
}

TEST(DataSampleTest, DataSamplesCanBeAddedTogether)
{
    DataSample<unsigned int, 5> dataSample1{10, 20, 30, 40, 50};
    DataSample<unsigned int, 5> dataSample2{10, 20, 30, 40, 50};
    DataSample<unsigned int, 5> actualResult = dataSample1+dataSample2;
    EXPECT_EQ(20u, actualResult.getValueAt(0));
    EXPECT_EQ(40u, actualResult.getValueAt(1));
    EXPECT_EQ(60u, actualResult.getValueAt(2));
    EXPECT_EQ(80u, actualResult.getValueAt(3));
    EXPECT_EQ(100u, actualResult.getValueAt(4));
}

TEST(DataSampleTest, DataSamplesCanBeAddedWithSingleValue)
{
    DataSample<unsigned int, 5> dataSample1{10, 20, 30, 40, 50};
    unsigned int singleValue = 1;
    DataSample<unsigned int, 5> actualResult = dataSample1+singleValue;
    EXPECT_EQ(11u, actualResult.getValueAt(0));
    EXPECT_EQ(21u, actualResult.getValueAt(1));
    EXPECT_EQ(31u, actualResult.getValueAt(2));
    EXPECT_EQ(41u, actualResult.getValueAt(3));
    EXPECT_EQ(51u, actualResult.getValueAt(4));
}



