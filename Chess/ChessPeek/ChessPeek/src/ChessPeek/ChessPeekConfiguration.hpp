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
    double getLeftIndentionMultiplier() const;
    double getRightIndentionMultiplier() const;
    double getTopIndentionMultiplier() const;
    double getBottomIndentionMultiplier() const;
    double getWhiteColorLimit() const;
    double getBlackColorLimit() const;

private:
    void initialize();
    void initializeChessDotComUserVsUser();
    void initializeChessDotComUserVsComputer();
    void initializeLichessDotOrg();

    ChessPeekConfigurationType m_type;
    AprgBitmap::BitmapXY m_topLeftCorner;
    AprgBitmap::BitmapXY m_bottomRightCorner;
    double m_leftIndentionMultiplier;
    double m_rightIndentionMultiplier;
    double m_topIndentionMultiplier;
    double m_bottomIndentionMultiplier;
    double m_whiteColorLimit;
    double m_blackColorLimit;
};

}

}
