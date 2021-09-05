#include "LRM.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Debug/AlbaDebug.hpp>
#include <FakeFramework/FakeFrameworkHelpers.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

DelayedLinkIndices::DliPoolData::DliPoolData()
{}

DelayedLinkIndices::DelayedLinkIndices()
{}

unsigned int DelayedLinkIndices::getAvailablePoolIdForRel4(unsigned int const minimumIndices) const
{
    unsigned int poolId(0);
    PoolIdVector poolIds(getAvailablePoolIds(minimumIndices));
    prioritizeDliPoolForRel4(poolIds);
    if(!poolIds.empty())
    {
        poolId = poolIds.front();
    }
    return poolId;
}

unsigned int DelayedLinkIndices::getNumberOfIndices(unsigned int const poolId) const
{
    unsigned int result(0);
    if(m_poolIdToNumberOfIndices.find(poolId) != m_poolIdToNumberOfIndices.cend())
    {
        result = m_poolIdToNumberOfIndices.at(poolId).numberOfIndices;
    }
    return result;
}

bool DelayedLinkIndices::isAllocated(unsigned int const poolId) const
{
    bool result(false);
    if(m_poolIdToNumberOfIndices.find(poolId) != m_poolIdToNumberOfIndices.cend())
    {
        result = m_poolIdToNumberOfIndices.at(poolId).isAllocated;
    }
    return result;
}

DelayedLinkIndices::PoolIdVector DelayedLinkIndices::getAvailablePoolIds(unsigned int const minimumIndices) const
{
    // WBTS_CP_21702
    PoolIdVector poolIds;
    for(PoolIdToNumberOfIndicesPair const& poolIdToNumberOfIndicesPair :  m_poolIdToNumberOfIndices)
    {
        DliPoolData const& dliPoolData(poolIdToNumberOfIndicesPair.second);
        //Unassigned to any other PIC in the given Core
        //Have available DLIs that is greater than or equal to the total amount of RX carriers from all cells in the given PIC pool. See [Note 3].
        if(dliPoolData.numberOfIndices>=minimumIndices && !dliPoolData.isAllocated)
        {
            poolIds.emplace_back(dliPoolData.poolId);
        }
    }
    return poolIds;
}

void DelayedLinkIndices::prioritizeDliPoolForRel4(PoolIdVector & dliPools) const
{
    // WBTS_CP_21702
    nth_element(dliPools.begin(), dliPools.begin(), dliPools.end(), [&](unsigned int const dliPoolId1, unsigned int const dliPoolId2)
    {
        bool result(false);
        unsigned int indicesForPoolId1(getNumberOfIndices(dliPoolId1));
        unsigned int indicesForPoolId2(getNumberOfIndices(dliPoolId2));

        if(indicesForPoolId1 == indicesForPoolId2)
        {
            result = dliPoolId1<dliPoolId2; //Lowest DLI pool ID.
        }
        else
        {
            result = indicesForPoolId1<indicesForPoolId2; //Has lowest number of DLIs.
        }
        return result;
    });
}

bool DelayedLinkIndices::hasConflictWithNextAvailablePool(PoolIdVector const& poolIds, unsigned int const minimumIndices) const
{
    bool result(false);
    unsigned int availablePoolId(getAvailablePoolIdForRel4(minimumIndices));
    for(unsigned int const poolId : poolIds)
    {
        bool hasSamePoolId(poolId == availablePoolId);
        bool oneAndFourConflict((poolId == 1 && availablePoolId==4) || (poolId == 4 && availablePoolId==1));
        bool twoAndThreeConflict(minimumIndices>8 && ((poolId == 2 && availablePoolId==3) || (poolId == 3 && availablePoolId==2))); //spec
        result = oneAndFourConflict || twoAndThreeConflict || hasSamePoolId;
        if(result)
        {
            break;
        }
    }
    return result;
}

