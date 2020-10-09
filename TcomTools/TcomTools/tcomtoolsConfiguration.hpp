#include <string>

using std::string;

struct tcomtoolsConfiguration
{
    bool isExtractStepOn;
    bool isCombineAndSortStepOn;
    bool isGrepStepOn;
    bool isCropStepOn;
    string acceptedFilesGrepCondition;
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
    bool isGrepCchhBchsenderEnabled;
    bool isGrepHschEnabled;
    bool isGrepDmgrEnabled;
    string otherGrepCondition;
    string prioritizedLogPrint;
};
