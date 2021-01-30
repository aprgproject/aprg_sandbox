#include "Lrm.hpp"

#include <algorithm>
#include <cassert>

#include <Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

SelectionDspResult::SelectionDspResult()
    : isSelectionSuccessful(false)
    , isNbicAllocated(false)
    , address(0)
    , dliPool(0)
{}

SelectionDspResultForCcdAndMcd::SelectionDspResultForCcdAndMcd()
    : isSelectionSuccessful(false)
    , isNbicAllocated(false)
    , ccdAddress(0)
    , mcdAddress(0)
    , dliPool(0)
{}

Lrm::Lrm(HardwareConfiguration& hardwareConfiguration)
    : m_lcgToValidPicPools()
    , m_hardwareConfigurationReference(hardwareConfiguration)
    , m_addressToDspMap(m_hardwareConfigurationReference.getAddressToDspMapReference())
    , m_addressToFspMap(m_hardwareConfigurationReference.getAddressToFspMapReference())
{}

void Lrm::setHibernationCommissioned(bool const isHibernationCommissioned)
{
    m_isHibernationCommissioned = isHibernationCommissioned;
}

void Lrm::setNumberOfPicPoolsPerLcg(unsigned int const lcgId, unsigned int const numberOfPicPools)
{
    m_lcgToValidPicPools[lcgId] = numberOfPicPools;
}

void Lrm::clearLcgPicPools(unsigned int const lcgId)
{
    m_lcgToValidPicPools.erase(lcgId);
}

SelectionDspResult Lrm::allocateMcdForLcgIdAccordingToMark(unsigned int const lcgId)
{
    SelectionDspResult result;
    SelectionDspResult fspSelectionResult = selectFspForEmptyDspForMcd(lcgId);    if(fspSelectionResult.isSelectionSuccessful)
    {
        SelectionDspResult dspSelectionResult = selectEmptyDspPriotizingNyquistTypeAndAddressInFsp(lcgId, fspSelectionResult.address);
        if(dspSelectionResult.isSelectionSuccessful)        {
            result.isSelectionSuccessful=true;
            result.address = dspSelectionResult.address;
            changeModeAndUpdateDspDetails(result, DspMode::NyquistMixedChannelDevice);
        }
    }
    if(!result.isSelectionSuccessful)
    {
        SelectionDspResult dspSelectionResult = selectNonEmptyDspToClearForMcd(lcgId);
        if(dspSelectionResult.isSelectionSuccessful)
        {
            result.isSelectionSuccessful=true;
            result.address = dspSelectionResult.address;
            changeModeAndUpdateDspDetails(result, DspMode::NyquistMixedChannelDevice);
        }
    }
    return result;
}

SelectionDspResultForCcdAndMcd Lrm::allocateCcdMcdForLcgIdAccordingToMark(unsigned int const lcgId)
{
    SelectionDspResultForCcdAndMcd ccdMcdAddress;
    FspAddresses selectedFspAddresses = selectFspsForCcdMcd(lcgId);    unsigned int ccdFspAddress(0), mcdFspAddress(0);
    if(selectedFspAddresses.size()==1)
    {
        ccdFspAddress = selectedFspAddresses[0];        mcdFspAddress = selectedFspAddresses[0];
    }
    else if(selectedFspAddresses.size()==2)
    {
        ccdFspAddress = selectedFspAddresses[0];
        mcdFspAddress = selectedFspAddresses[1];
    }
    SelectionDspResult ccdSelectionResult = selectEmptyDspPriotizingNyquistTypeAndAddressInFsp(lcgId, ccdFspAddress);
    if(ccdSelectionResult.isSelectionSuccessful)
    {
        ccdMcdAddress.ccdAddress = ccdSelectionResult.address;
        changeModeForCcdAndUpdateDspDetails(ccdMcdAddress);
        SelectionDspResult mcdSelectionResult = selectEmptyDspPriotizingNyquistTypeAndAddressInFsp(lcgId, mcdFspAddress);
        if(mcdSelectionResult.isSelectionSuccessful)
        {
            ccdMcdAddress.isSelectionSuccessful = true;
            ccdMcdAddress.mcdAddress = mcdSelectionResult.address;
            changeModeForMcdAndUpdateDspDetails(ccdMcdAddress);
        }
    }
    return ccdMcdAddress;
}

SelectionDspResult Lrm::allocateNbicMcdForLcgIdAccordingToMark(unsigned int const lcgId)
{
    SelectionDspResult result;
    SelectionDspResult fspSelectionResult = selectFspForEmptyDspForNbicMcd(lcgId);    if(fspSelectionResult.isSelectionSuccessful)
    {
        SelectionDspResult dspSelectionResult = selectEmptyDspPriotizingNyquistTypeAndAddressInFsp(lcgId, fspSelectionResult.address);
        if(dspSelectionResult.isSelectionSuccessful)        {
            result.dliPool = getFreeDliToAllocateForDsp(dspSelectionResult.address);
            if(result.dliPool!=0)
            {
                result.isSelectionSuccessful=true;
                result.address = dspSelectionResult.address;
                result.isNbicAllocated = true;
                changeModeAndUpdateDspDetails(result, DspMode::NyquistMixedChannelDevice);
            }
        }
    }
    if(!result.isSelectionSuccessful)
    {
        SelectionDspResult dspSelectionResult = selectNonEmptyDspToClearForNbicMcd(lcgId);
        if(dspSelectionResult.isSelectionSuccessful)
        {
            result.dliPool = getFreeDliToAllocateForDsp(dspSelectionResult.address);
            if(result.dliPool!=0)
            {
                result.isSelectionSuccessful=true;
                result.address = dspSelectionResult.address;
                result.isNbicAllocated = true;
                changeModeAndUpdateDspDetails(result, DspMode::NyquistMixedChannelDevice);
            }
        }
    }
    return result;
}

SelectionDspResultForCcdAndMcd Lrm::allocateCcdNbicMcdForLcgIdAccordingToMark(unsigned int const lcgId)
{
    SelectionDspResultForCcdAndMcd ccdMcdAddress;
    FspAddresses selectedFspAddresses = selectFspsForCcdNbicMcd(lcgId);    unsigned int ccdFspAddress(0), mcdFspAddress(0);
    if(selectedFspAddresses.size()==1)
    {
        ccdFspAddress = selectedFspAddresses[0];        mcdFspAddress = selectedFspAddresses[0];
    }
    else if(selectedFspAddresses.size()==2)
    {
        ccdFspAddress = selectedFspAddresses[0];
        mcdFspAddress = selectedFspAddresses[1];
    }
    SelectionDspResult ccdSelectionResult = selectEmptyDspPriotizingNyquistTypeAndAddressInFsp(lcgId, ccdFspAddress);
    if(ccdSelectionResult.isSelectionSuccessful)
    {
        ccdMcdAddress.ccdAddress = ccdSelectionResult.address;
        changeModeForCcdAndUpdateDspDetails(ccdMcdAddress);
        SelectionDspResult mcdSelectionResult = selectEmptyDspPriotizingNyquistTypeAndAddressInFsp(lcgId, mcdFspAddress);
        if(mcdSelectionResult.isSelectionSuccessful)
        {
            ccdMcdAddress.dliPool = getFreeDliToAllocateForDsp(mcdSelectionResult.address);
            if(ccdMcdAddress.dliPool!=0)
            {
                ccdMcdAddress.isSelectionSuccessful=true;
                ccdMcdAddress.mcdAddress = mcdSelectionResult.address;
                ccdMcdAddress.isNbicAllocated = true;
                changeModeForMcdAndUpdateDspDetails(ccdMcdAddress);
            }
        }
    }
    return ccdMcdAddress;
}

