#pragma once

#include <Algorithm/String/Tries/TernarySearchTrie.hpp>
#include <Common/Stream/AlbaStreamBitReader.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

namespace alba {

namespace algorithm {

template <typename Code>
class LzwCompression {
public:
    static constexpr unsigned int RADIX = 256U;
    static constexpr unsigned int CODE_WORD_WIDTH = 12;
    static constexpr Code MAX_NUMBER_CODE_WORDS = 1 << CODE_WORD_WIDTH;

    using SymbolTableUsingTrie = TernarySearchTrie<Code>;

    LzwCompression() = default;

    void compress(std::istream& input, std::ostream& output) {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);

        std::string wholeInputString(reader.readWholeStreamAsStringData());  // read whole input as string

        // This is the position of the code words : [0...RADIX-1(Single chars)][RADIX(Stop code
        // word)][RADIX+1...MAX_NUMBER_CODE_WORDS(Multi char strings)]
        SymbolTableUsingTrie codeTrie;
        initializeCodeTableWithAllSingleCharacters(
            codeTrie);             // initialize input as single char code words for radix R keys
        Code lastCode(RADIX + 1);  // RADIX+1 because its the first code of the multi char strings

        while (!wholeInputString.empty()) {
            std::string bestTrieMatch(codeTrie.getLongestPrefixOf(wholeInputString));  // find longest prefix match
            writeCode(writer, codeTrie.get(bestTrieMatch));  // write code word for the best match in trie
            Code matchLength(bestTrieMatch.length());
            if (matchLength < wholeInputString.length() && lastCode < MAX_NUMBER_CODE_WORDS) {
                codeTrie.put(wholeInputString.substr(0, matchLength + 1), lastCode++);  // add new next code word
            }
            // remove processed part in the input:
            wholeInputString = wholeInputString.substr(
                matchLength);  // this is inefficient but trie only supports strings (not deque of chars)
        }
        Code stopCodeWord(RADIX);
        writeCode(writer, stopCodeWord);  // write stop code word
    }

    void expand(std::istream& input, std::ostream& output) {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);

        stringHelper::strings lookupTable;
        initializeLookupTablewithAllSingleCharacters(lookupTable);
        Code codeWord = readOneCodeword(reader);
        Code multiCharCode = RADIX + 2;
        std::string currentString(lookupTable.at(codeWord));

        while (true) {
            writer.writeStringData(currentString);
            codeWord = readOneCodeword(reader);
            if (!input.eof() && codeWord != RADIX)  // exit at stop code word(RADIX)
            {
                std::string nextString(lookupTable.at(codeWord));
                if (codeWord == multiCharCode)  // not in the symbol table yet (tricky case)
                {
                    // we expand the current string as the same time as processing it as next
                    nextString = currentString + currentString.at(0);
                }
                if (multiCharCode < MAX_NUMBER_CODE_WORDS) {
                    lookupTable.emplace_back(currentString + nextString.at(0));  // add a new code word
                    multiCharCode++;
                }
                currentString = nextString;
            } else {
                break;
            }
        }
    }

private:
    void initializeCodeTableWithAllSingleCharacters(SymbolTableUsingTrie& codeTrie) {
        for (Code c = 0; c < RADIX; c++) {
            codeTrie.put(std::string() + static_cast<char>(c), c);
        }
    }

    void initializeLookupTablewithAllSingleCharacters(stringHelper::strings& lookupTable) {
        for (Code c = 0; c < RADIX; c++) {
            lookupTable.emplace_back(std::string() + static_cast<char>(c));
        }
        lookupTable.emplace_back("");  // assign one for stop code word (location is at RADIX, so after the loop)
    }

    void writeCode(AlbaStreamBitWriter& writer, Code const& code) {
        std::bitset<CODE_WORD_WIDTH> bitsetToWrite(code);
        writer.writeBitsetData<CODE_WORD_WIDTH>(bitsetToWrite, CODE_WORD_WIDTH - 1, 0U);
    }

    Code readOneCodeword(AlbaStreamBitReader& reader) {
        std::bitset<CODE_WORD_WIDTH> bitsetCodeword(reader.readBitsetData<CODE_WORD_WIDTH>(CODE_WORD_WIDTH - 1, 0U));
        return static_cast<Code>(bitsetCodeword.to_ullong());
    }
};

// LZW compression: created by Abraham Lempel and Jacob Ziv
// LZW stands for Lempel-Ziv-Welch

// Can we do better that Huffman compression?

// Statistical methods
// -> Static model: Same model for all texts
// ---> Fast
// ---> Not optimal: different texts have different statistical properties
// -----> Ex: ASCII, Morse code
// -> Dynamic model: Generate model based on text
// ---> Preliminary pass needed to generate model
// ---> Must transmit the model
// ---> Example: Huffman code (build the trie, write the trie)
// -> Adaptive model: Progressively learn and update model as you read text
// ---> More accurate modeling produces better compression
// ---> Decoding must start from the beginning
// ---> No need to transmit whole model (because in expansion it can do the same thing (it has the same information))
// ---> Example: LZW

// LZW compression
// -> 1) Create ST associating W-bit codewords with string keys
// -> 2) Initialize ST with codewords for single-char keys
// -> 3) Find longest string s in ST that is a prefix of unscanned part of input
// -> 4) Write the W-bit codeword associated with s
// -> 5) Add s+c to ST, where c is next char in the input

// How to represent LZW compression code table?
// -> A trie to support the longest prefix match.

// LZW expansion
// -> 1) Create ST associating string values with W-bit keys
// -> 2) Initialize ST to contain single-char values
// -> 3) Read a W-bit key
// -> 4) Find associated string value in ST and write it out
// -> 5) Update ST with a new code word (s+c)

// How to represent LZW expansion code table?
// -> A string array of size 2^w (its a vector in the implementation above)

// How big to make ST?
// -> How long is message?
// -> Whole message similar model?
// -> Many variations have been developed

// What to do when ST fills up?
// -> Throw away and start over. [GIF]
// -> Throw away when not effective. [Unix compress]
// -> Many variations have been developed

// Why not put longer substrings in ST
// -> Many variations have been developed

// LZW in the real world
// Lempel-Ziv and friends
// -> LZ77 -> not patented -> widely used in open source
// -> LZ78
// -> LZW -> LZW patent #4558302 expired in US on June 20, 2003
// -> Deflate/zlib = LZ77 variant + Huffman

// Unix compress, GIF, TIFF, V.41bis modem: LZW
// zip, 7zip, gzip, jar, png, pdf: deflate/zlib
// iPhone, Sony Playstation 3 Apache HTTP server: deflate/zlib

}  // namespace algorithm

}  // namespace alba
