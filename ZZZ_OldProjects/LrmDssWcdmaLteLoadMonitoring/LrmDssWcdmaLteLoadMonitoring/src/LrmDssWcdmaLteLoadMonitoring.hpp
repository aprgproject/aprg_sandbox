#pragma once

namespace alba {

// DssWcdmaLteLoadStateChangeFilteringCounts
constexpr unsigned int DSS_WCDMA_LTE_LOAD_STATE_CHANGE_FILTERING_COUNT = 5;

typedef enum EDssWcdmaFilterBandwidth {
    EDssWcdmaFilterBandwidth_0_KHz = 0,
    EDssWcdmaFilterBandwidth_600_KHz = 1,
    EDssWcdmaFilterBandwidth_1200_KHz = 2
} EDssWcdmaFilterBandwidth;

typedef enum EDssWcdmaLoad { EDssWcdmaLoad_Low = 0, EDssWcdmaLoad_Medium = 1, EDssWcdmaLoad_High = 2 } EDssWcdmaLoad;

class LrmDssWcdmaLteLoadMonitoring {
public:
    LrmDssWcdmaLteLoadMonitoring();
    unsigned int getConsecutiveLowerLoadStateCount() const;
    unsigned int getDchLoadFactor() const;
    unsigned int getHsdpaAndHsfachLoadFactor() const;
    unsigned int getMediumLoadThreshold() const;
    unsigned int getHighLoadThreshold() const;
    EDssWcdmaLoad getLoadStateFromCellLoad(unsigned int const cellLoad) const;
    unsigned int calculateCellLoad(
        unsigned int const numberOfDchUsers, unsigned int const numberOfHsdpaUsers,
        bool const hasHsfachInTheCell) const;
    EDssWcdmaLoad getNextLowerLoadState(EDssWcdmaLoad const loadState) const;
    EDssWcdmaFilterBandwidth convertLoadStateToFilterBandwidth(EDssWcdmaLoad const loadState) const;
    EDssWcdmaLoad convertFilterBandwidthToLoadState(EDssWcdmaFilterBandwidth const filterBandwidth) const;

    EDssWcdmaLoad determineLoadStateForTheNextFilterUpdateAndUpdateConsecutiveLowerLoadStateCountIfNeeded(
        EDssWcdmaLoad const currentLoadState, EDssWcdmaLoad const currentLoadStateOfTheAppliedFilter);

    void setConsecutiveLowerLoadStateCount(unsigned int const count);
    void setCommissioningLoadFactorValues(
        unsigned int const dchLoadFactor, unsigned int const hsdpaAndHsfachLoadFactor);
    void setCommissioningLoadThresholdValues(
        unsigned int const mediumLoadThreshold, unsigned int const highLoadThreshold);

private:
    unsigned int m_consecutiveLowerLoadStateCount;
    unsigned int m_dchLoadFactor;
    unsigned int m_hsdpaAndHsfachLoadFactor;
    unsigned int m_mediumLoadThreshold;
    unsigned int m_highLoadThreshold;
};

}  // namespace alba
