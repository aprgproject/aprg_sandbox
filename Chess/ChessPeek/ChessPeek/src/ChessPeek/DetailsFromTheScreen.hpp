#pragma once

#include <ChessPeek/BoardObserver.hpp>
#include <ChessPeek/BoardWithContext.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class DetailsFromTheScreen {
public:
    DetailsFromTheScreen(Configuration const& configuration, AlbaLocalScreenMonitoring const& screenMonitoring);

    struct CountOfPieces {
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
    BoardWithContext const& getBoardWithContext() const;

    void saveDetailsFromTheScreen();

private:
    bool areKingsValid() const;

    Board getBoardAndSaveDetails();
    void saveBoardDetails(Coordinate const& coordinate, Piece const& piece);
    void saveBoardKingDetails(Coordinate const& coordinate, Piece const& piece);
    void saveBoardUpperHalfAndLowerHalfDetails(Coordinate const& coordinate, Piece const& piece);
    void savePlayerColorAndOrientation();
    void savePlayerColorIfChessDotComPuzzle();
    void savePlayerColorIfLichessStream();    void savePlayerColorAndOrientationFromBoardDetails();
    void saveOrientationOnLowerHalfColor(PieceColor const lowerHalfColor);

    void savePlayerColor(PieceColor const newColor);    void saveOrientation(Board::Orientation const orientation);

    Configuration const& m_configuration;
    AlbaLocalScreenMonitoring const& m_screenMonitoring;
    BoardObserver m_boardObserver;
    BoardWithContext m_boardWithContext;
    PieceColor m_savedPlayerColor;
    Board::Orientation m_savedOrientation;
    CountOfPieces m_countOfPieces;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
