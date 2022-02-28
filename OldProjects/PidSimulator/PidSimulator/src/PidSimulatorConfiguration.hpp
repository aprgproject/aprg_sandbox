#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <map>

namespace alba
{

struct PidSimulatorConfiguration
{
    using StringToStringMap = std::map<std::string, std::string>;
    PidSimulatorConfiguration(stringHelper::strings const& argumentsInMain);
    void saveArgumentValues(StringToStringMap & argumentsToValuesMap);
    void processArgumentsWithEqualDelimeter(StringToStringMap & argumentsToValuesMap, stringHelper::strings const& argumentsInMain);
    void processOneArgumentWithEqualDelimeter(StringToStringMap & argumentsToValuesMap, std::string const& argument);
    void print() const;
    unsigned int numberOfLoopsOfPeriodicInputDemand;
    unsigned int amplitudeOfInputDemand;
    unsigned int numberOfSamplesOfInputDemandInOnePeriod;
    int addedOffsetOfInputDemand;
    double targetInPidCalculation;
    double maxCellTxPower;
    double kp;
    double ki;
    double kd;
    std::string inputType;
    std::string machsModelType;
};

}
