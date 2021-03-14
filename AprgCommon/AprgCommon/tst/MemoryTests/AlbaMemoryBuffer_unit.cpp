#include <Memory/AlbaMemoryBuffer.hpp>

#include <gtest/gtest.h>


#include <Debug/AlbaDebug.hpp>

using namespace std;

namespace alba{

TEST(AlbaMemoryBufferTest, DefaultValuesAreClear)
{    AlbaMemoryBuffer buffer;
    EXPECT_FALSE(buffer);
    EXPECT_FALSE(buffer.hasContent());
    EXPECT_EQ(0u, buffer.getSize());
}

TEST(AlbaMemoryBufferTest, PrimitiveTypesCanBeSavedDuringConstructionOfBuffer)
{
    int input = 11111111;
    AlbaMemoryBuffer buffer(static_cast<void*>(&input), sizeof(input));
    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());

    EXPECT_TRUE(buffer);    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(4u, buffer.getSize());
    EXPECT_EQ(input, output);
}
TEST(AlbaMemoryBufferTest, PrimitiveTypesCanBeSaved)
{
    AlbaMemoryBuffer buffer;
    int input = 11111111;
    buffer.addData(static_cast<void*>(&input), sizeof(input));
    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());

    EXPECT_TRUE(buffer);    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(4u, buffer.getSize());
    EXPECT_EQ(input, output);
}
TEST(AlbaMemoryBufferTest, MemoryBufferCanBeCopied)
{
    AlbaMemoryBuffer buffer;
    int input = 11111111;
    buffer.addData(static_cast<void*>(&input), sizeof(input));
    AlbaMemoryBuffer buffer2(buffer);
    int output = *reinterpret_cast<int*>(buffer2.getBufferPointer());
    EXPECT_TRUE(buffer2);
    EXPECT_TRUE(buffer2.hasContent());
    EXPECT_EQ(4u, buffer2.getSize());    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, MemoryBufferCanBeResizedToBeLarger)
{
    AlbaMemoryBuffer buffer;
    int input = 11111111;
    buffer.addData(static_cast<void*>(&input), sizeof(input));
    buffer.resize(8);
    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(8u, buffer.getSize());    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, MemoryBufferCanBeResizedToBeSmaller)
{
    AlbaMemoryBuffer buffer;
    int input = 0x12345678;
    buffer.addData(static_cast<void*>(&input), sizeof(input));
    buffer.resize(3);
    char* bufferPointer = reinterpret_cast<char*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(3u, buffer.getSize());    EXPECT_EQ(0x78, bufferPointer[0]);
    EXPECT_EQ(0x56, bufferPointer[1]);
    EXPECT_EQ(0x34, bufferPointer[2]);
}

TEST(AlbaMemoryBufferTest, PrimitiveTypesCanBeClearedAndSavedConsecutively2Times)
{
    AlbaMemoryBuffer buffer;
    int input = 11111111, input2 = 22222222;
    buffer.clearAndSetNewData(static_cast<void*>(&input), sizeof(input));
    buffer.clearAndSetNewData(static_cast<void*>(&input2), sizeof(input2));
    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());

    EXPECT_TRUE(buffer);    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(4u, buffer.getSize());
    EXPECT_EQ(input2, output);
}
TEST(AlbaMemoryBufferTest, StructureCanBeSaved)
{
    AlbaMemoryBuffer buffer;
    struct Sample
    {
        bool param1;
        int param2;
        double param3;
    };

    Sample input;
    input.param1 = true;
    input.param2 = 12345678;
    input.param3 = 1.234E56;
    buffer.addData(static_cast<void*>(&input), sizeof(input));
    Sample output = *reinterpret_cast<Sample *>(buffer.getBufferPointer());

    EXPECT_TRUE(buffer);    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(sizeof(Sample), buffer.getSize());
    EXPECT_EQ(input.param1, output.param1);
    EXPECT_EQ(input.param2, output.param2);    EXPECT_EQ(input.param3, output.param3);
}

TEST(AlbaMemoryBufferTest, DataForMemoryBufferCanBeWrittenConsecutivelyOutsideTheClass)
{
    AlbaMemoryBuffer buffer;
    unsigned char inputBuffer1[] = {0x12, 0x34, 0x56, 0x78};
    unsigned char inputBuffer2[] = {0x87, 0x65, 0x43, 0x21};
    memcpy(buffer.resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(4), inputBuffer1, 4);
    memcpy(buffer.resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(4), inputBuffer2, 4);

    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(8u, buffer.getSize());

    unsigned char* reader = reinterpret_cast<unsigned char*>(buffer.getBufferPointer());
    EXPECT_EQ(0x12u, reader[0]);
    EXPECT_EQ(0x34u, reader[1]);
    EXPECT_EQ(0x56u, reader[2]);
    EXPECT_EQ(0x78u, reader[3]);
    EXPECT_EQ(0x87u, reader[4]);
    EXPECT_EQ(0x65u, reader[5]);
    EXPECT_EQ(0x43u, reader[6]);
    EXPECT_EQ(0x21u, reader[7]);
}

TEST(AlbaMemoryBufferTest, GetDisplayableStringWorks)
{
    int input = 0x12345678;
    AlbaMemoryBuffer buffer(static_cast<void*>(&input), sizeof(input));

    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());    EXPECT_EQ(4u, buffer.getSize());
    EXPECT_FALSE(buffer.getDisplayableString().empty());
}

TEST(AlbaMemoryBufferTest, SettingAndRetrievingPrimitiveObjectWorks)
{
    AlbaMemoryBuffer buffer;
    int input = 0x12345678;
    buffer.saveObject<int>(input);
    int& output(buffer.retrieveObject<int>());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, SettingAndRetrievingDynamicSizeObjectWorks)
{
    AlbaMemoryBuffer buffer;
    struct SampleDynamicClass
    {
        vector<int> integers;
    };
    SampleDynamicClass dynamicInput;
    dynamicInput.integers.emplace_back(11);
    dynamicInput.integers.emplace_back(22);
    dynamicInput.integers.emplace_back(33);
    dynamicInput.integers.emplace_back(44);
    buffer.saveObject<SampleDynamicClass>(dynamicInput);
    SampleDynamicClass& output(buffer.retrieveObject<SampleDynamicClass>());
    ASSERT_EQ(4, output.integers.size());
    EXPECT_EQ(11, output.integers[0]);
    EXPECT_EQ(22, output.integers[1]);
    EXPECT_EQ(33, output.integers[2]);
    EXPECT_EQ(44, output.integers[3]);
}

}