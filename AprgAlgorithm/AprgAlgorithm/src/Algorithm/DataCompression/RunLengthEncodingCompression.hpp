#pragma once

#include <Common/Stream/AlbaStreamBitReader.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>

#include <iostream>
#include <limits>

namespace alba {

namespace algorithm {

template <typename Count>
class RunLengthEncodingCompression {
public:
    RunLengthEncodingCompression() = default;

    void compress(std::istream& input, std::ostream& output) {
        Count maxValueForCount(std::numeric_limits<Count>::max());
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);
        Count currentCount(0);
        bool currentBit(false), previousBit(false);
        while (true) {
            currentBit = reader.readBoolData();
            if (!input.eof())  // do not continue if end of file
            {
                if (currentBit != previousBit)  // if there is 0->1 or 1->0
                {
                    writer.writeBigEndianNumberData<Count>(currentCount);  // write count
                    currentCount = 0;                                      // reset count
                    previousBit = currentBit;                              // switch to the next bit value
                } else if (currentCount == maxValueForCount)               // if count reached max
                {
                    writer.writeBigEndianNumberData<Count>(currentCount);  // write current count
                    writer.writeBigEndianNumberData<Count>(0);             // write 0 to switch bits when reading
                    currentCount = 0;                                      // reset count
                }
                currentCount++;
            } else {
                break;
            }
        }
        writer.writeCharData(currentCount);
    }

    void expand(std::istream& input, std::ostream& output) {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);
        bool bit(false);  // start with 0
        while (true) {
            Count currentCount(reader.readBigEndianNumberData<Count>());
            if (!input.eof())  // do not continue if end of file
            {
                for (char i = 0; i < currentCount; i++) {
                    writer.writeBoolData(bit);  // write number of bits based from the count
                }
                bit = !bit;  // switch from 0->1 or 1->0
            } else {
                break;
            }
        }
    }
};

// Motivation:
// -> The data can have long run of repeated bits. Simple type of redundancy in a bitstream

// Representation:
// -> 4-bit counts to represent alternating runs of 0s and 1s:
// ---> 15 0s, then 7 1s then 7 0s then 11 1s.
// -> How many bits to store the counts?
// ---> We will use 8 bits (but 4 in the example above).
// -> What to do when run length exceeds max count?
// ---> If longer than 255, intersperse runs of length 0.

// Applications: JPEG ITU-T T4 Group 3 Fax,

// Application
// -> Compress a bitmap
// ---> Observation: Bits are mostly white

}  // namespace algorithm

}  // namespace alba
