#pragma once

#include <Algorithm/Sort/LargeSorter/AlbaLargeSorterConfiguration.hpp>
#include <Algorithm/Sort/LargeSorter/AlbaLargeSorterTypes.hpp>
#include <Algorithm/Sort/LargeSorter/DataBlock.hpp>
#include <Algorithm/Sort/LargeSorter/DataBlockCache.hpp>

#include <algorithm>
#include <functional>

namespace alba {

namespace algorithm {

template <typename ObjectToSort>
class DataBlocks {
    using BlockType = AlbaLargeSorterBlockType<ObjectToSort>;
    using BlockContainer = AlbaLargeSorterBlockContainer<ObjectToSort>;
    using BlockIterator = AlbaLargeSorterBlockIterator<ObjectToSort>;
    using BlockCache = AlbaLargeSorterBlockCache<BlockIterator>;

public:
    DataBlocks(
        AlbaLargeSorterConfiguration const& configuration, BlockCache& memoryCache, BlockCache& fileStreamOpenedCache)
        : m_configuration(configuration),
          m_memoryCache(memoryCache),
          m_fileStreamOpenedCache(fileStreamOpenedCache),
          m_numberOfBlocks(0) {
        initializeDataBlocks();
    }
    bool isEmpty() const {
        for (BlockType const& block : m_blocks) {
            if (block.getNumberOfObjects() != 0) {
                return false;
            }
        }
        return true;
    }
    BlockIterator getNearestBlockIterator(ObjectToSort const& objectToSort) {
        if (isLessThanOrEqual(m_mainIterator->getLowestObject(), objectToSort)) {
            while ((m_mainIterator != m_blocks.end()) &&
                   isLessThanOrEqual(m_mainIterator->getLowestObject(), objectToSort)) {
                m_mainIterator++;
            }
            m_mainIterator--;
        } else if (objectToSort < m_mainIterator->getLowestObject()) {
            while ((m_mainIterator != m_blocks.begin()) && (objectToSort < m_mainIterator->getLowestObject())) {
                m_mainIterator--;
            }
        }
        return m_mainIterator;
    }
    void moveMainInteratorToStart() { m_mainIterator = m_blocks.begin(); }
    void createNewBlockBeforeThisIterator(BlockIterator const& iteratorAfterNewBlock, DataBlockType const blockType) {
        m_blocks.emplace(
            iteratorAfterNewBlock, blockType, m_numberOfBlocks,
            m_configuration.getFilePathWithBlockNumber(m_numberOfBlocks));
        BlockIterator newBlockIterator(iteratorAfterNewBlock);
        newBlockIterator--;
        m_numberOfBlocks++;
    }
    void deleteBlock(BlockIterator const& iteratorOfBlockToErase) {
        bool const isMainIteratorDeleted = m_mainIterator == iteratorOfBlockToErase;
        m_memoryCache.deleteBlock(iteratorOfBlockToErase->getBlockId());
        m_fileStreamOpenedCache.deleteBlock(iteratorOfBlockToErase->getBlockId());
        BlockIterator newIterator = m_blocks.erase(iteratorOfBlockToErase);
        if (isMainIteratorDeleted) {
            m_mainIterator = newIterator;
        }
    }
    void addObjectToBlock(BlockIterator const& iteratorOfBlock, ObjectToSort const& objectToSort) {
        iteratorOfBlock->add(objectToSort);
        updateAllCaches(iteratorOfBlock);
    }
    void addObjectToBlockAtTheStart(BlockIterator const& iteratorOfBlock, ObjectToSort const& objectToSort) {
        iteratorOfBlock->addAtTheStart(objectToSort);
        updateAllCaches(iteratorOfBlock);
    }
    void sortThenDoFunctionThenReleaseAllObjects(std::function<void(ObjectToSort const&)> doFunctionForAllObjects) {
        for (BlockType& block : m_blocks) {
            block.sortThenDoFunctionThenRelease(doFunctionForAllObjects);
        }
        releaseAllBlocks();
        initializeDataBlocks();
    }
    void releaseAllBlocks() {
        m_blocks.clear();
        m_memoryCache.clear();
        m_fileStreamOpenedCache.clear();
        m_numberOfBlocks = 0;
    }
    void initializeDataBlocks() {
        createNewBlockBeforeThisIterator(m_blocks.begin(), DataBlockType::Memory);
        m_mainIterator = m_blocks.begin();
    }
    void updateAllCaches(BlockIterator const& iteratorOfBlock) {
        switch (iteratorOfBlock->getBlockType()) {
            case DataBlockType::File:
                m_fileStreamOpenedCache.addBlock(iteratorOfBlock->getBlockId(), iteratorOfBlock);
                break;
            case DataBlockType::Memory:
                m_memoryCache.addBlock(iteratorOfBlock->getBlockId(), iteratorOfBlock);
                break;
            case DataBlockType::Empty:
                break;
        }
    }

private:
    inline bool isLessThanOrEqual(ObjectToSort const& firstTerm, ObjectToSort const& secondTerm) {
        return (firstTerm < secondTerm) || (firstTerm == secondTerm);
    }
    AlbaLargeSorterConfiguration const& m_configuration;
    BlockCache& m_memoryCache;
    BlockCache& m_fileStreamOpenedCache;
    unsigned int m_numberOfBlocks;
    BlockContainer m_blocks;
    BlockIterator m_mainIterator;
};

}  // namespace algorithm

}  // namespace alba
