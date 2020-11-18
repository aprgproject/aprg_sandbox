#include <Memory/AlbaMemoryBuffer.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(AlbaMemoryBufferTest, DefaultValuesAreClear)
{
    AlbaMemoryBuffer buffer;
    EXPECT_FALSE(buffer);
    EXPECT_FALSE(buffer.hasContent());
    EXPECT_EQ(0, buffer.getSize());
}

TEST(AlbaMemoryBufferTest, PrimitiveTypesCanBeSavedDuringConstructionOfBuffer)
{
    int input = 11111111;
    AlbaMemoryBuffer buffer((void*)&input, sizeof(input));
    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());

    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(4, buffer.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, PrimitiveTypesCanBeSaved)
{
    AlbaMemoryBuffer buffer;
    int input = 11111111;
    buffer.addData((void*)&input, sizeof(input));
    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());

    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(4, buffer.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, MemoryBufferCanBeCopied)
{
    AlbaMemoryBuffer buffer;
    int input = 11111111;
    buffer.addData((void*)&input, sizeof(input));
    AlbaMemoryBuffer buffer2(buffer);
    int output = *reinterpret_cast<int*>(buffer2.getBufferPointer());

    EXPECT_TRUE(buffer2);
    EXPECT_TRUE(buffer2.hasContent());
    EXPECT_EQ(4, buffer2.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, PrimitiveTypesCanBeClearedAndSavedConsecutively2Times)
{
    AlbaMemoryBuffer buffer;
    int input = 11111111, input2 = 22222222;
    buffer.clearAndSetNewData((void*)&input, sizeof(input));
    buffer.clearAndSetNewData((void*)&input2, sizeof(input2));
    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());

    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(4, buffer.getSize());
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
    buffer.addData((void*)&input, sizeof(input));
    Sample output = *reinterpret_cast<Sample *>(buffer.getBufferPointer());

    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(sizeof(Sample), buffer.getSize());
    EXPECT_EQ(input.param1, output.param1);
    EXPECT_EQ(input.param2, output.param2);
    EXPECT_EQ(input.param3, output.param3);
}

TEST(AlbaMemoryBufferTest, DataForMemoryBufferCanBeWrittenConsecutivelyOutsideTheClass)
{
    AlbaMemoryBuffer buffer;
    unsigned char inputBuffer1[] = {0x12, 0x34, 0x56, 0x78};
    unsigned char inputBuffer2[] = {0x87, 0x65, 0x43, 0x21};
    memcpy(buffer.addDataForWritingOutside(4), inputBuffer1, 4);
    memcpy(buffer.addDataForWritingOutside(4), inputBuffer2, 4);

    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(8, buffer.getSize());

    unsigned char* reader = reinterpret_cast<unsigned char*>(buffer.getBufferPointer());
    EXPECT_EQ(0x12, reader[0]);
    EXPECT_EQ(0x34, reader[1]);
    EXPECT_EQ(0x56, reader[2]);
    EXPECT_EQ(0x78, reader[3]);
    EXPECT_EQ(0x87, reader[4]);
    EXPECT_EQ(0x65, reader[5]);
    EXPECT_EQ(0x43, reader[6]);
    EXPECT_EQ(0x21, reader[7]);
}

TEST(AlbaMemoryBufferTest, GetDisplayableStringWorks)
{
    int input = 0x12345678;
    AlbaMemoryBuffer buffer((void*)&input, sizeof(input));

    EXPECT_TRUE(buffer);
    EXPECT_TRUE(buffer.hasContent());
    EXPECT_EQ(4, buffer.getSize());
    EXPECT_FALSE(buffer.getDisplayableString().empty());
}
