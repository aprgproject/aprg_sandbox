#pragma once

#include <Algorithm/LargeSorter/AlbaLargeSorterConfiguration.hpp>

#include <string>
namespace wcdmaToolsBackend
{

struct BtsLogSorterConfiguration
{
    bool m_isFilterGrepOn;
    std::string m_acceptedFilesGrepCondition;
    std::string m_filterGrepCondition;
    std::string m_pathOfTempFiles;
    alba::algorithm::AlbaLargeSorterConfiguration m_configurationWithPcTime;
    alba::algorithm::AlbaLargeSorterConfiguration m_configurationWithoutPcTime;
};

}