SelectionDspResult Lrm::allocatePicForLcgIdAccordingToMark(unsigned int const lcgId)
{
    SelectionDspResult result;
    SelectionDspResult fspSelectionResult = selectFspForPic(lcgId);    if(fspSelectionResult.isSelectionSuccessful)
    {
        SelectionDspResult dspSelectionResult = selectTnPriotizingLessUsersAndHsupaCfsInFsp(lcgId, fspSelectionResult.address);
        if(dspSelectionResult.isSelectionSuccessful)        {
            result.dliPool = getFreeDliToAllocateForDsp(dspSelectionResult.address);
            if(result.dliPool!=0)
            {
                result.isSelectionSuccessful=true;
                result.address = dspSelectionResult.address;
                changeModeAndUpdateDspDetails(result, DspMode::NyquistPicDevice);
            }
        }
    }
    return result;
}

SelectionDspResult Lrm::selectFspForEmptyDspForMcd(unsigned int const lcgId) const
{
    SelectionDspResult result;
    FspAddresses fspAddresses;
    copyFspWithAtLeastThisNumberOfEmptyNAndTn(fspAddresses, 1, lcgId);
    sortFspBasedPriorityForMcdSelection(fspAddresses, lcgId);
    removeNotNeededFspsForMcd(fspAddresses, lcgId);
    if(!fspAddresses.empty())
    {
        setSelectionDspResult(result, fspAddresses.front());
    }
    return result;
}

void Lrm::sortFspBasedPriorityForMcdSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    sortFspAddressesBasedOnCondition(fspAddresses, [&](Fsp const& fsp1, Fsp const& fsp2)
    {
        unsigned int priorityForMasterTcomFsp1(fsp1.isMasterTcom() ? 2 : 1);
        unsigned int priorityForMasterTcomFsp2(fsp2.isMasterTcom() ? 2 : 1);
        unsigned int numberOfNonDcdsForFsp1(getNumberOfNonDcdsOfFsp(fsp1.getAddress()));
        unsigned int numberOfNonDcdsForFsp2(getNumberOfNonDcdsOfFsp(fsp2.getAddress()));
        unsigned int priorityForNAndTnCountFsp1(getPriorityBasedOnNAndTnCountForFspMcdSelection(fsp1, lcgId));
        unsigned int priorityForNAndTnCountFsp2(getPriorityBasedOnNAndTnCountForFspMcdSelection(fsp2, lcgId));
        bool result(false);
        if(priorityForMasterTcomFsp1!=priorityForMasterTcomFsp2)
        {
            result = priorityForMasterTcomFsp1>priorityForMasterTcomFsp2;
        }
        else if(numberOfNonDcdsForFsp1!=numberOfNonDcdsForFsp2)
        {
            result =  m_isHibernationCommissioned
                    ? numberOfNonDcdsForFsp1>numberOfNonDcdsForFsp2
                    : numberOfNonDcdsForFsp1<numberOfNonDcdsForFsp2;
        }
        else if(priorityForNAndTnCountFsp1!=priorityForNAndTnCountFsp2)
        {
            result =  priorityForNAndTnCountFsp1>priorityForNAndTnCountFsp2;
        }
        else
        {
            result =  fsp1.getAddress()<fsp2.getAddress();
        }
        return result;
    });
}

unsigned int Lrm::getPriorityBasedOnNAndTnCountForFspMcdSelection(Fsp const& fsp, unsigned int const lcgId) const
{
    unsigned int numberOfFreeDliPoolsForFsp(getNumberOfFreeDliPoolsOfFsp(fsp.getAddress()));
    NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNAndTnOfFspAndLcg(fsp.getAddress(), lcgId);
    unsigned int priority=0;
    if(emptyNAndTnCount.numberOfNyquists>=1)
    {
        priority = 4;
    }
    else if(emptyNAndTnCount.numberOfTurboNyquists>=1)
    {
        if(numberOfFreeDliPoolsForFsp==0)
        {
            priority = 3;
        }
        if(numberOfFreeDliPoolsForFsp==2)
        {
            priority = 2;
        }
        else if(numberOfFreeDliPoolsForFsp==1)
        {
            priority = 1;
        }
    }
    return priority;
}

SelectionDspResult Lrm::selectNonEmptyDspToClearForMcd(unsigned int const lcgId) const
{
    SelectionDspResult result;
    DspAddresses dspAddresses;
    copyDspAddressesThatSatisfiesThisCondition(dspAddresses, [&](Dsp const& currentDsp)
    {
        return currentDsp.getLcgId()==lcgId
                && (currentDsp.getMode()==DspMode::NyquistDedicatedChannelDevice || currentDsp.getMode()==DspMode::NyquistPicDevice)
                && !currentDsp.hasEmergencyCalls()
                && currentDsp.getNumberOfHsRachCfs()==0;
    });
    sortDspAddressesBasedOnCondition(dspAddresses, [&](Dsp const& dsp1, Dsp const& dsp2)
    {
        unsigned int priorityBasedOnModeForDsp1 = (dsp1.getMode()==DspMode::NyquistDedicatedChannelDevice) ? 2 : 1;
        unsigned int priorityBasedOnModeForDsp2 = (dsp2.getMode()==DspMode::NyquistDedicatedChannelDevice) ? 2 : 1;
        unsigned int priorityBasedOnHsupaCfsExistenceForDsp1 = (dsp1.getNumberOfHsupaCfs()==0) ? 2 : 1;
        unsigned int priorityBasedOnHsupaCfsExistenceForDsp2 = (dsp2.getNumberOfHsupaCfs()==0) ? 2 : 1;
        unsigned int numberOfNonDcdsOnFspOfDsp1(getNumberOfNonDcdsOfFsp(dsp1.getFspAddress()));
        unsigned int numberOfNonDcdsOnFspOfDsp2(getNumberOfNonDcdsOfFsp(dsp2.getFspAddress()));
        unsigned int priorityOfNumberOfDchUsersForDsp1 = (dsp1.getNumberOfHsupaCfs()==0) ? dsp1.getNumberOfDchUsers() : 0;
        unsigned int priorityOfNumberOfDchUsersForDsp2 = (dsp2.getNumberOfHsupaCfs()==0) ? dsp2.getNumberOfDchUsers() : 0;
        unsigned int priorityOrderCountForHsupaCfsForDsp1 = dsp1.getOrderCountOfCfAllocation();
        unsigned int priorityOrderCountForHsupaCfsForDsp2 = dsp2.getOrderCountOfCfAllocation();
        unsigned int numberOfPrereservedHsupaCfsForDsp1 = dsp1.getNumberOfPreservedHsupaCfs();
        unsigned int numberOfPrereservedHsupaCfsForDsp2 = dsp2.getNumberOfPreservedHsupaCfs();
        bool result(false);
        if(priorityBasedOnModeForDsp1!=priorityBasedOnModeForDsp2)
        {
            result = priorityBasedOnModeForDsp1>priorityBasedOnModeForDsp2;
        }
        else if(priorityBasedOnHsupaCfsExistenceForDsp1!=priorityBasedOnHsupaCfsExistenceForDsp2)
        {
            result = priorityBasedOnHsupaCfsExistenceForDsp1>priorityBasedOnHsupaCfsExistenceForDsp2;
        }
        else if(m_isHibernationCommissioned && numberOfNonDcdsOnFspOfDsp1!=numberOfNonDcdsOnFspOfDsp2)
        {
            result = numberOfNonDcdsOnFspOfDsp1<numberOfNonDcdsOnFspOfDsp2;
        }
        else if(priorityOfNumberOfDchUsersForDsp1!=priorityOfNumberOfDchUsersForDsp2)
        {
            result = priorityOfNumberOfDchUsersForDsp1<priorityOfNumberOfDchUsersForDsp2;
        }
        else if(priorityOrderCountForHsupaCfsForDsp1!=priorityOrderCountForHsupaCfsForDsp2)
        {
            result = priorityOrderCountForHsupaCfsForDsp1>priorityOrderCountForHsupaCfsForDsp2;
        }
        else if(numberOfPrereservedHsupaCfsForDsp1!=numberOfPrereservedHsupaCfsForDsp2)
        {
            result = numberOfPrereservedHsupaCfsForDsp1<numberOfPrereservedHsupaCfsForDsp1;
        }
        else
        {
            result = dsp1.getAddress()<dsp2.getAddress();
        }
        return result;
    });
    if(!dspAddresses.empty())
    {
        setSelectionDspResult(result, dspAddresses.front());
    }
    return result;
}

