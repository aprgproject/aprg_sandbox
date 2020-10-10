#pragma once

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
    bool isGrepErrWrnTcomEnabled;
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
    bool isGrepChEnabled;
    bool isGrepHschEnabled;
    bool isGrepDmgrEnabled;
    string grepConditionForTcom;
    string grepConditionForErr;
    string grepConditionForErrWrnTcom;
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
    string grepConditionForCh;
    string grepConditionForHsch;
    string grepConditionForDmgr;
    string inputFileOrDirectory;
    string extractGrepCondition;
    string acceptedFilesGrepCondition;
    string otherGrepCondition;
    string prioritizedLogPrint;
    string pathOfLogsWithoutPcTime;
    alba::AlbaLargeSorterConfiguration sorterConfigurationWithPcTime;
    alba::AlbaLargeSorterConfiguration sorterConfigurationWithoutPcTime;
};

}
