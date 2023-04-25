#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <ChessPeek/ChessPeekConfigurationType.hpp>
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
    AprgBitmap::BitmapXY getTopLeftCorner() const;
    AprgBitmap::BitmapXY getBottomRightCorner() const;
    double getWhiteColorLimit() const;
    double getBlackColorLimit() const;
    stringHelper::StringPairs const& getUciOptionNamesAndValuePairs() const;

private:
    void initialize();
    void initializeCommonParameters();
    void initializeChessDotComUserVsUser();
    void initializeChessDotComUserVsComputer();
    void initializeLichessDotOrg();

    ChessPeekConfigurationType m_type;
    std::string m_chessEnginePath;
    std::string m_screenShotPath;
    stringHelper::StringPairs m_uciOptionNamesAndValuePairs;
    AprgBitmap::BitmapXY m_topLeftCorner;
    AprgBitmap::BitmapXY m_bottomRightCorner;
    double m_whiteColorLimit;
    double m_blackColorLimit;
};

}  // namespace chess

}  // namespace alba
