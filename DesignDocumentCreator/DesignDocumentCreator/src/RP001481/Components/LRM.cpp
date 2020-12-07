#include "LRM.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Utils/AddressHelper.hpp>

#include <algorithm>
#include <iostream>#include <iterator>
#include <set>
#include <vector>

#include <Debug/AlbaDebug.hpp>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;
namespace DesignDocumentCreator
{

LRM::DspData::DspData()
    : mode(EDspMode_Original) // fake, only rel4 is needed here
{}

LRM::LcgData::LcgData(){}

LRM::PowerGroupData::PowerGroupData()
    : numberOfK2sInPowerGroup(0)
{}

LRM::FspData::FspData()
    : numberOfK2sInFsp(0)
    , numberOfMcdCcdPacketsInFsp(0)
{}

LRM::LRM(ComponentName const componentName)
    : Component(componentName)
    , m_masterTcomNid(AddressHelper::INVALID_DSP_ADDRESS)
{}

bool LRM::isTcomInThisK2(TAaSysComNid const dspAddress) const
{
    //This is FAKE!
    return getKeplerAddressWithoutCore(m_masterTcomNid)==getKeplerAddressWithoutCore(dspAddress);
}

TAaSysComNid LRM::getMasterTcomNid() const{
    logNoteOnComponent("LRM fetches the NidAddress of TCOM from WAM ADDRESS Indication message sent previously.");
    return m_masterTcomNid;
}

TAaSysComNid LRM::getKeplerAddressWithoutCore(TAaSysComNid const dspAddress) const
{
    //This is FAKE! Use framework functions instead
    return dspAddress & 0xFFF0;
}

TAaSysComNid LRM::getFspAddress(TAaSysComNid const dspAddress) const{
    //This is FAKE! Use framework functions instead
    return dspAddress>>8;
}

TPowerGroupId LRM::getPowerGroupId(TAaSysComNid const dspAddress) const
{
    //This is FAKE!
    TNumberOfItems powerGroupId(0);
    if(m_dspDatabase.find(dspAddress) != m_dspDatabase.cend())
    {
        powerGroupId = m_dspDatabase.at(dspAddress).dspInfo.powerGroupId;
    }
    return powerGroupId;
}

EDspMode LRM::getDspMode(TAaSysComNid const dspAddress) const
{
    //This is FAKE!
    EDspMode result(EDspMode_Original);
    if(m_dspDatabase.find(dspAddress) != m_dspDatabase.cend())
    {
        result = m_dspDatabase.at(dspAddress).mode;
    }
    return result;
}

TNumberOfItems LRM::getNumberOfK2sInPowerGroup(TPowerGroupId const powerGroupId) const
{
    //This is FAKE!    TNumberOfItems numberOfK2sInPowerGroup(0);
    if(m_powerGroupDatabase.find(powerGroupId) != m_powerGroupDatabase.cend())
    {
        numberOfK2sInPowerGroup = m_powerGroupDatabase.at(powerGroupId).numberOfK2sInPowerGroup;
    }
    return numberOfK2sInPowerGroup;
}

TNumberOfItems LRM::getNumberOfK2sForLcg(TLocalCellGroupId const lcgId) const
{
    //This is FAKE!
    unsigned int numberOfK2s(0);
    for(DspAddressToDspDataPair const & dspAddressToDspDataPair : m_dspDatabase)
    {
        DspData const& dspData(dspAddressToDspDataPair.second);
        if(dspData.dspInfo.localCellGroupId == lcgId)
        {
            numberOfK2s++;
        }
    }
    return numberOfK2s;
}

TNumberOfItems LRM::getNumberOfK2sInFspForLcg(TAaSysComNid const fspAddress, TLocalCellGroupId const lcgId) const
{
    //This is FAKE!
    unsigned int numberOfK2s(0);
    for(DspAddressToDspDataPair const & dspAddressToDspDataPair : m_dspDatabase)
    {
        DspData const& dspData(dspAddressToDspDataPair.second);
        if(dspData.dspInfo.localCellGroupId == lcgId && getFspAddress(dspData.dspInfo.dspAddress) == fspAddress)
        {
            numberOfK2s++;
        }
    }
    return numberOfK2s;
}

TNumberOfItems LRM::getNumberOfMcdDcdAndMcdCcdPacketsInFsp(TAaSysComNid const fspAddress, TLocalCellGroupId const lcgId) const
{
    //This is FAKE!
    unsigned int numberOfK2PacketsWhichSatisfy(0);
    for(DspAddressToDspDataPair const & dspAddressToDspDataPair : m_dspDatabase)
    {
        DspData const& dspData(dspAddressToDspDataPair.second);
        if(getFspAddress(dspData.dspInfo.dspAddress) == fspAddress && (dspData.mode == EDspMode_Kepler_MCD_DCD || dspData.mode == EDspMode_Kepler_MCD_CCDD))
        {
            numberOfK2PacketsWhichSatisfy++;
        }
    }
    return numberOfK2PacketsWhichSatisfy;
}

TNumberOfItems LRM::getNumberOfMcdCcdPacketsInFspForOtherLcgs(TAaSysComNid const fspAddress, TLocalCellGroupId const lcgId) const
{
    //This is FAKE!
    unsigned int numberOfMcdCcds(0);
    for(DspAddressToDspDataPair const & dspAddressToDspDataPair : m_dspDatabase)
    {
        DspData const& dspData(dspAddressToDspDataPair.second);
        if(dspData.dspInfo.localCellGroupId != lcgId && getFspAddress(dspData.dspInfo.dspAddress) == fspAddress && dspData.mode == EDspMode_Kepler_MCD_CCDD)
        {
            numberOfMcdCcds++;
        }
    }
    return numberOfMcdCcds;
}

LRM::DspAddressesVector LRM::getDspAddressesForLcgId(TLocalCellGroupId const lcgId) const
{
    DspAddressesVector dspAddresses;
    for(DspAddressToDspDataPair const & dspAddressToDspDataPair : m_dspDatabase)
    {
        DspData const& dspData(dspAddressToDspDataPair.second);
        if(dspData.dspInfo.localCellGroupId == lcgId)        {
            dspAddresses.emplace_back(dspData.dspInfo.dspAddress);
        }
    }
    return dspAddresses; //RVO (Return value optimization)
}

TAaSysComNid LRM::findLocationOfMcdDcdForStartup(TLocalCellGroupId const lcgId) const
{
    TAaSysComNid mcdDcdAddress(AddressHelper::INVALID_DSP_ADDRESS);
    DspAddressesVector dspAddresses(getDspAddressesForLcgId(lcgId));
    removeDspAddressesBasedOnFilterForSelectionMcdDcd(dspAddresses);
    prioritizeDspAddressesForSelectionMcdDcdForStartup(dspAddresses, lcgId);
    if(!dspAddresses.empty())
    {
        mcdDcdAddress = dspAddresses.front();
    }
    return mcdDcdAddress;
}

void LRM::removeDspAddressesBasedOnFilterForSelectionMcdDcd(DspAddressesVector & dspAddresses) const
{
    // WBTS_CP_19861
    dspAddresses.erase(remove_if(dspAddresses.begin(), dspAddresses.end(), [&](TAaSysComNid const dspAddress)
    {
        EDspMode dspMode(getDspMode(dspAddress));
        bool isAcceptableDspOriginalMode = (dspMode == EDspMode_Kepler_DCD_DCD) || (dspMode == EDspMode_Kepler_DCD_PIC); // WBTS_CP_19831
        return !isAcceptableDspOriginalMode;
    }), dspAddresses.end());
}

void LRM::prioritizeDspAddressesForSelectionMcdDcdForStartup(DspAddressesVector & dspAddresses, TLocalCellGroupId const lcgId) const
{
    // WBTS_CP_20066, Selection of free device since startup
    nth_element(dspAddresses.begin(), dspAddresses.begin(), dspAddresses.end(), [&](TAaSysComNid const dspAddress1, TAaSysComNid const dspAddress2)
    {
        bool result(false);
        unsigned int numberOfPacketsInFspForDspAddress1(getNumberOfMcdDcdAndMcdCcdPacketsInFsp(getFspAddress(dspAddress1), lcgId)); //selection rule 1. FSP card having the smallest number of already allocated MCD + CCD-d packets and MCD + DCD packets.
        unsigned int numberOfPacketsInFspForDspAddress2(getNumberOfMcdDcdAndMcdCcdPacketsInFsp(getFspAddress(dspAddress2), lcgId));

        if(numberOfPacketsInFspForDspAddress1 == numberOfPacketsInFspForDspAddress2)
        {
            result = dspAddress1<dspAddress2; //2. FSP card with the lowest address.

        }
        else
        {
            result = numberOfPacketsInFspForDspAddress1<numberOfPacketsInFspForDspAddress2;
        }
        return result;
    });
}

TAaSysComNid LRM::findLocationOfMcdCcdDForLcgId(TLocalCellGroupId const lcgId) const
{
    TAaSysComNid mcdCcdAddress(AddressHelper::INVALID_DSP_ADDRESS);
    DspAddressesVector dspAddresses(getDspAddressesForLcgId(lcgId));
    removeDspAddressesBasedOnFilterForSelectionMcdCcdD(dspAddresses);
    prioritizeDspAddressesForSelectionMcdCcdD(dspAddresses, lcgId);
    if(!dspAddresses.empty())
    {
        mcdCcdAddress = dspAddresses.front();
    }    return mcdCcdAddress;
}

void LRM::removeDspAddressesBasedOnFilterForSelectionMcdCcdD(DspAddressesVector & dspAddresses) const
{
    // WBTS_CP_19861
    dspAddresses.erase(remove_if(dspAddresses.begin(), dspAddresses.end(), [&](TAaSysComNid const dspAddress)
    {
        unsigned int numberOfPowerGroupForDspAddress(getNumberOfK2sInPowerGroup(getPowerGroupId(dspAddress)));
        EDspMode dspMode(getDspMode(dspAddress));
        bool isIncorrectNumberOfK2InPowerGroup(numberOfPowerGroupForDspAddress<2); //selection rule 1.  Belongs to Power Group where its two devices are allocated for the LCG.  See [Note 2].
        bool isAcceptableDspOriginalMode = (dspMode == EDspMode_Kepler_DCD_DCD) || (dspMode == EDspMode_Kepler_DCD_PIC); // WBTS_CP_19831
        // isTcomInThisK2() WBTS_CP_19862: Only devices where TCOM is not allocated in its ARM shall be considered here.
        return isTcomInThisK2(dspAddress) || isIncorrectNumberOfK2InPowerGroup || !isAcceptableDspOriginalMode;
    }), dspAddresses.end());
}

void LRM::prioritizeDspAddressesForSelectionMcdCcdD(DspAddressesVector & dspAddresses, TLocalCellGroupId const lcgId) const
{
    // WBTS_CP_19861
    nth_element(dspAddresses.begin(), dspAddresses.begin(), dspAddresses.end(), [&](TAaSysComNid const dspAddress1, TAaSysComNid const dspAddress2)
    {
        bool result(false);
        unsigned int numberOfMcdCcdPacketsInFspForDspAddress1(getNumberOfMcdCcdPacketsInFspForOtherLcgs(getFspAddress(dspAddress1), lcgId)); //selection rule 2: Is located on baseband card with lowest number of MCD + CCD-d packets allocated for other LCGs.  See [Note 3].
        unsigned int numberOfMcdCcdPacketsInFspForDspAddress2(getNumberOfMcdCcdPacketsInFspForOtherLcgs(getFspAddress(dspAddress2), lcgId));
        unsigned int numberOfK2InFspForDspAddress1(getNumberOfK2sInFspForLcg(getFspAddress(dspAddress1), lcgId)); //selection rule 3: Is located on baseband card with largest amount of K2 assigned to LCG.
        unsigned int numberOfK2InFspForDspAddress2(getNumberOfK2sInFspForLcg(getFspAddress(dspAddress2), lcgId));

        if(numberOfMcdCcdPacketsInFspForDspAddress1 == numberOfMcdCcdPacketsInFspForDspAddress2)
        {
            if(numberOfK2InFspForDspAddress1 == numberOfK2InFspForDspAddress2)
            {
                result = dspAddress1<dspAddress2; //4.  Has the lowest address.
            }
            else
            {
                result = numberOfK2InFspForDspAddress1>numberOfK2InFspForDspAddress2;
            }
        }
        else        {
            result = numberOfMcdCcdPacketsInFspForDspAddress1<numberOfMcdCcdPacketsInFspForDspAddress2;
        }
        return result;
    });
}

void LRM::processStartupForAllLcg()
{
    logNoteOnComponent("LRM performs startup for all LCGs.");
    for(LcgIdToLcgDataPair const& lcgIdToLcgDataPair : m_lcgDatabase)
    {
        LcgData const& lcgData(lcgIdToLcgDataPair.second);
        processStartupForOneLcg(lcgData.lcgInfo.lcgId);
    }
}
void LRM::processStartupForOneLcg(TLocalCellGroupId const lcgId)
{
    LcgData const& lcgData(m_lcgDatabase[lcgId]);
    if(lcgData.lcgInfo.hspaConfigurationType==EHspaConfigurationType_BasicRel4)
    {
        logNoteOnComponent("LRM performs allocation for REL4.");
        if(lcgData.lcgInfo.isNbicEnabled==EBoolean_True)
        {
            allocateMcdCcdDWithNbic();
        }
        else
        {
            TNumberOfItems numberOfK2s(getNumberOfK2sForLcg(lcgId));
            if(numberOfK2s>2)
            {
                allocateMcdCcdD();
            }
            else
            {
                allocateCcdDcd();
            }
        }
    }
    else
    {
        logNoteOnComponent("LRM performs legacy allocation for REL3.");
        if(lcgData.lcgInfo.isNbicEnabled==EBoolean_True)
        {
            logNoteOnComponent("LRM performs legacy NBIC allocation for REL3 in RAN3374.");
        }
    }
}

void LRM::allocateMcdDcd()
{
    logNoteOnComponent("LRM allocates MCD DCD.");
}

void LRM::allocateCcdDcd()
{
    logNoteOnComponent("LRM allocates CCD DCD.");
}

void LRM::allocateMcdCcdD()
{
    logNoteOnComponent("LRM allocates MCD CCD-d.");
    TAaSysComNid mcdCcdDAddress(findLocationOfMcdCcdDForLcgId(lcgId));
    if(mcdCcdDAddress != AddressHelper::INVALID_DSP_ADDRESS)
    {
        //allocateMcdCcdD(mcdCcdDAddress);
    }
}

void LRM::allocateMcdCcdDWithNbic()
{
    logNoteOnComponent("LRM allocates MCD CCD-d with NBIC");
    TAaSysComNid mcdCcdDAddress(findLocationOfMcdCcdDForLcgId(lcgId));
    if(mcdCcdDAddress != AddressHelper::INVALID_DSP_ADDRESS)
    {
        //allocateMcdCcdD(mcdCcdDAddress);
    }
}
void LRM::setMasterTcomNid(TAaSysComNid const masterTcomNid)
{
    //This is FAKE! This should be set in wamaddress indication. I'm not gonna cover wam address indication.    m_masterTcomNid = masterTcomNid;
}

void LRM::setDspModeToAddress(TAaSysComNid const dspAddress, EDspMode const mode)
{
    m_dspDatabase[dspAddress].mode = mode;
}

void LRM::saveDspInformation(SLrmConfigurationDataInd const& lrmConfigurationData)
{
    logNoteOnComponent("LRM saves DSP information from TC_LRM_CONFIGURATION_DATA_IND_MSG");    for(unsigned int index=0; index<lrmConfigurationData.numOfDsps; index++)
    {
        SDspInfo const& currentDspInfo(lrmConfigurationData.dspInfo[index]);
        m_dspDatabase[currentDspInfo.dspAddress].dspInfo = currentDspInfo;
        m_dspDatabase[currentDspInfo.dspAddress].mode = EDspMode_Kepler_DCD_DCD;
    }
}

void LRM::saveLcgInformation(SLrmConfigurationDataInd const& lrmConfigurationData)
{
    logNoteOnComponent("LRM saves LCG information from TC_LRM_CONFIGURATION_DATA_IND_MSG");
    for(unsigned int index=0; index<lrmConfigurationData.numOfLcgInfo; index++)
    {
        SLCGList const& currentLcgInfo(lrmConfigurationData.lcgInfo[index]);
        m_lcgDatabase[currentLcgInfo.lcgId].lcgInfo = currentLcgInfo;
    }
}

void LRM::savePowerGroupInformation(SLrmConfigurationDataInd const& lrmConfigurationData)
{
    logNoteOnComponent("LRM saves power group information from TC_LRM_CONFIGURATION_DATA_IND_MSG");
    for(unsigned int index=0; index<lrmConfigurationData.numOfDsps; index++)
    {
        SDspInfo const& currentDspInfo(lrmConfigurationData.dspInfo[index]);
        m_powerGroupDatabase[currentDspInfo.powerGroupId].numberOfK2sInPowerGroup++;
    }
}

void LRM::handleLrmConfigurationData(GenericMessage const& genericMessage)
{
    cout<<"handleLrmConfigurationData()"<<endl;    Environment & environment(Environment::getInstance());

    SpecificStaticMessage<MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG> message(convertGenericToSpecificStatic<MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG>(genericMessage));
    SLrmConfigurationDataInd& payload(message.getPayloadReference());
    logNoteOnPreviousMessage("TOAM sends configuration data with NBIC from HW_CONF");
    logNoteOnComponent("LRM will allocate MCD-CCD-d for NBIC LCGs (even with 2K2 configuration)"); //WBTS_CP_19858
    logNoteOnComponent("LRM will allocate according to MCD + CCD-d packet allocation rules"); // WBTS_CP_19861

    //send MODE_CHANGE?
    //check the node
    //How to guarantee that no nyquist mode change will happen?
    //Remake the RAN3374 flow chart

}

void LRM::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG:
        handleLrmConfigurationData(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<". Please create one!"<<endl;
        break;
    }
}

void LRM::handleTimerEvent(Timer const& timer)
{
    switch(timer.getType())
    {
    //case TimerType::Empty:
    //    cout<<"Handle Timer, Empty: "<<endl;
    //    break;
    default:
        cout<<"No handler for timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<". Please create one!"<<endl;
        break;
    }
}

void LRM::handleOtherEvent(OtherEvent const& otherEvent)
{
    switch(otherEvent.getType())
    {
    //case TimerType::Empty:
    //    cout<<"Handle OtherEvent, Empty: "<<endl;
    //    break;
    default:
        cout<<"No handler for otherEventType: "<<(int)otherEvent.getType()<<". Please create one!"<<endl;
        break;
    }
}

}
