#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

#include <EDspMode.h>
#include <SDspInfo.h>

#include <map>
#include <vector>

namespace DesignDocumentCreator
{

class LRM : public Component
{
public:
    const TAaSysComNid INVALID_DSP_ADDRESS=0xFFFF;

    struct DspData
    {
        DspData();
        SDspInfo dspInfo;
        EDspMode mode;
    };

    struct LcgData
    {
        LcgData();
        SLCGList lcgInfo;
    };

    struct PowerGroupData
    {
        PowerGroupData();
        unsigned int numberOfK2sInPowerGroup;
    };

    struct FspData
    {
        FspData();
        unsigned int numberOfK2sInFsp;
        unsigned int numberOfMcdCcdPacketsInFsp;
    };

    using DspAddressesVector = std::vector<TAaSysComNid>;
    using DspAddressToDspDataPair = std::pair<TAaSysComNid, DspData>;
    using DspAddressToDspDataMap = std::map<TAaSysComNid, DspData>;
    using LcgIdToLcgDataPair = std::pair<TLocalCellGroupId, LcgData>;
    using LcgIdToLcgDataMap = std::map<TLocalCellGroupId, LcgData>;
    using PowerGroupIdToPowerGroupDataMap = std::map<TPowerGroupId, PowerGroupData>;
    using FspAddressToFspDataMap = std::map<TAaSysComNid, FspData>;

    LRM(ComponentName const componentName);
    bool isTcomInThisK2(TAaSysComNid const dspAddress) const;
    TAaSysComNid getMasterTcomNid() const;
    TNumberOfItems getNumberOfMcdCcdPacketsInFsp(TAaSysComNid const fspNid) const;
    TAaSysComNid getFspAddress(TAaSysComNid const dspAddress) const;
    TPowerGroupId getPowerGroupId(TAaSysComNid const dspAddress) const;
    TNumberOfItems getNumberOfK2sInPowerGroup(TPowerGroupId const powerGroupId) const;
    TNumberOfItems getNumberOfK2sInFsp(TAaSysComNid const fspAddress) const;
    DspAddressesVector getDspAddressesForLcgId(TLocalCellGroupId const lcgId) const;

    TAaSysComNid findLocationOfMcdCcdD(TLocalCellGroupId const lcgId) const;
    void removeDspAddressesBasedOnFilterForSelectionMcdCcdD(DspAddressesVector & dspAddresses) const;
    void prioritizeDspAddressesForSelectionMcdCcdD(DspAddressesVector & dspAddresses) const;

    void processStartupForAllLcg();
    void processStartupForOneLcg(TLocalCellGroupId const lcgId);
    void allocateMcdCcdD(TAaSysComNid const mcdCcdDAddress);

    void setMasterTcomNid(TAaSysComNid const masterTcomNid);
    void saveDspInformation(SLrmConfigurationDataInd const& lrmConfigurationData);
    void saveLcgInformation(SLrmConfigurationDataInd const& lrmConfigurationData);
    void savePowerGroupInformation(SLrmConfigurationDataInd const& lrmConfigurationData);
    void saveFspInformationFromDspInformation(SLrmConfigurationDataInd const& lrmConfigurationData);

private:
    void handleLrmConfigurationData(GenericMessage const& genericMessage);
    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
    void handleOtherEvent(OtherEvent const& otherEvent) override;
    DspAddressToDspDataMap m_dspDatabase;
    LcgIdToLcgDataMap m_lcgDatabase;
    PowerGroupIdToPowerGroupDataMap m_powerGroupDatabase;
    FspAddressToFspDataMap m_fspDatabase;
    TAaSysComNid m_masterTcomNid;
};

}
