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
    using SymbolTableUsingTrie = TernarySearchTrie<DataType>;
    static constexpr DataType CODE_WORD_WIDTH = 12;
    static constexpr DataType NUMBER_CODE_WORDS = 1 << CODE_WORD_WIDTH;

    LzwCompression()
    {}

    void compress(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);

        std::string wholeInputString(readWholeInputString(input, reader));

        SymbolTableUsingTrie codeTable(buildCodeTableWithAllCharacters());
        DataType lastCode(RADIX+1);

        while(!wholeInputString.empty())
        {
            std::string maxPrefixMatch(codeTable.getLongestPrefixOf(wholeInputString));
            writeCodeBasedFromString(writer, codeTable, maxPrefixMatch);
            DataType maxPrefixMatchLength(maxPrefixMatch.length());
            if(maxPrefixMatchLength < wholeInputString.length() && lastCode < NUMBER_CODE_WORDS)
            {
                codeTable.put(wholeInputString.substr(0, maxPrefixMatchLength + 1), lastCode++); // put combination of letters on code table
            }
            wholeInputString = wholeInputString.substr(maxPrefixMatchLength);
        }
        writeCode(writer, RADIX);
    }

    void expand(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);

        stringHelper::strings lookupTable(buildLookUpTableFromAllCharacters());

        DataType codeword = readOneCodeword(reader);
        std::string value(lookupTable.at(codeword));

        DataType lastIndex = RADIX+2;
        while(true)
        {
            writer.writeStringData(value);
            codeword = readOneCodeword(reader);
            if(!input.eof() && codeword != RADIX)
            {
                std::string stringAtCode(lookupTable.at(codeword));
                if(codeword == lastIndex)
                {
                    stringAtCode = value + value.at(0);
                }
                if(lastIndex < NUMBER_CODE_WORDS)
                {
                    lookupTable.emplace_back(value + stringAtCode.at(0));
                    lastIndex++;
                }
                value = stringAtCode;
            }
            else
            {
                break;
            }
        }
    }

private:
    std::string readWholeInputString(std::istream & input, AlbaStreamBitReader & reader)
    {
        std::string result;
        while(true)
        {
            char c(reader.readCharData());
            if(!input.eof())
            {
                result += c;
            }
            else
            {
                break;
            }
        }
        return result;
    }

    SymbolTableUsingTrie buildCodeTableWithAllCharacters()
    {
        SymbolTableUsingTrie codeTable;
        for(DataType c=0; c < RADIX; c++)
        {
            codeTable.put(std::string()+static_cast<char>(c), static_cast<DataType>(c));
        }
        return codeTable;
    }

    stringHelper::strings buildLookUpTableFromAllCharacters()
    {
        stringHelper::strings lookupTable;
        for(DataType c=0; c < RADIX; c++)
        {
            lookupTable.emplace_back(std::string()+static_cast<char>(c));
        }
        lookupTable.emplace_back(" "); // assign one for end of stream
        return lookupTable;
    }

    void writeCodeBasedFromString(AlbaStreamBitWriter & writer, TernarySearchTrie<DataType> const& codeTable, std::string const& stringToWrite)
    {
        writeCode(writer, codeTable.get(stringToWrite));
    }

    void writeCode(AlbaStreamBitWriter & writer, DataType const& code)
    {
        std::bitset<CODE_WORD_WIDTH> bitsetToWrite(code);
        writer.writeBitsetData(bitsetToWrite, CODE_WORD_WIDTH-1, 0);
    }

    DataType readOneCodeword(AlbaStreamBitReader & reader)
    {
        std::bitset<CODE_WORD_WIDTH> bitsetCodeword(reader.readBitsetData<CODE_WORD_WIDTH>(static_cast<unsigned int>(CODE_WORD_WIDTH-1), static_cast<unsigned int>(0)));
        return static_cast<DataType>(bitsetCodeword.to_ullong());
    }

};


}

}
