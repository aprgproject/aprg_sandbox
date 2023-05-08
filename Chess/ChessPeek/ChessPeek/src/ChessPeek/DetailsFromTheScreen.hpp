#pragma once

#include <ChessPeek/BoardObserver.hpp>
#include <ChessUtilities/Board/Board.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class DetailsFromTheScreen {
public:
    DetailsFromTheScreen(Configuration const& configuration, AlbaLocalScreenMonitoring const& screenMonitoring);

    struct BoardDetails {
        unsigned int pieceCount;
        unsigned int whiteCountInUpperHalf;
        unsigned int blackCountInUpperHalf;
        unsigned int whiteCountInLowerHalf;
        unsigned int blackCountInLowerHalf;
        unsigned int numberOfWhiteKings;
        unsigned int numberOfBlackKings;
        Coordinate whiteKingCoordinate;
        Coordinate blackKingCoordinate;
    };

    bool canAnalyzeBoard() const;
    PieceColor getPlayerColor() const;
    Board const& getBoard() const;

    void saveDetailsFromTheScreen();

private:
    bool areKingsValid() const;
    bool isOpponentsKingOnCheck() const;
    Coordinate getOpponentsKingCoordinate() const;

    void saveBoardAndItsDetails();
    void saveBoardDetails(Coordinate const& coordinate, Piece const& chessPiece);
    void saveBoardKingDetails(Coordinate const& coordinate, Piece const& chessPiece);
    void saveBoardUpperHalfLowerHalfDetails(Coordinate const& coordinate, Piece const& chessPiece);
    void savePlayerColorAndOrientation();
    void savePlayerColorIfChessDotComPuzzle();
    void savePlayerColorIfLichessStream();
    void savePlayerColorAndOrientationFromBoardDetails();
    void saveOrientationDependingOnLowerHalfColor(PieceColor const lowerHalfColor);
    void savePlayerColor(PieceColor const newColor);

    Configuration const& m_configuration;
    AlbaLocalScreenMonitoring const& m_screenMonitoring;
    BoardObserver m_boardObserver;
    PieceColor m_playerColor;
    Board m_board;
    BoardDetails m_boardDetails;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
