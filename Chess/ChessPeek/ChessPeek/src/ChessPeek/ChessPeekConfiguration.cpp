#include "ChessPeekConfiguration.hpp"

using namespace std;

namespace alba {

namespace chess {

ChessPeekConfiguration::ChessPeekConfiguration(ChessPeekConfigurationType const type)
    : m_type(type),
      m_chessEnginePath(),
      m_uciOptionNamesAndValuePairs(),
      m_boardTopLeft{},
      m_boardBottomRight{},      m_whiteColorLimit{},
      m_blackColorLimit{} {
    initialize();
}
ChessPeekConfigurationType ChessPeekConfiguration::getType() const { return m_type; }

string const& ChessPeekConfiguration::getChessEnginePath() const { return m_chessEnginePath; }

XY ChessPeekConfiguration::getTopLeftOfBoard() const { return m_boardTopLeft; }

XY ChessPeekConfiguration::getBottomRightOfBoard() const { return m_boardBottomRight; }
double ChessPeekConfiguration::getWhiteColorLimit() const { return m_whiteColorLimit; }

double ChessPeekConfiguration::getBlackColorLimit() const { return m_blackColorLimit; }
stringHelper::StringPairs const& ChessPeekConfiguration::getUciOptionNamesAndValuePairs() const {
    return m_uciOptionNamesAndValuePairs;
}

void ChessPeekConfiguration::initialize() {
    initializeCommonParameters();
    initializeSpecificParameters();
}

void ChessPeekConfiguration::initializeCommonParameters() {
    m_chessEnginePath = APRG_DIR R"(\Chess\ChessPeek\Files\stockfish15.exe)";
    // m_chessEnginePath = APRG_DIR R"(\Chess\ChessPeek\Files\zappa.exe)";

    m_uciOptionNamesAndValuePairs = {{"MultiPV", "20"}};  // number of moves to search
}

void ChessPeekConfiguration::initializeSpecificParameters() {    switch (m_type) {
        case ChessPeekConfigurationType::ChessDotComVersus: {
            initializeChessDotComVersus();
            break;        }
        case ChessPeekConfigurationType::ChessDotComPuzzle: {
            initializeChessDotComPuzzle();
            break;
        }
        case ChessPeekConfigurationType::LichessVersus: {
            initializeLichessVersus();
            break;
        }
        case ChessPeekConfigurationType::LichessStream: {
            initializeLichessStream();
            break;
        }
    }
}

void ChessPeekConfiguration::initializeChessDotComVersus() {
    m_boardTopLeft = XY(2292, 151);
    m_boardBottomRight = XY(3107, 966);
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.40;
}

void ChessPeekConfiguration::initializeChessDotComPuzzle() {
    m_boardTopLeft = XY(2225, 101);
    m_boardBottomRight = XY(3144, 1020);
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.40;
}

void ChessPeekConfiguration::initializeLichessVersus() {
    m_boardTopLeft = XY(2488, 145);
    m_boardBottomRight = XY(3239, 896);
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.30;
}

void ChessPeekConfiguration::initializeLichessStream() {
    m_boardTopLeft = XY(2498, 159);
    m_boardBottomRight = XY(3233, 894);
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.30;
}

}  // namespace chess

}  // namespace alba