void Lrm::removeNotNeededFspsForMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    unsigned int numberOfDspToAllocate=1;
    UniqueFspAddresses neededUniqueFspAddresses;
    saveNeededFspsForCcdOrMcdBasedOnNOrTn(neededUniqueFspAddresses, numberOfDspToAllocate, fspAddresses, lcgId);
    fspAddresses.clear();
    copy(neededUniqueFspAddresses.cbegin(), neededUniqueFspAddresses.cend(), back_inserter(fspAddresses));
    sortFspBasedPriorityForMcdSelection(fspAddresses, lcgId);}

FspAddresses Lrm::selectFspsForCcdMcd(unsigned int const lcgId) const
{    FspAddresses fspAddresses;
    copyFspWithAtLeastThisNumberOfEmptyNAndTn(fspAddresses, 2, lcgId);
    sortFspBasedPriorityForCcdMcdSelection(fspAddresses, lcgId);
    removeNotNeededFspsForCcdMcd(fspAddresses, lcgId);
    return fspAddresses;
}

void Lrm::sortFspBasedPriorityForCcdMcdSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    sortFspAddressesBasedOnCondition(fspAddresses, [&](Fsp const& fsp1, Fsp const& fsp2)
    {
        unsigned int priorityForMasterTcomFsp1(fsp1.isMasterTcom() ? 2 : 1);
        unsigned int priorityForMasterTcomFsp2(fsp2.isMasterTcom() ? 2 : 1);
        unsigned int numberOfNonDcdsForFsp1(getNumberOfNonDcdsOfFsp(fsp1.getAddress()));
        unsigned int numberOfNonDcdsForFsp2(getNumberOfNonDcdsOfFsp(fsp2.getAddress()));
        unsigned int priorityForNAndTnCountFsp1(getPriorityBasedOnNAndTnCountForFspCcdMcdSelection(fsp1, lcgId));
        unsigned int priorityForNAndTnCountFsp2(getPriorityBasedOnNAndTnCountForFspCcdMcdSelection(fsp2, lcgId));
        bool result(false);
        if(priorityForMasterTcomFsp1!=priorityForMasterTcomFsp2)
        {
            result = priorityForMasterTcomFsp1>priorityForMasterTcomFsp2;
        }
        else if(numberOfNonDcdsForFsp1!=numberOfNonDcdsForFsp2)
        {
            result =  m_isHibernationCommissioned
                    ? numberOfNonDcdsForFsp1>numberOfNonDcdsForFsp2
                    : numberOfNonDcdsForFsp1<numberOfNonDcdsForFsp2;
        }
        else if(priorityForNAndTnCountFsp1!=priorityForNAndTnCountFsp2)
        {
            result =  priorityForNAndTnCountFsp1>priorityForNAndTnCountFsp2;
        }
        else
        {
            result =  fsp1.getAddress()<fsp2.getAddress();
        }
        return result;
    });
}

unsigned int Lrm::getPriorityBasedOnNAndTnCountForFspCcdMcdSelection(Fsp const& fsp, unsigned int const lcgId) const
{
    unsigned int numberOfFreeDliPoolsForFsp(getNumberOfFreeDliPoolsOfFsp(fsp.getAddress()));
    NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNAndTnOfFspAndLcg(fsp.getAddress(), lcgId);
    unsigned int priority=0;
    if(emptyNAndTnCount.numberOfNyquists>=2)
    {
        priority = 8;
    }
    else if(emptyNAndTnCount.numberOfNyquists>=1)
    {
        priority = 7;
    }
    else if(emptyNAndTnCount.numberOfTurboNyquists>=2)
    {
        if(numberOfFreeDliPoolsForFsp==0)
        {
            priority = 6;
        }
        if(numberOfFreeDliPoolsForFsp==2)
        {
            priority = 4;
        }
        else if(numberOfFreeDliPoolsForFsp==1)
        {
            priority = 2;
        }
    }
    else if(emptyNAndTnCount.numberOfTurboNyquists>=1)
    {
        if(numberOfFreeDliPoolsForFsp==0)
        {
            priority = 5;
        }
        else if(numberOfFreeDliPoolsForFsp==2)
        {
            priority = 3;
        }
        else if(numberOfFreeDliPoolsForFsp==1)
        {
            priority = 1;
        }
    }
    return priority;
}

void Lrm::removeNotNeededFspsForCcdMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    unsigned int numberOfDspToAllocate=2;
    UniqueFspAddresses neededUniqueFspAddresses;
    saveNeededFspsForCcdOrMcdBasedOnNOrTn(neededUniqueFspAddresses, numberOfDspToAllocate, fspAddresses, lcgId);
    fspAddresses.clear();
    copy(neededUniqueFspAddresses.cbegin(), neededUniqueFspAddresses.cend(), back_inserter(fspAddresses));
    sortFspBasedPriorityForCcdMcdSelection(fspAddresses, lcgId);
}

SelectionDspResult Lrm::selectFspForEmptyDspForNbicMcd(unsigned int const lcgId) const
{
    SelectionDspResult result;
    FspAddresses fspAddresses;
    copyFspWithAtLeastThisNumberOfEmptyNAndTnWithDliRestrictions(fspAddresses, 1, lcgId);
    sortFspBasedPriorityForMcdSelection(fspAddresses, lcgId);
    if(!fspAddresses.empty())
    {
        setSelectionDspResult(result, fspAddresses.front());
    }
    return result;
}

