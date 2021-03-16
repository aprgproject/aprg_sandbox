#pragma once

#include <BtsLogSorterConfiguration.hpp>
#include <LargeSorter/AlbaLargeSorterConfiguration.hpp>

#include <unordered_map>
#include <string>

namespace wcdmaToolsGui{

struct WcdmaToolsConfiguration
{
    using NameToValueMap = std::unordered_map<std::string, std::string>;
    WcdmaToolsConfiguration();
    void loadDefaultConfigurationFile();
    void saveToConfigurationFile() const;
    std::string getGrepCondition() const;
    std::string getGrepFileName() const;
    std::string getSortedFileName() const;
    void determineVariousLocationsBasedOnCurrentLocation();
    void loadConfigurationFromFile(std::string const& filePath);
    void copyNamesAndValuesFromFile(NameToValueMap & nameToValueMap, std::string const& filePath);
    void loadNamesAndValues(NameToValueMap & nameToValueMap);
    void addConditionIntoGrepCondition(std::string & condition, bool const isGrepEnabled, std::string const& grepCondition) const;
    void addGrepIntoFileName(std::string & wholeFileName, bool const isGrepEnabled, std::string const& grepName) const;
    bool isExtractStepOn;
    bool isCombineAndSortStepOn;
    bool isGrepStepOn;
    bool isCropStepOn;
    bool isFilterSubStepOn;
    bool isGrepTcomEnabled;
    bool isGrepErrEnabled;
    bool isGrepErrWrnNoSpamEnabled;    bool isGrepBtsStatusEnabled;
    bool isGrepRecoveryEnabled;
    bool isGrepAllocationEnabled;
    bool isGrepFaultEnabled;
    bool isGrepLrmEnabled;
    bool isGrepGrmEnabled;
    bool isGrepToamEnabled;
    bool isGrepTupcEnabled;
    bool isGrepRlhEnabled;
    bool isGrepCchhEnabled;
    bool isGrepBchsenderEnabled;
    bool isGrepHschEnabled;
    bool isGrepDmgrEnabled;
    bool isGrepCodecEnabled;
    bool isGrepLtcomEnabled;
    bool isGrepLomEnabled;
    bool isGrepRakeEnabled;
    bool isGrepPicEnabled;
    bool isGrepHsdpaEnabled;
    bool isGrepHsTupEnabled;
    bool isGrepHsupaL2Enabled;
    std::string grepConditionForTcom;
    std::string grepConditionForErr;
    std::string grepConditionForErrWrn;    std::string grepConditionForBtsStatus;
    std::string grepConditionForRecovery;
    std::string grepConditionForAllocation;
    std::string grepConditionForFault;
    std::string grepConditionForLrm;
    std::string grepConditionForGrm;
    std::string grepConditionForToam;
    std::string grepConditionForTupc;
    std::string grepConditionForRlh;
    std::string grepConditionForCchh;
    std::string grepConditionForBchsender;
    std::string grepConditionForHsch;
    std::string grepConditionForDmgr;
    std::string grepConditionForCodec;
    std::string grepConditionForLtcom;
    std::string grepConditionForLom;
    std::string grepConditionForRake;
    std::string grepConditionForPic;
    std::string grepConditionForHsdpa;
    std::string grepConditionForHsTup;
    std::string grepConditionForHsupaL2;
    std::string inputFileOrDirectory;
    std::string extractGrepCondition;
    std::string acceptedFilesGrepCondition;
    std::string filterGrepCondition;
    std::string otherGrepCondition;
    std::string prioritizedLogCondition;
    double cropSize;
    wcdmaToolsBackend::BtsLogSorterConfiguration btsLogSorterConfiguration;
    std::string configurationFileLocation;
    std::string defaultConfigurationFileLocation;
    std::string locationOf7zExecutable;
};

}
