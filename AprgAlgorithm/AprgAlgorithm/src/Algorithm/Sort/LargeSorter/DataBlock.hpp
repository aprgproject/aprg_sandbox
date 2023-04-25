#pragma once

#include <Algorithm/Sort/LargeSorter/AlbaLargeSorterTypes.hpp>
#include <Algorithm/Sort/LargeSorter/DataBlockFileHandler.hpp>
#include <Algorithm/Sort/LargeSorter/DataBlockMemoryHandler.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>

#include <algorithm>
#include <fstream>
#include <functional>
#include <optional>
#include <string>

namespace alba {

namespace algorithm {

enum class DataBlockType { Empty, File, Memory };

template <typename ObjectToSort>
class DataBlock {
    typedef DataBlockMemoryContainer<ObjectToSort> MemoryContainer;

public:
    DataBlock(DataBlockType const blockType, unsigned int const blockNumber, std::string const& fileDumpPath)
        : m_blockType(blockType),
          m_blockId(blockNumber),
          m_fileDumpPath(fileDumpPath),
          m_numberOfObjects(0),
          m_lowestValue{} {
        switch (blockType) {
            case DataBlockType::Empty:
                break;
            case DataBlockType::File:
                createFileHandlerIfNeeded();
                break;
            case DataBlockType::Memory:
                createMemoryHandlerIfNeeded();
                break;
        }
    }
    DataBlockType getBlockType() const { return m_blockType; }
    unsigned int getBlockId() const { return m_blockId; }
    unsigned int getNumberOfObjects() const { return m_numberOfObjects; }
    unsigned int getNumberOfObjectsInMemory() const {
        unsigned int numberOfObjectsInMemory(0);
        if (m_memoryBlockHandler) {
            numberOfObjectsInMemory = m_memoryBlockHandler->getContainerConstReference().size();
        }
        return numberOfObjectsInMemory;
    }
    ObjectToSort getLowestObject() const { return m_lowestValue; }
    bool isFileStreamOpened() const {
        bool isOpened = false;
        if (m_blockFileHandler) {
            isOpened = m_blockFileHandler->isFileStreamOpened();
        }
        return isOpened;
    }
    void add(ObjectToSort const& objectToSort) {
        switch (m_blockType) {
            case DataBlockType::Empty:
                createMemoryHandlerIfNeeded();
                m_memoryBlockHandler->add(objectToSort);
                m_blockType = DataBlockType::Memory;
                break;
            case DataBlockType::File:
                m_blockFileHandler->openFileIfNeeded(m_fileDumpPath);
                m_blockFileHandler->add(objectToSort);
                break;
            case DataBlockType::Memory:
                m_memoryBlockHandler->add(objectToSort);
                break;
        }
        setLowestObjectIfNeeded(objectToSort);
        m_numberOfObjects++;
    }
    void addAtTheStart(ObjectToSort const& objectToSort) {
        switchToMemoryMode();
        m_memoryBlockHandler->addAtTheStart(objectToSort);
        setLowestObjectIfNeeded(objectToSort);
        m_numberOfObjects++;
    }
    void sortThenDoFunctionThenRelease(std::function<void(ObjectToSort const&)> doFunctionForAllObjects) {
        switchToMemoryMode();
        MemoryContainer& contents(m_memoryBlockHandler->getContainerReference());
        std::stable_sort(contents.begin(), contents.end());
        for (ObjectToSort const& objectToSort : contents) {
            doFunctionForAllObjects(objectToSort);
        }
        clearAll();
    }
    void nthElementThenDoFunctionThenRelease(
        Indexes const& indexes, std::function<void(ObjectToSort const&)> doFunctionForAllObjects) {
        switchToMemoryMode();
        MemoryContainer& contents(m_memoryBlockHandler->getContainerReference());
        typename MemoryContainer::iterator iteratorForStart = contents.begin();
        for (unsigned int const& index : indexes) {
            typename MemoryContainer::iterator iteratorForNext = contents.begin() + index;
            std::nth_element(iteratorForStart, iteratorForNext, contents.end());
            iteratorForStart = iteratorForNext;
        }
        for (ObjectToSort const& objectToSort : contents) {
            doFunctionForAllObjects(objectToSort);
        }
        clearAll();
    }
    void switchToFileMode() {
        createFileHandlerIfNeeded();
        if (m_memoryBlockHandler) {
            MemoryContainer const& contents(m_memoryBlockHandler->getContainerReference());
            m_blockFileHandler->openFileIfNeeded(m_fileDumpPath);
            std::ofstream& fileDump = m_blockFileHandler->getFileDumpStreamReference();
            containerHelper::saveContentsToStream(fileDump, contents, containerHelper::StreamFormat::File);
        }
        m_memoryBlockHandler.reset();
        m_blockType = DataBlockType::File;
    }
    void switchToMemoryMode() {
        createMemoryHandlerIfNeeded();
        if (m_blockFileHandler) {
            m_blockFileHandler->releaseFileStream();
            MemoryContainer& contents(m_memoryBlockHandler->getContainerReference());
            std::ifstream inputFileStream(m_fileDumpPath);
            containerHelper::retrieveContentsFromStream(inputFileStream, contents);
            assert(contents.size() == m_numberOfObjects);
        }
        m_blockFileHandler.reset();
        m_blockType = DataBlockType::Memory;
    }
    void releaseFileStream() { m_blockFileHandler->releaseFileStream(); }

private:
    void createMemoryHandlerIfNeeded() {
        if (!m_memoryBlockHandler) {
            m_memoryBlockHandler.emplace();
        }
    }
    void createFileHandlerIfNeeded() {
        if (!m_blockFileHandler) {
            m_blockFileHandler.emplace();
        }
    }
    void clearAll() {
        m_memoryBlockHandler.reset();
        m_blockFileHandler.reset();
        m_blockType = DataBlockType::Empty;
        m_numberOfObjects = 0;
    }
    void setLowestObjectIfNeeded(ObjectToSort const& objectToSort) {
        if (objectToSort < m_lowestValue || m_numberOfObjects == 0) {
            m_lowestValue = objectToSort;
        }
    }
    DataBlockType m_blockType;
    unsigned int const m_blockId;
    std::string const m_fileDumpPath;
    unsigned int m_numberOfObjects;
    ObjectToSort m_lowestValue;
    std::optional<DataBlockMemoryHandler<ObjectToSort>> m_memoryBlockHandler;
    std::optional<DataBlockFileHandler<ObjectToSort>> m_blockFileHandler;
};

}  // namespace algorithm

}  // namespace alba
