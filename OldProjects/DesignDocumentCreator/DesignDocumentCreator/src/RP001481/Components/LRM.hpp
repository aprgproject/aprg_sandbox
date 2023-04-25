#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>
#include <EDspMode.h>
#include <SDspInfo.h>

#include <map>
#include <set>
#include <vector>

namespace DesignDocumentCreator {

class DelayedLinkIndices {
public:
    struct DliPoolData {
        DliPoolData();
        unsigned int poolId;
        unsigned int numberOfIndices;
        bool isAllocated;
    };
    using PoolIdToNumberOfIndicesMap = std::map<unsigned int, DliPoolData>;
    using PoolIdToNumberOfIndicesPair = std::pair<unsigned int, DliPoolData>;
    using PoolIdVector = std::vector<unsigned int>;

    DelayedLinkIndices();
    unsigned int getAvailablePoolIdForRel4(unsigned int const minimumIndices) const;
    unsigned int getNumberOfIndices(unsigned int const poolId) const;
    bool isAllocated(unsigned int const poolId) const;
    PoolIdVector getAvailablePoolIds(unsigned int const minimumIndices) const;
    void prioritizeDliPoolForRel4(PoolIdVector& poolIds) const;
    bool hasConflictWithNextAvailablePool(PoolIdVector const& poolIds, unsigned int const minimumIndices) const;

    void setIndices(unsigned int const maximumIndices);
    void setPoolAsAllocated(unsigned int const poolId);
    void setPoolAsNotAllocated(unsigned int const poolId);

private:
    PoolIdToNumberOfIndicesMap m_poolIdToNumberOfIndices;
    unsigned int const m_numberOfIndices = 12;
};

class LRM : public Component {
public:
    struct DspData {
        DspData();
        SDspInfo dspInfo;
        EDspMode mode;
        bool isNbic;
        unsigned int dliPoolId;
    };

    struct LcgData {
        LcgData();
        SLCGList lcgInfo;
        unsigned int neededNumberOfDlis;
    };

    struct PowerGroupData {
        PowerGroupData();
        unsigned int numberOfK2sInPowerGroup;
    };

    using AddressesSet = std::set<TAaSysComNid>;
    using AddressesVector = std::vector<TAaSysComNid>;
    using DspAddressToDspDataPair = std::pair<TAaSysComNid, DspData>;
    using DspAddressToDspDataMap = std::map<TAaSysComNid, DspData>;
    using LcgIdToLcgDataPair = std::pair<TLocalCellGroupId, LcgData>;
    using LcgIdToLcgDataMap = std::map<TLocalCellGroupId, LcgData>;
    using PowerGroupIdToPowerGroupDataMap = std::map<TPowerGroupId, PowerGroupData>;
    using CoreToDliMap = std::map<TAaSysComNid, DelayedLinkIndices>;

    LRM(ComponentName const componentName);
    bool isRel4() const;
    bool isTcomInThisK2(TAaSysComNid const dspAddress) const;
    TAaSysComNid getMasterTcomNid() const;
    TAaSysComNid getKeplerAddressWithoutCore(TAaSysComNid const dspAddress) const;
    TAaSysComNid getFspAddressFromDspAddress(TAaSysComNid const dspAddress) const;
    TAaSysComNid getBoardFromFspAddress(TAaSysComNid const fspAddress) const;
    TAaSysComNid getBoardFromDspAddress(TAaSysComNid const dspAddress) const;
    TAaSysComNid getBoardFromSubrackAddress(const TAaSysComSicad subrackAddress) const;
    TPowerGroupId getPowerGroupId(TAaSysComNid const dspAddress) const;
    EDspMode getDspMode(TAaSysComNid const dspAddress) const;
    TNumberOfItems getNumberOfK2sInPowerGroup(TPowerGroupId const powerGroupId) const;
    TNumberOfItems getNumberOfK2sForLcg(TLocalCellGroupId const lcgId) const;
    TNumberOfItems getNumberOfK2sInFspForLcg(TAaSysComNid const fspAddress, TLocalCellGroupId const lcgId) const;
    DelayedLinkIndices::PoolIdVector getDliPoolIdsInFsp(TAaSysComNid const fspAddress) const;
    TNumberOfItems getNumberOfPicAndNbicPacketsInFsp(TAaSysComNid const fspAddress) const;
    TNumberOfItems getNumberOfMcdDcdAndMcdCcdPacketsInFsp(TAaSysComNid const fspAddress) const;
    TNumberOfItems getNumberOfMcdCcdPacketsInFspForOtherLcgs(
        TAaSysComNid const fspAddress, TLocalCellGroupId const lcgId) const;
    AddressesVector getDspAddressesForLcgId(TLocalCellGroupId const lcgId) const;
    AddressesVector getDspAddressesForFspAddressAndLcgId(
        AddressesVector const& fspAddresses, TLocalCellGroupId const lcgId) const;
    AddressesVector getFspAddressesForLcgId(TLocalCellGroupId const lcgId) const;

