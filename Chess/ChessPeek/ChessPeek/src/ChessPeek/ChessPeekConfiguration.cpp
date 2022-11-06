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
    , m_leftIndentionMultiplier{}
    , m_rightIndentionMultiplier{}
    , m_topIndentionMultiplier{}
    , m_bottomIndentionMultiplier{}
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

double ChessPeekConfiguration::getLeftIndentionMultiplier() const
{
    return m_leftIndentionMultiplier;
}

double ChessPeekConfiguration::getRightIndentionMultiplier() const
{
    return m_rightIndentionMultiplier;
}

double ChessPeekConfiguration::getTopIndentionMultiplier() const
{
    return m_topIndentionMultiplier;
}

double ChessPeekConfiguration::getBottomIndentionMultiplier() const
{
    return m_bottomIndentionMultiplier;
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
    else if(ChessPeekConfigurationType::ChessDotComUserVsComputer == m_type)
    {
        initializeChessDotComUserVsComputer();
    }
    else if(ChessPeekConfigurationType::LichessDotOrg == m_type)
    {
        initializeLichessDotOrg();
    }
}

void ChessPeekConfiguration::initializeChessDotComUserVsUser()
{
    m_topLeftCorner = BitmapXY(2200, 151);
    m_bottomRightCorner = BitmapXY(3023, 974);
    m_leftIndentionMultiplier = 0.05;
    m_rightIndentionMultiplier = 0.05;
    m_topIndentionMultiplier = 0.03;
    m_bottomIndentionMultiplier = 0.03;
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.40;
}

void ChessPeekConfiguration::initializeChessDotComUserVsComputer()
{
    m_topLeftCorner = BitmapXY(2215, 151);
    m_bottomRightCorner = BitmapXY(3022, 958);
    m_leftIndentionMultiplier = 0.05;
    m_rightIndentionMultiplier = 0.05;
    m_topIndentionMultiplier = 0.03;
    m_bottomIndentionMultiplier = 0.03;
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.40;
}

void ChessPeekConfiguration::initializeLichessDotOrg()
{
    m_topLeftCorner = BitmapXY(2491, 145);
    m_bottomRightCorner = BitmapXY(3242, 896);
    m_leftIndentionMultiplier = 0.17;
    m_rightIndentionMultiplier = 0.09;
    m_topIndentionMultiplier = 0.21;
    m_bottomIndentionMultiplier = 0.15;
    m_whiteColorLimit = 0.91;
    m_blackColorLimit = 0.40;
}

}

}