SelectionDspResult Lrm::selectNonEmptyDspToClearForNbicMcd(unsigned int const lcgId) const
{
    SelectionDspResult result;
    DspAddresses dspAddresses;
    copyDspAddressesThatSatisfiesThisCondition(dspAddresses, [&](Dsp const& currentDsp)
    {
        return currentDsp.getLcgId()==lcgId
                && currentDsp.getMode()==DspMode::NyquistDedicatedChannelDevice
                && !currentDsp.hasEmergencyCalls()
                && currentDsp.getNumberOfHsRachCfs()==0;
    });
    sortDspAddressesBasedOnCondition(dspAddresses, [&](Dsp const& dsp1, Dsp const& dsp2)
    {
        unsigned int priorityBasedOnHsupaCfsExistenceForDsp1 = (dsp1.getNumberOfHsupaCfs()==0) ? 2 : 1;
        unsigned int priorityBasedOnHsupaCfsExistenceForDsp2 = (dsp2.getNumberOfHsupaCfs()==0) ? 2 : 1;
        unsigned int numberOfNonDcdsOnFspOfDsp1(getNumberOfNonDcdsOfFsp(dsp1.getFspAddress()));
        unsigned int numberOfNonDcdsOnFspOfDsp2(getNumberOfNonDcdsOfFsp(dsp2.getFspAddress()));
        unsigned int priorityOfNumberOfDchUsersForDsp1 = (dsp1.getNumberOfHsupaCfs()==0) ? dsp1.getNumberOfDchUsers() : 0;
        unsigned int priorityOfNumberOfDchUsersForDsp2 = (dsp2.getNumberOfHsupaCfs()==0) ? dsp2.getNumberOfDchUsers() : 0;
        unsigned int priorityOrderCountForHsupaCfsForDsp1 = dsp1.getOrderCountOfCfAllocation();
        unsigned int priorityOrderCountForHsupaCfsForDsp2 = dsp2.getOrderCountOfCfAllocation();
        unsigned int numberOfPrereservedHsupaCfsForDsp1 = dsp1.getNumberOfPreservedHsupaCfs();
        unsigned int numberOfPrereservedHsupaCfsForDsp2 = dsp2.getNumberOfPreservedHsupaCfs();
        bool result(false);
        if(priorityBasedOnHsupaCfsExistenceForDsp1!=priorityBasedOnHsupaCfsExistenceForDsp2)
        {
            result = priorityBasedOnHsupaCfsExistenceForDsp1>priorityBasedOnHsupaCfsExistenceForDsp2;
        }
        else if(m_isHibernationCommissioned && numberOfNonDcdsOnFspOfDsp1!=numberOfNonDcdsOnFspOfDsp2)
        {
            result = numberOfNonDcdsOnFspOfDsp1<numberOfNonDcdsOnFspOfDsp2;
        }
        else if(priorityOfNumberOfDchUsersForDsp1!=priorityOfNumberOfDchUsersForDsp2)
        {
            result = priorityOfNumberOfDchUsersForDsp1<priorityOfNumberOfDchUsersForDsp2;
        }
        else if(priorityOrderCountForHsupaCfsForDsp1!=priorityOrderCountForHsupaCfsForDsp2)
        {
            result = priorityOrderCountForHsupaCfsForDsp1>priorityOrderCountForHsupaCfsForDsp2;
        }
        else if(numberOfPrereservedHsupaCfsForDsp1!=numberOfPrereservedHsupaCfsForDsp2)
        {
            result = numberOfPrereservedHsupaCfsForDsp1<numberOfPrereservedHsupaCfsForDsp1;
        }
        else
        {
            result = dsp1.getAddress()<dsp2.getAddress();
        }
        return result;
    });
    if(!dspAddresses.empty())
    {
        setSelectionDspResult(result, dspAddresses.front());
    }
    return result;
}

FspAddresses Lrm::selectFspsForCcdNbicMcd(unsigned int const lcgId) const
{
    FspAddresses fspAddresses;
    copyFspWithAtLeastThisNumberOfEmptyNAndTn(fspAddresses, 1, lcgId);
    sortFspBasedPriorityForCcdMcdSelection(fspAddresses, lcgId);
    removeNotNeededFspsForCcdNbicMcd(fspAddresses, lcgId);
    return fspAddresses;
}

void Lrm::removeNotNeededFspsForCcdNbicMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    UniqueFspAddresses neededUniqueFspAddresses;
    saveNeededFspsForCcdNbicMcdBasedOnNOrTnWithDliRestrictions(neededUniqueFspAddresses, fspAddresses, lcgId);
    fspAddresses.clear();
    copy(neededUniqueFspAddresses.cbegin(), neededUniqueFspAddresses.cend(), back_inserter(fspAddresses));
    sortFspBasedPriorityForCcdMcdSelection(fspAddresses, lcgId);
}

void Lrm::saveNeededFspsForCcdNbicMcdBasedOnNOrTnWithDliRestrictions(UniqueFspAddresses & neededUniqueFspAddresses, FspAddresses const& fspAddresses, unsigned int const lcgId) const
{
    DliPools freeDliPools;
    copyFreeDliPools(freeDliPools);
    unsigned int numberOfDspToAllocate = 2;
    for(unsigned int const currentFspAddress : fspAddresses)
    {
        bool isFspNeeded(false);
        Fsp currentFsp(m_addressToFspMap.at(currentFspAddress));
        bool isFspValidBasedOnDliPoolRestrictions(canAFreeDliBeAllocatedInFsp(freeDliPools, currentFsp.getAddress(), lcgId));
        NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNAndTnOfFspAndLcg(currentFsp.getAddress(), lcgId);
        unsigned int emptyTurboNyquists(emptyNAndTnCount.numberOfTurboNyquists);
        unsigned int emptyNyquists(emptyNAndTnCount.numberOfNyquists);
        while(numberOfDspToAllocate>0 && emptyNyquists>0)
        {
            if(numberOfDspToAllocate==1 && !isFspValidBasedOnDliPoolRestrictions)//for NBIC MCD
            {
                break;
            }            isFspNeeded=true; numberOfDspToAllocate--; emptyNyquists--;
        }
        while(numberOfDspToAllocate>0 && emptyTurboNyquists>0 && isThereSpaceForTnForMcdOrCcdConsideringPic(currentFsp,  lcgId))
        {
            if(numberOfDspToAllocate==1 && !isFspValidBasedOnDliPoolRestrictions)//for NBIC MCD
            {
                break;
            }            isFspNeeded=true; numberOfDspToAllocate--; emptyTurboNyquists--;
        }
        if(isFspNeeded)
        {            neededUniqueFspAddresses.emplace(currentFspAddress);
        }
    }
}

SelectionDspResult Lrm::selectFspForPic(unsigned int const lcgId) const
{
    SelectionDspResult result;
    FspAddresses fspAddresses;
    copyFspWithAtLeastThisNumberOfTnDcdsWithoutHsRachCfsWithDliRestrictions(fspAddresses, lcgId);
    sortFspBasedPriorityForPicSelection(fspAddresses, lcgId);
    if(!fspAddresses.empty())
    {
        setSelectionDspResult(result, fspAddresses.front());
    }
    return result;
}

void Lrm::sortFspBasedPriorityForPicSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    //things to settle
    //Empty Cfs or empty allocated Cfs only?
    //non shared limitation is not put is this really needed?
    sortFspAddressesBasedOnCondition(fspAddresses, [&](Fsp const& fsp1, Fsp const& fsp2)
    {
        unsigned int priorityForMasterTcomFsp1(fsp1.isMasterTcom() ? 2 : 1);
        unsigned int priorityForMasterTcomFsp2(fsp2.isMasterTcom() ? 2 : 1);
        unsigned int priorityForOneFreeDliFsp1(getNumberOfFreeDliPoolsOfFsp(fsp1.getAddress())==1 ? 2 : 1);
        unsigned int priorityForOneFreeDliFsp2(getNumberOfFreeDliPoolsOfFsp(fsp2.getAddress())==1 ? 2 : 1);
        unsigned int numberOfNonDcdsForFsp1(getNumberOfNonDcdsOfFsp(fsp1.getAddress()));
        unsigned int numberOfNonDcdsForFsp2(getNumberOfNonDcdsOfFsp(fsp2.getAddress()));
        unsigned int priorityForTnCountWithEmptyCfsFsp1(getPriorityBasedOnNAndTnCountForFspMcdSelection(fsp1, lcgId));
        unsigned int priorityForTnCountWithEmptyCfsFsp2(getPriorityBasedOnNAndTnCountForFspMcdSelection(fsp2, lcgId));
        bool result(false);
        if(priorityForOneFreeDliFsp1!=priorityForOneFreeDliFsp2)
        {
            result = priorityForOneFreeDliFsp1>priorityForOneFreeDliFsp2;
        }
        else if(priorityForMasterTcomFsp1!=priorityForMasterTcomFsp2)
        {
            result = priorityForMasterTcomFsp1>priorityForMasterTcomFsp2;
        }
        else if(numberOfNonDcdsForFsp1!=numberOfNonDcdsForFsp2)
        {
            result =  m_isHibernationCommissioned
                    ? numberOfNonDcdsForFsp1>numberOfNonDcdsForFsp2
                    : numberOfNonDcdsForFsp1<numberOfNonDcdsForFsp2;
        }
        else if(priorityForTnCountWithEmptyCfsFsp1!=priorityForTnCountWithEmptyCfsFsp2)
        {
            result =  priorityForTnCountWithEmptyCfsFsp1>priorityForTnCountWithEmptyCfsFsp2;
        }
        else
        {
            result =  fsp1.getAddress()<fsp2.getAddress();
        }
        return result;
    });
}

