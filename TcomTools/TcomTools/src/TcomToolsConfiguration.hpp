#pragma once

#include <BtsLogSorterConfiguration.hpp>
#include <LargeSorter/AlbaLargeSorterConfiguration.hpp>

#include <string>

namespace tcomToolsGui
{
struct TcomToolsConfiguration
{
    TcomToolsConfiguration();
    std::string getGrepCondition() const;
    std::string getGrepFileName() const;
    void determineVariousLocationsBasedOnCurrentLocation();
    void loadConfigurationFromFile();
    void saveConfigurationToFile() const;
    bool isExtractStepOn;    bool isCombineAndSortStepOn;
    bool isGrepStepOn;
    bool isCropStepOn;
    bool isGrepTcomEnabled;    bool isGrepErrEnabled;
    bool isGrepErrWrnNoSpamEnabled;
    bool isGrepBtsStatusEnabled;
    bool isGrepRecoveryEnabled;
    bool isGrepAllocationEnabled;
    bool isGrepFaultEnabled;
    bool isGrepLrmEnabled;
    bool isGrepGrmEnabled;
    bool isGrepToamEnabled;
    bool isGrepTupcEnabled;
    bool isGrepRlhEnabled;
    bool isGrepCchhEnabled;
    bool isGrepCchhSdlEnabled;
    bool isGrepHschEnabled;
    bool isGrepDmgrEnabled;
    std::string grepConditionForTcom;
    std::string grepConditionForErr;
    std::string grepConditionForErrWrn;
    std::string grepConditionForBtsStatus;
    std::string grepConditionForRecovery;
    std::string grepConditionForAllocation;
    std::string grepConditionForFault;
    std::string grepConditionForLrm;
    std::string grepConditionForGrm;
    std::string grepConditionForToam;
    std::string grepConditionForTupc;
    std::string grepConditionForRlh;
    std::string grepConditionForCchh;
    std::string grepConditionForCchhSdl;
    std::string grepConditionForHsch;
    std::string grepConditionForDmgr;
    std::string inputFileOrDirectory;
    std::string extractGrepCondition;
    std::string acceptedFilesGrepCondition;
    std::string otherGrepCondition;
    std::string prioritizedLogPrint;
    double cropSize;
    tcomToolsBackend::BtsLogSorterConfiguration btsLogSorterConfiguration;
    std::string configurationFileLocation;
    std::string locationOf7zExecutable;
};

}