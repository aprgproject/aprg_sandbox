#include "Book.hpp"

#include <Common/File/AlbaFileReader.hpp>

#include <fstream>

using namespace std;

namespace alba {

namespace chess {

ostream& operator<<(ostream& out, Move const& move) {
    out << move.first.getX() << " ";
    out << move.first.getY() << " ";
    out << move.second.getX() << " ";
    out << move.second.getY();
    return out;
}

istream& operator>>(istream& in, Move& move) {
    int firstX, firstY, secondX, secondY;
    in >> firstX;
    in >> firstY;
    in >> secondX;
    in >> secondY;
    move = Move{{firstX, firstY}, {secondX, secondY}};
    return in;
}

namespace ChessPeek {

Book::LineDetailOptional Book::getLine(Board const& board) const {
    LineDetailOptional result;
    auto it = m_boardToLineDetail.find(BoardValue(board));
    if (it != m_boardToLineDetail.cend()) {
        result = it->second;
    }
    return result;
}

void Book::saveDatabaseTo(std::string const& path) const {
    ofstream outStream(path);
    for (auto const& pairValue : m_boardToLineDetail) {
        outStream << pairValue.first << "\n";
        outStream << pairValue.second.nameOfLine << "\n";
        outStream << pairValue.second.nextMoves.size() << "\n";
        for (auto const& moveDetails : pairValue.second.nextMoves) {
            outStream << moveDetails.move << "\n";
            outStream << moveDetails.numberOfGames << "\n";
            outStream << moveDetails.whiteWinPercentage << "\n";
            outStream << moveDetails.drawPercentage << "\n";
            outStream << moveDetails.blackWinPercentage << "\n";
        }
    }
}

void Book::clear() { m_boardToLineDetail.clear(); }

void Book::addLine(Board const& board, LineDetail const& lineDetail) {
    m_boardToLineDetail[BoardValue(board)] = lineDetail;
}

void Book::loadDatabaseFrom(std::string const& path) {
    ifstream inStream(path);
    AlbaFileReader fileReader(inStream);
    while (inStream.good()) {
        BoardValue boardValue;
        LineDetail lineDetail;
        inStream >> boardValue;
        lineDetail.nameOfLine = fileReader.getLineAndIgnoreWhiteSpaces();
        int moveSize{};
        inStream >> moveSize;
        for (int i = 0; i < moveSize; i++) {
            MoveDetail moveDetail;
            inStream >> moveDetail.move;
            inStream >> moveDetail.numberOfGames;
            inStream >> moveDetail.whiteWinPercentage;
            inStream >> moveDetail.drawPercentage;
            inStream >> moveDetail.blackWinPercentage;
            lineDetail.nextMoves.emplace_back(moveDetail);
        }
        m_boardToLineDetail[boardValue] = lineDetail;
    }
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
