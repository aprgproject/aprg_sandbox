#pragma once

#include <LargeSorter/DataBlockCache.hpp>
#include <LargeSorter/AlbaLargeSorterConfiguration.hpp>
#include <LargeSorter/AlbaLargeSorterTypes.hpp>

#include <LargeSorter/DataBlocks.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <functional>

namespace alba
{

template <typename ObjectToSort>
class AlbaLargeSorter
{
    typedef AlbaLargeSorterBlockType<ObjectToSort> BlockType;
    typedef AlbaLargeSorterBlockIterator<ObjectToSort> BlockIterator;
    typedef DataBlockCache<BlockIterator> BlockCache;
    typedef typename BlockCache::BlockInformationPair BlockInformationPair;
    typedef typename BlockCache::BlocksInformationContainer BlockInformationContainer;

public:
    AlbaLargeSorter(AlbaLargeSorterConfiguration const& configuration)
        : m_size(0)
        , m_configuration(configuration)
        , m_memoryCache()
        , m_fileStreamOpenedCache()
        , m_blocks(m_configuration, m_memoryCache, m_fileStreamOpenedCache)
    {
        deleteAllFilesInDirectory();
    }
    bool isEmpty() const
    {
        return 0 == m_size;
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
        m_size++;
    }
    void addAtTheStart(ObjectToSort const& objectToSort)
    {
        m_blocks.moveMainInteratorToStart();
        BlockIterator blockIterator(m_blocks.getNearestBlockIterator(objectToSort));
        m_blocks.addObjectToBlockAtTheStart(blockIterator, objectToSort);
        splitToSmallestBlocksIfOverflow(blockIterator);
        limitMemoryConsumption();
        limitFileStreams();
        m_size++;
    }
    void sortThenDoFunctionThenReleaseAllObjects(std::function<void(ObjectToSort const&)> doFunctionForAllObjects)
    {
        m_blocks.sortThenDoFunctionThenReleaseAllObjects(doFunctionForAllObjects);
        m_size = 0;
    }
    unsigned long long getSize()
    {
        return m_size;
    }

private:
    void splitToSmallestBlocksIfOverflow(BlockIterator const & blockIterator)
    {
        while(blockIterator->getNumberOfObjects() >= m_configuration.m_maximumNumberOfObjectsPerBlock)
        {
            splitToSmallestBlocks(blockIterator, DataBlockType::Memory);
        }
    }
    void splitToSmallestBlocks(BlockIterator const & blockIterator, DataBlockType const blockTypeForNewBlocks)
    {
        BlockIterator iteratorAfterBlockToSplit(blockIterator);
        BlockIterator iteratorStartCopy(blockIterator);
        iteratorAfterBlockToSplit++;
        int numberOfObjectsInCurrentBlock=0;
        BlockIterator newBlockIterator(iteratorAfterBlockToSplit);

        unsigned int numberOfObjects = blockIterator->getNumberOfObjects();
        DataBlock::Indexes indexes;
        for(DataBlock::Index index=m_configuration.m_minimumNumberOfObjectsPerBlock; index<numberOfObjects; index+=m_configuration.m_minimumNumberOfObjectsPerBlock)
        {
            indexes.emplace_back(index);
            m_blocks.createNewBlockBeforeThisIterator(iteratorAfterBlockToSplit, blockTypeForNewBlocks);
            newBlockIterator = iteratorAfterBlockToSplit;
            newBlockIterator--;
        }
        DataBlock::Index index=0;
        blockIterator->sortThenDoFunctionThenRelease([&](ObjectToSort const& objectToSort) // this should be nth element // you need to finish this.
        {
            if(index)
            {
                iteratorStartCopy++;
            }
            m_blocks.addObjectToBlock(iteratorStartCopy, objectToSort);
            numberOfObjectsInCurrentBlock++;
            numberOfObjectsInCurrentBlock = (numberOfObjectsInCurrentBlock < static_cast<int>(m_configuration.m_minimumNumberOfObjectsPerBlock)) ? numberOfObjectsInCurrentBlock : 0;
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
        BlockInformationContainer const & memoryLimitCache(m_memoryCache.getContainerReference());
        unsigned int totalMemoryConsumption  =
                accumulate(memoryLimitCache.cbegin(), memoryLimitCache.cend(), 0, [](unsigned int memoryConsumption, BlockInformationPair const& blockInformationPair)
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
                blockToSwitchToFileMode->releaseFileStream();
            }
        }
    }
    void limitFileStreams()
    {
        while(m_configuration.m_maximumFileStreams < m_fileStreamOpenedCache.getContainerReference().size())
        {
            BlockIterator iteratorOfBlockToReleaseFile(m_fileStreamOpenedCache.popTheEarliestAddedBlock());
            iteratorOfBlockToReleaseFile->releaseFileStream();
        }
    }
    void deleteAllFilesInDirectory()
    {
        AlbaLocalPathHandler directoryPathHandler(m_configuration.m_directoryForBlocks);
        std::set<std::string> listOfFiles;
        std::set<std::string> listOfDirectories;
        directoryPathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
        for(std::string const& filePath : listOfFiles)
        {
            AlbaLocalPathHandler(filePath).deleteFile();
        }
    }
    unsigned long long m_size;
    AlbaLargeSorterConfiguration const m_configuration;
    BlockCache m_memoryCache;
    BlockCache m_fileStreamOpenedCache;
    DataBlocks<ObjectToSort> m_blocks;
};

}//namespace alba
