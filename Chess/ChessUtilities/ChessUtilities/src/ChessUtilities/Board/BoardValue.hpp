#pragma once

#include <ChessUtilities/Board/Board.hpp>

#include <array>
#include <cstdint>

namespace alba {

namespace chess {

class BoardValue {
public:
    static constexpr int SIZE_OF_DATA = 4;
    using Data = std::array<uint64_t, SIZE_OF_DATA>;

    BoardValue();
    BoardValue(Board const& board);
    BoardValue(Data const& data);

    friend bool operator<(BoardValue const& bv1, BoardValue const& bv2);
    friend bool operator==(BoardValue const& bv1, BoardValue const& bv2);
    friend std::ostream& operator<<(std::ostream& out, BoardValue const& boardValue);
    friend std::istream& operator>>(std::istream& in, BoardValue& boardValue);

    bool isZero() const;
    Data const& getData() const;

private:
    Coordinate getCorrectCoordinate(Board const& board, CoordinateDataType const x, CoordinateDataType const y);
    void saveBoardToData(Board const& board);
    Data m_data;
};

bool operator<(BoardValue const& bv1, BoardValue const& bv2);
bool operator==(BoardValue const& bv1, BoardValue const& bv2);

}  // namespace chess

}  // namespace alba
