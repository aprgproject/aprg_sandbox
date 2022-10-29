#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <ChessPeek/ChessPeekConfigurationType.hpp>

namespace alba
{

namespace chess
{

class ChessPeekConfiguration
{
public:

    ChessPeekConfiguration() = delete;
    ChessPeekConfiguration(ChessPeekConfigurationType const type);

    ChessPeekConfigurationType getType() const;
    AprgBitmap::BitmapXY getTopLeftCorner() const;
    AprgBitmap::BitmapXY getBottomRightCorner() const;
    double getXIndentionMultiplier() const;
    double getYIndentionMultiplier() const;
    double getWhiteColorLimit() const;
    double getBlackColorLimit() const;

private:
    void initialize();
    void initializeChessDotComUserVsUser();
    void initializeChessDotComUserVsComputer();

    ChessPeekConfigurationType m_type;
    AprgBitmap::BitmapXY m_topLeftCorner;
    AprgBitmap::BitmapXY m_bottomRightCorner;
    double m_xIndentionMultiplier;
    double m_yIndentionMultiplier;
    double m_whiteColorLimit;
    double m_blackColorLimit;
};

}

}
