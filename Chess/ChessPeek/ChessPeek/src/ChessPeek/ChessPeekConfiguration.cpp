#include "ChessPeekConfiguration.hpp"

using namespace alba::AprgBitmap;

namespace alba
{

namespace chess
{

ChessPeekConfiguration::ChessPeekConfiguration(
        ChessPeekConfigurationType const type)
    : m_type(type)
    , m_topLeftCorner{}
    , m_bottomRightCorner{}
    , m_xIndentionMultiplier{}
    , m_yIndentionMultiplier{}
    , m_whiteColorLimit{}
    , m_blackColorLimit{}
{
    initialize();
}

ChessPeekConfigurationType ChessPeekConfiguration::getType() const
{
    return m_type;
}

AprgBitmap::BitmapXY ChessPeekConfiguration::getTopLeftCorner() const
{
    return m_topLeftCorner;
}

AprgBitmap::BitmapXY ChessPeekConfiguration::getBottomRightCorner() const
{
    return m_bottomRightCorner;
}

double ChessPeekConfiguration::getXIndentionMultiplier() const
{
    return m_xIndentionMultiplier;
}

double ChessPeekConfiguration::getYIndentionMultiplier() const
{
    return m_yIndentionMultiplier;
}

double ChessPeekConfiguration::getWhiteColorLimit() const
{
    return m_whiteColorLimit;
}

double ChessPeekConfiguration::getBlackColorLimit() const
{
    return m_blackColorLimit;
}

void ChessPeekConfiguration::initialize()
{
    if(ChessPeekConfigurationType::ChessDotComUserVsUser == m_type)
    {
        initializeChessDotComUserVsUser();
    }
    else if(ChessPeekConfigurationType::ChessDotComUserVsUser == m_type)
    {
        initializeChessDotComUserVsComputer();
    }
}

void ChessPeekConfiguration::initializeChessDotComUserVsUser()
{
    m_topLeftCorner = BitmapXY(2200, 151);
    m_bottomRightCorner = BitmapXY(3023, 974);
    m_xIndentionMultiplier = 0.05;
    m_yIndentionMultiplier = 0.03;
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.40;
}

void ChessPeekConfiguration::initializeChessDotComUserVsComputer()
{
    m_topLeftCorner = BitmapXY(2207, 151);
    m_bottomRightCorner = BitmapXY(3014, 958);
    m_xIndentionMultiplier = 0.05;
    m_yIndentionMultiplier = 0.03;
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.40;
}

}

}
