#pragma once

#include <Common/Stream/AlbaStreamBitReader.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>

#include <array>
#include <iostream>
#include <memory>
#include <queue>

namespace alba
{

namespace algorithm
{

template <typename DataType>
class HuffmanCompression
{
public :
    static constexpr unsigned int RADIX=256U;

    using Characters = std::vector<char>;
    using HuffmanCode = std::vector<bool>;
    using FrequencyOfEachCharacter = std::array<DataType, RADIX>;
    using HuffmanCodeTable = std::array<HuffmanCode, RADIX>;
    struct CharacterFrequency
    {
        CharacterFrequency(char const characterAsParameter, DataType const frequencyAsParameter, bool const isProritizedAsParameter)
            : character(characterAsParameter)
            , frequency(frequencyAsParameter)
            , isProritized(isProritizedAsParameter)
        {}

        bool operator>(CharacterFrequency const& second) const
        {
            bool result(false);
            if(frequency != second.frequency)
            {
                result = frequency > second.frequency;
            }
            else
            {
                if(isProritized != second.isProritized)
                {
                    result = isProritized < second.isProritized;
                }
                else
                {
                    result = frequency > second.frequency;
                }
            }
            return result;
        }

        char character;
        DataType frequency;
        bool isProritized;
    };
    struct TrieNode;
    using TrieNodeUniquePointer = std::unique_ptr<TrieNode>;
    struct TrieNode
    {
        TrieNode(char const characterAsParameter, TrieNodeUniquePointer leftAsParameter, TrieNodeUniquePointer rightAsParameter)
            : character(characterAsParameter)
            , left(std::move(leftAsParameter))
            , right(std::move(rightAsParameter))
        {}

        bool isLeaf() const
        {
            return !left && !right;
        }
        char character;
        TrieNodeUniquePointer left;
        TrieNodeUniquePointer right;
    };

    struct TrieNodeArrayEntry
    {
        TrieNodeArrayEntry()
        {}

        TrieNodeArrayEntry(TrieNodeArrayEntry const&) // copying does nothing
        {}

        TrieNodeUniquePointer node;
    };

    HuffmanCompression()
    {}

    void compress(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);

        Characters allInputCharacters(readAllCharacters(reader));
        FrequencyOfEachCharacter frequency(getFrequencyOfEachCharacter(allInputCharacters));

        TrieNodeUniquePointer root(buildTrie(frequency));
        HuffmanCodeTable huffmanCodeTable(buildHuffmanCodeTableFromTrie(root));

        writeTrie(writer, root);
        writer.writeNumberData<DataType>(AlbaStreamBitEndianType::BigEndian, allInputCharacters.size());
        writeHuffmanCodes(writer, allInputCharacters, huffmanCodeTable);
    }

    void expand(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);

        TrieNodeUniquePointer root(readTrie(reader));
        DataType lengthOfString(reader.readNumberData<DataType>(AlbaStreamBitEndianType::BigEndian));
        expandAllCharacters(reader, writer, root, lengthOfString);
    }

private:

    Characters readAllCharacters(AlbaStreamBitReader & reader)
    {
        Characters result;
        while(true)
        {
            char c(reader.readCharData());
            if(!reader.getInputStream().eof())
            {
                result.emplace_back(c);
            }
            else
            {
                break;
            }
        }
        return result;
    }

    FrequencyOfEachCharacter getFrequencyOfEachCharacter(Characters const& charactersInput)
    {
        FrequencyOfEachCharacter frequency{};
        for(DataType i=0; i< charactersInput.size(); i++)
        {
            frequency[charactersInput.at(i)]++;
        }
        return frequency;
    }

    void writeHuffmanCodes(AlbaStreamBitWriter & writer, Characters const& wholeInput, HuffmanCodeTable const& huffmanCodeTable)
    {
        for(DataType i=0; i< wholeInput.size(); i++)
        {
            HuffmanCode const& huffmanCode(huffmanCodeTable.at(wholeInput.at(i)));
            for(bool const b : huffmanCode)
            {
                writer.writeBoolData(b);
            }
        }
    }

    void expandAllCharacters(AlbaStreamBitReader & reader, AlbaStreamBitWriter & writer, TrieNodeUniquePointer const& root, DataType const lengthOfString)
    {
        for(DataType i=0; i<lengthOfString; i++)
        {
            expandOneCharacterBasedFromTrieAndCode(reader, writer, root);
        }
    }