unsigned int Lrm::getPriorityBasedOnTnWithoutCfsForFspPicSelection(Fsp const& fsp, unsigned int const lcgId) const
{
    NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfNAndTnWithoutCfsOfFspAndLcg(fsp.getAddress(), lcgId);
    unsigned int priority=0;
    if(emptyNAndTnCount.numberOfTurboNyquists>=1)
    {
        priority = 2;
    }
    else
    {
        priority = 1;
    }
    return priority;
}


/*
void Lrm::saveNeededFspsForCcdOrMcdBasedOnNyquist(UniqueFspAddresses & neededUniqueFspAddresses, unsigned int& numberOfDspToAllocate, FspAddresses const& fspAddresses, unsigned int const lcgId) const
{
    for(unsigned int const currentFspAddress : fspAddresses)
    {
        bool isFspNeeded(false);
        Fsp currentFsp(m_addressToFspMap.at(currentFspAddress));
        NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNyquistAndTurboNyquistOfFspAndLcg(currentFsp.getAddress(), lcgId);
        unsigned int emptyNyquists(emptyNAndTnCount.numberOfNyquists);
        while(numberOfDspToAllocate>0 && emptyNyquists>0)
        {
            isFspNeeded=true; numberOfDspToAllocate--; emptyNyquists--;
        }
        if(isFspNeeded)
        {
            neededUniqueFspAddresses.emplace(currentFspAddress);
        }
    }
}

void Lrm::saveNeededFspsForCcdOrMcdBasedOnTurboNyquist(UniqueFspAddresses & neededUniqueFspAddresses, unsigned int& numberOfDspToAllocate, FspAddresses const& fspAddresses, unsigned int const lcgId) const
{
    bool isPicToBeAllocated(m_lcgToValidPicPools.at(lcgId));
    bool isSharedLcgId(isSharedLcg(lcgId));
    for(unsigned int const currentFspAddress : fspAddresses)
    {
        bool isFspNeeded(false);
        Fsp currentFsp(m_addressToFspMap.at(currentFspAddress));
        NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNyquistAndTurboNyquistOfFspAndLcg(currentFsp.getAddress(), lcgId);
        NyquistAndTurboNyquistCount emptyNAndTnCountInMsm = getNumberOfEmptyNyquistAndTurboNyquistInMsmOfLcg(lcgId);
        unsigned int emptyTurboNyquists(emptyNAndTnCount.numberOfTurboNyquists);
        bool isTnInMsmSufficientForPic=canTurboNyquistsBeAllocatedBasedOnPicAndNumberOfTurboNyquists(emptyNAndTnCountInMsm, numberOfDspToAllocate, lcgId);
        bool shouldConsiderPic = isSharedLcgId && currentFsp.getSmType() == SmType::MSM;
        while(shouldConsiderPic && isTnInMsmSufficientForPic && isPicToBeAllocated && emptyTurboNyquists>0)
        {
            isPicToBeAllocated=false; emptyTurboNyquists--;
        }
        bool isTurboNyquistForCcdOrMcdAllowed = !shouldConsiderPic ||(shouldConsiderPic && !isPicToBeAllocated);
        while(isTurboNyquistForCcdOrMcdAllowed && numberOfDspToAllocate>0 && emptyTurboNyquists>0)
        {
            isFspNeeded=true; numberOfDspToAllocate--; emptyTurboNyquists--;
        }
        if(isFspNeeded)
        {
            neededUniqueFspAddresses.emplace(currentFspAddress);
        }
    }
}
*/


unsigned int Lrm::getPriorityBasedOnLessUsersAndHsupaCfsForDsp(Dsp const& dsp) const
{
    bool noUsersInDsp = dsp.getNumberOfDchUsers()==0;
    bool noHsupaCfsInDsp = dsp.getNumberOfHsupaCfs()==0;
    unsigned int priority=0;
    if(noUsersInDsp && noHsupaCfsInDsp)
    {
        priority = 3;
    }
    else if(noUsersInDsp)
    {
        priority = 2;
    }
    else
    {
        priority = 1;
    }
    return priority;
}

void Lrm::saveNeededFspsForCcdOrMcdBasedOnNOrTn(UniqueFspAddresses & neededUniqueFspAddresses, unsigned int& numberOfDspToAllocate, FspAddresses const& fspAddresses, unsigned int const lcgId) const
{
    for(unsigned int const currentFspAddress : fspAddresses)
    {
        bool isFspNeeded(false);
        Fsp currentFsp(m_addressToFspMap.at(currentFspAddress));
        NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNAndTnOfFspAndLcg(currentFsp.getAddress(), lcgId);
        unsigned int emptyTurboNyquists(emptyNAndTnCount.numberOfTurboNyquists);
        unsigned int emptyNyquists(emptyNAndTnCount.numberOfNyquists);
        while(numberOfDspToAllocate>0 && emptyNyquists>0)
        {
            isFspNeeded=true; numberOfDspToAllocate--; emptyNyquists--;
        }
        while(numberOfDspToAllocate>0 && emptyTurboNyquists>0 && isThereSpaceForTnForMcdOrCcdConsideringPic(currentFsp,  lcgId))
        {
            isFspNeeded=true; numberOfDspToAllocate--; emptyTurboNyquists--;
        }
        if(isFspNeeded)
        {
            neededUniqueFspAddresses.emplace(currentFspAddress);
        }
    }
}

bool Lrm::isThereSpaceForTnForMcdOrCcdConsideringPic(Fsp const& fsp, unsigned int const lcgId) const
{
    bool isMsmOnly = isSharedLcg(lcgId) && fsp.getSmType() == SmType::MSM;
    bool isThereSpace(false);
    if(isMsmOnly)
    {
        NyquistAndTurboNyquistCount emptyNAndTnCountInMsmOfLcg = getNumberOfEmptyNAndTnInMsmOfLcg(lcgId);
        isThereSpace=canTnBeAllocatedBasedOnPicAndNumberOfTnToBeAllocated(emptyNAndTnCountInMsmOfLcg, 1, lcgId);
    }
    else
    {
        NyquistAndTurboNyquistCount emptyNAndTnCountOfLcg = getNumberOfEmptyNAndTnOfLcg(lcgId);
        isThereSpace=canTnBeAllocatedBasedOnPicAndNumberOfTnToBeAllocated(emptyNAndTnCountOfLcg, 1, lcgId);
    }
    return isThereSpace;
}

