#pragma once

#include <LargeSorter/AlbaLargeSorterConfiguration.hpp>

#include <string>

namespace wcdmaToolsBackend
{

struct BtsLogSorterConfiguration
{
    std::string m_condition;
    std::string m_pathOfTempFiles;
    alba::AlbaLargeSorterConfiguration m_configurationWithPcTime;
    alba::AlbaLargeSorterConfiguration m_configurationWithoutPcTime;
};

}