void DelayedLinkIndices::setIndices(unsigned int const maximumIndices)
{
    m_poolIdToNumberOfIndices.clear();
    unsigned int numberOfFilledIndices = maximumIndices/m_numberOfIndices;
    unsigned int remainderIndices = maximumIndices%m_numberOfIndices;
    unsigned int poolId = 1;
    for(; poolId<numberOfFilledIndices+1; poolId++)
    {
        m_poolIdToNumberOfIndices[poolId].poolId = poolId;
        m_poolIdToNumberOfIndices[poolId].numberOfIndices = m_numberOfIndices;
        m_poolIdToNumberOfIndices[poolId].isAllocated = false;
    }
    if(remainderIndices>0)
    {
        m_poolIdToNumberOfIndices[poolId].poolId = poolId;
        m_poolIdToNumberOfIndices[poolId].numberOfIndices = remainderIndices;
        m_poolIdToNumberOfIndices[poolId].isAllocated = false;
    }
}

void DelayedLinkIndices::setPoolAsAllocated(unsigned int const poolId)
{
    m_poolIdToNumberOfIndices[poolId].isAllocated = true;
}

void DelayedLinkIndices::setPoolAsNotAllocated(unsigned int const poolId)
{
    m_poolIdToNumberOfIndices[poolId].isAllocated = false;
}

LRM::DspData::DspData()
    : mode(EDspMode_Original) // fake, only rel4 is needed here
    , isNbic(false)
{}

LRM::LcgData::LcgData()
    : neededNumberOfDlis(0)
{}

LRM::PowerGroupData::PowerGroupData()
    : numberOfK2sInPowerGroup(0)
{}

LRM::LRM(ComponentName const componentName)
    : Component(componentName)
    , m_masterTcomNid(FakeFrameworkHelpers::INVALID_DSP_ADDRESS)
{}

bool LRM::isRel4() const
{
    //This is FAKE! This should be based on WAM address indication.
    return true;
}

bool LRM::isTcomInThisK2(TAaSysComNid const dspAddress) const
{
    //This is FAKE!
    return getKeplerAddressWithoutCore(m_masterTcomNid)==getKeplerAddressWithoutCore(dspAddress);
}

TAaSysComNid LRM::getMasterTcomNid() const
{
    logNoteOnComponent("LRM fetches the NidAddress of TCOM from WAM ADDRESS Indication message sent previously.");
    return m_masterTcomNid;
}

TAaSysComNid LRM::getKeplerAddressWithoutCore(TAaSysComNid const dspAddress) const
{
    //This is FAKE! Use framework functions instead
    return dspAddress & 0xFFF0;
}

TAaSysComNid LRM::getFspAddressFromDspAddress(TAaSysComNid const dspAddress) const
{
    //This is FAKE! Use framework functions instead
    return dspAddress>>8;
}

TAaSysComNid LRM::getBoardFromFspAddress(TAaSysComNid const fspAddress) const
{
    //This is FAKE! Use framework functions instead
    return fspAddress & 0xF0;
}

TAaSysComNid LRM::getBoardFromSubrackAddress(TAaSysComSicad const subrackAddress) const
{
    //This is FAKE! Use framework functions instead
    return (subrackAddress>>24) & 0xF0;
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
    //This is FAKE!
    TNumberOfItems numberOfK2sInPowerGroup(0);
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
        if(dspData.dspInfo.localCellGroupId == lcgId && getFspAddressFromDspAddress(dspData.dspInfo.dspAddress) == fspAddress)
        {
            numberOfK2s++;
        }
    }
    return numberOfK2s;
}

DelayedLinkIndices::PoolIdVector LRM::getDliPoolIdsInFsp(TAaSysComNid const fspAddress) const
{
    //This is FAKE!
    DelayedLinkIndices::PoolIdVector poolIds;
    for(DspAddressToDspDataPair const & dspAddressToDspDataPair : m_dspDatabase)
    {
        DspData const& dspData(dspAddressToDspDataPair.second);
        if(getFspAddressFromDspAddress(dspData.dspInfo.dspAddress) == fspAddress && dspData.dliPoolId!=0)//spec?
        {
            poolIds.emplace_back(dspData.dliPoolId);
        }
    }
    return poolIds;
}