SelectionDspResult Lrm::selectEmptyDspPriotizingNyquistTypeAndAddressInFsp(unsigned int const lcgId, unsigned int const fspAddress) const
{
    SelectionDspResult result;
    DspAddresses dspAddressesForLcgInFsp;
    copyDspAddressesInFspThatSatisfiesThisCondition(dspAddressesForLcgInFsp, fspAddress, [&](Dsp const& currentDsp)
    {
        return currentDsp.getLcgId()==lcgId && currentDsp.isEmpty();
    });
    sortDspAddressesBasedOnCondition(dspAddressesForLcgInFsp, [&](Dsp const& dsp1, Dsp const& dsp2)
    {
        unsigned int dsp1NyquistValue = (dsp1.getNyquistType()==NyquistType::Nyquist) ? 0 : 1;
        unsigned int dsp2NyquistValue = (dsp2.getNyquistType()==NyquistType::Nyquist) ? 0 : 1;
        bool result(false);
        if(dsp1NyquistValue!=dsp2NyquistValue)
        {
            result = dsp1NyquistValue<dsp2NyquistValue;
        }
        else
        {
            result = dsp1.getAddress()<dsp2.getAddress();
        }
        return result;
    });
    if(!dspAddressesForLcgInFsp.empty())
    {
        setSelectionDspResult(result, dspAddressesForLcgInFsp.front());
    }
    return result;
}

SelectionDspResult Lrm::selectTnPriotizingLessUsersAndHsupaCfsInFsp(unsigned int const lcgId, unsigned int const fspAddress) const
{
    SelectionDspResult result;
    DspAddresses dspAddressesForLcgInFsp;
    copyDspAddressesInFspThatSatisfiesThisCondition(dspAddressesForLcgInFsp, fspAddress, [&](Dsp const& currentDsp)
    {
        return currentDsp.getLcgId()==lcgId
                && currentDsp.getNyquistType()==NyquistType::TurboNyquist
                && currentDsp.getMode() == DspMode::NyquistDedicatedChannelDevice
                && currentDsp.getNumberOfHsRachCfs()==0;
    });
    sortDspAddressesBasedOnCondition(dspAddressesForLcgInFsp, [&](Dsp const& dsp1, Dsp const& dsp2)
    {
        unsigned int priorityForDsp1 = getPriorityBasedOnLessUsersAndHsupaCfsForDsp(dsp1);
        unsigned int priorityForDsp2 = getPriorityBasedOnLessUsersAndHsupaCfsForDsp(dsp1);
        unsigned int dchUsersForDsp1 = dsp1.getNumberOfDchUsers();
        unsigned int dchUsersForDsp2 = dsp2.getNumberOfDchUsers();
        unsigned int hsupaCfsForDsp1 = dsp1.getNumberOfHsupaCfs();
        unsigned int hsupaCfsForDsp2 = dsp2.getNumberOfHsupaCfs();
        bool result(false);
        if(priorityForDsp1!=priorityForDsp2)
        {
            result = priorityForDsp1>priorityForDsp2;
        }
        else if(dchUsersForDsp1!=dchUsersForDsp2)
        {
            result = dchUsersForDsp1<dchUsersForDsp2;
        }
        else if(hsupaCfsForDsp1!=hsupaCfsForDsp2)
        {
            result = hsupaCfsForDsp1<hsupaCfsForDsp2;
        }
        else
        {
            result = dsp1.getAddress()<dsp2.getAddress();
        }
        return result;
    });
    if(!dspAddressesForLcgInFsp.empty())
    {
        setSelectionDspResult(result, dspAddressesForLcgInFsp.front());
    }
    return result;
}

void Lrm::copyFspWithAtLeastThisNumberOfEmptyNAndTn(FspAddresses& fspAddresses, unsigned int const requiredEmptyCount, unsigned int const lcgId) const
{
    copyFspAddressesThatSatisfiesThisCondition(fspAddresses, [&](Fsp const& currentFsp)
    {
        NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNAndTnOfFspAndLcg(currentFsp.getAddress(), lcgId);
        return (emptyNAndTnCount.numberOfNyquists+emptyNAndTnCount.numberOfTurboNyquists)>=requiredEmptyCount;
    });
}

void Lrm::copyFspWithAtLeastThisNumberOfEmptyNAndTnWithDliRestrictions(FspAddresses& fspAddresses, unsigned int const requiredEmptyCount, unsigned int const lcgId) const
{
    DliPools freeDliPools;
    copyFreeDliPools(freeDliPools);
    copyFspAddressesThatSatisfiesThisCondition(fspAddresses, [&](Fsp const& currentFsp)
    {
        NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNAndTnOfFspAndLcg(currentFsp.getAddress(), lcgId);
        bool isNumberOfEmptyDspsSufficient((emptyNAndTnCount.numberOfNyquists+emptyNAndTnCount.numberOfTurboNyquists)>=requiredEmptyCount);
        bool isDliPoolAvailableInFsp(canAFreeDliBeAllocatedInFsp(freeDliPools, currentFsp.getAddress(), lcgId));
        return isNumberOfEmptyDspsSufficient && isDliPoolAvailableInFsp;
    });
}
void Lrm::copyFspWithAtLeastThisNumberOfTnDcdsWithoutHsRachCfsWithDliRestrictions(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    DliPools freeDliPools;    copyFreeDliPools(freeDliPools);
    copyFspAddressesThatSatisfiesThisCondition(fspAddresses, [&](Fsp const& currentFsp)
    {
        bool result(false);
        bool isDliPoolAvailableInFsp(canAFreeDliBeAllocatedInFsp(freeDliPools, currentFsp.getAddress(), lcgId));
        if(isDliPoolAvailableInFsp)
        {
            DspAddresses const& dspAddresses(currentFsp.getDspAddresses());            for(unsigned int const dspAddress : dspAddresses)
            {
                Dsp& currentDsp(m_addressToDspMap.at(dspAddress));
                DspMode mode(currentDsp.getMode());                if(currentDsp.getLcgId()==lcgId
                        && mode==DspMode::NyquistDedicatedChannelDevice
                        && currentDsp.getNumberOfHsRachCfs()==0)
                {
                    result=true;
                    break;
                }
            }
        }
        return result;
    });
}

NyquistAndTurboNyquistCount Lrm::getNumberOfEmptyNAndTnOfFspAndLcg(unsigned int const fspAddress, unsigned int const lcgId) const
{
    NyquistAndTurboNyquistCount result{0, 0};
    Fsp& fsp(m_addressToFspMap.at(fspAddress));
    DspAddresses const& dspAddresses(fsp.getDspAddresses());
    for(unsigned int const dspAddress : dspAddresses)
    {
        Dsp& currentDsp(m_addressToDspMap.at(dspAddress));
        if(currentDsp.getLcgId()==lcgId && currentDsp.isEmpty())
        {
            incrementNAndTnCountBasedOnNyquistType(result, currentDsp.getNyquistType());
        }
    }
    return result;
}

NyquistAndTurboNyquistCount Lrm::getNumberOfNAndTnWithoutCfsOfFspAndLcg(unsigned int const fspAddress, unsigned int const lcgId) const
{
    NyquistAndTurboNyquistCount result{0, 0};
    Fsp& fsp(m_addressToFspMap.at(fspAddress));
    DspAddresses const& dspAddresses(fsp.getDspAddresses());
    for(unsigned int const dspAddress : dspAddresses)
    {
        Dsp& currentDsp(m_addressToDspMap.at(dspAddress));
        if(currentDsp.getLcgId()==lcgId && currentDsp.getNumberOfHsupaCfs()==0 && currentDsp.getNumberOfHsRachCfs()==0)
        {
            incrementNAndTnCountBasedOnNyquistType(result, currentDsp.getNyquistType());
        }
    }
    return result;
}

