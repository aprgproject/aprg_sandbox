#pragma once

#include <cstdint>

namespace alba {

namespace BitManipulation {

uint64_t changeKthBitToOne(uint64_t const value, uint64_t const k);
uint64_t changeKthBitToZero(uint64_t const value, uint64_t const k);
uint64_t invertKthBit(uint64_t const value, uint64_t const k);
uint64_t invertKthBit(uint64_t const value, uint64_t const k);
uint64_t changeLastOneToZero(uint64_t const value);
uint64_t changeAllOnesToZeroExceptForLast(uint64_t const value);
uint64_t invertAllBitsAfterTheLastOne(uint64_t const value);

}  // namespace BitManipulation

}  // namespace alba
