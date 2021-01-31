#pragma once

#include <HardwareConfiguration.hpp>

#include <functional>
#include <map>
#include <set>
#include <vector>

namespace alba
{

struct NyquistAndTurboNyquistCount
{
    unsigned int numberOfNyquists;    unsigned int numberOfTurboNyquists;
};

struct SelectionDspResult{
    SelectionDspResult();
    bool isSelectionSuccessful;
    bool isNbicAllocated;
    unsigned int address;
    unsigned int dliPool;
};

struct SelectionDspResultForCcdAndMcd
{
    SelectionDspResultForCcdAndMcd();
    bool isSelectionSuccessful;
    bool isNbicAllocated;
    unsigned int ccdAddress;
    unsigned int mcdAddress;
    unsigned int dliPool;
};

struct FspPairDetails
{
    FspPairDetails(unsigned int const firstFspAddress, unsigned int const secondFspAddress, unsigned int const priority);
    unsigned int firstFspAddress;
    unsigned int secondFspAddress;
    unsigned int priority;
};

using FspPairsDetails = std::vector<FspPairDetails>;
using DspBooleanCondition = std::function<bool(Dsp const&)>;
using DspComparisonCondition = std::function<bool(Dsp const&, Dsp const&)>;
using FspBooleanCondition = std::function<bool(Fsp const&)>;
using FspComparisonCondition = std::function<bool(Fsp const&, Fsp const&)>;
using FspPairDetailsComparisonCondition = std::function<bool(FspPairDetails const&, FspPairDetails const&)>;
using FspPairDetailsCondition = std::function<bool(FspPairDetails const&)>;
using DliPools = std::set<unsigned int>;

class Lrm
{
public:    Lrm(HardwareConfiguration& hardwareConfiguration);
    void setHibernationCommissioned(bool const isHibernationCommissioned);
    void setNumberOfUnallocatedPicPoolsPerLcg(unsigned int const lcgId, unsigned int const numberOfPicPools);
    void clearLcgToUnallocatedPicPools(unsigned int const lcgId);    void setMaxAmountOfNonDcdsPerFsp(unsigned int const maxAmountOfNonDcdsPerFsp);

