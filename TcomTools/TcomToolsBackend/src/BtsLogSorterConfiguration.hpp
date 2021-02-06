#pragma once

#include <LargeSorter/AlbaLargeSorterConfiguration.hpp>

#include <string>

namespace tcomToolsBackend
{

struct BtsLogSorterConfiguration
{
    std::string m_condition;
    alba::AlbaLargeSorterConfiguration m_configurationWithPcTime;
    alba::AlbaLargeSorterConfiguration m_configurationWithoutPcTime;
    std::string m_pathOfLogsWithoutPcTime;
    std::string m_pathOfStartupLog;
};

}