TNumberOfItems LRM::getNumberOfPicAndNbicPacketsInFsp(TAaSysComNid const fspAddress) const
{
    //This is FAKE!
    unsigned int numberOfK2PacketsWhichSatisfy(0);
    for(DspAddressToDspDataPair const & dspAddressToDspDataPair : m_dspDatabase)
    {
        DspData const& dspData(dspAddressToDspDataPair.second);
        if(getFspAddressFromDspAddress(dspData.dspInfo.dspAddress) == fspAddress && ((dspData.mode == EDspMode_Kepler_MCD_CCDD && dspData.isNbic) || dspData.mode == EDspMode_Kepler_DCD_PIC))//spec?
        {
            numberOfK2PacketsWhichSatisfy++;
        }
    }
    return numberOfK2PacketsWhichSatisfy;
}

TNumberOfItems LRM::getNumberOfMcdDcdAndMcdCcdPacketsInFsp(TAaSysComNid const fspAddress) const
{
    //This is FAKE!
    unsigned int numberOfK2PacketsWhichSatisfy(0);
    for(DspAddressToDspDataPair const & dspAddressToDspDataPair : m_dspDatabase)
    {
        DspData const& dspData(dspAddressToDspDataPair.second);
        if(getFspAddressFromDspAddress(dspData.dspInfo.dspAddress) == fspAddress && (dspData.mode == EDspMode_Kepler_MCD_DCD || dspData.mode == EDspMode_Kepler_MCD_CCDD))
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
        if(dspData.dspInfo.localCellGroupId != lcgId && getFspAddressFromDspAddress(dspData.dspInfo.dspAddress) == fspAddress && dspData.mode == EDspMode_Kepler_MCD_CCDD)
        {
            numberOfMcdCcds++;
        }
    }
    return numberOfMcdCcds;
}

LRM::AddressesVector LRM::getFspAddressesForLcgId(TLocalCellGroupId const lcgId) const
{
    AddressesVector result;
    AddressesSet fspAddresses;
    for(DspAddressToDspDataPair const & dspAddressToDspDataPair : m_dspDatabase)
    {
        DspData const& dspData(dspAddressToDspDataPair.second);
        if(dspData.dspInfo.localCellGroupId == lcgId)
        {
            fspAddresses.emplace(getFspAddressFromDspAddress(dspData.dspInfo.dspAddress));
        }
    }
    copy(fspAddresses.cbegin(), fspAddresses.cend(), back_inserter(result));
    return result; //RVO (Return value optimization)
}

LRM::AddressesVector LRM::getDspAddressesForLcgId(TLocalCellGroupId const lcgId) const
{
    AddressesVector dspAddresses;
    for(DspAddressToDspDataPair const & dspAddressToDspDataPair : m_dspDatabase)
    {
        DspData const& dspData(dspAddressToDspDataPair.second);
        if(dspData.dspInfo.localCellGroupId == lcgId)
        {
            dspAddresses.emplace_back(dspData.dspInfo.dspAddress);
        }
    }
    return dspAddresses; //RVO (Return value optimization)
}

LRM::AddressesVector LRM::getDspAddressesForFspAddressAndLcgId(AddressesVector const& fspAddresses, TLocalCellGroupId const lcgId) const
{
    AddressesVector dspAddresses;
    for(TAaSysComNid const fspAddress : fspAddresses) //quadratic time is a no no
    {
        for(DspAddressToDspDataPair const & dspAddressToDspDataPair : m_dspDatabase)
        {
            DspData const& dspData(dspAddressToDspDataPair.second);
            TAaSysComNid dspAddress(dspData.dspInfo.dspAddress);
            if(dspData.dspInfo.localCellGroupId == lcgId && getFspAddressFromDspAddress(dspAddress) == fspAddress)
            {
                dspAddresses.emplace_back(dspAddress);
            }
        }
    }
    return dspAddresses; //RVO (Return value optimization)
}

