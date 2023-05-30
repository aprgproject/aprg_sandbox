#include <Algorithm/String/Alphabet/Alphabet.hpp>
#include <Common/Bit/AlbaBitField.hpp>
#include <Common/Stream/AlbaStreamBitReader.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>

#include <gtest/gtest.h>

#include <bitset>

using namespace std;

namespace alba {

namespace algorithm {

namespace {

string compressCharactersToValues(string const& characters) {
    Alphabet<uint8_t> dnaAlphabet("ACTG");
    stringstream inputSs;
    inputSs << characters;
    stringstream outputSs;
    AlbaStreamBitReader reader(inputSs);
    AlbaStreamBitWriter writer(outputSs);
    while (true) {
        bitset<2> valueBitset(dnaAlphabet.getDigitValue(reader.readCharData()));
        if (!inputSs.eof()) {
            writer.writeBitsetData<2>(valueBitset, 0, 1);
        } else {
            break;
        }
    }
    writer.flush();
    return outputSs.str();
}

string expandValuesToCharacters(string const& characters) {
    Alphabet<uint8_t> dnaAlphabet("ACTG");
    stringstream inputSs;
    inputSs << characters;
    stringstream outputSs;
    AlbaStreamBitReader reader(inputSs);
    AlbaStreamBitWriter writer(outputSs);
    while (true) {
        bitset<2> valueBitset(reader.readBitsetData<2>(0, 1));
        if (!inputSs.eof()) {
            writer.writeCharData(dnaAlphabet.getCharacter(static_cast<uint8_t>(valueBitset.to_ulong())));
        } else {
            break;
        }
    }
    writer.flush();
    return outputSs.str();
}

}  // namespace

TEST(GenomicExampleTest, CompressCharactersToValuesWorks) {
    EXPECT_EQ("\x13\x1E\x13", compressCharactersToValues("ATAGATGCATAG"));
}

TEST(GenomicExampleTest, ExpandValuesToCharactersWorks) {
    EXPECT_EQ("ATAGATGCATAG", expandValuesToCharacters("\x13\x1E\x13"));
}

}  // namespace algorithm

}  // namespace alba
