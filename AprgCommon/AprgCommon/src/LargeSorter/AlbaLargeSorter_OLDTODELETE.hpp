#pragma once

#include "AlbaLargeSorterConfiguration.hpp"
#include "AlbaLargeSorterCache.hpp"
#include "AlbaLargeSorterTypes.hpp"
#include <algorithm>
#include "DataBlock.hpp"
#include <functional>
#include <list>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <set>
#include <sstream>

#include <iostream>

namespace alba
{

template <typename ObjectToSort>
class AlbaLargeSorter
{
    typedef AlbaLargeSorterBlockType<ObjectToSort> BlockType;
    typedef AlbaLargeSorterBlockContainer<ObjectToSort> BlockContainer;
    typedef AlbaLargeSorterBlockIterator<ObjectToSort> BlockIterator;
    typedef typename AlbaLargeSorterCache<BlockIterator>::BlockInformationPair BlockInformationPair;
    typedef typename AlbaLargeSorterCache<BlockIterator>::BlocksInformationContainer BlockInformationContainer;

public:
    AlbaLargeSorter(AlbaLargeSorterConfiguration const& configuration)
        : m_configuration(configuration)
        , m_numberOfBlocks(0)
    {
        createNewBlockBeforeThisIterator(m_blocks.begin(), DataBlockType::Memory);
        m_mainIterator = m_blocks.begin();
        deleteAllFilesInDirectory();
    }
    void add(ObjectToSort const& objectToSort)
    {
        //cout<<"add start"<<endl;
        moveMainIteratorToNearestBlock(objectToSort);
        addToBlock(m_mainIterator, objectToSort);
        splitToSmallestBlocksIfOverflow();
        limitMemoryConsumption();
        limitFileStreams();
        //printAllBlocks();
        //cout<<"add end"<<endl;
    }
    void sortThenDoFunctionThenReleaseAllObjects(std::function<void(ObjectToSort const&)> doFunctionForAllObjects)
    {
        for(BlockType& block : m_blocks)
        {
            block.sortThenDoFunctionThenRelease(doFunctionForAllObjects);
        }
        releaseAllBlocks();
    }
    AlbaLargeSorterConfiguration getConfiguration() const
    {
        return m_configuration;
    }

private:
    void moveMainIteratorToNearestBlock(ObjectToSort const& objectToSort)
    {
        //cout<<"moveMainIteratorToNearestBlock start"<<endl;
        if(isLessThanOrEqual(m_mainIterator->getLowestObject(), objectToSort))
        {
            //cout<<"moveMainIteratorToNearestBlock 1 blockId:"<<m_mainIterator->getBlockId()<<endl;
            while((m_mainIterator != m_blocks.end()) && isLessThanOrEqual(m_mainIterator->getLowestObject(), objectToSort))
            {
                m_mainIterator++;
            }
            m_mainIterator--;
            //cout<<"moveMainIteratorToNearestBlock 2 blockId:"<<m_mainIterator->getBlockId()<<endl;
        }
        else if(objectToSort < m_mainIterator->getLowestObject())
        {
            //cout<<"moveMainIteratorToNearestBlock 3 blockId:"<<m_mainIterator->getBlockId()<<endl;
            while((m_mainIterator != m_blocks.begin()) && (objectToSort < m_mainIterator->getLowestObject()))
            {
                m_mainIterator--;
            }
            //cout<<"moveMainIteratorToNearestBlock 4"<<endl;
        }
        //cout<<"moveMainIteratorToNearestBlock end"<<endl;
    }
    void splitToSmallestBlocksIfOverflow()
    {
        //cout<<"splitToSmallestBlocksIfOverflow start"<<endl;
        while(m_mainIterator->getNumberOfObjects() >= m_configuration.m_maximumNumberOfObjectsPerBlock)
        {
            splitToSmallestBlocks(m_mainIterator, DataBlockType::Memory);
        }
        //cout<<"splitToSmallestBlocksIfOverflow end"<<endl;
    }
    void limitMemoryConsumption()
    {
        //cout<<"limitMemoryConsumption start"<<endl;
        unsigned int totalMemoryConsumption = calculateTotalMemoryConsumption();
        transferMemoryBlocksToFileIfNeeded(totalMemoryConsumption);
        //cout<<"limitMemoryConsumption end"<<totalMemoryConsumption<<endl;
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
            //cout<<"transferMemoryBlocksToFileIfNeeded blockId:"<<blockToSwitchToFileMode->getBlockId()<<" total:"<<totalMemoryConsumption<<"::"<<m_configuration.maximumNumberOfObjectsInMemory<<endl;
            totalMemoryConsumption -= blockToSwitchToFileMode->getNumberOfObjectsInMemory();
            if(blockToSwitchToFileMode->getNumberOfObjectsInMemory() > m_configuration.m_minimumNumberOfObjectsPerBlock)
            {
                //cout<<"transferMemoryBlocksToFileIfNeeded 1"<<endl;
                splitToSmallestBlocks(blockToSwitchToFileMode, DataBlockType::File);
            }
            else
            {
                //cout<<"transferMemoryBlocksToFileIfNeeded 2 "<<m_fileStreamOpenedCache.getContainerReference().size()<<endl;
                blockToSwitchToFileMode->switchToFileMode();
                m_fileStreamOpenedCache.addBlock(blockToSwitchToFileMode->getBlockId(), blockToSwitchToFileMode);
                //cout<<"transferMemoryBlocksToFileIfNeeded 3 "<<m_fileStreamOpenedCache.getContainerReference().size()<<endl;
            }
        }
    }
    void limitFileStreams()
    {
        //cout<<"limitFileStreams start :"<<m_configuration.maximumFileStreams<<"::"<<m_fileStreamOpenedCache.getContainerReference().size()<<endl;
        while(m_configuration.m_maximumFileStreams < m_fileStreamOpenedCache.getContainerReference().size())
        {
            BlockIterator iteratorOfBlockToReleaseFile(m_fileStreamOpenedCache.popTheEarliestAddedBlock());
            if(iteratorOfBlockToReleaseFile->isFileStreamOpened())
            {
                iteratorOfBlockToReleaseFile->releaseFileStream();
            }
        }
        //cout<<"limitFileStreams end"<<endl;
    }
    void splitToSmallestBlocks(BlockIterator const & iteratorOfBlock, DataBlockType const blockType)
    {
        //cout<<"splitToSmallestBlocks start"<<endl;
        BlockIterator iteratorAfterBlockToSplit(iteratorOfBlock);
        iteratorAfterBlockToSplit++;
        int numberOfObjectsInCurrentBlock=0;
        BlockIterator newBlockIterator(iteratorAfterBlockToSplit);
        iteratorOfBlock->sortThenDoFunctionThenRelease([&](ObjectToSort const& objectToSort)
        {
            if(numberOfObjectsInCurrentBlock == 0)
            {
                createNewBlockBeforeThisIterator(iteratorAfterBlockToSplit, blockType);
                newBlockIterator = iteratorAfterBlockToSplit;
                newBlockIterator--;
            }
            addToBlock(newBlockIterator, objectToSort);
            numberOfObjectsInCurrentBlock++;
            numberOfObjectsInCurrentBlock = (numberOfObjectsInCurrentBlock < m_configuration.m_minimumNumberOfObjectsPerBlock) ? numberOfObjectsInCurrentBlock : 0;
        });
        deleteBlock(iteratorOfBlock);
        //cout<<"splitToSmallestBlocks end"<<endl;
    }
    void createNewBlockBeforeThisIterator(BlockIterator const& iteratorAfterNewBlock, DataBlockType const blockType)
    {
        std::stringstream ss;
        ss << m_configuration.m_directoryForBlocks << R"(\BLOCK_)" << m_numberOfBlocks << ".txt";
        m_blocks.emplace(iteratorAfterNewBlock, blockType, m_numberOfBlocks, ss.str());
        BlockIterator newBlockIterator(iteratorAfterNewBlock);
        newBlockIterator--;
        m_numberOfBlocks++;
        //cout<<"addBlock end numBlocks:"<<m_numberOfBlocks<<" blockId:"<<newBlockIterator->getBlockId()<<" size:"<<newBlockIterator->getNumberOfObjects()<<endl;

    }
    void deleteBlock(BlockIterator const& iteratorOfBlockToErase)
    {
        //cout<<"deleteBlock start"<<" blockId:"<<iteratorOfBlockToErase->getBlockId()<<" size:"<<m_blocks.size()<<endl;
        bool const isMainIteratorDeleted = m_mainIterator==iteratorOfBlockToErase;
        m_memoryCache.deleteBlock(iteratorOfBlockToErase->getBlockId());
        m_fileStreamOpenedCache.deleteBlock(iteratorOfBlockToErase->getBlockId());
        BlockIterator newIterator= m_blocks.erase(iteratorOfBlockToErase);
        if(isMainIteratorDeleted) { m_mainIterator = newIterator; }
        //cout<<"deleteBlock end"<<" blockId:"<<m_mainIterator->getBlockId()<<" isMainIteratorDeleted:"<<isMainIteratorDeleted<<endl;
    }
    void addToBlock(BlockIterator const& iteratorOfBlock, ObjectToSort const& objectToSort)
    {
        iteratorOfBlock->add(objectToSort);
        //cout<<"addToBlock blockId:"<<iteratorOfBlock->getBlockId()<<"::"<<objectToSort<<endl;
        switch(iteratorOfBlock->getBlockType())
        {
        case DataBlockType::File:
            m_fileStreamOpenedCache.addBlock(iteratorOfBlock->getBlockId(), iteratorOfBlock);
            //cout<<"addToBlock File blockId:"<<iteratorOfBlock->getBlockId()<<":: addressof:"<<std::addressof(*iteratorOfBlock)<<endl;
            break;
        case DataBlockType::Memory:
            m_memoryCache.addBlock(iteratorOfBlock->getBlockId(), iteratorOfBlock);
            break;
        case DataBlockType::Empty:
            break;
        }
    }
    void releaseAllBlocks()
    {
        m_blocks.clear();
        m_memoryCache.clear();
        m_fileStreamOpenedCache.clear();
        m_numberOfBlocks = 0;
    }
    void printAllBlocks()
    {
        std::cout << "printAllBlocks(): " << std::endl;
        for(BlockType& block : m_blocks)
        {
            std::cout << "BlockId: " << block.getBlockId() << " NumObjects: " << block.getNumberOfObjects() << " type:" << (int)block.getBlockType()<< " fileOpened:" << block.isFileStreamOpened() << std::endl;
            //block.printBlock();
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
    inline bool isLessThanOrEqual(ObjectToSort const& firstTerm, ObjectToSort const& secondTerm)
    {
        return (firstTerm < secondTerm) || (firstTerm == secondTerm);
    }
    AlbaLargeSorterConfiguration const m_configuration;
    unsigned int m_numberOfBlocks;
    BlockContainer m_blocks;
    BlockIterator m_mainIterator;
    AlbaLargeSorterCache<BlockIterator> m_memoryCache;
    AlbaLargeSorterCache<BlockIterator> m_fileStreamOpenedCache;
};

}//namespace alba
