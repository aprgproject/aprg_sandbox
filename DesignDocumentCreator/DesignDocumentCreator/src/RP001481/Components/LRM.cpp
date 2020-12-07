#include "LRM.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

LRM::DspData::DspData()
    : mode(EDspMode_Kepler_DCD_DCD) // fake, only rel4 is needed here
{}

LRM::LcgData::LcgData()
{}

LRM::PowerGroupData::PowerGroupData()
    : numberOfK2sInPowerGroup(0)
{}

LRM::FspData::FspData()
    : numberOfK2sInFsp(0)
    , numberOfMcdCcdPacketsInFsp(0)
{}

LRM::LRM(ComponentName const componentName)
    : Component(componentName)
{}

bool LRM::isTcomInThisK2(TAaSysComNid const dspAddress) const
{
    //This is FAKE!
    return getFspAddress(m_masterTcomNid)==getFspAddress(dspAddress);
}

TAaSysComNid LRM::getMasterTcomNid() const
{
    logNoteOnComponent("LRM fetches the NidAddress of TCOM from WAM ADDRESS Indication message sent previously.");
    return m_masterTcomNid;
}

TNumberOfItems LRM::getNumberOfMcdCcdPacketsInFsp(TAaSysComNid const fspNid) const
{
    //This is FAKE! I'm sure LRM has a way to get current number McdCcdPackets in FSP.
    TNumberOfItems numberOfMcdCcdPacketsInFsp(0);
    if(m_fspDatabase.find(fspNid) != m_fspDatabase.cend())
    {
        numberOfMcdCcdPacketsInFsp = m_fspDatabase.at(fspNid).numberOfMcdCcdPacketsInFsp;
    }
    return numberOfMcdCcdPacketsInFsp;
}

