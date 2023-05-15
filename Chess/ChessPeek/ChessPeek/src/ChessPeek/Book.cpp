#include "Book.hpp"

#include <ChessUtilities/Board/StreamOperators.hpp>
#include <Common/File/AlbaFileReader.hpp>

#include <fstream>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

size_t Book::getSize() const { return m_boardToLineDetail.size(); }

Book::LineDetailOptional Book::getLine(Board const& board) const {
    LineDetailOptional result;
    auto itPair = m_boardToLineDetail.find(BoardValue(board));
    if (itPair != m_boardToLineDetail.cend()) {
        result = itPair->second;
    }
    return result;
}

void Book::saveDatabaseTo(std::string const& path) const {
    ofstream outStream(path);
    for (auto const& pairValue : m_boardToLineDetail) {
        outStream << pairValue.first << "\n";
        outStream << pairValue.second.nameOfLine << "\n";
        outStream << static_cast<int>(pairValue.second.colorToMove) << "\n";
        outStream << pairValue.second.totalNumberOfGames << "\n";
        outStream << pairValue.second.nextMoves.size() << "\n";
        for (auto const& moveDetails : pairValue.second.nextMoves) {
            outStream << moveDetails.move << "\n";
            outStream << moveDetails.winPercentage << "\n";
        }
    }
}

void Book::clear() { m_boardToLineDetail.clear(); }

void Book::addLine(Board const& board, LineDetail const& lineDetail) {
    BoardValue boardValue(board);
    auto itExistingPair = m_boardToLineDetail.find(boardValue);
    if (itExistingPair != m_boardToLineDetail.cend()) {
        if (lineDetail.totalNumberOfGames > itExistingPair->second.totalNumberOfGames) {
            // prefer line with many games
            itExistingPair->second = lineDetail;
        }
    } else {
        m_boardToLineDetail.emplace(boardValue, lineDetail);
    }
}

void Book::loadDatabaseFrom(std::string const& path) {
    ifstream inStream(path);
    AlbaFileReader fileReader(inStream);
    while (inStream.good()) {
        BoardValue boardValue;
        int colorToMove{};
        LineDetail lineDetail;
        int moveSize{};
        inStream >> boardValue;
        lineDetail.nameOfLine = fileReader.getLineAndIgnoreWhiteSpaces();
        inStream >> colorToMove;
        lineDetail.colorToMove = static_cast<PieceColor>(colorToMove);
        inStream >> lineDetail.totalNumberOfGames;
        inStream >> moveSize;
        for (int i = 0; i < moveSize; i++) {
            MoveDetail moveDetail;
            moveDetail.move = fileReader.getLineAndIgnoreWhiteSpaces();
            inStream >> moveDetail.winPercentage;
            lineDetail.nextMoves.emplace_back(moveDetail);
        }
        if (!boardValue.isZero()) {
            m_boardToLineDetail[boardValue] = lineDetail;
        }
    }
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