NyquistAndTurboNyquistCount Lrm::getNumberOfEmptyNAndTnInMsmOfLcg(unsigned int const lcgId) const
{
    NyquistAndTurboNyquistCount result{0, 0};
    for(AddressToDspPair const& addressToDspPair : m_addressToDspMap)
    {
        Dsp currentDsp(addressToDspPair.second);
        if(currentDsp.getLcgId()==lcgId && currentDsp.isEmpty())
        {
            incrementNAndTnCountBasedOnNyquistType(result, currentDsp.getNyquistType());
        }
    }
    return result;
}

NyquistAndTurboNyquistCount Lrm::getNumberOfEmptyNAndTnOfLcg(unsigned int const lcgId) const
{
    NyquistAndTurboNyquistCount result{0, 0};
    for(AddressToDspPair const& addressToDspPair : m_addressToDspMap)
    {
        Dsp currentDsp(addressToDspPair.second);
        if(currentDsp.getLcgId()==lcgId && currentDsp.isEmpty())
        {
            incrementNAndTnCountBasedOnNyquistType(result, currentDsp.getNyquistType());
        }
    }
    return result;
}

unsigned int Lrm::getNumberOfNonDcdsOfFsp(unsigned int const fspAddress) const
{
    unsigned int resultCount=0;
    Fsp& fsp(m_addressToFspMap.at(fspAddress));
    DspAddresses const& dspAddresses(fsp.getDspAddresses());
    for(unsigned int const dspAddress : dspAddresses)
    {
        Dsp& currentDsp(m_addressToDspMap.at(dspAddress));
        DspMode mode(currentDsp.getMode());
        if(mode!=DspMode::NyquistDedicatedChannelDevice)
        {
            resultCount++;
        }
    }
    return resultCount;
}

unsigned int Lrm::getNumberOfFreeDliPoolsOfFsp(unsigned int const fspAddress) const
{
    unsigned int countOfDliPoolsAllocated=0;
    Fsp& fsp(m_addressToFspMap.at(fspAddress));
    DspAddresses const& dspAddresses(fsp.getDspAddresses());
    for(unsigned int const dspAddress : dspAddresses)
    {
        Dsp& currentDsp(m_addressToDspMap.at(dspAddress));
        if(!currentDsp.hasFreeDli())
        {
            countOfDliPoolsAllocated++;
        }
    }
    return countOfDliPoolsAllocated>=2 ? 0 : 2-countOfDliPoolsAllocated;
}

void Lrm::copyFspAddressesThatSatisfiesThisCondition(FspAddresses & fspAddresses, FspBooleanCondition const& condition) const
{
    for(AddressToFspPair const& addressToFspPair : m_addressToFspMap)
    {
        Fsp currentFsp(addressToFspPair.second);
        unsigned int const currentFspAddress(currentFsp.getAddress());
        if(condition(currentFsp))
        {
            fspAddresses.emplace_back(currentFspAddress);
        }
    }
}

void Lrm::sortFspAddressesBasedOnCondition(FspAddresses & fspAddresses, FspComparisonCondition const& condition) const
{
    stable_sort(fspAddresses.begin(), fspAddresses.end(), [&](unsigned int const fspAddress1, unsigned int const fspAddress2)
    {
        Fsp const& fsp1(m_addressToFspMap.at(fspAddress1));
        Fsp const& fsp2(m_addressToFspMap.at(fspAddress2));
        return condition(fsp1, fsp2);
    });
}

void Lrm::copyDspAddressesThatSatisfiesThisCondition(DspAddresses & dspAddresses, DspBooleanCondition const& condition) const
{
    for(AddressToDspPair const& addressToDspPair : m_addressToDspMap)
    {
        Dsp currentDsp(addressToDspPair.second);
        unsigned int const currentDspAddress(currentDsp.getAddress());
        if(condition(currentDsp))
        {
            dspAddresses.emplace_back(currentDspAddress);
        }
    }
}

void Lrm::copyDspAddressesInFspThatSatisfiesThisCondition(DspAddresses & dspAddressesForLcgInFsp, unsigned int fspAddress, DspBooleanCondition const& condition) const
{
    Fsp& fsp(m_addressToFspMap.at(fspAddress));
    DspAddresses const& dspAddresses(fsp.getDspAddresses());
    copy_if(dspAddresses.cbegin(), dspAddresses.cend(), back_inserter(dspAddressesForLcgInFsp), [&](unsigned int const dspAddress)
    {
        Dsp const& currentDsp(m_addressToDspMap.at(dspAddress));
        return condition(currentDsp);
    });
}

void Lrm::sortDspAddressesBasedOnCondition(DspAddresses & dspAddressesForLcgInFsp, DspComparisonCondition const& condition) const
{
    stable_sort(dspAddressesForLcgInFsp.begin(), dspAddressesForLcgInFsp.end(), [&](unsigned int const dspAddress1, unsigned int const dspAddress2)
    {
        Dsp const& dsp1(m_addressToDspMap.at(dspAddress1));
        Dsp const& dsp2(m_addressToDspMap.at(dspAddress2));
        return condition(dsp1, dsp2);
    });
}

void Lrm::setSelectionDspResult(SelectionDspResult& selectionDspResultReference, unsigned int const fspAddress) const
{
    selectionDspResultReference.isSelectionSuccessful = true;
    selectionDspResultReference.address = fspAddress;
}

void Lrm::incrementNAndTnCountBasedOnNyquistType(NyquistAndTurboNyquistCount& countReference, NyquistType const nyquistType) const
{
    if(nyquistType==NyquistType::Nyquist)
    {
        countReference.numberOfNyquists++;
    }
    else
    {
        countReference.numberOfTurboNyquists++;
    }
}

unsigned int Lrm::getFreeDliToAllocateForDsp(unsigned int const dspAddress) const
{
    Dsp const& dsp(m_addressToDspMap.at(dspAddress));
    unsigned int freeDliResult(0);
    DliPools freeDliPools;
    copyFreeDliPools(freeDliPools);
    if(!freeDliPools.empty())
    {
        freeDliResult = getFreeDliBasedOnSameFsp(dsp, freeDliPools);
        if(freeDliResult==0)
        {
            freeDliResult = getFreeDliBasedOnOtherFsps(dsp, freeDliPools);
            if(freeDliResult==0)
            {
                freeDliResult = *(freeDliPools.cbegin());
            }
        }
    }
    return freeDliResult;
}

unsigned int Lrm::getFreeDliBasedOnSameFsp(Dsp const& dsp, DliPools const& freeDliPools) const
{
    unsigned int freeDliResult(0);
    DliPools usedDliPoolsOnFsp;
    copyUsedDliPoolsOnFsp(usedDliPoolsOnFsp, dsp.getFspAddress());
    for(unsigned int currentUsedDli : usedDliPoolsOnFsp)
    {
        unsigned int leastConflictingDli(getLeastConflictingDliPoolForThisDli(currentUsedDli));
        if(freeDliPools.find(leastConflictingDli)!=freeDliPools.cend())
        {
            freeDliResult = leastConflictingDli;
            break;
        }
    }
    return freeDliResult;
}

unsigned int Lrm::getFreeDliBasedOnOtherFsps(Dsp const& dsp, DliPools const& freeDliPools) const
{
    unsigned int freeDliResult(0);
    DliPools usedDliPoolsOnOtherFsp;
    copyUsedDliPoolsOnOtherFspsExceptThisFsp(usedDliPoolsOnOtherFsp, dsp.getFspAddress());
    for(unsigned int currentUsedDli : usedDliPoolsOnOtherFsp)
    {
        unsigned int conflictDliInOtherFsp(getConflictingDliPoolForThisDli(currentUsedDli));
        if(freeDliPools.find(conflictDliInOtherFsp)!=freeDliPools.cend())
        {
            freeDliResult = conflictDliInOtherFsp;
            break;
        }
    }
    return freeDliResult;
}

