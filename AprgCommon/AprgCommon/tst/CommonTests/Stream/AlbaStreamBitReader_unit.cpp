#include <Common/Stream/AlbaStreamBitReader.hpp>

#include <gtest/gtest.h>

#include <sstream>

using namespace std;

namespace alba
{

TEST(AlbaStreamBitReaderTest, ReadBoolDataWorks)
{
    stringstream ss;
    ss << "A";
    AlbaStreamBitReader reader(ss);

    EXPECT_FALSE(reader.readBoolData());
    EXPECT_TRUE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_TRUE(reader.readBoolData());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadCharDataWorks)
{
    stringstream ss;
    ss << "./*";
    AlbaStreamBitReader reader(ss);

    EXPECT_EQ('.', reader.readCharData());
    EXPECT_EQ('/', reader.readCharData());
    EXPECT_EQ('*', reader.readCharData());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadStringDataWorks)
{
    stringstream ss;
    ss << "./*";
    AlbaStreamBitReader reader(ss);

    EXPECT_EQ("./", reader.readStringData(2));
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadWholeStreamAsStringDataWorks)
{
    stringstream ss;
    ss << "./*";
    AlbaStreamBitReader reader(ss);

    EXPECT_EQ("./*", reader.readWholeStreamAsStringData());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadNumberDataWorks)
{
    stringstream ss;    ss.put(0x01);
    ss.put(0x02);
    ss.put(0x03);
    ss.put(0x04);    ss.put(0x01);
    ss.put(0x02);
    ss.put(0x03);
    ss.put(0x04);
    AlbaStreamBitReader reader(ss);

    EXPECT_EQ(0x01020304U, reader.readNumberData<unsigned int>(AlbaStreamBitEndianType::BigEndian));
    EXPECT_EQ(0x04030201U, reader.readNumberData<unsigned int>(AlbaStreamBitEndianType::LittleEndian));
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadBigEndianNumberDataWorks)
{
    stringstream ss;
    ss.put(0x01);
    ss.put(0x02);
    ss.put(0x03);
    ss.put(0x04);
    AlbaStreamBitReader reader(ss);

    EXPECT_EQ(0x01020304U, reader.readBigEndianNumberData<unsigned int>());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadLittleEndianNumberDataWorks)
{
    stringstream ss;
    ss.put(0x01);
    ss.put(0x02);
    ss.put(0x03);
    ss.put(0x04);
    AlbaStreamBitReader reader(ss);

    EXPECT_EQ(0x04030201U, reader.readLittleEndianNumberData<unsigned int>());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadBitsetDataWorks)
{
    stringstream ss;    ss.put(0x12);
    ss.put(0x34);
    AlbaStreamBitReader reader(ss);
    EXPECT_EQ(0x00000C48U, static_cast<unsigned int>(reader.readBitsetData<32>(0, 11).to_ulong())); //swapped due to reversed index
    EXPECT_FALSE(reader.noRemainingBitsInBuffer()); // 4Bits remaining
}

}
