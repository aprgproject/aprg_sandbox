#pragma once

#include <String/AlbaStringHelper.hpp>

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

    double kp;
    double ki;
    double kd;
    unsigned int numberOfLoopsOfPeriodicInput;
    unsigned int amplitudeOfInput;
    unsigned int numberOfSamplesOfInputInOnePeriod;
    int addedOffsetOfInput;
    double targetInPidCalculation;
    std::string inputType;
};

}
