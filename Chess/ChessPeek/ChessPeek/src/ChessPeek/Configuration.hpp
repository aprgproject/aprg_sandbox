#pragma once

#include <ChessPeek/CommonTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class Configuration {
public:
    enum class Type { ChessDotComVersus, ChessDotComPuzzle, ChessDotComExplorer, LichessVersus, LichessStream };

    Configuration() = delete;
    Configuration(Type const type);
    Type getType() const;
    std::string const& getChessEnginePath() const;
    std::string const& getScreenShotPath() const;
    XY getTopLeftOfBoard() const;
    XY getBottomRightOfBoard() const;
    double getWhiteColorLimit() const;
    double getBlackColorLimit() const;
    stringHelper::StringPairs const& getUciOptionNamesAndValuePairs() const;

private:
    void initialize();
    void initializeCommonParameters();
    void initializeSpecificParameters();
    void initializeChessDotComVersus();
    void initializeChessDotComPuzzle();
    void initializeChessDotComExplorer();
    void initializeLichessVersus();
    void initializeLichessStream();
    Type m_type;
    std::string m_chessEnginePath;
    stringHelper::StringPairs m_uciOptionNamesAndValuePairs;
    XY m_boardTopLeft;
    XY m_boardBottomRight;
    double m_whiteColorLimit;
    double m_blackColorLimit;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
