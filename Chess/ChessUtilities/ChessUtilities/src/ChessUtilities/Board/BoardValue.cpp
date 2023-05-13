#include "BoardValue.hpp"

#include <Common/Bit/AlbaBitManipulation.hpp>

using namespace std;
namespace alba {

namespace chess {

// Basis:
//     00 01 02 03 04 05 06 07
//    -------------------------
// 00 |48|40|32|33|34|35|42|50|
//    -------------------------
// 01 |49|41|16|17|18|19|43|51|
//    -------------------------
// 02 |56|24|08|09|10|11|28|60|
//    -------------------------
// 03 |57|25|00|01|02|03|29|61|
//    -------------------------
// 04 |58|26|04|05|06|07|30|62|
//    -------------------------
// 05 |59|27|12|13|14|15|31|63|
//    -------------------------
// 06 |52|44|20|21|22|23|46|54|
//    -------------------------
// 07 |53|45|36|37|38|39|47|55|
//    -------------------------

constexpr int SIZE_OF_COORDINATES = 64;
using C = std::pair<CoordinateDataType, CoordinateDataType>;
using Cs = std::array<C, SIZE_OF_COORDINATES>;

constexpr Cs coordinates = {C{2, 3}, {3, 3}, {4, 3}, {5, 3}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {2, 2}, {3, 2}, {4, 2},
                            {5, 2},  {2, 5}, {3, 5}, {4, 5}, {5, 5}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {2, 6}, {3, 6},
                            {4, 6},  {5, 6}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {2, 0},
                            {3, 0},  {4, 0}, {5, 0}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {1, 0}, {1, 1}, {6, 0}, {6, 1},
                            {1, 6},  {1, 7}, {6, 6}, {6, 7}, {0, 0}, {0, 1}, {7, 0}, {7, 1}, {0, 6}, {0, 7}, {7, 6},
                            {7, 7},  {0, 2}, {0, 3}, {0, 4}, {0, 5}, {7, 2}, {7, 3}, {7, 4}, {7, 5}};

BoardValue::BoardValue() : m_data{} {}

BoardValue::BoardValue(Board const& board) : m_data{} { saveBoardToData(board); }

BoardValue::BoardValue(Data const& data) : m_data(data) {}

bool BoardValue::isZero() const { return m_data == Data{}; }

BoardValue::Data const& BoardValue::getData() const { return m_data; }
Coordinate BoardValue::getCorrectCoordinate(
    Board const& board, CoordinateDataType const x, CoordinateDataType const y) {
    if (BoardOrientation::BlackUpWhiteDown == board.getOrientation()) {
        return Coordinate(x, y);
    } else if (BoardOrientation::WhiteUpBlackDown == board.getOrientation()) {
        return Coordinate(7 - x, 7 - y);
    } else {
        return {};
    }
}

void BoardValue::saveBoardToData(Board const& board) {
    using BitManip = AlbaBitManipulation<uint64_t>;
    for (int i = 0; i < SIZE_OF_COORDINATES; i += 16) {
        Coordinate c01 = getCorrectCoordinate(board, coordinates.at(i).first, coordinates.at(i).second);        Coordinate c02 = getCorrectCoordinate(board, coordinates.at(i + 1).first, coordinates.at(i + 1).second);
        Coordinate c03 = getCorrectCoordinate(board, coordinates.at(i + 2).first, coordinates.at(i + 2).second);
        Coordinate c04 = getCorrectCoordinate(board, coordinates.at(i + 3).first, coordinates.at(i + 3).second);
        Coordinate c05 = getCorrectCoordinate(board, coordinates.at(i + 4).first, coordinates.at(i + 4).second);
        Coordinate c06 = getCorrectCoordinate(board, coordinates.at(i + 5).first, coordinates.at(i + 5).second);
        Coordinate c07 = getCorrectCoordinate(board, coordinates.at(i + 6).first, coordinates.at(i + 6).second);
        Coordinate c08 = getCorrectCoordinate(board, coordinates.at(i + 7).first, coordinates.at(i + 7).second);
        Coordinate c09 = getCorrectCoordinate(board, coordinates.at(i + 8).first, coordinates.at(i + 8).second);
        Coordinate c10 = getCorrectCoordinate(board, coordinates.at(i + 9).first, coordinates.at(i + 9).second);
        Coordinate c11 = getCorrectCoordinate(board, coordinates.at(i + 10).first, coordinates.at(i + 10).second);
        Coordinate c12 = getCorrectCoordinate(board, coordinates.at(i + 11).first, coordinates.at(i + 11).second);
        Coordinate c13 = getCorrectCoordinate(board, coordinates.at(i + 12).first, coordinates.at(i + 12).second);
        Coordinate c14 = getCorrectCoordinate(board, coordinates.at(i + 13).first, coordinates.at(i + 13).second);
        Coordinate c15 = getCorrectCoordinate(board, coordinates.at(i + 14).first, coordinates.at(i + 14).second);
        Coordinate c16 = getCorrectCoordinate(board, coordinates.at(i + 15).first, coordinates.at(i + 15).second);
        uint8_t nibble01 = static_cast<uint8_t>(board.getPieceAt(c01).getColorAndType());
        uint8_t nibble02 = static_cast<uint8_t>(board.getPieceAt(c02).getColorAndType());
        uint8_t nibble03 = static_cast<uint8_t>(board.getPieceAt(c03).getColorAndType());
        uint8_t nibble04 = static_cast<uint8_t>(board.getPieceAt(c04).getColorAndType());
        uint8_t nibble05 = static_cast<uint8_t>(board.getPieceAt(c05).getColorAndType());
        uint8_t nibble06 = static_cast<uint8_t>(board.getPieceAt(c06).getColorAndType());
        uint8_t nibble07 = static_cast<uint8_t>(board.getPieceAt(c07).getColorAndType());
        uint8_t nibble08 = static_cast<uint8_t>(board.getPieceAt(c08).getColorAndType());
        uint8_t nibble09 = static_cast<uint8_t>(board.getPieceAt(c09).getColorAndType());
        uint8_t nibble10 = static_cast<uint8_t>(board.getPieceAt(c10).getColorAndType());
        uint8_t nibble11 = static_cast<uint8_t>(board.getPieceAt(c11).getColorAndType());
        uint8_t nibble12 = static_cast<uint8_t>(board.getPieceAt(c12).getColorAndType());
        uint8_t nibble13 = static_cast<uint8_t>(board.getPieceAt(c13).getColorAndType());
        uint8_t nibble14 = static_cast<uint8_t>(board.getPieceAt(c14).getColorAndType());
        uint8_t nibble15 = static_cast<uint8_t>(board.getPieceAt(c15).getColorAndType());
        uint8_t nibble16 = static_cast<uint8_t>(board.getPieceAt(c16).getColorAndType());
        m_data[i / 16] = BitManip::concatenateNibbles(
            nibble01, nibble02, nibble03, nibble04, nibble05, nibble06, nibble07, nibble08, nibble09, nibble10,
            nibble11, nibble12, nibble13, nibble14, nibble15, nibble16);    }
}

bool operator<(BoardValue const& bv1, BoardValue const& bv2) {
    for (int i = 0; i < BoardValue::SIZE_OF_DATA; i++) {
        if (bv1.m_data.at(i) != bv2.m_data.at(i)) {
            return bv1.m_data.at(i) < bv2.m_data.at(i);
        }
    }
    return false;
}

bool operator==(BoardValue const& bv1, BoardValue const& bv2) {
    for (int i = 0; i < BoardValue::SIZE_OF_DATA; i++) {
        if (bv1.m_data.at(i) != bv2.m_data.at(i)) {
            return false;
        }
    }
    return true;
}

}  // namespace chess

}  // namespace alba