TAaSysComNid LRM::findLocationOfMcdCcdDWithNbicForLcgId(TLocalCellGroupId const lcgId) const
{
    TAaSysComNid nbicMcdCcdAddress(FakeFrameworkHelpers::INVALID_DSP_ADDRESS);
    AddressesVector fspAddresses(getFspAddressesForLcgId(lcgId));
    removeFspAddressInConflictWithDli(fspAddresses, lcgId);
    if(!fspAddresses.empty())
    {
        AddressesVector dspAddresses(getDspAddressesForFspAddressAndLcgId(fspAddresses, lcgId));
        removeDspAddressesBasedOnFilterForSelectionMcdCcdD(dspAddresses);
        prioritizeDspAddressesForSelectionMcdCcdD(dspAddresses, lcgId);
        if(!dspAddresses.empty())
        {
            nbicMcdCcdAddress = dspAddresses.front();
        }
    }
    return nbicMcdCcdAddress;
}

TAaSysComNid LRM::findLocationOfMcdCcdDForLcgId(TLocalCellGroupId const lcgId) const
{
    TAaSysComNid mcdCcdAddress(FakeFrameworkHelpers::INVALID_DSP_ADDRESS);
    AddressesVector dspAddresses(getDspAddressesForLcgId(lcgId));
    removeDspAddressesBasedOnFilterForSelectionMcdCcdD(dspAddresses);
    prioritizeDspAddressesForSelectionMcdCcdD(dspAddresses, lcgId);
    if(!dspAddresses.empty())
    {
        mcdCcdAddress = dspAddresses.front();
    }
    return mcdCcdAddress;
}

void LRM::removeFspAddressInConflictWithDli(AddressesVector & fspAddresses, TLocalCellGroupId const lcgId) const
{
    fspAddresses.erase(remove_if(fspAddresses.begin(), fspAddresses.end(), [&](TAaSysComNid const fspAddress)
    {
                           unsigned int numberOfPicAndNbicPacketsInFsp(getNumberOfPicAndNbicPacketsInFsp(fspAddress));
                           DelayedLinkIndices::PoolIdVector poolIdsInFsp(getDliPoolIdsInFsp(fspAddress));
                           return numberOfPicAndNbicPacketsInFsp>=2 || hasConflictWithNextAvailablePool(fspAddress, poolIdsInFsp, lcgId); //spec?
                       }), fspAddresses.end());
}

void LRM::removeDspAddressesBasedOnFilterForSelectionMcdCcdD(AddressesVector & dspAddresses) const
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

void LRM::prioritizeDspAddressesForSelectionMcdCcdD(AddressesVector & dspAddresses, TLocalCellGroupId const lcgId) const
{
    // WBTS_CP_19861
    nth_element(dspAddresses.begin(), dspAddresses.begin(), dspAddresses.end(), [&](TAaSysComNid const dspAddress1, TAaSysComNid const dspAddress2)
    {
        bool result(false);
        unsigned int numberOfMcdCcdPacketsInFspForDspAddress1(getNumberOfMcdCcdPacketsInFspForOtherLcgs(getFspAddressFromDspAddress(dspAddress1), lcgId)); //selection rule 2: Is located on baseband card with lowest number of MCD + CCD-d packets allocated for other LCGs.  See [Note 3].
        unsigned int numberOfMcdCcdPacketsInFspForDspAddress2(getNumberOfMcdCcdPacketsInFspForOtherLcgs(getFspAddressFromDspAddress(dspAddress2), lcgId));
        unsigned int numberOfK2InFspForDspAddress1(getNumberOfK2sInFspForLcg(getFspAddressFromDspAddress(dspAddress1), lcgId)); //selection rule 3: Is located on baseband card with largest amount of K2 assigned to LCG.
        unsigned int numberOfK2InFspForDspAddress2(getNumberOfK2sInFspForLcg(getFspAddressFromDspAddress(dspAddress2), lcgId));

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
        else
        {
            result = numberOfMcdCcdPacketsInFspForDspAddress1<numberOfMcdCcdPacketsInFspForDspAddress2;
        }
        return result;
    });
}

void LRM::processStartupForAllLcg()
{
    log("loop LRM performs startup for all LCGs.");
    for(LcgIdToLcgDataPair const& lcgIdToLcgDataPair : m_lcgDatabase)
    {
        LcgData const& lcgData(lcgIdToLcgDataPair.second);
        processStartupForOneLcg(lcgData.lcgInfo.lcgId);
    }
    log("end loop");
}

