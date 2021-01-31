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
    : m_isHibernationCommissioned(false)
    , m_maxAmountOfNonDcdsPerFsp(6)
    , m_hardwareConfigurationReference(hardwareConfiguration)
    , m_addressToDspMap(m_hardwareConfigurationReference.getAddressToDspMapReference())
    , m_addressToFspMap(m_hardwareConfigurationReference.getAddressToFspMapReference()){}

void Lrm::setHibernationCommissioned(bool const isHibernationCommissioned)
{
    m_isHibernationCommissioned = isHibernationCommissioned;
}

void Lrm::setMaxAmountOfNonDcdsPerFsp(unsigned int const maxAmountOfNonDcdsPerFsp)
{
    m_maxAmountOfNonDcdsPerFsp = maxAmountOfNonDcdsPerFsp;
}

void Lrm::setNumberOfUnallocatedPicPoolsPerLcg(unsigned int const lcgId, unsigned int const numberOfPicPools)
{
    m_lcgToUnallocatedPicPools[lcgId] = numberOfPicPools;
}

void Lrm::clearLcgToUnallocatedPicPools(unsigned int const lcgId)
{
    m_lcgToUnallocatedPicPools.erase(lcgId);
}

SelectionDspResult Lrm::allocateMcdForLcgIdAccordingToMark(unsigned int const lcgId)
{
    SelectionDspResult result;    SelectionDspResult fspSelectionResult = selectFspForEmptyDspForMcd(lcgId);
    if(fspSelectionResult.isSelectionSuccessful)
    {
        SelectionDspResult dspSelectionResult = selectEmptyDspPriotizingNyquistTypeAndAddressInFsp(lcgId, fspSelectionResult.address);        if(dspSelectionResult.isSelectionSuccessful)
        {
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
    FspAddresses selectedFspAddresses = selectFspsForCcdMcd(lcgId);
    unsigned int ccdFspAddress(0), mcdFspAddress(0);
    if(selectedFspAddresses.size()==1)
    {
        ccdFspAddress = selectedFspAddresses[0];
        mcdFspAddress = selectedFspAddresses[0];
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
        else
        {
            SelectionDspResult changeModeFromCcdToDcdAgain;
            changeModeFromCcdToDcdAgain.isSelectionSuccessful = true;
            changeModeFromCcdToDcdAgain.address = ccdMcdAddress.ccdAddress;
            changeModeAndUpdateDspDetails(changeModeFromCcdToDcdAgain, DspMode::NyquistDedicatedChannelDevice);
        }
    }
    return ccdMcdAddress;
}

SelectionDspResult Lrm::allocateNbicMcdForLcgIdAccordingToMark(unsigned int const lcgId)
{
    SelectionDspResult result;
    SelectionDspResult fspSelectionResult = selectFspForEmptyDspForNbicMcd(lcgId);
    if(fspSelectionResult.isSelectionSuccessful)    {
        SelectionDspResult dspSelectionResult = selectEmptyDspPriotizingNyquistTypeAndAddressInFsp(lcgId, fspSelectionResult.address);
        if(dspSelectionResult.isSelectionSuccessful)
        {            result.dliPool = getFreeDliToAllocateForDsp(dspSelectionResult.address);
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
    FspAddresses selectedFspAddresses = selectFspsForCcdNbicMcd(lcgId);
    unsigned int ccdFspAddress(0), mcdFspAddress(0);
    if(selectedFspAddresses.size()==1)
    {
        ccdFspAddress = selectedFspAddresses[0];
        mcdFspAddress = selectedFspAddresses[0];
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
        else
        {
            SelectionDspResult changeModeFromCcdToDcdAgain;
            changeModeFromCcdToDcdAgain.isSelectionSuccessful = true;
            changeModeFromCcdToDcdAgain.address = ccdMcdAddress.ccdAddress;
            changeModeAndUpdateDspDetails(changeModeFromCcdToDcdAgain, DspMode::NyquistDedicatedChannelDevice);
        }
    }
    return ccdMcdAddress;
}

SelectionDspResult Lrm::allocatePicForLcgIdAccordingToMark(unsigned int const lcgId)
{
    SelectionDspResult result;
    SelectionDspResult fspSelectionResult = selectFspForPic(lcgId);
    if(fspSelectionResult.isSelectionSuccessful)
    {
        SelectionDspResult dspSelectionResult = selectTnPriotizingLessUsersAndHsupaCfsInFsp(lcgId, fspSelectionResult.address);
        if(dspSelectionResult.isSelectionSuccessful)
        {
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
    copyFspWithAtLeastThisNumberOfEmptyNAndTnAndBelowMaxAmountOfNonDcds(fspAddresses, 1, lcgId);
    sortFspBasedPriorityForMcdSelection(fspAddresses, lcgId);
    removeNotNeededFspsForMcd(fspAddresses, lcgId);
    if(!fspAddresses.empty())    {
        setSelectionDspResult(result, fspAddresses.front());
    }
    return result;}

void Lrm::sortFspBasedPriorityForMcdSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    sortFspAddressesBasedOnCondition(fspAddresses, [&](Fsp const& fsp1, Fsp const& fsp2)
    {
        unsigned int priorityForMasterTcomFsp1(fsp1.isMasterTcom() ? 2 : 1);
        unsigned int priorityForMasterTcomFsp2(fsp2.isMasterTcom() ? 2 : 1);
        unsigned int priorityForNAndTnCountFsp1(getPriorityBasedOnNAndTnCountForFspMcdSelection(fsp1, lcgId));
        unsigned int priorityForNAndTnCountFsp2(getPriorityBasedOnNAndTnCountForFspMcdSelection(fsp2, lcgId));
        unsigned int numberOfNonDcdsForFsp1(getNumberOfNonDcdsInFsp(fsp1.getAddress()));
        unsigned int numberOfNonDcdsForFsp2(getNumberOfNonDcdsInFsp(fsp2.getAddress()));
        bool result(false);
        if(priorityForMasterTcomFsp1!=priorityForMasterTcomFsp2)
        {
            result = priorityForMasterTcomFsp1>priorityForMasterTcomFsp2;
        }
        else if(priorityForNAndTnCountFsp1!=priorityForNAndTnCountFsp2)
        {
            result =  priorityForNAndTnCountFsp1>priorityForNAndTnCountFsp2;
        }
        else if(numberOfNonDcdsForFsp1!=numberOfNonDcdsForFsp2)
        {
            result =  m_isHibernationCommissioned                    ? numberOfNonDcdsForFsp1>numberOfNonDcdsForFsp2
                    : numberOfNonDcdsForFsp1<numberOfNonDcdsForFsp2;
        }
        else
        {
            result =  fsp1.getAddress()<fsp2.getAddress();        }
        return result;
    });
}
unsigned int Lrm::getPriorityBasedOnNAndTnCountForFspMcdSelection(Fsp const& fsp, unsigned int const lcgId) const
{
    NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNAndTnOfFspAndLcg(fsp.getAddress(), lcgId);
    unsigned int priority=0;
    if(emptyNAndTnCount.numberOfNyquists>=1)
    {
        priority = 4;
    }
    else if(emptyNAndTnCount.numberOfTurboNyquists>=1)
    {
        priority = 3;
        /*unsigned int numberOfFreeDliPoolsForFsp(getNumberOfFreeDliPoolsOfFsp(fsp.getAddress()));
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
        }*/
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
    {        unsigned int priorityBasedOnModeForDsp1 = (dsp1.getMode()==DspMode::NyquistDedicatedChannelDevice) ? 2 : 1;
        unsigned int priorityBasedOnModeForDsp2 = (dsp2.getMode()==DspMode::NyquistDedicatedChannelDevice) ? 2 : 1;
        unsigned int priorityBasedOnHsupaCfsExistenceForDsp1 = (dsp1.getNumberOfHsupaCfs()==0) ? 2 : 1;
        unsigned int priorityBasedOnHsupaCfsExistenceForDsp2 = (dsp2.getNumberOfHsupaCfs()==0) ? 2 : 1;
        unsigned int numberOfNonDcdsOnFspOfDsp1(getNumberOfNonDcdsInFsp(dsp1.getFspAddress()));
        unsigned int numberOfNonDcdsOnFspOfDsp2(getNumberOfNonDcdsInFsp(dsp2.getFspAddress()));
        unsigned int priorityOfNumberOfDchUsersForDsp1 = (dsp1.getNumberOfHsupaCfs()==0) ? dsp1.getNumberOfDchUsers() : 0;
        unsigned int priorityOfNumberOfDchUsersForDsp2 = (dsp2.getNumberOfHsupaCfs()==0) ? dsp2.getNumberOfDchUsers() : 0;
        unsigned int priorityOrderCountForHsupaCfsForDsp1 = dsp1.getOrderCountOfCfAllocation();        unsigned int priorityOrderCountForHsupaCfsForDsp2 = dsp2.getOrderCountOfCfAllocation();
        unsigned int numberOfPrereservedHsupaCfsForDsp1 = dsp1.getNumberOfPreservedHsupaCfs();
        unsigned int numberOfPrereservedHsupaCfsForDsp2 = dsp2.getNumberOfPreservedHsupaCfs();
        bool result(false);        if(priorityBasedOnModeForDsp1!=priorityBasedOnModeForDsp2)
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
    sortFspBasedPriorityForMcdSelection(fspAddresses, lcgId);
}

FspAddresses Lrm::selectFspsForCcdMcd(unsigned int const lcgId) const
{
    FspAddresses fspAddresses;
    copyFspWithAtLeastThisNumberOfEmptyNAndTnAndBelowMaxAmountOfNonDcds(fspAddresses, 1, lcgId);
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
        unsigned int numberOfNonDcdsForFsp1(getNumberOfNonDcdsInFsp(fsp1.getAddress()));
        unsigned int numberOfNonDcdsForFsp2(getNumberOfNonDcdsInFsp(fsp2.getAddress()));
        unsigned int priorityForNAndTnCountFsp1(getPriorityBasedOnNAndTnCountForFspCcdMcdSelection(fsp1, lcgId));
        unsigned int priorityForNAndTnCountFsp2(getPriorityBasedOnNAndTnCountForFspCcdMcdSelection(fsp2, lcgId));
        bool result(false);        if(priorityForMasterTcomFsp1!=priorityForMasterTcomFsp2)
        {
            result = priorityForMasterTcomFsp1>priorityForMasterTcomFsp2;
        }        else if(numberOfNonDcdsForFsp1!=numberOfNonDcdsForFsp2)
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
        priority = 6;
        /*
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
        }*/
    }
    else if(emptyNAndTnCount.numberOfTurboNyquists>=1)
    {
        priority = 5;
        /*
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
        }*/
    }
    return priority;
}

void Lrm::removeNotNeededFspsForCcdMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    unsigned int numberOfDspToAllocate=2;
    UniqueFspAddresses neededUniqueFspAddresses;
    saveNeededFspsForCcdOrMcdBasedOnNOrTn(neededUniqueFspAddresses, numberOfDspToAllocate, fspAddresses, lcgId);    fspAddresses.clear();
    copy(neededUniqueFspAddresses.cbegin(), neededUniqueFspAddresses.cend(), back_inserter(fspAddresses));
    sortFspBasedPriorityForCcdMcdSelection(fspAddresses, lcgId);
}

SelectionDspResult Lrm::selectFspForEmptyDspForNbicMcd(unsigned int const lcgId) const
{
    SelectionDspResult result;
    FspAddresses fspAddresses;
    copyFspWithAtLeastThisNumberOfEmptyNAndTnWithDliRestrictions(fspAddresses, 1, lcgId);
    sortFspBasedPriorityForMcdSelection(fspAddresses, lcgId);
    removeNotNeededFspsForNbicMcd(fspAddresses, lcgId);
    if(!fspAddresses.empty())
    {
        setSelectionDspResult(result, fspAddresses.front());    }
    return result;
}
void Lrm::removeNotNeededFspsForNbicMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    UniqueFspAddresses neededUniqueFspAddresses;
    saveNeededFspsForCcdOrNbicMcdBasedOnNOrTnWithDliRestrictions(neededUniqueFspAddresses, fspAddresses, lcgId, 1);
    fspAddresses.clear();
    copy(neededUniqueFspAddresses.cbegin(), neededUniqueFspAddresses.cend(), back_inserter(fspAddresses));
    sortFspBasedPriorityForMcdSelection(fspAddresses, lcgId);
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
                && currentDsp.getNumberOfHsRachCfs()==0
                && canAFreeDliBeAllocatedInFsp(currentDsp.getFspAddress(), lcgId)
                && (currentDsp.getNyquistType() == NyquistType::Nyquist ||
                    (currentDsp.getNyquistType() == NyquistType::TurboNyquist && isThereSpaceForTnForMcdOrCcdConsideringPic(currentDsp.getFspAddress(),  lcgId)));
    });
    sortDspAddressesBasedOnCondition(dspAddresses, [&](Dsp const& dsp1, Dsp const& dsp2)
    {
        unsigned int priorityBasedOnHsupaCfsExistenceForDsp1 = (dsp1.getNumberOfHsupaCfs()==0) ? 2 : 1;
        unsigned int priorityBasedOnHsupaCfsExistenceForDsp2 = (dsp2.getNumberOfHsupaCfs()==0) ? 2 : 1;
        unsigned int numberOfNonDcdsOnFspOfDsp1(getNumberOfNonDcdsInFsp(dsp1.getFspAddress()));
        unsigned int numberOfNonDcdsOnFspOfDsp2(getNumberOfNonDcdsInFsp(dsp2.getFspAddress()));
        unsigned int priorityOfNumberOfDchUsersForDsp1 = (dsp1.getNumberOfHsupaCfs()==0) ? dsp1.getNumberOfDchUsers() : 0;
        unsigned int priorityOfNumberOfDchUsersForDsp2 = (dsp2.getNumberOfHsupaCfs()==0) ? dsp2.getNumberOfDchUsers() : 0;
        unsigned int priorityOrderCountForHsupaCfsForDsp1 = dsp1.getOrderCountOfCfAllocation();        unsigned int priorityOrderCountForHsupaCfsForDsp2 = dsp2.getOrderCountOfCfAllocation();
        unsigned int numberOfPrereservedHsupaCfsForDsp1 = dsp1.getNumberOfPreservedHsupaCfs();
        unsigned int numberOfPrereservedHsupaCfsForDsp2 = dsp2.getNumberOfPreservedHsupaCfs();
        bool result(false);        if(priorityBasedOnHsupaCfsExistenceForDsp1!=priorityBasedOnHsupaCfsExistenceForDsp2)
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
    copyFspWithAtLeastThisNumberOfEmptyNAndTnAndBelowMaxAmountOfNonDcds(fspAddresses, 1, lcgId);
    for(unsigned int fspAddress: fspAddresses)
    {
        ALBA_PRINT2(lcgId, fspAddress);
    }
    sortFspBasedPriorityForCcdMcdSelection(fspAddresses, lcgId);
    for(unsigned int fspAddress: fspAddresses)
    {
        ALBA_PRINT2(lcgId, fspAddress);
    }
    removeNotNeededFspsForCcdNbicMcd(fspAddresses, lcgId);
    return fspAddresses;
}
void Lrm::removeNotNeededFspsForCcdNbicMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    UniqueFspAddresses neededUniqueFspAddresses;    saveNeededFspsForCcdOrNbicMcdBasedOnNOrTnWithDliRestrictions(neededUniqueFspAddresses, fspAddresses, lcgId, 2);
    fspAddresses.clear();
    copy(neededUniqueFspAddresses.cbegin(), neededUniqueFspAddresses.cend(), back_inserter(fspAddresses));
    sortFspBasedPriorityForCcdMcdSelection(fspAddresses, lcgId);
    fixFspsForNbic(fspAddresses, lcgId);
}

void Lrm::fixFspsForNbic(FspAddresses& fspAddresses, unsigned int const lcgId) const{
    if(fspAddresses.size()==1)
    {
        Fsp const & fsp(m_addressToFspMap.at(fspAddresses[0]));        bool isFspValidBasedOnDliPoolRestrictions(canAFreeDliBeAllocatedInFsp(fsp.getAddress(), lcgId));
        if(!isFspValidBasedOnDliPoolRestrictions)
        {
            fspAddresses.clear();
        }
    }
    else if(fspAddresses.size()>=2)
    {

        Fsp const & fsp1(m_addressToFspMap.at(fspAddresses[0]));
        Fsp const & fsp2(m_addressToFspMap.at(fspAddresses[1]));
        bool isFspValidBasedOnDliPoolRestrictions1(canAFreeDliBeAllocatedInFsp(fsp1.getAddress(), lcgId));
        bool isFspValidBasedOnDliPoolRestrictions2(canAFreeDliBeAllocatedInFsp(fsp2.getAddress(), lcgId));
        if(!isFspValidBasedOnDliPoolRestrictions1 && !isFspValidBasedOnDliPoolRestrictions2)
        {
            fspAddresses.clear();
        }
        else if(!isFspValidBasedOnDliPoolRestrictions2)
        {
            swap(fspAddresses[0], fspAddresses[1]);
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
        unsigned int priorityBasedOnSharedLcgForFsp1(getPriorityBasedSharedLcgTnInPicSelection(fsp1, lcgId));
        unsigned int priorityBasedOnSharedLcgForFsp2(getPriorityBasedSharedLcgTnInPicSelection(fsp2, lcgId));
        unsigned int priorityForOneFreeDliFsp1(getNumberOfFreeDliPoolsOfFsp(fsp1.getAddress())==1 ? 2 : 1);
        unsigned int priorityForOneFreeDliFsp2(getNumberOfFreeDliPoolsOfFsp(fsp2.getAddress())==1 ? 2 : 1);
        unsigned int priorityForMasterTcomFsp1(fsp1.isMasterTcom() ? 2 : 1);
        unsigned int priorityForMasterTcomFsp2(fsp2.isMasterTcom() ? 2 : 1);
        unsigned int numberOfNonDcdsForFsp1(getNumberOfNonDcdsInFsp(fsp1.getAddress()));
        unsigned int numberOfNonDcdsForFsp2(getNumberOfNonDcdsInFsp(fsp2.getAddress()));
        unsigned int priorityForTnCountWithEmptyCfsFsp1(getPriorityBasedOnTnWithoutCfsForFspPicSelection(fsp1, lcgId));
        unsigned int priorityForTnCountWithEmptyCfsFsp2(getPriorityBasedOnTnWithoutCfsForFspPicSelection(fsp2, lcgId));
        bool result(false);        if(priorityBasedOnSharedLcgForFsp1!=priorityBasedOnSharedLcgForFsp2)
        {
            result = priorityBasedOnSharedLcgForFsp1>priorityBasedOnSharedLcgForFsp2;
        }        else if(priorityForOneFreeDliFsp1!=priorityForOneFreeDliFsp2)
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

unsigned int Lrm::getPriorityBasedSharedLcgTnInPicSelection(Fsp const& fsp, unsigned int const lcgId) const
{
    NyquistAndTurboNyquistCount emptyNAndTnCountOfSharedLcgInFsp = getNumberOfEmptyNAndTnOfFspAndLcg(fsp.getAddress(), m_hardwareConfigurationReference.getSharedLcgId());
    unsigned int priority=0;
    if(isSharedLcg(lcgId))
    {
        priority = 4;
    }
    else if(fsp.getSmType() == SmType::MSM)
    {
        if(emptyNAndTnCountOfSharedLcgInFsp.numberOfTurboNyquists==0)
        {
            priority = 3;
        }
        else
        {
            priority = 2;
        }
    }
    else
    {
        priority = 1;
    }
    return priority;
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
        Fsp const & currentFsp(m_addressToFspMap.at(currentFspAddress));
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
        Fsp const & currentFsp(m_addressToFspMap.at(currentFspAddress));
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
        Fsp const & currentFsp(m_addressToFspMap.at(currentFspAddress));
        NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNAndTnOfFspAndLcg(currentFsp.getAddress(), lcgId);
        unsigned int emptyTurboNyquists(emptyNAndTnCount.numberOfTurboNyquists);
        unsigned int emptyNyquists(emptyNAndTnCount.numberOfNyquists);
        while(numberOfDspToAllocate>0 && emptyNyquists>0)
        {
            isFspNeeded=true; numberOfDspToAllocate--; emptyNyquists--;
        }
        while(numberOfDspToAllocate>0 && emptyTurboNyquists>0 && isThereSpaceForTnForMcdOrCcdConsideringPic(currentFsp.getAddress(),  lcgId))
        {
            isFspNeeded=true; numberOfDspToAllocate--; emptyTurboNyquists--;
        }
        if(isFspNeeded)        {
            neededUniqueFspAddresses.emplace(currentFspAddress);
        }
    }}

void Lrm::saveNeededFspsForCcdOrNbicMcdBasedOnNOrTnWithDliRestrictions(
        UniqueFspAddresses & neededUniqueFspAddresses,
        FspAddresses const& fspAddresses,
        unsigned int const lcgId,
        unsigned int const numberOfDspCcdAndMcd) const
{
    unsigned int numberOfDspToAllocate=numberOfDspCcdAndMcd;
    bool isFspValidBasedInDliPoolRestrictionsAlreadyAllocated(false);
    for(unsigned int const currentFspAddress : fspAddresses)
    {
        bool isFspNeeded(false);        Fsp const & currentFsp(m_addressToFspMap.at(currentFspAddress));
        bool isFspValidBasedOnDliPoolRestrictions(canAFreeDliBeAllocatedInFsp(currentFsp.getAddress(), lcgId));
        NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNAndTnOfFspAndLcg(currentFsp.getAddress(), lcgId);
        unsigned int emptyTurboNyquists(emptyNAndTnCount.numberOfTurboNyquists);
        unsigned int emptyNyquists(emptyNAndTnCount.numberOfNyquists);
        ALBA_PRINT5(currentFspAddress, emptyTurboNyquists, emptyNyquists, isFspValidBasedInDliPoolRestrictionsAlreadyAllocated, isFspValidBasedOnDliPoolRestrictions);
        while(numberOfDspToAllocate>0 && emptyNyquists>0)
        {
            if(numberOfDspToAllocate==2 || (numberOfDspToAllocate==1 && (isFspValidBasedInDliPoolRestrictionsAlreadyAllocated || isFspValidBasedOnDliPoolRestrictions)))
            {
                ALBA_PRINT5(hex<<currentFspAddress, isFspValidBasedInDliPoolRestrictionsAlreadyAllocated, isFspValidBasedOnDliPoolRestrictions, numberOfDspToAllocate, emptyNyquists);
                if(isFspValidBasedOnDliPoolRestrictions)
                {
                    isFspValidBasedInDliPoolRestrictionsAlreadyAllocated = true;
                }
                isFspNeeded=true; numberOfDspToAllocate--; emptyNyquists--;
            }
            else
            {
                break;
            }
        }
        while(numberOfDspToAllocate>0 && emptyTurboNyquists>0 && isThereSpaceForTnForMcdOrCcdConsideringPic(currentFsp.getAddress(),  lcgId))
        {
            if(numberOfDspToAllocate==2 || (numberOfDspToAllocate==1 && (isFspValidBasedInDliPoolRestrictionsAlreadyAllocated || isFspValidBasedOnDliPoolRestrictions)))
            {
                ALBA_PRINT5(hex<<currentFspAddress, isFspValidBasedInDliPoolRestrictionsAlreadyAllocated, isFspValidBasedOnDliPoolRestrictions, numberOfDspToAllocate, emptyTurboNyquists);
                if(isFspValidBasedOnDliPoolRestrictions)
                {
                    isFspValidBasedInDliPoolRestrictionsAlreadyAllocated = true;
                }
                isFspNeeded=true; numberOfDspToAllocate--; emptyTurboNyquists--;
            }
            else
            {
                break;
            }
        }
        if(isFspNeeded)
        {            neededUniqueFspAddresses.emplace(currentFspAddress);
        }
    }
}
bool Lrm::isThereSpaceForTnForMcdOrCcdConsideringPic(unsigned int const fspAddress, unsigned int const lcgId) const
{
    Fsp const& fsp(m_addressToFspMap.at(fspAddress));
    bool isThereSpace(false);
    if(isSharedLcg(lcgId))
    {
        if(fsp.getSmType() == SmType::MSM)
        {
            NyquistAndTurboNyquistCount emptyNAndTnCountInMsmOfLcg = getNumberOfEmptyNAndTnInMsmOfLcg(lcgId);
            isThereSpace=canTnBeAllocatedBasedOnPicAndNumberOfTnToBeAllocated(emptyNAndTnCountInMsmOfLcg, 1, lcgId);
        }
        else
        {
            isThereSpace = true;
        }
    }
    else
    {        NyquistAndTurboNyquistCount emptyNAndTnCountOfLcg = getNumberOfEmptyNAndTnOfLcg(lcgId);
        isThereSpace=canTnBeAllocatedBasedOnPicAndNumberOfTnToBeAllocated(emptyNAndTnCountOfLcg, 1, lcgId);
    }
    return isThereSpace;}

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

void Lrm::copyFspWithAtLeastThisNumberOfEmptyNAndTnAndBelowMaxAmountOfNonDcds(FspAddresses& fspAddresses, unsigned int const requiredEmptyCount, unsigned int const lcgId) const
{
    copyFspAddressesThatSatisfiesThisCondition(fspAddresses, [&](Fsp const& currentFsp)
    {
        NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNAndTnOfFspAndLcg(currentFsp.getAddress(), lcgId);
        unsigned int numberOfNonDcdsOfFsp(getNumberOfNonDcdsInFsp(currentFsp.getAddress()));
        return (emptyNAndTnCount.numberOfNyquists+emptyNAndTnCount.numberOfTurboNyquists)>=requiredEmptyCount
                && numberOfNonDcdsOfFsp<m_maxAmountOfNonDcdsPerFsp-1;
    });
}
void Lrm::copyFspWithAtLeastThisNumberOfEmptyNAndTnWithDliRestrictions(FspAddresses& fspAddresses, unsigned int const requiredEmptyCount, unsigned int const lcgId) const
{
    copyFspAddressesThatSatisfiesThisCondition(fspAddresses, [&](Fsp const& currentFsp)    {
        NyquistAndTurboNyquistCount emptyNAndTnCount = getNumberOfEmptyNAndTnOfFspAndLcg(currentFsp.getAddress(), lcgId);
        bool isNumberOfEmptyDspsSufficient((emptyNAndTnCount.numberOfNyquists+emptyNAndTnCount.numberOfTurboNyquists)>=requiredEmptyCount);
        bool isDliPoolAvailableInFsp(canAFreeDliBeAllocatedInFsp(currentFsp.getAddress(), lcgId));
        unsigned int numberOfNonDcdsOfFsp(getNumberOfNonDcdsInFsp(currentFsp.getAddress()));
        return isNumberOfEmptyDspsSufficient && isDliPoolAvailableInFsp && numberOfNonDcdsOfFsp<m_maxAmountOfNonDcdsPerFsp-1;
    });
}
void Lrm::copyFspWithAtLeastThisNumberOfTnDcdsWithoutHsRachCfsWithDliRestrictions(FspAddresses& fspAddresses, unsigned int const lcgId) const
{
    copyFspAddressesThatSatisfiesThisCondition(fspAddresses, [&](Fsp const& currentFsp)    {
        bool result(false);
        bool isDliPoolAvailableInFsp(canAFreeDliBeAllocatedInFsp(currentFsp.getAddress(), lcgId));
        if(isDliPoolAvailableInFsp)
        {
            DspAddresses const& dspAddresses(currentFsp.getDspAddresses());
            for(unsigned int const dspAddress : dspAddresses)
            {
                Dsp& currentDsp(m_addressToDspMap.at(dspAddress));
                DspMode mode(currentDsp.getMode());
                if(currentDsp.getLcgId()==lcgId
                        && mode==DspMode::NyquistDedicatedChannelDevice
                        && currentDsp.getNyquistType() == NyquistType::TurboNyquist
                        && currentDsp.getNumberOfHsRachCfs()==0)
                {
                    result=true;                    break;
                }
            }
        }        return result;
    });
}

NyquistAndTurboNyquistCount Lrm::getNumberOfEmptyNAndTnOfFspAndLcg(unsigned int const fspAddress, unsigned int const lcgId) const
{
    NyquistAndTurboNyquistCount result{0, 0};
    Fsp const & fsp(m_addressToFspMap.at(fspAddress));
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
    Fsp const & fsp(m_addressToFspMap.at(fspAddress));
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
        Dsp const & currentDsp(addressToDspPair.second);
        Fsp const & currentFsp(m_addressToFspMap.at(currentDsp.getFspAddress()));
        if(currentDsp.getLcgId()==lcgId && currentDsp.isEmpty() && currentFsp.getSmType()==SmType::MSM)
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
        Dsp const & currentDsp(addressToDspPair.second);
        if(currentDsp.getLcgId()==lcgId && currentDsp.isEmpty())
        {
            incrementNAndTnCountBasedOnNyquistType(result, currentDsp.getNyquistType());
        }
    }
    return result;
}

unsigned int Lrm::getNumberOfNonDcdsInFsp(unsigned int const fspAddress) const
{
    unsigned int resultCount=0;
    Fsp const & fsp(m_addressToFspMap.at(fspAddress));    DspAddresses const& dspAddresses(fsp.getDspAddresses());
    for(unsigned int const dspAddress : dspAddresses)
    {
        Dsp& currentDsp(m_addressToDspMap.at(dspAddress));        DspMode mode(currentDsp.getMode());
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
    Fsp const & fsp(m_addressToFspMap.at(fspAddress));
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
        Fsp const & currentFsp(addressToFspPair.second);
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
        Dsp const & currentDsp(addressToDspPair.second);
        unsigned int const currentDspAddress(currentDsp.getAddress());
        if(condition(currentDsp))
        {
            dspAddresses.emplace_back(currentDspAddress);
        }
    }
}

void Lrm::copyDspAddressesInFspThatSatisfiesThisCondition(DspAddresses & dspAddressesForLcgInFsp, unsigned int fspAddress, DspBooleanCondition const& condition) const
{
    Fsp const & fsp(m_addressToFspMap.at(fspAddress));
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
        Fsp const & currentFsp(addressToFspPair.second);
        unsigned int const currentFspAddress(currentFsp.getAddress());
        copyUsedDliPoolsOnFsp(usedDliPools, currentFspAddress);
    }
}

void Lrm::copyUsedDliPoolsOnFsp(DliPools & usedDliPools, unsigned int const fspAddress) const
{
    Fsp const & fsp(m_addressToFspMap.at(fspAddress));
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
        Fsp const & currentFsp(addressToFspPair.second);
        unsigned int const currentFspAddress(currentFsp.getAddress());
        if(currentFspAddress != fspAddressOfSkippedFsp)
        {
            copyUsedDliPoolsOnFsp(usedDliPools, currentFspAddress);
        }
    }
}

bool Lrm::canAFreeDliBeAllocatedInFsp(unsigned int const fspAddress, unsigned int const lcgId) const
{
    DliPools freeDliPools;
    copyFreeDliPools(freeDliPools);
    DliPools usedDliPools;
    copyUsedDliPoolsOnFsp(usedDliPools, fspAddress);
    bool result(false);
    bool isSharedLcgId(isSharedLcg(lcgId));
    Fsp const & fsp(m_addressToFspMap.at(fspAddress));
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

    return (getNumberOfUnallocatedPicPoolsForLcg(lcgId) + numberOfTurboNyquistToBeUsed) <= nAndTnCountInMsmOfLcg.numberOfTurboNyquists;
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

unsigned int Lrm::getNumberOfUnallocatedPicPoolsForLcg(unsigned int const lcgId) const
{
    return m_lcgToUnallocatedPicPools.count(lcgId)>0 ? m_lcgToUnallocatedPicPools.at(lcgId) : 0;
}

}