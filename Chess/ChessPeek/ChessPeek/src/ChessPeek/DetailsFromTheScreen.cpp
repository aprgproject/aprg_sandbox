#include "DetailsFromTheScreen.hpp"

#include <ChessPeek/Utilities.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

DetailsFromTheScreen::DetailsFromTheScreen(
    Configuration const& configuration, AlbaLocalScreenMonitoring const& screenMonitoring)
    : m_configuration(configuration),
      m_screenMonitoring(screenMonitoring),
      m_boardObserver(m_configuration, m_screenMonitoring),
      m_playerColor(PieceColor::White),
      m_board(Board::Orientation::BlackUpWhiteDown, {}),
      m_boardDetails{} {}

bool DetailsFromTheScreen::canAnalyzeBoard() const { return areKingsValid() && !isOpponentsKingOnCheck(); }

PieceColor DetailsFromTheScreen::getPlayerColor() const { return m_playerColor; }

Board const& DetailsFromTheScreen::getBoard() const { return m_board; }

void DetailsFromTheScreen::saveDetailsFromTheScreen() {
    saveBoardAndItsDetails();
    savePlayerColorAndOrientation();
}

bool DetailsFromTheScreen::areKingsValid() const {
    return m_boardDetails.numberOfWhiteKings == 1 && m_boardDetails.numberOfBlackKings == 1;
}

bool DetailsFromTheScreen::isOpponentsKingOnCheck() const {
    return m_board.canBeCaptured(getOpponentsKingCoordinate());
}

Coordinate DetailsFromTheScreen::getOpponentsKingCoordinate() const {
    Coordinate result = {};
    if (m_playerColor == PieceColor::White) {
        result = m_boardDetails.blackKingCoordinate;
    } else if (m_playerColor == PieceColor::Black) {
        result = m_boardDetails.whiteKingCoordinate;
    }
    return result;
}

void DetailsFromTheScreen::saveBoardAndItsDetails() {
    m_boardDetails = {};
    for (unsigned int j = 0; j < 8; j++) {
        for (unsigned int i = 0; i < 8; i++) {
            Piece chessPiece(m_boardObserver.getPieceFromCell(i, j));
            Coordinate coordinate(i, j);
            m_board.setPieceAt(coordinate, chessPiece);
            if (!chessPiece.isEmpty()) {
                saveBoardDetails(coordinate, chessPiece);
            }
        }
    }
}

void DetailsFromTheScreen::saveBoardDetails(Coordinate const& coordinate, Piece const& chessPiece) {
    m_boardDetails.pieceCount++;
    saveBoardKingDetails(coordinate, chessPiece);
    saveBoardUpperHalfLowerHalfDetails(coordinate, chessPiece);
}

void DetailsFromTheScreen::saveBoardKingDetails(Coordinate const& coordinate, Piece const& chessPiece) {
    if (PieceType::King == chessPiece.getType()) {
        if (PieceColor::White == chessPiece.getColor()) {
            m_boardDetails.numberOfWhiteKings++;
            m_boardDetails.whiteKingCoordinate = coordinate;
        } else {
            m_boardDetails.numberOfBlackKings++;
            m_boardDetails.blackKingCoordinate = coordinate;
        }
    }
}

void DetailsFromTheScreen::saveBoardUpperHalfLowerHalfDetails(Coordinate const& coordinate, Piece const& chessPiece) {
    if (coordinate.getY() <= 3) {
        if (PieceColor::White == chessPiece.getColor()) {
            m_boardDetails.whiteCountInUpperHalf++;
        } else if (PieceColor::Black == chessPiece.getColor()) {
            m_boardDetails.blackCountInUpperHalf++;
        }
    } else {
        if (PieceColor::White == chessPiece.getColor()) {
            m_boardDetails.whiteCountInLowerHalf++;
        } else if (PieceColor::Black == chessPiece.getColor()) {
            m_boardDetails.blackCountInLowerHalf++;
        }
    }
}