void LRM::processStartupForOneLcg(TLocalCellGroupId const lcgId)
{
    LcgData const& lcgData(m_lcgDatabase[lcgId]);
    log("alt if FSMr4 base from wam address indication");
    if(isRel4())
    {
        logNoteOnComponent("LRM performs allocation for REL4 for the LCG.");
        log("alt if nbic is commissioned for the LCG");
        if(lcgData.lcgInfo.isNbicEnabled==EBoolean_True)
        {
            allocateMcdCcdDWithNbic(lcgId);
        }
        else
        {
            TNumberOfItems numberOfK2s(getNumberOfK2sForLcg(lcgId));
            if(numberOfK2s>2)
            {
                allocateMcdCcdD(lcgId);
            }
            else
            {
                allocateCcdDcd(lcgId);
            }
        }
        log("end alt");
    }
    else
    {
        logNoteOnComponent("LRM performs legacy allocation for REL3.");
        if(lcgData.lcgInfo.isNbicEnabled==EBoolean_True)
        {
            logNoteOnComponent("LRM performs legacy NBIC allocation for REL3 in RAN3374.");
        }
    }
    log("end alt");
}

void LRM::allocateMcdDcd(TLocalCellGroupId const lcgId)
{
    logNoteOnComponent("LRM allocates MCD DCD.");
}

void LRM::allocateCcdDcd(TLocalCellGroupId const lcgId)
{
    logNoteOnComponent("LRM allocates CCD DCD.");
}

void LRM::allocateMcdCcdD(TLocalCellGroupId const lcgId)
{
    logNoteOnComponent("LRM allocates MCD CCD-d.");
    TAaSysComNid mcdCcdDAddress(findLocationOfMcdCcdDForLcgId(lcgId));
    if(mcdCcdDAddress != FakeFrameworkHelpers::INVALID_DSP_ADDRESS)
    {
        setDspModeInAddress(mcdCcdDAddress, EDspMode_Kepler_MCD_CCDD);
    }
}

void LRM::allocateMcdCcdDWithNbic(TLocalCellGroupId const lcgId)
{
    logNoteOnComponent("LRM allocates MCD CCD-d with NBIC");
    TAaSysComNid nbicMcdCcdDAddress(findLocationOfMcdCcdDWithNbicForLcgId(lcgId));
    if(nbicMcdCcdDAddress != FakeFrameworkHelpers::INVALID_DSP_ADDRESS)
    {
        unsigned int dliPoolId(getAvailableDliInAddress(getFspAddressFromDspAddress(nbicMcdCcdDAddress), lcgId)); //use save it
        setAsNbicMcdCcdDInAddress(nbicMcdCcdDAddress);
        setPoolIdInDspAddress(nbicMcdCcdDAddress, dliPoolId);
    }
    else
    {
        allocateMcdCcdD(lcgId);
    }
}

unsigned int LRM::getAvailableDliInAddress(TAaSysComNid const fspAddress, TLocalCellGroupId const lcgId) const
{
    unsigned int result(0);
    TAaSysComNid board(getBoardFromFspAddress(fspAddress));
    if(m_coreToDli.find(board) != m_coreToDli.cend())
    {
        result = m_coreToDli.at(board).getAvailablePoolIdForRel4(getNeededNumberOfDlis(lcgId));
    }
    return result;
}

bool LRM::hasConflictWithNextAvailablePool(TAaSysComNid const fspAddress, DelayedLinkIndices::PoolIdVector const& poolIds, TLocalCellGroupId const lcgId) const
{
    bool result(false);
    TAaSysComNid board(getBoardFromFspAddress(fspAddress));
    if(m_coreToDli.find(board) != m_coreToDli.cend())
    {
        result = m_coreToDli.at(board).hasConflictWithNextAvailablePool(poolIds, getNeededNumberOfDlis(lcgId));
    }
    return result;
}

unsigned int LRM::getNeededNumberOfDlis(TLocalCellGroupId const lcgId) const
{
    unsigned int result(0);
    if(m_lcgDatabase.find(lcgId) != m_lcgDatabase.cend())
    {
        result = m_lcgDatabase.at(lcgId).neededNumberOfDlis;
    }
    return result;
}

