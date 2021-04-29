#include "LrmDssWcdmaLteLoadMonitoring.hpp"

namespace alba
{

LrmDssWcdmaLteLoadMonitoring::LrmDssWcdmaLteLoadMonitoring()
    : m_consecutiveLowerLoadStateCount(0)
    , m_dchLoadFactor(0)
    , m_hsdpaAndHsfachLoadFactor(0)
    , m_mediumLoadThreshold(0)
    , m_highLoadThreshold(0)
{}

unsigned int LrmDssWcdmaLteLoadMonitoring::getConsecutiveLowerLoadStateCount() const
{
    return m_consecutiveLowerLoadStateCount;
}

unsigned int LrmDssWcdmaLteLoadMonitoring::getDchLoadFactor() const
{
    return m_dchLoadFactor;
}

unsigned int LrmDssWcdmaLteLoadMonitoring::getHsdpaAndHsfachLoadFactor() const
{
    return m_hsdpaAndHsfachLoadFactor;
}

unsigned int LrmDssWcdmaLteLoadMonitoring::getMediumLoadThreshold() const
{
    return m_mediumLoadThreshold;
}

unsigned int LrmDssWcdmaLteLoadMonitoring::getHighLoadThreshold() const
{
    return m_highLoadThreshold;
}

EDssWcdmaLoad LrmDssWcdmaLteLoadMonitoring::getLoadStateFromCellLoad(unsigned int const cellLoad) const
{
    EDssWcdmaLoad loadState(EDssWcdmaLoad_Low);

    if(cellLoad >= m_highLoadThreshold)
    {
        loadState = EDssWcdmaLoad_High;
    }
    else if(cellLoad >= m_mediumLoadThreshold)
    {
        loadState = EDssWcdmaLoad_Medium;
    }
    return loadState;
}

unsigned int LrmDssWcdmaLteLoadMonitoring::calculateCellLoad(unsigned int const numberOfDchUsers, unsigned int const numberOfHsdpaUsers, bool const hasHsfachInTheCell) const
{
    unsigned const int hsfachLoad = hasHsfachInTheCell ? 1 : 0;
    return (numberOfDchUsers*m_dchLoadFactor) + ((numberOfHsdpaUsers+hsfachLoad)*m_hsdpaAndHsfachLoadFactor);
}

EDssWcdmaLoad LrmDssWcdmaLteLoadMonitoring::getNextLowerLoadState(EDssWcdmaLoad const loadState) const
{
    EDssWcdmaLoad result(EDssWcdmaLoad_Low);
    unsigned int loadStateValue = static_cast<EDssWcdmaLoad>(loadState);
    constexpr unsigned int lowLoadStateValue = static_cast<EDssWcdmaLoad>(EDssWcdmaLoad_Low);
    if(loadStateValue > lowLoadStateValue)
    {
        result = static_cast<EDssWcdmaLoad>(loadStateValue-1);
    }
    return result;
}

EDssWcdmaFilterBandwidth LrmDssWcdmaLteLoadMonitoring::convertLoadStateToFilterBandwidth(EDssWcdmaLoad const loadState) const
{
    EDssWcdmaFilterBandwidth result(EDssWcdmaFilterBandwidth_0_KHz);
    switch (loadState)
    {
    case EDssWcdmaLoad_Low:
        result = EDssWcdmaFilterBandwidth_1200_KHz;
        break;
    case EDssWcdmaLoad_Medium:
        result = EDssWcdmaFilterBandwidth_600_KHz;
        break;
    case EDssWcdmaLoad_High:
        result = EDssWcdmaFilterBandwidth_0_KHz;
        break;
    }
    return result;
}

EDssWcdmaLoad LrmDssWcdmaLteLoadMonitoring::convertFilterBandwidthToLoadState(EDssWcdmaFilterBandwidth const filterBandwidth) const
{
    EDssWcdmaLoad result(EDssWcdmaLoad_Low);
    switch (filterBandwidth)
    {
    case EDssWcdmaFilterBandwidth_0_KHz:
        result = EDssWcdmaLoad_High;
        break;
    case EDssWcdmaFilterBandwidth_600_KHz:
        result = EDssWcdmaLoad_Medium;
        break;
    case EDssWcdmaFilterBandwidth_1200_KHz:
        result = EDssWcdmaLoad_Low;
        break;
    }
    return result;
}

EDssWcdmaLoad LrmDssWcdmaLteLoadMonitoring::determineLoadStateForTheNextFilterUpdateAndUpdateConsecutiveLowerLoadStateCountIfNeeded(EDssWcdmaLoad const currentLoadState, EDssWcdmaLoad const currentLoadStateOfTheAppliedFilter)
{
    EDssWcdmaLoad result(currentLoadState);
    if(currentLoadState<currentLoadStateOfTheAppliedFilter)
    {
        m_consecutiveLowerLoadStateCount++;
        if(m_consecutiveLowerLoadStateCount<DSS_WCDMA_LTE_LOAD_STATE_CHANGE_FILTERING_COUNT)
        {
            result = getNextLowerLoadState(currentLoadStateOfTheAppliedFilter);
        }
        else
        {
            result = currentLoadStateOfTheAppliedFilter;
        }
    }
    else
    {
        m_consecutiveLowerLoadStateCount=0;
    }
    return result;
}

void LrmDssWcdmaLteLoadMonitoring::setConsecutiveLowerLoadStateCount(unsigned int const count)
{
    m_consecutiveLowerLoadStateCount = count;
}

void LrmDssWcdmaLteLoadMonitoring::setCommissioningLoadFactorValues(unsigned int const dchLoadFactor, unsigned int const hsdpaAndHsfachLoadFactor)
{
    m_dchLoadFactor = dchLoadFactor;
    m_hsdpaAndHsfachLoadFactor = hsdpaAndHsfachLoadFactor;
}

void LrmDssWcdmaLteLoadMonitoring::setCommissioningLoadThresholdValues(unsigned int const mediumLoadThreshold, unsigned int const highLoadThreshold)
{
    m_mediumLoadThreshold = mediumLoadThreshold;
    m_highLoadThreshold = highLoadThreshold;
}



}