    SelectionDspResult allocateMcdForLcgIdAccordingToMark(unsigned int const lcgId);
    SelectionDspResultForCcdAndMcd allocateCcdMcdForLcgIdAccordingToMark(unsigned int const lcgId);
    SelectionDspResult allocateNbicMcdForLcgIdAccordingToMark(unsigned int const lcgId);
    SelectionDspResultForCcdAndMcd allocateCcdNbicMcdForLcgIdAccordingToMark(unsigned int const lcgId);
    SelectionDspResult allocatePicForLcgIdAccordingToMark(unsigned int const lcgId);


private:
    //MCD
    SelectionDspResult selectFspForEmptyDspForMcd(unsigned int const lcgId) const;
    void sortFspBasedPriorityForMcdSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void sortFspBasedPriorityForMcdSelection2(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void sortFspBasedPriorityForNbicMcdSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void sortFspBasedPriorityForNbicMcdSelection2(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    unsigned int getPriorityBasedOnNAndTnCountForFspMcdSelection(Fsp const& fsp, unsigned int const lcgId) const;
    unsigned int getPriorityBasedSharedLcgFspMcdSelection(Fsp const& fsp, unsigned int const lcgId) const;
    SelectionDspResult selectNonEmptyDspToClearForMcd(unsigned int const lcgId) const;    void removeNotNeededFspsForMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const;

    //CCD+MCD
    FspAddresses selectFspsForCcdMcd(unsigned int const lcgId) const;
    FspAddresses selectFspsForCcdMcd2(unsigned int const lcgId) const;
    void sortFspBasedPriorityForCcdMcdSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    unsigned int getPriorityBasedOnNAndTnCountForFspCcdMcdSelection(Fsp const& fsp, unsigned int const lcgId) const;
    void removeNotNeededFspsForCcdMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    //NBIC MCD
    SelectionDspResult selectFspForEmptyDspForNbicMcd(unsigned int const lcgId) const;
    void removeNotNeededFspsForNbicMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const;    void fixFspsForNbic(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    SelectionDspResult selectNonEmptyDspToClearForNbicMcd(unsigned int const lcgId) const;

    //CCD NBIC MCD
    FspAddresses selectFspsForCcdNbicMcd(unsigned int const lcgId) const;
    FspAddresses selectFspsForCcdNbicMcd2(unsigned int const lcgId) const;
    void removeNotNeededFspsForCcdNbicMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const;

    //PIC    SelectionDspResult selectFspForPic(unsigned int const lcgId) const;
    void sortFspBasedPriorityForPicSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    unsigned int getPriorityBasedSharedLcgTnInPicSelection(Fsp const& fsp, unsigned int const lcgId) const;
    unsigned int getPriorityBasedOnTnWithoutCfsForFspPicSelection(Fsp const& fsp, unsigned int const lcgId) const;
    //Common
    //void saveNeededFspsForCcdOrMcdBasedOnNyquist(UniqueFspAddresses & neededUniqueFspAddresses, unsigned int& numberOfDspToAllocate, FspAddresses const& fspAddresses, unsigned int const lcgId) const;
    //void saveNeededFspsForCcdOrMcdBasedOnTurboNyquist(UniqueFspAddresses & neededUniqueFspAddresses, unsigned int& numberOfDspToAllocate, FspAddresses const& fspAddresses, unsigned int const lcgId) const;
    unsigned int getPriorityBasedOnLessUsersAndHsupaCfsForDsp(Dsp const& dsp) const;
    void saveNeededFspsForCcdOrMcdBasedOnNOrTn(UniqueFspAddresses & neededUniqueFspAddresses, unsigned int& numberOfDspCcdAndMcd, FspAddresses const& fspAddresses, unsigned int const lcgId) const;
    void saveNeededFspsForCcdOrNbicMcdBasedOnNOrTnWithDliRestrictions(UniqueFspAddresses & neededUniqueFspAddresses, FspAddresses const& fspAddresses, unsigned int const lcgId, unsigned int const numberOfDspToAllocate) const;
    bool isThereSpaceForTnForMcdOrCcdConsideringPic(unsigned int const fspAddress, unsigned int const numberOfMcdOrCcd, unsigned int const lcgId) const;
    SelectionDspResult selectEmptyDspPriotizingNyquistTypeAndAddressInFsp(unsigned int const lcgId, unsigned int const fspAddress) const;
    SelectionDspResult selectTnPriotizingLessUsersAndHsupaCfsInFsp(unsigned int const lcgId, unsigned int const fspAddress) const;
    void copyFspWithAtLeastThisNumberOfEmptyNAndTnAndBelowMaxAmountOfNonDcds(FspAddresses& fspAddresses, unsigned int const requiredEmptyCount, unsigned int const lcgId) const;    void copyFspWithAtLeastThisNumberOfEmptyNAndTnWithDliRestrictions(FspAddresses& fspAddresses, unsigned int const requiredEmptyCount, unsigned int const lcgId) const;
    void copyFspWithAtLeastThisNumberOfTnDcdsWithoutHsRachCfsWithDliRestrictions(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    NyquistAndTurboNyquistCount getNumberOfEmptyNAndTnOfFspAndLcg(unsigned int const fspAddress, unsigned int const lcgId) const;
    NyquistAndTurboNyquistCount getNumberOfNAndTnWithoutCfsOfFspAndLcg(unsigned int const fspAddress, unsigned int const lcgId) const;    NyquistAndTurboNyquistCount getNumberOfEmptyNAndTnOfLcg(unsigned int const lcgId) const;
    NyquistAndTurboNyquistCount getNumberOfEmptyNAndTnInMsmOfLcg(unsigned int const lcgId) const;
    unsigned int getNumberOfNonDcdsInFsp(unsigned int const fspAddress) const;
    unsigned int getNumberOfFreeDliPoolsOfFsp(unsigned int const fspAddress) const;

    void copyFspAddressesThatSatisfiesThisCondition(FspAddresses & fspAddresses, FspBooleanCondition const& condition) const;
    void sortFspAddressesBasedOnCondition(FspAddresses & fspAddresses, FspComparisonCondition const& condition) const;

    void copyDspAddressesThatSatisfiesThisCondition(DspAddresses & dspAddressesForLcgInFsp, DspBooleanCondition const& condition) const;
    void copyDspAddressesInFspThatSatisfiesThisCondition(DspAddresses & dspAddressesForLcgInFsp, unsigned int fspAddress, DspBooleanCondition const& condition) const;
    void sortDspAddressesBasedOnCondition(DspAddresses & dspAddressesForLcgInFsp, DspComparisonCondition const& condition) const;

    void setSelectionDspResult(SelectionDspResult& selectionDspResultReference, unsigned int const fspAddress) const;
    void incrementNAndTnCountBasedOnNyquistType(NyquistAndTurboNyquistCount& countReference, NyquistType const nyquistType) const;

    bool canTnBeAllocatedBasedOnPicAndNumberOfTnToBeAllocated(NyquistAndTurboNyquistCount const& nAndTnCountInMsmOfLcg, unsigned int const numberOfTurboNyquistToBeUsed, unsigned int const lcgId) const;
    bool isSharedLcg(unsigned int const lcgId) const;

    unsigned int getFreeDliToAllocateForDsp(unsigned int const dspAddress) const;
    unsigned int getFreeDliBasedOnSameFsp(Dsp const& dsp, DliPools const& freeDliPools) const;
    unsigned int getFreeDliBasedOnOtherFsps(Dsp const& dsp, DliPools const& freeDliPools) const;
    void copyFreeDliPools(DliPools & freeDliPools) const;
    void copyUsedDliPools(DliPools & usedDliPools) const;
    void copyUsedDliPoolsOnFsp(DliPools & usedDliPools, unsigned int const fspAddress) const;
    void copyUsedDliPoolsOnOtherFspsExceptThisFsp(DliPools & usedDliPools, unsigned int const fspAddressOfSkippedFsp) const;
    unsigned int getConflictingDliPoolForThisDli(unsigned int const dliPool) const;
    unsigned int getLeastConflictingDliPoolForThisDli(unsigned int const dliPool) const;
    bool canAFreeDliBeAllocatedInFsp(unsigned int const fspAddress, unsigned int const lcgId) const;

    void copyAllFspPairs(FspPairsDetails & fspPairsDetails) const;
    void sortFspPairsForCcdMcdSelection(FspPairsDetails & fspPairsDetails) const;
    void removeFspPairsForCcdMcdSelection(FspPairsDetails & fspPairsDetails, unsigned int const lcgId) const;
    void removeFspPairsForCcdNbicMcdSelection(FspPairsDetails & fspPairsDetails, unsigned int const lcgId) const;
    void sortFspPairsBasedOnCondition(FspPairsDetails & fspPairsDetails, FspPairDetailsComparisonCondition const& condition) const;
    void removeFspPairsBasedOnCondition(FspPairsDetails & fspPairsDetails, FspPairDetailsCondition const& condition) const;
    void updatePriorityForAllFspPairs(FspPairsDetails & fspPairsDetail, unsigned int const lcgId) const;
    unsigned int getPriorityForFspPair(FspPairDetails const& fspPairDetails, unsigned int const lcgId) const;

    void changeModeForCcdAndUpdateDspDetails(SelectionDspResultForCcdAndMcd const& selectionDspResultForCcdAndMcd);
    void changeModeForMcdAndUpdateDspDetails(SelectionDspResultForCcdAndMcd const& selectionDspResultForCcdAndMcd);
    void changeModeAndUpdateDspDetails(SelectionDspResult const& selectionDspResult, DspMode const dspMode);    void changeMode(Dsp& dspToChange, DspMode const dspMode);
    void setDliIfNeeded(Dsp& dspToChange, DspMode const dspMode, bool const isNbic, unsigned int const dliPool);
    void setAsNbicIfNeeded(Dsp& dspToChange, DspMode const dspMode, bool const isNbic);
    unsigned int getNumberOfUnallocatedPicPoolsForLcg(unsigned int const lcgId) const;

    bool m_isHibernationCommissioned;
    unsigned int m_maxAmountOfNonDcdsPerFsp;
    std::map<unsigned int, bool> m_lcgToUnallocatedPicPools;
    HardwareConfiguration& m_hardwareConfigurationReference;
    AddressToDspMap& m_addressToDspMap;
    AddressToFspMap& m_addressToFspMap;
};

}
