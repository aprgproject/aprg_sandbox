#pragma once

#include <BtsLogSorterConfiguration.hpp>
#include <LargeSorter/AlbaLargeSorterConfiguration.hpp>
#include <string>

#define CONFIGURATION_FILE R"(C:\APRG\TcomTools\TcomTools\configuration\configuration.txt)"

using std::string;

namespace tcomToolsGui
{

struct TcomToolsConfiguration
{
    TcomToolsConfiguration();
    string getGrepCondition() const;
    string getGrepFileName() const;
    void loadConfigurationFromFile();
    void saveConfigurationToFile() const;
    bool isExtractStepOn;
    bool isCombineAndSortStepOn;
    bool isGrepStepOn;
    bool isCropStepOn;
    bool isGrepTcomEnabled;
    bool isGrepErrEnabled;
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
    string grepConditionForTcom;
    string grepConditionForErr;
    string grepConditionForErrWrn;
    string grepConditionForBtsStatus;
    string grepConditionForRecovery;
    string grepConditionForAllocation;
    string grepConditionForFault;
    string grepConditionForLrm;
    string grepConditionForGrm;
    string grepConditionForToam;
    string grepConditionForTupc;
    string grepConditionForRlh;
    string grepConditionForCchh;
    string grepConditionForCchhSdl;
    string grepConditionForHsch;
    string grepConditionForDmgr;
    string inputFileOrDirectory;
    string extractGrepCondition;
    string acceptedFilesGrepCondition;
    string otherGrepCondition;
    string prioritizedLogPrint;
    double cropSize;
    tcomToolsBackend::BtsLogSorterConfiguration btsLogSorterConfiguration;
};

}