    TAaSysComNid findLocationOfMcdCcdDWithNbicForLcgId(TLocalCellGroupId const lcgId) const;
    TAaSysComNid findLocationOfMcdCcdDForLcgId(TLocalCellGroupId const lcgId) const;
    void removeFspAddressInConflictWithDli(AddressesVector& fspAddresses, TLocalCellGroupId const lcgId) const;
    void removeDspAddressesBasedOnFilterForSelectionMcdCcdD(AddressesVector& dspAddresses) const;
    void prioritizeDspAddressesForSelectionMcdCcdD(AddressesVector& dspAddresses, TLocalCellGroupId const lcgId) const;

    void processStartupForAllLcg();
    void processStartupForOneLcg(TLocalCellGroupId const lcgId);
    void allocateMcdDcd(TLocalCellGroupId const lcgId);
    void allocateCcdDcd(TLocalCellGroupId const lcgId);
    void allocateMcdCcdD(TLocalCellGroupId const lcgId);
    void allocateMcdCcdDWithNbic(TLocalCellGroupId const lcgId);
    unsigned int getAvailableDliInAddress(TAaSysComNid const dspAddress, TLocalCellGroupId const lcgId) const;
    bool hasConflictWithNextAvailablePool(
        TAaSysComNid const dspAddress, DelayedLinkIndices::PoolIdVector const& poolIds,
        TLocalCellGroupId const lcgId) const;
    unsigned int getNeededNumberOfDlis(TLocalCellGroupId const lcgId) const;

    void setMasterTcomNid(TAaSysComNid const masterTcomNid);
    void setDspModeInAddress(TAaSysComNid const dspAddress, EDspMode const mode);
    void setAsNbicMcdCcdDInAddress(TAaSysComNid const dspAddress);
    void setPoolIdInDspAddress(TAaSysComNid const dspAddress, unsigned int const poolId);
    void saveDspInformation(SLrmConfigurationDataInd const& lrmConfigurationData);
    void saveLcgInformation(SLrmConfigurationDataInd const& lrmConfigurationData);
    void saveLcrInformationInLcg(SLrmConfigurationDataInd const& lrmConfigurationData);
    void savePowerGroupInformation(SLrmConfigurationDataInd const& lrmConfigurationData);
    void saveDliInfo(SLrmConfigurationDataInd const& lrmConfigurationData);
    void saveDataFromLrmConfigurationDataInd(SLrmConfigurationDataInd const& lrmConfigurationData);

private:
    void handleLrmConfigurationData(GenericMessage const& genericMessage);
    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
    void handleOtherEvent(OtherEvent const& otherEvent) override;
    DspAddressToDspDataMap m_dspDatabase;
    LcgIdToLcgDataMap m_lcgDatabase;
    PowerGroupIdToPowerGroupDataMap m_powerGroupDatabase;
    DelayedLinkIndices m_delayedLinkIndices;
    CoreToDliMap m_coreToDli;
    TAaSysComNid m_masterTcomNid;
};

}  // namespace DesignDocumentCreator
