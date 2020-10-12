#pragma once

#include <LargeSorter/DataBlock.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>

using std::string;

namespace alba
{

struct AlbaLargeSorterConfiguration
{
    AlbaLargeSorterConfiguration()
        : m_directoryForBlocks("")
        , m_minimumNumberOfObjectsPerBlock(100)
        , m_maximumNumberOfObjectsPerBlock(1000)
        , m_maximumNumberOfObjectsInMemory(2000)
        , m_maximumFileStreams(100)
    {}
    AlbaLargeSorterConfiguration(
            string directoryForBlocks,
            unsigned int minimumNumberOfObjectsPerBlock,
            unsigned int maximumNumberOfObjectsPerBlock,
            unsigned int maximumNumberOfObjectsInMemory,
            unsigned int maximumFileStreams)
        : m_directoryForBlocks(directoryForBlocks)
        , m_minimumNumberOfObjectsPerBlock(minimumNumberOfObjectsPerBlock)
        , m_maximumNumberOfObjectsPerBlock(maximumNumberOfObjectsPerBlock)
        , m_maximumNumberOfObjectsInMemory(maximumNumberOfObjectsInMemory)
        , m_maximumFileStreams(maximumFileStreams)
    {}
    string m_directoryForBlocks;
    unsigned int m_minimumNumberOfObjectsPerBlock;
    unsigned int m_maximumNumberOfObjectsPerBlock;
    unsigned int m_maximumNumberOfObjectsInMemory;
    unsigned int m_maximumFileStreams;
    bool isConfigurationValid() const
    {
        if(m_minimumNumberOfObjectsPerBlock <= 0) { return false; }
        if(m_maximumNumberOfObjectsPerBlock <= m_minimumNumberOfObjectsPerBlock) { return false; }
        AlbaWindowsPathHandler directoryPath(m_directoryForBlocks);
        if(!directoryPath.isFoundInLocalSystem()) { return false; }
        if(!directoryPath.isDirectory()) { return false; }
        return true;
    }
};

}