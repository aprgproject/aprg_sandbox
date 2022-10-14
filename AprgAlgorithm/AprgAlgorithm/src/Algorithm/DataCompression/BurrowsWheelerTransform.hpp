#pragma once

#include <Algorithm/String/SuffixArray/SuffixArray.hpp>
#include <Common/Stream/AlbaStreamBitReader.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

namespace alba
{

namespace algorithm
{

template <typename Index, char END_CHARACTER>
class BurrowsWheelerTransform
{
public :

    BurrowsWheelerTransform() = default;

    void encode(std::istream & input, std::ostream & output)
    {        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);

        std::string wholeInputString(reader.readWholeStreamAsStringData());        wholeInputString += END_CHARACTER; // put end character for decoding
        std::string stringOutput;
        SuffixArray<Index> suffixArray(wholeInputString);
        for(Index i=0; i<suffixArray.getSize(); i++)
        {
            Index deltaLength(wholeInputString.length()-suffixArray.getSuffixAt(i).length());
            if(deltaLength > 0) // if its a suffix, take the character based from the delta
            {
                stringOutput += wholeInputString.at(deltaLength-1);
            }
            else // if its the whole input string, just take the last item
            {
                stringOutput += wholeInputString.at(wholeInputString.length()-1);
            }
        }
        writer.writeStringData(stringOutput);
    }

    void decode(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);

        std::string wholeInputString(reader.readWholeStreamAsStringData());
        if(!wholeInputString.empty())
        {
            alba::stringHelper::strings prefix;
            for(char const c : wholeInputString)
            {
                prefix.emplace_back(1, c); // create string with one character
            }
            alba::stringHelper::strings possibleOutputs(prefix.size());
            for(Index iteration=0; iteration<wholeInputString.length(); iteration++)
            {
                for(Index index=0; index<wholeInputString.length(); index++)
                {
                    possibleOutputs[index] = prefix.at(index) + possibleOutputs.at(index); // add prefixes
                }
                std::sort(possibleOutputs.begin(), possibleOutputs.end()); // sort outputs, possible optimization to use radix sort here
            }
            auto it = std::find_if(possibleOutputs.cbegin(), possibleOutputs.cend(), [](std::string const& possibleOutput)
            {
                return END_CHARACTER == possibleOutput.back();
            });
            if(it != possibleOutputs.cend())
            {
                writer.writeStringData(it->substr(0, it->length()-1)); // remove last character
            }
        }
    }

};

// The Burrows–Wheeler transform is an algorithm used to prepare data for use with data compression techniques such as bzip2.
// It was invented by Michael Burrows and David Wheeler in 1994 while Burrows was working at DEC Systems Research Center in Palo Alto, California.
// It is based on a previously unpublished transformation discovered by Wheeler in 1983.
// The algorithm can be implemented efficiently using a suffix array thus reaching linear time complexity.

// When a character string is transformed by the BWT, the transformation permutes the order of the characters.
// If the original string had several substrings that occurred often, then the transformed string will have several places where a single character is repeated multiple times in a row.
// The output is easier to compress because it has many repeated characters.

// The transformation works like this:
// -> 1. Input
// ^BANANA|
// -> 2. All get all rotations
// ^BANANA|
// |^BANANA
// A|^BANAN
// NA|^BANA
// ANA|^BAN
// NANA|^BA
// ANANA|^B
// BANANA|^
// -> 3. Sort into lexical order
// ANANA|^B
// ANA|^BAN
// A|^BANAN
// BANANA|^
// NANA|^BA
// NA|^BANA
// ^BANANA|
// |^BANANA
// -> 4. Take the last column
// ANANA|^B
// ANA|^BAN
// A|^BANAN
// BANANA|^
// NANA|^BA
// NA|^BANA
// ^BANANA|
// |^BANANA
// -> 5. Output
// BNN^AA|A

// The transformation works like this:
// 1) Add the characters of the encoded string as prefix
// 2) Sort the strings
// 3) continue until number of characters is reached
// Example:
// Input:BNN^AA|A
// Add 1:
// B
// N
// N
// ^
// A
// A
// |
// A
// Sort 1:
// A
// A
// A
// B
// N
// N
// ^
// |
// Add 2:
// BA
// NA
// NA
// ^B
// AN
// AN
// |^
// A|
// Sort 2:
// AN
// AN
// A|
// BA
// NA
// NA
// ^B
// |^
// Continue until length is reached

// To understand why this creates more-easily-compressible data, consider transforming a long English text frequently containing the word "the".
// Sorting the rotations of this text will group rotations starting with "he " together,
// and the last character of that rotation (which is also the character before the "he ") will usually be "t",
// so the result of the transform would contain a number of "t" characters along with the perhaps less-common exceptions (such as if it contains "ache ") mixed in.
// So it can be seen that the success of this transform depends upon one value having a high probability of occurring before a sequence,
// so that in general it needs fairly long samples (a few kilobytes at least) of appropriate data (such as text).

}

}
