#pragma once

#include <LargeSorter/DataBlock.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <string>

namespace alba
{

struct AlbaLargeSorterConfiguration
{
    AlbaLargeSorterConfiguration()
        : m_directoryForBlocks()
        , m_minimumNumberOfObjectsPerBlock(100)
        , m_maximumNumberOfObjectsPerBlock(1000)
        , m_maximumNumberOfObjectsInMemory(2000)        , m_maximumFileStreams(100)
    {}
    AlbaLargeSorterConfiguration(
            std::string const& directoryForBlocks,            unsigned int minimumNumberOfObjectsPerBlock,
            unsigned int maximumNumberOfObjectsPerBlock,
            unsigned int maximumNumberOfObjectsInMemory,
            unsigned int maximumFileStreams)
        : m_directoryForBlocks(getFixedPath(directoryForBlocks))
        , m_minimumNumberOfObjectsPerBlock(minimumNumberOfObjectsPerBlock)
        , m_maximumNumberOfObjectsPerBlock(maximumNumberOfObjectsPerBlock)
        , m_maximumNumberOfObjectsInMemory(maximumNumberOfObjectsInMemory)        , m_maximumFileStreams(maximumFileStreams)
    {}
    AlbaLargeSorterConfiguration(
            AlbaLargeSorterConfiguration const& sorterConfiguration,
            std::string const& directoryForBlocks)
        : AlbaLargeSorterConfiguration(sorterConfiguration)
    {
        m_directoryForBlocks = getFixedPath(directoryForBlocks);
    }
    std::string m_directoryForBlocks;
    unsigned int m_minimumNumberOfObjectsPerBlock;    unsigned int m_maximumNumberOfObjectsPerBlock;
    unsigned int m_maximumNumberOfObjectsInMemory;
    unsigned int m_maximumFileStreams;
    bool isConfigurationValid() const    {
        if(m_minimumNumberOfObjectsPerBlock <= 0) { return false; }
        if(m_maximumNumberOfObjectsPerBlock <= m_minimumNumberOfObjectsPerBlock) { return false; }
        AlbaLocalPathHandler directoryPath(m_directoryForBlocks);
        if(!directoryPath.isFoundInLocalSystem()) { return false; }
        if(!directoryPath.isDirectory()) { return false; }
        return true;
    }
    std::string getFilePathWithBlockNumber(unsigned int const blockNumber) const
    {
        std::stringstream ss;
        ss << m_directoryForBlocks << R"(\BLOCK_)" << blockNumber << ".txt";
        return getFixedPath(ss.str());
    }
    std::string getFixedPath(std::string const& path) const
    {
        return AlbaLocalPathHandler(path).getFullPath();
    }
};

}