#pragma once

#include <LargeSorter/AlbaLargeSorterConfiguration.hpp>
#include <string>

using std::string;

namespace tcomToolsBackend
{

struct BtsLogSorterConfiguration
{
    string m_condition;
    alba::AlbaLargeSorterConfiguration m_configurationWithPcTime;
    alba::AlbaLargeSorterConfiguration m_configurationWithoutPcTime;
    string m_pathOfLogsWithoutPcTime;
    string m_pathOfStartupLog;
};

}
