#include <LargeSorter/AlbaLargeSorterConfiguration.hpp>
#include <string>

#define CONFIGURATION_FILE R"(C:\APRG\TcomTools\TcomTools\configuration\configuration.txt)"
using std::string;

namespace tcomToolsGui
{

struct TcomToolsConfiguration
{
    TcomToolsConfiguration();
    void loadConfigurationFromFile();
    void saveConfigurationToFile() const;
    bool isExtractStepOn;
    bool isCombineAndSortStepOn;
    bool isGrepStepOn;    bool isCropStepOn;
    bool isGrepTcomEnabled;
    bool isGrepErrEnabled;
    bool isGrepErrWrnTcomEnabled;    bool isGrepBtsStatusEnabled;
    bool isGrepRecoveryEnabled;
    bool isGrepAllocationEnabled;
    bool isGrepFaultEnabled;
    bool isGrepLrmEnabled;
    bool isGrepGrmEnabled;
    bool isGrepToamEnabled;
    bool isGrepTupcEnabled;
    bool isGrepRlhEnabled;
    bool isGrepCchhBchsenderEnabled;
    bool isGrepHschEnabled;
    bool isGrepDmgrEnabled;
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