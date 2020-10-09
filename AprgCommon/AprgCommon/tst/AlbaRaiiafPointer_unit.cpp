#include <AlbaRaiiafPointer.hpp>

#include <gtest/gtest.h>
#include <iostream>
#include <string>

using namespace alba;
using namespace std;

TEST(AlbaRaiiafPointerTest, IntegerTest)
{
    AlbaRaiiafPointer integerPointer;
    integerPointer.setAndAllocateNewContent<int>(0xA1BA);
    EXPECT_EQ(integerPointer.get<int>(), 0xA1BA);
    EXPECT_EQ(integerPointer.getReference<int>(), 0xA1BA);
    integerPointer.deAllocate<int>();
    integerPointer.setAndAllocateNewContent<int>(0x1234);
    EXPECT_EQ(integerPointer.get<int>(), 0x1234);
    EXPECT_EQ(integerPointer.getReference<int>(), 0x1234);
    integerPointer.deAllocate<int>();
}

TEST(AlbaRaiiafPointerTest, StringTest)
{
    AlbaRaiiafPointer stringPointer;
    stringPointer.setAndAllocateNewContent<string>("Allocate new object");
    EXPECT_EQ(stringPointer.get<string>(), "Allocate new object");
    EXPECT_EQ(stringPointer.getReference<string>(), "Allocate new object");
    stringPointer.deAllocate<string>();
    stringPointer.setAndAllocateNewContent<string>("Replace with new object");
    EXPECT_EQ(stringPointer.get<string>(), "Replace with new object");
    EXPECT_EQ(stringPointer.getReference<string>(), "Replace with new object");
    stringPointer.deAllocate<string>();
}

TEST(AlbaRaiiafPointerTest, IntAndStringTest)
{
    //for(unsigned int i = 0; i < 0x1000; i++)
    //{
        AlbaRaiiafPointer anyPointer;
        anyPointer.setAndAllocateNewContent<int>(0xA1BA);
        EXPECT_EQ(anyPointer.get<int>(), 0xA1BA);
        EXPECT_EQ(anyPointer.getReference<int>(), 0xA1BA);
        anyPointer.deAllocate<int>();
        anyPointer.setAndAllocateNewContent<string>("Allocate new object");
        EXPECT_EQ(anyPointer.get<string>(), "Allocate new object");
        EXPECT_EQ(anyPointer.getReference<string>(), "Allocate new object");
        anyPointer.deAllocate<string>();
        anyPointer.setAndAllocateNewContent<int>(0x1234);
        EXPECT_EQ(anyPointer.get<int>(), 0x1234);
        EXPECT_EQ(anyPointer.getReference<int>(), 0x1234);
        anyPointer.deAllocate<int>();
        anyPointer.setAndAllocateNewContent<string>("Replace with new object");
        EXPECT_EQ(anyPointer.get<string>(), "Replace with new object");
        EXPECT_EQ(anyPointer.getReference<string>(), "Replace with new object");
        anyPointer.deAllocate<string>();
    //}
}

