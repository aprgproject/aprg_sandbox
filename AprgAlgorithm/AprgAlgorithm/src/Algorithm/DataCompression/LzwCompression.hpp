#pragma once

#include <Common/Stream/AlbaStreamBitReader.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Algorithm/String/Tries/TernarySearchTrie.hpp>

#include <iostream>

namespace alba
{

namespace algorithm
{

template <unsigned int RADIX, typename DataType>
class LzwCompression
{
public :
    static constexpr DataType CODE_WORD_WIDTH = 12;
    static constexpr DataType NUMBER_CODE_WORDS = 1 << CODE_WORD_WIDTH;

    LzwCompression()
    {}

    void compress(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);

        std::string inputString(readWholeInputString(input, reader));

        TernarySearchTrie<DataType> symbolTable;
        for(DataType c=0; c < RADIX; c++)
        {
            symbolTable.put(std::string()+static_cast<char>(c), static_cast<DataType>(c));
        }
        DataType lastCode(RADIX+1);

        while(!inputString.empty())
        {
            std::string maxPrefixMatch(symbolTable.getLongestPrefixOf(inputString));
            std::bitset<CODE_WORD_WIDTH> bitsetToWrite(symbolTable.get(maxPrefixMatch));
            writer.writeBitsetData(bitsetToWrite, CODE_WORD_WIDTH-1, 0);
            DataType maxPrefixMatchLength(maxPrefixMatch.length());
            if(maxPrefixMatchLength < inputString.length() && lastCode < NUMBER_CODE_WORDS)
            {
                symbolTable.put(inputString.substr(0, maxPrefixMatchLength + 1), lastCode++);
            }
            inputString = inputString.substr(maxPrefixMatchLength);
        }

        std::bitset<CODE_WORD_WIDTH> bitsetToWrite(RADIX);
        writer.writeBitsetData(bitsetToWrite, CODE_WORD_WIDTH-1, 0);
    }

    void expand(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);
        stringHelper::strings lookupTable;

        for(DataType c=0; c < RADIX; c++)
        {
            lookupTable.emplace_back(std::string()+static_cast<char>(c));
        }
        lookupTable.emplace_back(" ");

        std::bitset<CODE_WORD_WIDTH> bitsetCodeword(reader.readBitsetData<CODE_WORD_WIDTH>(static_cast<unsigned int>(CODE_WORD_WIDTH-1), static_cast<unsigned int>(0)));
        DataType codeword(static_cast<DataType>(bitsetCodeword.to_ullong()));
        std::string value(lookupTable.at(codeword));

        DataType lastIndex = RADIX+2;
        while(true)
        {
            writer.writeStringData(value);
            std::bitset<CODE_WORD_WIDTH> bitsetCodeword = reader.readBitsetData<CODE_WORD_WIDTH>(static_cast<unsigned int>(CODE_WORD_WIDTH-1), static_cast<unsigned int>(0));
            codeword = static_cast<DataType>(bitsetCodeword.to_ullong());
            if(!input.eof() && codeword != RADIX)
            {
                std::string s = lookupTable.at(codeword);
                if(codeword == lastIndex)
                {
                    s = value + value.at(0);
                }
                if(lastIndex < NUMBER_CODE_WORDS)
                {
                    lookupTable.emplace_back(value + s.at(0));
                    lastIndex++;
                }
                value = s;
            }
            else
            {
                break;
            }
        }
    }

private:
    std::string readWholeInputString(std::istream& input, AlbaStreamBitReader reader)
    {
        std::string inputString;
        while(!input.eof())
        {
            char c(reader.readCharData());
            if(!input.eof())
            {
                inputString += c;
            }
        }

        return inputString;
    }

};


}

}
