#include "Configuration.hpp"

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

Configuration::Configuration(Type const type)
    : m_type(type),
      m_chessEnginePath(),
      m_uciOptionNamesAndValuePairs(),
      m_boardTopLeft{},
      m_boardBottomRight{},
      m_whiteColorLimit{},
      m_blackColorLimit{} {
    initialize();
}

Configuration::Type Configuration::getType() const { return m_type; }

string const& Configuration::getChessEnginePath() const { return m_chessEnginePath; }

XY Configuration::getTopLeftOfBoard() const { return m_boardTopLeft; }

XY Configuration::getBottomRightOfBoard() const { return m_boardBottomRight; }

double Configuration::getWhiteColorLimit() const { return m_whiteColorLimit; }

double Configuration::getBlackColorLimit() const { return m_blackColorLimit; }

stringHelper::StringPairs const& Configuration::getUciOptionNamesAndValuePairs() const {
    return m_uciOptionNamesAndValuePairs;
}

void Configuration::initialize() {
    initializeCommonParameters();
    initializeSpecificParameters();
}

void Configuration::initializeCommonParameters() {
    m_chessEnginePath = APRG_DIR R"(\Chess\ChessPeek\Files\stockfish15.exe)";

    // Stockfish UCI parameters
    // uci
    // id name Stockfish 15
    // id author the Stockfish developers (see AUTHORS file)
    // option name Debug Log File type string default
    // option name Threads type spin default 1 min 1 max 512
    // option name Hash type spin default 16 min 1 max 33554432
    // option name Clear Hash type button
    // option name Ponder type check default false
    // option name MultiPV type spin default 1 min 1 max 500
    // option name Skill Level type spin default 20 min 0 max 20
    // option name Move Overhead type spin default 10 min 0 max 5000
    // option name Slow Mover type spin default 100 min 10 max 1000
    // option name nodestime type spin default 0 min 0 max 10000
    // option name UCI_Chess960 type check default false
    // option name UCI_AnalyseMode type check default false
    // option name UCI_LimitStrength type check default false
    // option name UCI_Elo type spin default 1350 min 1350 max 2850
    // option name UCI_ShowWDL type check default false
    // option name SyzygyPath type string default <empty>
    //  option name SyzygyProbeDepth type spin default 1 min 1 max 100
    // option name Syzygy50MoveRule type check default true
    // option name SyzygyProbeLimit type spin default 7 min 0 max 7
    // option name Use NNUE type check default true
    // option name EvalFile type string default nn-6877cd24400e.nnue
    // uciok

    m_uciOptionNamesAndValuePairs = {
        {"Threads", "4"},               // set equal to number of cores to have optimized performance
        {"MultiPV", "15"},              // number of moves to search
        {"Slow Mover", "1000"},         // max value, let engine think for max time
        {"UCI_LimitStrength", "true"},  // limit the strength to be more like a human
        {"UCI_Elo", "1350"},            // limit the strength to be more like a human
        {"Skill Level", "1"}};          // limit the strength to be more like a human
}

void Configuration::initializeSpecificParameters() {
    switch (m_type) {
        case Type::ChessDotComVersus: {
            initializeChessDotComVersus();
            break;
        }
        case Type::ChessDotComPuzzle: {
            initializeChessDotComPuzzle();
            break;
        }
        case Type::LichessVersus: {
            initializeLichessVersus();
            break;
        }
        case Type::LichessStream: {
            initializeLichessStream();
            break;
        }
    }
}

void Configuration::initializeChessDotComVersus() {
    m_boardTopLeft = XY(2292, 151);
    m_boardBottomRight = XY(3107, 966);
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.40;
}

void Configuration::initializeChessDotComPuzzle() {
    m_boardTopLeft = XY(2225, 101);
    m_boardBottomRight = XY(3144, 1020);
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.40;
}

void Configuration::initializeLichessVersus() {
    m_boardTopLeft = XY(2488, 145);
    m_boardBottomRight = XY(3239, 896);
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.30;
}

void Configuration::initializeLichessStream() {
    m_boardTopLeft = XY(2498, 159);
    m_boardBottomRight = XY(3233, 894);
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.30;
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