void DetailsFromTheScreen::savePlayerColorAndOrientation() {
    if (m_configuration.getType() == Configuration::Type::ChessDotComPuzzle) {
        savePlayerColorIfChessDotComPuzzle();
    } else if (m_configuration.getType() == Configuration::Type::LichessStream) {
        savePlayerColorIfLichessStream();
    } else {
        savePlayerColorAndOrientationFromBoardDetails();
    }
}

void DetailsFromTheScreen::savePlayerColorIfChessDotComPuzzle() {
    auto intensity = calculateColorIntensityDecimal(m_screenMonitoring.getColorAt(3337, 137));
    if (intensity < m_configuration.getBlackColorLimit()) {
        saveOrientationDependingOnLowerHalfColor(PieceColor::Black);
        savePlayerColor(PieceColor::Black);
    } else if (intensity > m_configuration.getWhiteColorLimit()) {
        saveOrientationDependingOnLowerHalfColor(PieceColor::White);
        savePlayerColor(PieceColor::White);
    }
}

void DetailsFromTheScreen::savePlayerColorIfLichessStream() {
    constexpr auto xForWhiteSection = 3387, xForBlackSection = 3553;
    constexpr auto lastMovePixelColor = 0x2A4053U, rgbMask = 0xFFFFFFU;
    for (auto yCoordinate = 897; yCoordinate >= 199; yCoordinate -= 1) {
        auto pixelColorInWhiteSection = m_screenMonitoring.getColorAt(xForWhiteSection, yCoordinate) & rgbMask;
        auto pixelColorInBlackSection = m_screenMonitoring.getColorAt(xForBlackSection, yCoordinate) & rgbMask;
        if (lastMovePixelColor == pixelColorInWhiteSection) {
            savePlayerColor(PieceColor::Black);
            break;
        } else if (lastMovePixelColor == pixelColorInBlackSection) {
            savePlayerColor(PieceColor::White);
            break;
        }
    }
}

void DetailsFromTheScreen::savePlayerColorAndOrientationFromBoardDetails() {
    constexpr unsigned int MIN_PIECE_COUNT_TO_CONSIDER = 12U;
    if (m_boardDetails.pieceCount >= MIN_PIECE_COUNT_TO_CONSIDER) {
        optional<PieceColor> lowerHalfColorOptional;
        if (m_boardDetails.whiteCountInLowerHalf > m_boardDetails.blackCountInLowerHalf &&
            m_boardDetails.blackCountInUpperHalf > m_boardDetails.whiteCountInUpperHalf &&
            isInLowerHalf(m_boardDetails.whiteKingCoordinate) && isInUpperHalf(m_boardDetails.blackKingCoordinate)) {
            lowerHalfColorOptional = PieceColor::White;
        } else if (
            m_boardDetails.blackCountInLowerHalf > m_boardDetails.whiteCountInLowerHalf &&
            m_boardDetails.whiteCountInUpperHalf > m_boardDetails.blackCountInUpperHalf &&
            isInLowerHalf(m_boardDetails.blackKingCoordinate) && isInUpperHalf(m_boardDetails.whiteKingCoordinate)) {
            lowerHalfColorOptional = PieceColor::Black;
        }

        if (lowerHalfColorOptional) {
            saveOrientationDependingOnLowerHalfColor(lowerHalfColorOptional.value());
            savePlayerColor(lowerHalfColorOptional.value());
        }
    }
}

void DetailsFromTheScreen::saveOrientationDependingOnLowerHalfColor(PieceColor const lowerHalfColor) {
    if (PieceColor::White == lowerHalfColor) {
        m_board.setOrientation(Board::Orientation::BlackUpWhiteDown);
    } else if (PieceColor::Black == lowerHalfColor) {
        m_board.setOrientation(Board::Orientation::WhiteUpBlackDown);
    }
}

void DetailsFromTheScreen::savePlayerColor(PieceColor const newColor) { m_playerColor = newColor; }

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