TAaSysComNid LRM::getFspAddress(TAaSysComNid const dspAddress) const
{
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

TNumberOfItems LRM::getNumberOfK2sInPowerGroup(TPowerGroupId const powerGroupId) const
{
    //This is FAKE!
    TNumberOfItems numberOfK2sInPowerGroup(0);
    if(m_powerGroupDatabase.find(powerGroupId) != m_powerGroupDatabase.cend())
    {
        numberOfK2sInPowerGroup = m_powerGroupDatabase.at(powerGroupId).numberOfK2sInPowerGroup;
    }
    return numberOfK2sInPowerGroup;
}

TNumberOfItems LRM::getNumberOfK2sInFsp(TAaSysComNid const fspAddress) const
{
    //This is FAKE!
    TNumberOfItems numberOfK2sInFsp(0);
    if(m_fspDatabase.find(fspAddress) != m_fspDatabase.cend())
    {
        numberOfK2sInFsp = m_fspDatabase.at(fspAddress).numberOfK2sInFsp;
    }
    return numberOfK2sInFsp;
}

LRM::DspAddressesVector LRM::getDspAddressesForLcgId(TLocalCellGroupId const lcgId) const
{
    DspAddressesVector dspAddresses;
    for(DspAddressToDspDataPair dspAddressToDspDataPair : m_dspDatabase)
    {
        DspData const& dspData(dspAddressToDspDataPair.second);
        if(dspData.dspInfo.localCellGroupId == lcgId)
        {
            dspAddresses.emplace_back(dspData.dspInfo.dspAddress);
        }
    }
    return dspAddresses; //RVO (Return value optimization)
}

TAaSysComNid LRM::findLocationOfMcdCcdD(TLocalCellGroupId const lcgId) const
{
    TAaSysComNid mcdCcdAddress(INVALID_DSP_ADDRESS);
    DspAddressesVector dspAddresses(getDspAddressesForLcgId(lcgId));
    removeDspAddressesBasedOnFilterForSelectionMcdCcdD(dspAddresses);
    prioritizeDspAddressesForSelectionMcdCcdD(dspAddresses);
    if(dspAddresses.empty())
    {
        mcdCcdAddress = dspAddresses.front();
    }
    return mcdCcdAddress;
}

void LRM::removeDspAddressesBasedOnFilterForSelectionMcdCcdD(DspAddressesVector & dspAddresses) const
{
    // WBTS_CP_19861
    dspAddresses.erase(remove_if(dspAddresses.begin(), dspAddresses.end(), [&](TAaSysComNid const dspAddress)
    {
        unsigned int numberOfPowerGroupForDspAddress(getNumberOfK2sInPowerGroup(getPowerGroupId(dspAddress)));
        bool isIncorrectNumberOfK2InPowerGroup(numberOfPowerGroupForDspAddress!=2); //selection rule 1.  Belongs to Power Group where its two devices are allocated for the LCG.  See [Note 2].
        // isTcomInThisK2() WBTS_CP_19862: Only devices where TCOM is not allocated in its ARM shall be considered here.
        return isTcomInThisK2(dspAddress) || isIncorrectNumberOfK2InPowerGroup;
    }));
}

void LRM::prioritizeDspAddressesForSelectionMcdCcdD(DspAddressesVector & dspAddresses) const
{
    // WBTS_CP_19861
    nth_element(dspAddresses.begin(), dspAddresses.begin(), dspAddresses.end(), [&](TAaSysComNid const dspAddress1, TAaSysComNid const dspAddress2)
    {
        bool result(false);
        unsigned int numberOfMcdCcdPacketsInFspForDspAddress1(getNumberOfMcdCcdPacketsInFsp(getFspAddress(dspAddress1))); //selection rule 2: Is located on baseband card with lowest number of MCD + CCD-d packets allocated for other LCGs.  See [Note 3].
        unsigned int numberOfMcdCcdPacketsInFspForDspAddress2(getNumberOfMcdCcdPacketsInFsp(getFspAddress(dspAddress2)));
        unsigned int numberOfK2InFspForDspAddress1(getNumberOfK2sInFsp(getFspAddress(dspAddress1))); //selection rule 3: Is located on baseband card with largest amount of K2 assigned to LCG.
        unsigned int numberOfK2InFspForDspAddress2(getNumberOfK2sInFsp(getFspAddress(dspAddress2)));

        if(numberOfMcdCcdPacketsInFspForDspAddress1 == numberOfMcdCcdPacketsInFspForDspAddress2)
        {
            if(numberOfK2InFspForDspAddress1 == numberOfK2InFspForDspAddress2)
            {
                result = dspAddress1<dspAddress2;
            }
            else
            {
                result = numberOfK2InFspForDspAddress1<numberOfK2InFspForDspAddress2;
            }
        }
        else
        {
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
        LcgData lcgData(lcgIdToLcgDataPair.second);
        processStartupForOneLcg(lcgData.lcgInfo.lcgId);
    }
}

void LRM::processStartupForOneLcg(TLocalCellGroupId const lcgId)
{
    TAaSysComNid mcdCcdDAddress(findLocationOfMcdCcdD(lcgId));
    if(mcdCcdDAddress != INVALID_DSP_ADDRESS)
    {
        allocateMcdCcdD(mcdCcdDAddress);
    }
}

void LRM::allocateMcdCcdD(TAaSysComNid const mcdCcdDAddress)
{
    logNoteOnComponent("LRM allocates MCD CCD-D");
}

void LRM::setMasterTcomNid(TAaSysComNid const masterTcomNid)
{
    //This is FAKE! This should be set in wamaddress indication. I'm not gonna cover wam address indication.
    m_masterTcomNid = masterTcomNid;
}

void LRM::saveDspInformation(SLrmConfigurationDataInd const& lrmConfigurationData)
{
    logNoteOnComponent("LRM saves DSP information from TC_LRM_CONFIGURATION_DATA_IND_MSG");
    for(unsigned int index=0; index<lrmConfigurationData.numOfDsps; index++)
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

void LRM::saveFspInformationFromDspInformation(SLrmConfigurationDataInd const& lrmConfigurationData)
{
    logNoteOnComponent("LRM saves power group information from TC_LRM_CONFIGURATION_DATA_IND_MSG");
    for(unsigned int index=0; index<lrmConfigurationData.numOfDsps; index++)
    {
        SDspInfo const& currentDspInfo(lrmConfigurationData.dspInfo[index]);
        m_fspDatabase[getFspAddress(currentDspInfo.dspAddress)].numberOfK2sInFsp++;
    }
}

void LRM::handleLrmConfigurationData(GenericMessage const& genericMessage)
{
    cout<<"handleLrmConfigurationData()"<<endl;
    Environment & environment(Environment::getInstance());

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
