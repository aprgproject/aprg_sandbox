#pragma once

#include <ChessPeek/ChessPeekConfigurationType.hpp>
#include <ChessPeek/CommonTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba {

namespace chess {

class ChessPeekConfiguration {
public:
    ChessPeekConfiguration() = delete;
    ChessPeekConfiguration(ChessPeekConfigurationType const type);

    ChessPeekConfigurationType getType() const;
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
    void initializeLichessVersus();
    void initializeLichessStream();

    ChessPeekConfigurationType m_type;
    std::string m_chessEnginePath;
    stringHelper::StringPairs m_uciOptionNamesAndValuePairs;
    XY m_boardTopLeft;
    XY m_boardBottomRight;    double m_whiteColorLimit;
    double m_blackColorLimit;
};
}  // namespace chess

}  // namespace alba
