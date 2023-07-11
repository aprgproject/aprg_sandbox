#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba {

class CountingSubGrids {
public:
    // Given an nxn grid whose each square is either black (1) or white (0), calculate the number of subgrids whose all
    // corners are black.

    using BitValue = uint64_t;
    using BitValueUtilities = AlbaBitValueUtilities<BitValue>;
    using BitGrid = matrix::AlbaMatrix<bool>;
    using BitValueGrid = matrix::AlbaMatrix<BitValue>;
    static constexpr int NUMBER_OF_BITS = BitValueUtilities::getNumberOfBits();

    CountingSubGrids(BitGrid const& bitGrid);

    int countSubGridsWithAllBlackCorners() const;

private:
    void initialize(BitGrid const& bitGrid);
    BitValueGrid m_bitValueGrid;
};

}  // namespace alba
