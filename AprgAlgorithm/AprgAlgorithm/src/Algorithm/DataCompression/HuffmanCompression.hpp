#pragma once

#include <Common/Container/AlbaFakeCopyable.hpp>
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

template <typename Count>
class HuffmanCompression
{
public :
    static constexpr unsigned int RADIX=256U;

    using Characters = std::vector<char>;
    using HuffmanCode = std::vector<bool>;
    using FrequencyOfEachCharacter = std::array<Count, RADIX>;
    using HuffmanCodeTable = std::array<HuffmanCode, RADIX>;
    struct CharacterFrequency
    {
        CharacterFrequency(char const characterAsParameter, Count const frequencyAsParameter, bool const isProritizedAsParameter)
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
        Count frequency;
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
        char character; // not used if internal node
        TrieNodeUniquePointer left;
        TrieNodeUniquePointer right;
    };
    using TrieNodeArrayEntry=AlbaFakeCopyable<TrieNodeUniquePointer>;

    HuffmanCompression() = default;

    void compress(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);

        Characters allInputCharacters(readAllCharacters(reader));
        FrequencyOfEachCharacter frequency(getFrequencyOfEachCharacter(allInputCharacters));

        TrieNodeUniquePointer root(buildTrie(frequency));
        HuffmanCodeTable huffmanCodeTable(buildHuffmanCodeTableFromTrie(root));