void LRM::setMasterTcomNid(TAaSysComNid const masterTcomNid)
{
    //This is FAKE! This should be set in wamaddress indication. I'm not gonna cover wam address indication.
    m_masterTcomNid = masterTcomNid;
}

void LRM::setDspModeInAddress(TAaSysComNid const dspAddress, EDspMode const mode)
{
    m_dspDatabase[dspAddress].mode = mode;
}

void LRM::setAsNbicMcdCcdDInAddress(TAaSysComNid const dspAddress)
{
    m_dspDatabase[dspAddress].mode = EDspMode_Kepler_MCD_CCDD;
    m_dspDatabase[dspAddress].isNbic = true;
}

void LRM::setPoolIdInDspAddress(TAaSysComNid const dspAddress, unsigned int const poolId)
{
    m_dspDatabase[dspAddress].dliPoolId = poolId;
}

void LRM::saveDspInformation(SLrmConfigurationDataInd const& lrmConfigurationData)
{
    logNoteOnComponent("LRM saves DSP information from TC_LRM_CONFIGURATION_DATA_IND_MSG");
    for(unsigned int index=0; index<lrmConfigurationData.numOfDsps; index++)
    {
        SDspInfo const& currentDspInfo(lrmConfigurationData.dspInfo[index]);
        m_dspDatabase[currentDspInfo.dspAddress].dspInfo = currentDspInfo;
        m_dspDatabase[currentDspInfo.dspAddress].mode = EDspMode_Kepler_DCD_DCD;
        m_dspDatabase[currentDspInfo.dspAddress].isNbic = false;
        m_dspDatabase[currentDspInfo.dspAddress].dliPoolId = 0;
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

void LRM::saveLcrInformationInLcg(SLrmConfigurationDataInd const& lrmConfigurationData)
{
    logNoteOnComponent("LRM saves number of RX information for each LCG from TC_LRM_CONFIGURATION_DATA_IND_MSG");

    for(auto it=m_lcgDatabase.begin(); it != m_lcgDatabase.end(); it++)
    {
        LcgData & lcgData(it->second);
        lcgData.neededNumberOfDlis=0;
    }
    for(unsigned int index=0; index<lrmConfigurationData.numOfLcrInfo; index++)
    {
        SLCRList const& currentLcrInfo(lrmConfigurationData.lcrInfo[index]);
        m_lcgDatabase[currentLcrInfo.lcgId].neededNumberOfDlis += currentLcrInfo.numOfRx;
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

void LRM::saveDliInfo(SLrmConfigurationDataInd const& lrmConfigurationData)
{
    logNoteOnComponent("LRM saves DLI information from TC_LRM_CONFIGURATION_DATA_IND_MSG");
    for(unsigned int index=0; index<lrmConfigurationData.numberOfDelayedLinksInfo; index++)
    {
        SDelayedLinksInfo const& currentLinksInfo(lrmConfigurationData.delayedLinksInfo[index]);
        m_coreToDli[getBoardFromSubrackAddress(currentLinksInfo.subrackAddress)].setIndices(currentLinksInfo.numberOfDelayedLinkIndices);
    }
}

void LRM::saveDataFromLrmConfigurationDataInd(SLrmConfigurationDataInd const& lrmConfigurationData)
{
    saveDspInformation(lrmConfigurationData);
    saveLcgInformation(lrmConfigurationData);
    saveLcrInformationInLcg(lrmConfigurationData);
    log("alt if FSMr4 base from wam address indication");
    if(isRel4())
    {
        savePowerGroupInformation(lrmConfigurationData);
        saveDliInfo(lrmConfigurationData);
    }
    log("end alt");
}


void LRM::handleLrmConfigurationData(GenericMessage const& genericMessage)
{
    Environment & environment(Environment::getInstance());

    SpecificStaticMessage<MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG> message(convertGenericToSpecificStatic<MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG>(genericMessage));
    SLrmConfigurationDataInd payload(message.getStaticPayloadReference());

    logNoteOnPreviousMessage("TOAM sends configuration data with NBIC from HW_CONF");
    saveDataFromLrmConfigurationDataInd(payload);
    processStartupForAllLcg();

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
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<" in component: "<<getComponentNameInString()<<endl;
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
