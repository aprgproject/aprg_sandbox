#pragma once

#include <LargeSorter/AlbaLargeSorterConfiguration.hpp>

#include <string>

namespace wcdmaToolsBackend
{

struct BtsLogSorterConfiguration
{
    bool m_isFilterGrepOn;
    std::string m_acceptedFilesGrepCondition;
    std::string m_filterGrepCondition;
    std::string m_pathOfTempFiles;
    alba::AlbaLargeSorterConfiguration m_configurationWithPcTime;
    alba::AlbaLargeSorterConfiguration m_configurationWithoutPcTime;
};

}
