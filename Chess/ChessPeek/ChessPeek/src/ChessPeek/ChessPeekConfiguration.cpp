#include "ChessPeekConfiguration.hpp"

using namespace alba::AprgBitmap;
using namespace std;

namespace alba {

namespace chess {

ChessPeekConfiguration::ChessPeekConfiguration(ChessPeekConfigurationType const type)
    : m_type(type),
      m_chessEnginePath(),
      m_screenShotPath(),
      m_uciOptionNamesAndValuePairs(),
      m_topLeftCorner{},
      m_bottomRightCorner{},
      m_whiteColorLimit{},
      m_blackColorLimit{} {
    initialize();
}

ChessPeekConfigurationType ChessPeekConfiguration::getType() const { return m_type; }

string const& ChessPeekConfiguration::getChessEnginePath() const { return m_chessEnginePath; }

string const& ChessPeekConfiguration::getScreenShotPath() const { return m_screenShotPath; }

AprgBitmap::BitmapXY ChessPeekConfiguration::getTopLeftCorner() const { return m_topLeftCorner; }

AprgBitmap::BitmapXY ChessPeekConfiguration::getBottomRightCorner() const { return m_bottomRightCorner; }

double ChessPeekConfiguration::getWhiteColorLimit() const { return m_whiteColorLimit; }

double ChessPeekConfiguration::getBlackColorLimit() const { return m_blackColorLimit; }

stringHelper::StringPairs const& ChessPeekConfiguration::getUciOptionNamesAndValuePairs() const {
    return m_uciOptionNamesAndValuePairs;
}

void ChessPeekConfiguration::initialize() {
    initializeCommonParameters();
    if (ChessPeekConfigurationType::ChessDotComUserVsUser == m_type) {
        initializeChessDotComUserVsUser();
    } else if (ChessPeekConfigurationType::ChessDotComUserVsComputer == m_type) {
        initializeChessDotComUserVsComputer();
    } else if (ChessPeekConfigurationType::LichessDotOrg == m_type) {
        initializeLichessDotOrg();
    }
}

void ChessPeekConfiguration::initializeCommonParameters() {
    m_chessEnginePath = APRG_DIR R"(\Chess\ChessPeek\Files\stockfish13.exe)";
    m_uciOptionNamesAndValuePairs = {{"Contempt", "100"}};

    // m_chessEnginePath = APRG_DIR R"(\Chess\ChessPeek\Files\zappa.exe)";

    m_screenShotPath = APRG_DIR R"(\Chess\ChessPeek\Files\ScreenShot.bmp)";
}

void ChessPeekConfiguration::initializeChessDotComUserVsUser() {
    m_topLeftCorner = BitmapXY(2218, 151);
    m_bottomRightCorner = BitmapXY(3033, 966);
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.40;
}

void ChessPeekConfiguration::initializeChessDotComUserVsComputer() {
    m_topLeftCorner = BitmapXY(2215, 151);
    m_bottomRightCorner = BitmapXY(3022, 958);
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.40;
}

void ChessPeekConfiguration::initializeLichessDotOrg() {
    m_topLeftCorner = BitmapXY(2491, 145);
    m_bottomRightCorner = BitmapXY(3242, 896);
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.30;
}

}  // namespace chess

}  // namespace alba
