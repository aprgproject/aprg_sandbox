#pragma once

#include <Common/Optional/AlbaOptional.hpp>
#include <Common/Stream/AlbaStreamBitReader.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <array>
#include <iostream>
#include <memory>
#include <queue>

namespace alba
{

namespace algorithm
{

template <unsigned int RADIX, typename Index>
class HuffmanCompression
{
public :

    using FrequencyOfEachCharacter = std::array<Index, RADIX>;
    struct CharacterFrequency
    {
        CharacterFrequency(char const characterAsParameter, Index const frequencyAsParameter, bool const isProritizedAsParameter)
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
        Index frequency;
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

    void expand(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);
        TrieNodeUniquePointer root(readTrie(reader));
        Index lengthOfString(reader.readNumberData<Index>(AlbaStreamBitEndianType::BigEndian));
        for(Index i=0; i<lengthOfString; i++)
        {
            TrieNode const* currentNodePointer(root.get());
            while(!currentNodePointer->isLeaf() && !input.eof())
            {
                bool bit(reader.readBoolData());
                if(!input.eof())
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
            }
            writer.writeCharData(currentNodePointer->character);
        }
    }

    void compress(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);
        std::vector<char> charactersInput;
        while(!input.eof())
        {
            char c(reader.readCharData());
            if(!input.eof())
            {
                charactersInput.emplace_back(c);
            }
        }

        FrequencyOfEachCharacter frequency{};
        for(Index i=0; i< charactersInput.size(); i++)
        {
            frequency[charactersInput.at(i)]++;
        }

        TrieNodeUniquePointer root(buildTrie(frequency));
        stringHelper::strings huffmanCodeTable(buildHuffmanCodeTableFromTrie(root));

        writeTrie(writer, root);
        writer.writeNumberData<Index>(AlbaStreamBitEndianType::BigEndian, charactersInput.size());

        for(Index i=0; i< charactersInput.size(); i++)
        {
            std::string const& huffmanCode(huffmanCodeTable.at(charactersInput.at(i)));
            for(char const c : huffmanCode)
            {
                if(c == '1' || c == '0')
                {
                    writer.writeBoolData(c == '1');
                }
            }
        }
    }

private:

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
        std::priority_queue<CharacterFrequency, std::vector<CharacterFrequency>, std::greater<CharacterFrequency>> characterFrequencies; // min priority queue
        std::array<TrieNodeArrayEntry, RADIX> nodePerCharacter{};
        for(Index c=0; c < RADIX; c++)
        {
            if(frequency.at(c) > 0)
            {
                characterFrequencies.emplace(static_cast<char>(c), frequency.at(c), false);
                nodePerCharacter[c].node = std::make_unique<TrieNode>(static_cast<char>(c), nullptr, nullptr);
            }
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

    stringHelper::strings buildHuffmanCodeTableFromTrie(TrieNodeUniquePointer const& root)
    {
        stringHelper::strings lookupTable(RADIX, std::string());
        buildHuffmanCodeTableFromTrie(lookupTable, root, "");
        return lookupTable;
    }

    void buildHuffmanCodeTableFromTrie(stringHelper::strings & lookupTable, TrieNodeUniquePointer const& nodePointer, std::string const& s)
    {
        if(nodePointer)
        {
            if(nodePointer->isLeaf())
            {
                lookupTable[nodePointer->character] = s;
            }
            else
            {
                buildHuffmanCodeTableFromTrie(lookupTable, nodePointer->left, s + '0');
                buildHuffmanCodeTableFromTrie(lookupTable, nodePointer->right, s + '1');
            }
        }
    }
};


}

}
