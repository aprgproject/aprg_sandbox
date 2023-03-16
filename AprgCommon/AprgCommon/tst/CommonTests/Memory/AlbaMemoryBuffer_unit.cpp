#include <Common/Memory/AlbaMemoryBuffer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaMemoryBufferTest, DefaultConstructorWorks)
{
    AlbaMemoryBuffer buffer;

    EXPECT_FALSE(buffer);
    EXPECT_FALSE(buffer.hasContent());
    EXPECT_EQ(0U, buffer.getSize());
}

TEST(AlbaMemoryBufferTest, ConstructorWithPointerAndSizeWorks)
{
    int input = 11111111;

    AlbaMemoryBuffer buffer(static_cast<void*>(&input), sizeof(input));

    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(4U, buffer.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, CopyConstructorWorks)
{
    int input = 11111111;
    AlbaMemoryBuffer buffer1(static_cast<void*>(&input), sizeof(input));

    AlbaMemoryBuffer buffer2(buffer1);

    int output = *reinterpret_cast<int*>(buffer2.getBufferPointer());
    EXPECT_TRUE(buffer2);
    EXPECT_TRUE(buffer2.hasContent());
    EXPECT_EQ(4U, buffer2.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, CopyAssignmentWorks)
{
    int input = 11111111;
    AlbaMemoryBuffer buffer1(static_cast<void*>(&input), sizeof(input));
    AlbaMemoryBuffer buffer2;

    buffer2 = buffer1;

    int output = *reinterpret_cast<int*>(buffer2.getBufferPointer());
    EXPECT_TRUE(buffer2);
    EXPECT_TRUE(buffer2.hasContent());
    EXPECT_EQ(4U, buffer2.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, MoveConstructorWorks)
{
    int input = 11111111;
    AlbaMemoryBuffer buffer1(static_cast<void*>(&input), sizeof(input));

    AlbaMemoryBuffer buffer2(move(buffer1));

    EXPECT_FALSE(buffer1.hasContent());
    EXPECT_EQ(0U, buffer1.getSize());
    int output2 = *reinterpret_cast<int*>(buffer2.getBufferPointer());
    EXPECT_TRUE(buffer2);
    EXPECT_TRUE(buffer2.hasContent());
    EXPECT_EQ(4U, buffer2.getSize());
    EXPECT_EQ(input, output2);
}

TEST(AlbaMemoryBufferTest, MoveAssignmentWorks)
{
    int input = 11111111;
    AlbaMemoryBuffer buffer1(static_cast<void*>(&input), sizeof(input));
    AlbaMemoryBuffer buffer2;

    buffer2 = move(buffer1);

    EXPECT_FALSE(buffer1.hasContent());
    EXPECT_EQ(0U, buffer1.getSize());
    int output2 = *reinterpret_cast<int*>(buffer2.getBufferPointer());
    EXPECT_TRUE(buffer2);
    EXPECT_TRUE(buffer2.hasContent());
    EXPECT_EQ(4U, buffer2.getSize());
    EXPECT_EQ(input, output2);
}

TEST(AlbaMemoryBufferTest, ResizeWorksOnMakingTheBufferLarger)
{
    int input = 11111111;
    AlbaMemoryBuffer buffer(static_cast<void*>(&input), sizeof(input));

    buffer.resize(8);

    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(8U, buffer.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, ResizeWorksOnMakingTheBufferSmaller)
{
    int input = 0x12345678;
    AlbaMemoryBuffer buffer(static_cast<void*>(&input), sizeof(input));

    buffer.resize(3);

    char* bufferPointer = reinterpret_cast<char*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(3U, buffer.getSize());
    EXPECT_EQ(0x78, bufferPointer[0]);
    EXPECT_EQ(0x56, bufferPointer[1]);
    EXPECT_EQ(0x34, bufferPointer[2]);
}

TEST(AlbaMemoryBufferTest, ClearAndSetNewDataWorks)
{
    int input = 11111111, input2 = 22222222;
    AlbaMemoryBuffer buffer;

    buffer.clearAndSetNewData(static_cast<void*>(&input), sizeof(input));
    buffer.clearAndSetNewData(static_cast<void*>(&input2), sizeof(input2));

    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(4U, buffer.getSize());
    EXPECT_EQ(input2, output);
}

TEST(AlbaMemoryBufferTest, ResizeWithAdditionalSizeAndReturnBeginOfAdditionalDataWorks)
{
    AlbaMemoryBuffer buffer;
    unsigned char inputBuffer1[] = {0x12, 0x34, 0x56, 0x78};
    unsigned char inputBuffer2[] = {0x87, 0x65, 0x43, 0x21};

    memcpy(buffer.resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(4), inputBuffer1, 4);
    memcpy(buffer.resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(4), inputBuffer2, 4);

    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(8U, buffer.getSize());
    unsigned char* reader = reinterpret_cast<unsigned char*>(buffer.getBufferPointer());
    EXPECT_EQ(0x12U, reader[0]);
    EXPECT_EQ(0x34U, reader[1]);
    EXPECT_EQ(0x56U, reader[2]);
    EXPECT_EQ(0x78U, reader[3]);
    EXPECT_EQ(0x87U, reader[4]);
    EXPECT_EQ(0x65U, reader[5]);
    EXPECT_EQ(0x43U, reader[6]);
    EXPECT_EQ(0x21U, reader[7]);
}

TEST(AlbaMemoryBufferTest, AddDataWorksOnPrimitiveTypes)
{
    int input = 11111111;
    AlbaMemoryBuffer buffer;

    buffer.addData(static_cast<void*>(&input), sizeof(input));

    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(4U, buffer.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, AddDataWorksOnPodStructure)
{
    AlbaMemoryBuffer buffer;
    struct Sample
    {
        bool param1;
        int param2;
        double param3;
    };
    Sample input{};
    input.param1 = true;
    input.param2 = 12345678;
    input.param3 = 1.234E56;

    buffer.addData(static_cast<void*>(&input), sizeof(input));

    Sample output = *reinterpret_cast<Sample *>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(sizeof(Sample), buffer.getSize());
    EXPECT_EQ(input.param1, output.param1);
    EXPECT_EQ(input.param2, output.param2);
    EXPECT_EQ(input.param3, output.param3);
}

TEST(AlbaMemoryBufferTest, SaveObjectWorksOnPrimitiveTypes)
{
    AlbaMemoryBuffer buffer;
    int input = 0x12345678;

    buffer.saveObject<int>(input);

    int& output(buffer.retrieveObjectAsReference<int>());
    EXPECT_EQ(input, buffer.retrieveObjectAsConstReference<int>());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, SaveObjectWorksOnDynamicTypes)
{
    AlbaMemoryBuffer buffer;
    struct SampleDynamicClass
    {
        vector<int> integers;
    };
    SampleDynamicClass dynamicInput;
    dynamicInput.integers = vector<int>{11, 22, 33, 44, 55};

    buffer.saveObject<SampleDynamicClass>(dynamicInput);

    SampleDynamicClass& output(buffer.retrieveObjectAsReference<SampleDynamicClass>());
    EXPECT_EQ((vector<int>{11, 22, 33, 44, 55}), output.integers);
}

TEST(AlbaMemoryBufferTest, OutputStreamOperatorWorks)
{
    int input = 0x12345678;
    AlbaMemoryBuffer buffer(static_cast<void*>(&input), sizeof(input));
    stringstream ss;

    ss<<buffer;

    EXPECT_EQ("Decimal values: {120, 86, 52, 18, }\nHexadecimal values: {78, 56, 34, 12, }\n", ss.str());
}

}