void Lrm::copyFreeDliPools(DliPools & freeDliPools) const
{
    DliPools usedDliPools;
    copyUsedDliPools(usedDliPools);
    for(unsigned int dliPool=1; dliPool<=4; dliPool++)
    {
        if(usedDliPools.find(dliPool)==usedDliPools.cend())
        {
            freeDliPools.emplace(dliPool);
        }
    }
}

void Lrm::copyUsedDliPools(DliPools & usedDliPools) const
{
    for(AddressToFspPair const& addressToFspPair : m_addressToFspMap)
    {
        Fsp currentFsp(addressToFspPair.second);
        unsigned int const currentFspAddress(currentFsp.getAddress());
        copyUsedDliPoolsOnFsp(usedDliPools, currentFspAddress);
    }
}

void Lrm::copyUsedDliPoolsOnFsp(DliPools & usedDliPools, unsigned int const fspAddress) const
{
    Fsp& fsp(m_addressToFspMap.at(fspAddress));
    DspAddresses const& dspAddresses(fsp.getDspAddresses());
    for(unsigned int const dspAddress : dspAddresses)
    {
        Dsp& currentDsp(m_addressToDspMap.at(dspAddress));
        if(!currentDsp.hasFreeDli())
        {
            usedDliPools.emplace(currentDsp.getDliPool());
        }
    }
}

void Lrm::copyUsedDliPoolsOnOtherFspsExceptThisFsp(DliPools & usedDliPools, unsigned int const fspAddressOfSkippedFsp) const
{
    for(AddressToFspPair const& addressToFspPair : m_addressToFspMap)
    {
        Fsp currentFsp(addressToFspPair.second);
        unsigned int const currentFspAddress(currentFsp.getAddress());
        if(currentFspAddress != fspAddressOfSkippedFsp)
        {
            copyUsedDliPoolsOnFsp(usedDliPools, currentFspAddress);
        }
    }
}

bool Lrm::canAFreeDliBeAllocatedInFsp(DliPools const& freeDliPools, unsigned int const fspAddress, unsigned int const lcgId) const
{
    DliPools usedDliPools;
    copyUsedDliPoolsOnFsp(usedDliPools, fspAddress);
    bool result(false);
    bool isSharedLcgId(isSharedLcg(lcgId));
    Fsp fsp(m_addressToFspMap.at(fspAddress));
    if(!isSharedLcgId || (isSharedLcgId && fsp.getSmType()==SmType::MSM))
    {
        for(unsigned int const freeDliToBeAllocated : freeDliPools)
        {
            unsigned int conflictingDliPoolForThisDli(getConflictingDliPoolForThisDli(freeDliToBeAllocated));
            bool canBeAllocated(true);
            for(unsigned int currentUsedDli : usedDliPools)
            {
                if(freeDliToBeAllocated==currentUsedDli || conflictingDliPoolForThisDli==currentUsedDli)
                {
                    canBeAllocated=false;
                    break;
                }
            }
            if(canBeAllocated==true)
            {
                result=true;
                break;
            }
        }
    }
    return result;
}
bool Lrm::canTnBeAllocatedBasedOnPicAndNumberOfTnToBeAllocated(
        NyquistAndTurboNyquistCount const& nAndTnCountInMsmOfLcg,
        unsigned int const numberOfTurboNyquistToBeUsed,
        unsigned int const lcgId) const
{

    return (getNumberOfPicPoolsForLcg(lcgId) + numberOfTurboNyquistToBeUsed) <= nAndTnCountInMsmOfLcg.numberOfTurboNyquists;
}

bool Lrm::isSharedLcg(unsigned int const lcgId) const{
    return lcgId == m_hardwareConfigurationReference.getSharedLcgId();
}
unsigned int Lrm::getConflictingDliPoolForThisDli(unsigned int const dliPool) const
{
    unsigned int conflictPool;
    if(dliPool==1)
    {
        conflictPool = 4;
    }
    else if(dliPool==2)
    {
        conflictPool = 3;
    }
    else if(dliPool==3)
    {
        conflictPool = 2;
    }
    else if(dliPool==4)
    {
        conflictPool = 1;
    }
    return conflictPool;
}

unsigned int Lrm::getLeastConflictingDliPoolForThisDli(unsigned int const dliPool) const
{
    unsigned int leastConflictPool;
    if(dliPool==1)
    {
        leastConflictPool = 3;
    }
    else if(dliPool==2)
    {
        leastConflictPool = 4;
    }
    else if(dliPool==3)
    {
        leastConflictPool = 1;
    }
    else if(dliPool==4)
    {
        leastConflictPool = 2;
    }
    return leastConflictPool;
}

void Lrm::changeModeForCcdAndUpdateDspDetails(SelectionDspResultForCcdAndMcd const& selectionDspResultForCcdAndMcd)
{
    SelectionDspResult ccdSelectionDspResult;
    ccdSelectionDspResult.isSelectionSuccessful = selectionDspResultForCcdAndMcd.isSelectionSuccessful;
    ccdSelectionDspResult.address = selectionDspResultForCcdAndMcd.ccdAddress;
    changeModeAndUpdateDspDetails(ccdSelectionDspResult, DspMode::NyquistCommonChannelDeviceNormal);
}

void Lrm::changeModeForMcdAndUpdateDspDetails(SelectionDspResultForCcdAndMcd const& selectionDspResultForCcdAndMcd)
{
    SelectionDspResult mcdSelectionDspResult;
    mcdSelectionDspResult.isSelectionSuccessful = selectionDspResultForCcdAndMcd.isSelectionSuccessful;
    mcdSelectionDspResult.address = selectionDspResultForCcdAndMcd.mcdAddress;
    mcdSelectionDspResult.isNbicAllocated = selectionDspResultForCcdAndMcd.isNbicAllocated;
    mcdSelectionDspResult.dliPool = selectionDspResultForCcdAndMcd.dliPool;
    changeModeAndUpdateDspDetails(mcdSelectionDspResult, DspMode::NyquistMixedChannelDevice);
}

void Lrm::changeModeAndUpdateDspDetails(SelectionDspResult const& selectionDspResult, DspMode const dspMode)
{
    Dsp & dsp(m_addressToDspMap.at(selectionDspResult.address));
    changeMode(dsp, dspMode);
    setDliIfNeeded(dsp, dspMode, selectionDspResult.isNbicAllocated, selectionDspResult.dliPool);
    setAsNbicIfNeeded(dsp, dspMode, selectionDspResult.isNbicAllocated);
}

void Lrm::changeMode(Dsp& dspToChange, DspMode const dspMode)
{
    dspToChange.setMode(dspMode);
}

void Lrm::setDliIfNeeded(Dsp& dspToChange, DspMode const dspMode, bool const isNbic, unsigned int const dliPool)
{
    if(dspMode == DspMode::NyquistPicDevice
            ||(dspMode == DspMode::NyquistMixedChannelDevice && isNbic))
    {
        dspToChange.setDliPool(dliPool);
    }
}

void Lrm::setAsNbicIfNeeded(Dsp& dspToChange, DspMode const dspMode, bool const isNbic)
{
    if(dspMode == DspMode::NyquistMixedChannelDevice && isNbic)
    {
        dspToChange.setIsNbicAllocated(isNbic);
    }
}

unsigned int Lrm::getNumberOfPicPoolsForLcg(unsigned int const lcgId) const
{
    return m_lcgToValidPicPools.count(lcgId)>0 ? m_lcgToValidPicPools.at(lcgId) : 0;
}

}