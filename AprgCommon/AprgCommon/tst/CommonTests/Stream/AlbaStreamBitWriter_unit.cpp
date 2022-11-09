#include <Common/Stream/AlbaStreamBitWriter.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <sstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

TEST(AlbaStreamBitWriterTest, WriteBoolDataWorks)
{
    stringstream ss;
    AlbaStreamBitWriter writer(ss);

    writer.writeBoolData(false);
    writer.writeBoolData(false);
    writer.writeBoolData(true);
    writer.writeBoolData(true);
    writer.writeBoolData(false);
    writer.writeBoolData(false);
    writer.writeBoolData(true);
    writer.writeBoolData(true);

    EXPECT_EQ(R"(3)", ss.str());
}

TEST(AlbaStreamBitWriterTest, WriteCharDataWorks)
{
    stringstream ss;
    AlbaStreamBitWriter writer(ss);

    writer.writeCharData('.');
    writer.writeCharData('/');
    writer.writeCharData('*');

    EXPECT_EQ(R"(./*)", ss.str());
}

TEST(AlbaStreamBitWriterTest, WriteStringDataWorks)
{
    stringstream ss;
    AlbaStreamBitWriter writer(ss);

    writer.writeStringData("A1BA");

    EXPECT_EQ(R"(A1BA)", ss.str());
}

TEST(AlbaStreamBitWriterTest, WriteHexDigitDataWorks)
{
    stringstream ss;
    AlbaStreamBitWriter writer(ss);

    writer.writeHexDigitData("A1BAA1BA");

    EXPECT_EQ(R"(A1BAA1BA)", getHexEquivalentOfCharacters(ss.str()));
}

TEST(AlbaStreamBitWriterTest, WriteNumberDataWorks)
{
    stringstream ss;
    AlbaStreamBitWriter writer(ss);

    writer.writeNumberData<unsigned int>(AlbaStreamBitEndianType::BigEndian, 0x01020304);
    writer.writeNumberData<unsigned int>(AlbaStreamBitEndianType::LittleEndian, 0x01020304);

    EXPECT_EQ(R"(0102030404030201)", getHexEquivalentOfCharacters(ss.str()));
}

TEST(AlbaStreamBitWriterTest, WriteBigEndianNumberDataWorks)
{
    stringstream ss;
    AlbaStreamBitWriter writer(ss);

    writer.writeBigEndianNumberData<unsigned int>(0x01020304);

    EXPECT_EQ(R"(01020304)", getHexEquivalentOfCharacters(ss.str()));
}

TEST(AlbaStreamBitWriterTest, WriteLittleEndianNumberDataWorks)
{
    stringstream ss;
    AlbaStreamBitWriter writer(ss);

    writer.writeLittleEndianNumberData<unsigned int>(0x01020304);

    EXPECT_EQ(R"(04030201)", getHexEquivalentOfCharacters(ss.str()));
}

TEST(AlbaStreamBitWriterTest, WriteBitsetDataWorks)
{
    stringstream ss;
    AlbaStreamBitWriter writer(ss);
    bitset<32U> bitsetToWrite(0x12345678);

    writer.writeBitsetData<32U>(bitsetToWrite, 15U, 22U);

    EXPECT_EQ(R"(16)", getHexEquivalentOfCharacters(ss.str()));
}

TEST(AlbaStreamBitWriterTest, FlushWorks)
{
    stringstream ss;
    AlbaStreamBitWriter writer(ss);
    writer.writeBoolData(true);

    writer.flush();

    EXPECT_EQ(R"(80)", getHexEquivalentOfCharacters(ss.str()));
}

}
