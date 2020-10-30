#include <Statistics/DataSample.hpp>
#include <Statistics/DataStatistics.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;

TEST(DataSampleTest, DataSampleWithDefaultConstructorIsZero)
{
    DataSample<unsigned int, 5> dataSample;
    EXPECT_EQ(0, dataSample.getValueAt(0));
    EXPECT_EQ(0, dataSample.getValueAt(1));
    EXPECT_EQ(0, dataSample.getValueAt(2));
    EXPECT_EQ(0, dataSample.getValueAt(3));
    EXPECT_EQ(0, dataSample.getValueAt(4));
}

TEST(DataSampleTest, DataSampleWithInitializerListIsCorrectlyInitialized)
{
    DataSample<unsigned int, 5> dataSample{10, 20, 30, 40, 50};
    EXPECT_EQ(10, dataSample.getValueAt(0));
    EXPECT_EQ(20, dataSample.getValueAt(1));
    EXPECT_EQ(30, dataSample.getValueAt(2));
    EXPECT_EQ(40, dataSample.getValueAt(3));
    EXPECT_EQ(50, dataSample.getValueAt(4));
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
    EXPECT_EQ(0, dataSample.getValueAt(5));
    EXPECT_EQ(0, dataSample.getValueAt(-5));
}

TEST(DataSampleTest, DataSampleCanBeSet)
{
    DataSample<unsigned int, 5> dataSample{10, 20, 30, 40, 50};
    dataSample.setValueAt(0, 500);
    dataSample.setValueAt(1, 400);
    dataSample.setValueAt(2, 300);
    dataSample.setValueAt(3, 200);
    dataSample.setValueAt(4, 100);
    EXPECT_EQ(500, dataSample.getValueAt(0));
    EXPECT_EQ(400, dataSample.getValueAt(1));
    EXPECT_EQ(300, dataSample.getValueAt(2));
    EXPECT_EQ(200, dataSample.getValueAt(3));
    EXPECT_EQ(100, dataSample.getValueAt(4));
}

TEST(DataSampleTest, DataSamplesCanBeAddedTogether)
{
    DataSample<unsigned int, 5> dataSample1{10, 20, 30, 40, 50};
    DataSample<unsigned int, 5> dataSample2{10, 20, 30, 40, 50};
    DataSample<unsigned int, 5> actualResult = dataSample1+dataSample2;
    EXPECT_EQ(20, actualResult.getValueAt(0));
    EXPECT_EQ(40, actualResult.getValueAt(1));
    EXPECT_EQ(60, actualResult.getValueAt(2));
    EXPECT_EQ(80, actualResult.getValueAt(3));
    EXPECT_EQ(100, actualResult.getValueAt(4));
}

TEST(DataSampleTest, DataSamplesCanBeAddedWithSingleValue)
{
    DataSample<unsigned int, 5> dataSample1{10, 20, 30, 40, 50};
    unsigned int singleValue = 1;
    DataSample<unsigned int, 5> actualResult = dataSample1+singleValue;
    EXPECT_EQ(11, actualResult.getValueAt(0));
    EXPECT_EQ(21, actualResult.getValueAt(1));
    EXPECT_EQ(31, actualResult.getValueAt(2));
    EXPECT_EQ(41, actualResult.getValueAt(3));
    EXPECT_EQ(51, actualResult.getValueAt(4));
}