        writeTrie(writer, root);
        writer.writeBigEndianNumberData<Count>(allInputCharacters.size());
        writeHuffmanCodes(writer, allInputCharacters, huffmanCodeTable);
    }

    void expand(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);

        TrieNodeUniquePointer root(readTrie(reader));
        Count lengthOfString(reader.readBigEndianNumberData<Count>());
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
        for(Count i=0; i< charactersInput.size(); i++)
        {
            frequency[charactersInput.at(i)]++;
        }
        return frequency;
    }

    void writeHuffmanCodes(AlbaStreamBitWriter & writer, Characters const& wholeInput, HuffmanCodeTable const& huffmanCodeTable)
    {
        for(Count i=0; i< wholeInput.size(); i++)
        {
            HuffmanCode const& huffmanCode(huffmanCodeTable.at(wholeInput.at(i)));
            for(bool const b : huffmanCode)
            {
                writer.writeBoolData(b);
            }
        }
    }

    void expandAllCharacters(AlbaStreamBitReader & reader, AlbaStreamBitWriter & writer, TrieNodeUniquePointer const& root, Count const lengthOfString)
    {
        for(Count i=0; i<lengthOfString; i++)
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
                if(bit) // if one, go to the right
                {
                    currentNodePointer = currentNodePointer->right.get();
                }
                else // if zero, go to the left
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
                // recursively read the left and read the right
                TrieNodeUniquePointer left(readTrie(reader));
                TrieNodeUniquePointer right(readTrie(reader));
                result = std::make_unique<TrieNode>('\0', std::move(left), std::move(right));
            }
        }
        return result;
    }

    TrieNodeUniquePointer buildTrie(FrequencyOfEachCharacter const& frequency)
    {
        // This is quite different from the original huffman algorithm
        // Here, frequency is not placed on the trie because its not really needed after building the trie.
        std::priority_queue<CharacterFrequency, std::deque<CharacterFrequency>, std::greater<CharacterFrequency>> frequenciesInMinimumOrder; // min priority queue
        std::array<TrieNodeArrayEntry, RADIX> characterNode{};
        for(Count c=0; c < RADIX; c++)
        {
            if(frequency.at(c) > 0)
            {
                frequenciesInMinimumOrder.emplace(static_cast<char>(c), frequency.at(c), false); // This PQ is used to prioritize low frequency characters first
                characterNode[c].getObjectReference() = std::make_unique<TrieNode>(static_cast<char>(c), nullptr, nullptr); // These character nodes are used to build trie later on
            }
        }

        while(frequenciesInMinimumOrder.size() > 1) // Needs to be 2 or higher because we are popping 2 items per iteration
        {
            // process the frequencies (minimum first) and build the trie by combining two nodes with lowest frequencies
            CharacterFrequency first(frequenciesInMinimumOrder.top());
            frequenciesInMinimumOrder.pop();
            CharacterFrequency second(frequenciesInMinimumOrder.top());
            frequenciesInMinimumOrder.pop();
            frequenciesInMinimumOrder.emplace(first.character, first.frequency+second.frequency, true); // use first character to keep track
            TrieNodeUniquePointer firstNode(std::move(characterNode[first.character].getObjectReference()));
            TrieNodeUniquePointer secondNode(std::move(characterNode[second.character].getObjectReference()));
            characterNode[first.character].getObjectReference() = std::make_unique<TrieNode>('\0', std::move(firstNode), std::move(secondNode)); // only leafs have characters
        }
        CharacterFrequency last(frequenciesInMinimumOrder.top());
        return std::move(characterNode[last.character].getObjectReference());
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

// Variable length codes
// -> use different numbers of bit to encode different chars
// ---> example: Morse code
// ---> issue: Ambuiguity (it can be translated to multiple things). Solution: there is pause when transmitting

// How to we ambiguity?
// -> Ensure that no codeword is a prefix of another
// ---> Solution 1: Fixed length code
// ---> Solution 2: Append special stop character to each codeword
// ---> Solution 3: General prefix free code -> Huffman code is an example (it also uses the fewest bits for representing)

// How to represent the prefix free code?
// -> We can use a binary trie!
// ---> Two children: 0 and 1 (bit)
// ---> Chars in the leaves
// ---> Codeword is path from root to leaf

// Compression:
// -> Method 1: Start at leaf: Follow path up to the root; print bits in reverse
// -> Method 2: create ST of key value pairs

// Expansion:
// -> 1) Start at root
// -> 2) Go left if bit is 0; go right is 1.
// -> 3) If leaf node, print cahr and return to root.
// -> Running time: Linear

// How to transmit?
// -> How to write the trie?
// ---> Write preorder tranversal of trie; mark left and internal nodes with a bit.
// ---> Note: If message is long -> overhead of transmitting a trie is small
// -> How to read in the trie?
// ---> Reconstruct from preorder traversal of trie

// How to find best prefix-free code?
// -> Shannon-Fano algorithm:
// ---> 1) Partition symbols S into two subset S0 and S1 of (roughly) equal frequency.
// ---> 2) Codewords for symbols in S0 start with 0; for symbols in S1 start with 1.
// ---> 3) Recur in S0 and S1.
// ---> How to divide up the symbols?
// ---> This is not optimal!
// -> Huffman algorithm:
// ---> 1) Count frequency for each character in input
// ---> 2) Start with one trie node corresponding to each character with the frequency as weight.
// ---> 3) Repeat this until a single trie is formed
// ---> 3.1) Select two tries with minimum weight
// ---> 3.2) Merge into a single trie with cumulative weight

// Huffman algorithm is used in:
// -> JPEG
// -> PDF
// -> MP3
// -> DIVX
// -> GZIP

// Proposition: Huffman algorithm produces an optimal prefix-free code
// Proof: See textbook.

// Implementation.
// -> Pass 1: Tabulate char frequencies and build trie
// -> Pass 2: Encode file by traversing trie or lookup table

// Running time for encoding -> N*R*log(R) -> Where R is the RADIX


// Other discussions:

// Huffman coding is a lossless data compression algorithm.
// The idea is to assign variable-length codes to input characters,
// lengths of the assigned codes are based on the frequencies of corresponding characters.
// The most frequent character gets the smallest code and the least frequent character gets the largest code.
// The variable-length codes assigned to input characters are Prefix Codes,
// means the codes (bit sequences) are assigned in such a way that the code assigned to one character
// is not the prefix of code assigned to any other character.
// This is how Huffman Coding makes sure that there is no ambiguity when decoding the generated bitstream.

// Let us understand prefix codes with a counter example.
// Let there be four characters a, b, c and d, and their corresponding variable length codes be 00, 01, 0 and 1.
// This coding leads to ambiguity because code assigned to c is the prefix of codes assigned to a and b.
// If the compressed bit stream is 0001, the de-compressed output may be “cccd” or “ccb” or “acd” or “ab”.

// There are mainly two major parts in Huffman Coding
// -> Build a Huffman Tree from input characters.
// -> Traverse the Huffman Tree and assign codes to characters.

// Steps to build Huffman Tree
// Input is an array of unique characters along with their frequency of occurrences and output is Huffman Tree.
// 1) Create a leaf node for each unique character and build a min heap of all leaf nodes (Min Heap is used as a priority queue.
// -> The value of frequency field is used to compare two nodes in min heap. Initially, the least frequent character is at root)
// 2) Extract two nodes with the minimum frequency from the min heap.
// 3) Create a new internal node with a frequency equal to the sum of the two nodes frequencies.
// -> Make the first extracted node as its left child and the other extracted node as its right child.
// -> Add this node to the min heap.
// 4) Repeat steps#2 and #3 until the heap contains only one node.
// -> The remaining node is the root node and the tree is complete.

// Steps to print codes from Huffman Tree:
// 1) Traverse the tree formed starting from the root.
// 2) Maintain an auxiliary array.
// 3.1) While moving to the left child, write 0 to the array.
// 3.2) While moving to the right child, write 1 to the array.
// 4) Print the array when a leaf node is encountered.

// Time complexity: O(nlogn) where n is the number of unique characters.
// If there are n nodes, extractMin() is called 2*(n – 1) times, extractMin() takes O(logn) time as it calles minHeapify().
// So, overall complexity is O(nlogn).
// If the input array is sorted, there exists a linear time algorithm. We will soon be discussing in our next post.

// Applications of Huffman Coding:
// -> They are used for transmitting fax and text.
// -> They are used by conventional compression formats like PKZIP, GZIP, etc.
// It is useful in cases where there is a series of frequently occurring characters.

// Improvements:

// Efficient Huffman Coding for Sorted Input (NOT IMPLEMENTED)
// Time complexity of the algorithm discussed in above is O(nLogn).
// If we know that the given array is sorted (by non-decreasing order of frequency), we can generate Huffman codes in O(n) time.
// Following is a O(n) algorithm for sorted input:
// Step 1: Create two empty queues.
// Step 2: Create a leaf node for each unique character and enqueue it to the first queue in non-decreasing order of frequency.
// -> Initially second queue is empty.
// Step 3: Dequeue two nodes with the minimum frequency by examining the front of both queues.
// -> Repeat following steps two times
// ---> 3.1: If second queue is empty, dequeue from first queue.
// ---> 3.2: If first queue is empty, dequeue from second queue.
// ---> 3.3: Else, compare the front of two queues and dequeue the minimum.
// Step 4: Create a new internal node with frequency equal to the sum of the two nodes frequencies.
// -> Make the first dequeued node as its left child and the second dequeued node as right child. Enqueue this node to second queue.
// Step 5: Repeat steps#3 and #4 while there is more than one node in the queues.
// -> The remaining node is the root node and the tree is complete.
// Time complexity: O(n) for sorted input
// -> If the input is not sorted, it need to be sorted first before it can be processed by the above algorithm.
// -> Sorting can be done using heap-sort or merge-sort both of which run in Theta(nlogn).
// -> So, the overall time complexity becomes O(nlogn) for unsorted input.


}

}
