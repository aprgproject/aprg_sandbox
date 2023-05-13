#include "BoardUtilities.hpp"

#include <Common/Macros/AlbaMacros.hpp>

#include <sstream>

using namespace std;

namespace alba {

namespace chess {

bool isAToH(char const c) { return 'a' <= c && c <= 'h'; }

bool is1To8(char const c) { return '1' <= c && c <= '8'; }

bool isCoordinateWithinTheBoard(Coordinate const& coordinate) {
    auto x(coordinate.getX());
    auto y(coordinate.getY());
    return (x >= 0 && x <= 7) && (y >= 0 && y <= 7);
}

bool isInUpperHalf(Coordinate const& coordinate) { return coordinate.getY() <= 3; }

bool isInLowerHalf(Coordinate const& coordinate) { return coordinate.getY() >= 4; }

bool areCoordinatesValid(Move const& move) {
    return move.first != move.second && isCoordinateWithinTheBoard(move.first) &&
           isCoordinateWithinTheBoard(move.second);
}

bool areOpposingColors(PieceColor const pieceColor1, PieceColor const pieceColor2) {
    return (PieceColor::White == pieceColor1 && PieceColor::Black == pieceColor2) ||
           (PieceColor::Black == pieceColor1 && PieceColor::White == pieceColor2);
}

PieceColor getOppositeColor(PieceColor const pieceColor) {
    PieceColor result(PieceColor::Unknown);
    if (PieceColor::White == pieceColor) {
        result = PieceColor::Black;
    } else if (PieceColor::Black == pieceColor) {
        result = PieceColor::White;
    }
    return result;
}

int getValueOfPieceType(PieceType const pieceType) {
    int result{};
    switch (pieceType) {
        case PieceType::Pawn: {
            result = 1;
            break;
        }
        case PieceType::Knight: {
            result = 3;
            break;
        }
        case PieceType::Bishop: {
            result = 3;
            break;
        }
        case PieceType::Rook: {
            result = 5;
            break;
        }
        case PieceType::Queen: {
            result = 9;
            break;
        }
        case PieceType::King: {
            result = 0;
            break;
        }
        default: {
            break;
        }
    }
    return result;
}

std::string getEnumString(PieceColor const pieceColor) {
    switch (pieceColor) {
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColor::Unknown, "Unknown")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColor::White, "White")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColor::Black, "Black")
        default:
            return "default";
    }
}

std::string getEnumString(PieceType const pieceType) {
    switch (pieceType) {
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Empty, "Empty")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Pawn, "Pawn")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Knight, "Knight")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Bishop, "Bishop")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Rook, "Rook")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Queen, "Queen")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::King, "King")
        default:
            return "default";
    }
}
std::string getEnumString(PieceColorAndType const pieceColorAndType) {
    switch (pieceColorAndType) {
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::Empty, "Empty")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhitePawn, "WhitePawn")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhiteKnight, "WhiteKnight")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhiteBishop, "WhiteBishop")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhiteRook, "WhiteRook")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhiteQueen, "WhiteQueen")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhiteKing, "WhiteKing")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackPawn, "BlackPawn")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackKnight, "BlackKnight")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackBishop, "BlackBishop")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackRook, "BlackRook")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackQueen, "BlackQueen")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackKing, "BlackKing")
        default:
            return "default";
    }
}

char convertToFenCharacter(PieceType const pieceType, PieceColor const pieceColor) {
    // Source: https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
    char result{};
    switch (pieceType) {
        case PieceType::Empty: {
            result = ' ';
            break;
        }
        case PieceType::Pawn: {
            result = 'p';
            break;
        }
        case PieceType::Knight: {
            result = 'n';
            break;
        }
        case PieceType::Bishop: {
            result = 'b';
            break;
        }
        case PieceType::Rook: {
            result = 'r';
            break;
        }
        case PieceType::Queen: {
            result = 'q';
            break;
        }
        case PieceType::King: {
            result = 'k';
            break;
        }
        default: {
            break;
        }
    }
    result = (PieceColor::White == pieceColor) ? toupper(result) : result;
    return result;
}

string constructFenString(
    Board const& board, PieceColor const colorToMove, string const& castlingAvailability, string const& enPassantTarget,
    unsigned int const halfMoveClock, unsigned int const fullMoveNumber) {
    // Source: https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
    stringstream ss;
    ss << board.getNotationPartOfFenString() << " ";
    if (PieceColor::White == colorToMove) {        ss << "w ";
    } else if (PieceColor::Black == colorToMove) {
        ss << "b ";
    }
    ss << castlingAvailability << " " << enPassantTarget << " " << halfMoveClock << " " << fullMoveNumber;
    return ss.str();
}

}  // namespace chess

}  // namespace alba