    void expandOneCharacterBasedFromTrieAndCode(AlbaStreamBitReader & reader, AlbaStreamBitWriter & writer, TrieNodeUniquePointer const& root)
    {
        TrieNode const* currentNodePointer(root.get());
        while(!currentNodePointer->isLeaf())
        {
            bool bit(reader.readBoolData());
            if(!reader.getInputStream().eof())
            {
                if(bit)
                {
                    currentNodePointer = currentNodePointer->right.get();
                }
                else
                {
                    currentNodePointer = currentNodePointer->left.get();
                }
            }
            else
            {
                break;
            }
        }
        writer.writeCharData(currentNodePointer->character);
    }

    void writeTrie(AlbaStreamBitWriter & writer, TrieNodeUniquePointer const& nodePointer)
    {
        if(nodePointer)
        {
            if(nodePointer->isLeaf())
            {
                writer.writeBoolData(true);
                writer.writeCharData(nodePointer->character);
            }
            else
            {
                writer.writeBoolData(false);
                writeTrie(writer, nodePointer->left);
                writeTrie(writer, nodePointer->right);
            }
        }
    }

    TrieNodeUniquePointer readTrie(AlbaStreamBitReader & reader)
    {
        TrieNodeUniquePointer result;
        bool bit(reader.readBoolData());
        if(!reader.getInputStream().eof())
        {
            if(bit) // this mean its a leaf
            {
                char c(reader.readCharData());
                result = std::make_unique<TrieNode>(c, nullptr, nullptr);
            }
            else // keep reading if not leaf
            {
                TrieNodeUniquePointer left(readTrie(reader));
                TrieNodeUniquePointer right(readTrie(reader));
                result = std::make_unique<TrieNode>('\0', std::move(left), std::move(right));
            }
        }
        return result;
    }

    TrieNodeUniquePointer buildTrie(FrequencyOfEachCharacter const& frequency)
    {
        std::priority_queue<CharacterFrequency, std::deque<CharacterFrequency>, std::greater<CharacterFrequency>> characterFrequencies; // min priority queue
        std::array<TrieNodeArrayEntry, RADIX> nodePerCharacter{};
        for(DataType c=0; c < RADIX; c++)
        {            if(frequency.at(c) > 0)
            {
                characterFrequencies.emplace(static_cast<char>(c), frequency.at(c), false);
                nodePerCharacter[c].node = std::make_unique<TrieNode>(static_cast<char>(c), nullptr, nullptr);            }
        }

        while(characterFrequencies.size() > 1)
        {
            CharacterFrequency first(characterFrequencies.top());
            characterFrequencies.pop();
            CharacterFrequency second(characterFrequencies.top());
            characterFrequencies.pop();
            characterFrequencies.emplace(first.character, first.frequency+second.frequency, true); //use first character to keep track
            TrieNodeUniquePointer firstNode(std::move(nodePerCharacter[first.character].node));
            TrieNodeUniquePointer secondNode(std::move(nodePerCharacter[second.character].node));
            nodePerCharacter[first.character].node = std::make_unique<TrieNode>('\0', std::move(firstNode), std::move(secondNode)); //only leafs have characters
        }
        CharacterFrequency last(characterFrequencies.top());
        return std::move(nodePerCharacter[last.character].node);
    }

    HuffmanCodeTable buildHuffmanCodeTableFromTrie(TrieNodeUniquePointer const& root)
    {
        HuffmanCodeTable result{};
        buildHuffmanCodeTableFromTrie(result, root, {});
        return result;
    }

    void buildHuffmanCodeTableFromTrie(HuffmanCodeTable & huffmanCodeTable, TrieNodeUniquePointer const& nodePointer, HuffmanCode const& huffmanCode)
    {
        if(nodePointer)
        {
            if(nodePointer->isLeaf())
            {
                huffmanCodeTable[nodePointer->character] = huffmanCode;
            }
            else
            {
                HuffmanCode newHuffmanCode(huffmanCode);
                newHuffmanCode.emplace_back(false);
                buildHuffmanCodeTableFromTrie(huffmanCodeTable, nodePointer->left, newHuffmanCode);
                newHuffmanCode.pop_back();
                newHuffmanCode.emplace_back(true);
                buildHuffmanCodeTableFromTrie(huffmanCodeTable, nodePointer->right, newHuffmanCode);
            }
        }
    }
};


}

}
