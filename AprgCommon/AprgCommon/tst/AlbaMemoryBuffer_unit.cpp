#include <Memory/AlbaMemoryBuffer.hpp>

#include <gtest/gtest.h>
using namespace alba;
using namespace std;
TEST(AlbaMemoryBufferTest, DefaultValuesAreClear)
{
    AlbaMemoryBuffer buffer;
    EXPECT_FALSE(buffer);
    EXPECT_EQ(0, buffer.getSize());
}

TEST(AlbaMemoryBufferTest, PrimitiveTypesCanBeSaved)
{
    AlbaMemoryBuffer buffer;
    int input = 11111111;
    buffer.setNewBuffer((void*)&input, sizeof(input));
    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());

    EXPECT_TRUE(buffer);
    EXPECT_EQ(4, buffer.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, MemoryBufferCanBeCopied)
{
    AlbaMemoryBuffer buffer;
    int input = 11111111;
    buffer.setNewBuffer((void*)&input, sizeof(input));
    AlbaMemoryBuffer buffer2(buffer);
    int output = *reinterpret_cast<int*>(buffer2.getBufferPointer());

    EXPECT_TRUE(buffer2);
    EXPECT_EQ(4, buffer2.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, PrimitiveTypesCanBeSavedConsecutively2Times)
{
    AlbaMemoryBuffer buffer;
    int input = 11111111, input2 = 22222222;
    buffer.setNewBuffer((void*)&input, sizeof(input));
    buffer.setNewBuffer((void*)&input2, sizeof(input2));
    int output = *reinterpret_cast<int*>(buffer.getBufferPointer());

    EXPECT_TRUE(buffer);
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
    buffer.setNewBuffer((void*)&input, sizeof(input));
    Sample output = *reinterpret_cast<Sample *>(buffer.getBufferPointer());

    EXPECT_TRUE(buffer);
    EXPECT_EQ(sizeof(Sample), buffer.getSize());
    EXPECT_EQ(input.param1, output.param1);
    EXPECT_EQ(input.param2, output.param2);
    EXPECT_EQ(input.param3, output.param3);
}
