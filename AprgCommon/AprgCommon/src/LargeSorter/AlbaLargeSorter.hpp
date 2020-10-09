#pragma once

#include <AlbaLargeSorterConfiguration.hpp>
#include <AlbaLargeSorterCache.hpp>
#include <AlbaLargeSorterTypes.hpp>
#include <AlbaWindowsPathHandler.hpp>
#include <DataBlocks.hpp>
#include <functional>

namespace alba
{
template <typename ObjectToSort>
class AlbaLargeSorter
{    typedef AlbaLargeSorterBlockType<ObjectToSort> BlockType;
    typedef AlbaLargeSorterBlockIterator<ObjectToSort> BlockIterator;
    typedef AlbaLargeSorterCache<BlockIterator> BlockCache;
    typedef typename BlockCache::BlockInformationPair BlockInformationPair;
    typedef typename BlockCache::BlocksInformationContainer BlockInformationContainer;

public:
    AlbaLargeSorter(AlbaLargeSorterConfiguration const& configuration)
        : m_configuration(configuration)
        , m_memoryCache()
        , m_fileStreamOpenedCache()
        , m_blocks(m_configuration, m_memoryCache, m_fileStreamOpenedCache)
    {
        deleteAllFilesInDirectory();
    }
    bool isEmpty() const
    {
        return m_blocks.isEmpty();
    }
    AlbaLargeSorterConfiguration getConfiguration() const
    {
        return m_configuration;
    }
    void add(ObjectToSort const& objectToSort)
    {
        BlockIterator blockIterator(m_blocks.getNearestBlockIterator(objectToSort));
        m_blocks.addObjectToBlock(blockIterator, objectToSort);
        splitToSmallestBlocksIfOverflow(blockIterator);
        limitMemoryConsumption();
        limitFileStreams();
    }
    void addAtTheStart(ObjectToSort const& objectToSort)
    {
        m_blocks.moveMainInteratorToStart();
        BlockIterator blockIterator(m_blocks.getNearestBlockIterator(objectToSort));
        m_blocks.addObjectToBlockAtTheStart(blockIterator, objectToSort);
        splitToSmallestBlocksIfOverflow(blockIterator);
        limitMemoryConsumption();
        limitFileStreams();
    }
    void sortThenDoFunctionThenReleaseAllObjects(std::function<void(ObjectToSort const&)> doFunctionForAllObjects)
    {
        m_blocks.sortThenDoFunctionThenReleaseAllObjects(doFunctionForAllObjects);
    }

private:
    void splitToSmallestBlocksIfOverflow(BlockIterator const & blockIterator)
    {
        while(blockIterator->getNumberOfObjects() >= m_configuration.m_maximumNumberOfObjectsPerBlock)
        {
            splitToSmallestBlocks(blockIterator, DataBlockType::Memory);
        }
    }
    void splitToSmallestBlocks(BlockIterator const & blockIterator, DataBlockType const blockType)
    {
        BlockIterator iteratorAfterBlockToSplit(blockIterator);
        iteratorAfterBlockToSplit++;
        int numberOfObjectsInCurrentBlock=0;
        BlockIterator newBlockIterator(iteratorAfterBlockToSplit);
        blockIterator->sortThenDoFunctionThenRelease([&](ObjectToSort const& objectToSort)
        {
            if(numberOfObjectsInCurrentBlock == 0)
            {
                m_blocks.createNewBlockBeforeThisIterator(iteratorAfterBlockToSplit, blockType);
                newBlockIterator = iteratorAfterBlockToSplit;
                newBlockIterator--;
            }
            m_blocks.addObjectToBlock(newBlockIterator, objectToSort);
            numberOfObjectsInCurrentBlock++;
            numberOfObjectsInCurrentBlock = (numberOfObjectsInCurrentBlock < m_configuration.m_minimumNumberOfObjectsPerBlock) ? numberOfObjectsInCurrentBlock : 0;
        });
        m_blocks.deleteBlock(blockIterator);
    }
    void limitMemoryConsumption()
    {
        unsigned int totalMemoryConsumption = calculateTotalMemoryConsumption();
        transferMemoryBlocksToFileIfNeeded(totalMemoryConsumption);
    }
    unsigned int calculateTotalMemoryConsumption()
    {
        BlockInformationContainer memoryLimitCache = m_memoryCache.getContainerReference();
        unsigned int totalMemoryConsumption  =
                accumulate(memoryLimitCache.begin(), memoryLimitCache.end(), 0, [](unsigned int memoryConsumption, BlockInformationPair const& blockInformationPair)
        {
            memoryConsumption += blockInformationPair.m_blockInformation->getNumberOfObjectsInMemory();
            return memoryConsumption;
        });
        return totalMemoryConsumption;
    }
    void transferMemoryBlocksToFileIfNeeded(unsigned int totalMemoryConsumption)
    {
        while(totalMemoryConsumption > m_configuration.m_maximumNumberOfObjectsInMemory)
        {
            BlockIterator blockToSwitchToFileMode(m_memoryCache.popTheEarliestAddedBlock());
            totalMemoryConsumption -= blockToSwitchToFileMode->getNumberOfObjectsInMemory();
            if(blockToSwitchToFileMode->getNumberOfObjectsInMemory() > m_configuration.m_minimumNumberOfObjectsPerBlock)
            {
                splitToSmallestBlocks(blockToSwitchToFileMode, DataBlockType::File);
            }
            else
            {
                blockToSwitchToFileMode->switchToFileMode();
                m_fileStreamOpenedCache.addBlock(blockToSwitchToFileMode->getBlockId(), blockToSwitchToFileMode);
            }
        }
    }
    void limitFileStreams()
    {
        while(m_configuration.m_maximumFileStreams < m_fileStreamOpenedCache.getContainerReference().size())
        {
            BlockIterator iteratorOfBlockToReleaseFile(m_fileStreamOpenedCache.popTheEarliestAddedBlock());
            if(iteratorOfBlockToReleaseFile->isFileStreamOpened())
            {
                iteratorOfBlockToReleaseFile->releaseFileStream();
            }
        }
    }
    void deleteAllFilesInDirectory()
    {
        AlbaWindowsPathHandler directoryPathHandler;
        directoryPathHandler.inputPath(m_configuration.m_directoryForBlocks);
        set<string> listOfFiles;
        set<string> listOfDirectories;
        directoryPathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
        for(string const& filePath : listOfFiles)
        {
            AlbaWindowsPathHandler filePathHandler;
            filePathHandler.inputPath(filePath);
            filePathHandler.deleteFile();
        }
    }
    AlbaLargeSorterConfiguration const m_configuration;
    BlockCache m_memoryCache;
    BlockCache m_fileStreamOpenedCache;
    DataBlocks<ObjectToSort> m_blocks;
};

}//namespace alba
