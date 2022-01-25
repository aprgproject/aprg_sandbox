#pragma once

#include <Container/AlbaContainerHelper.hpp>
#include <LargeSorter/AlbaLargeSorterTypes.hpp>
#include <LargeSorter/DataBlockFileHandler.hpp>
#include <LargeSorter/DataBlockMemoryHandler.hpp>
#include <Optional/AlbaOptional.hpp>

#include <algorithm>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

namespace alba
{

enum class DataBlockType
{
    Empty,
    File,
    Memory
};

template <typename ObjectToSort>
class DataBlock
{
    typedef DataBlockMemoryContainer<ObjectToSort> MemoryContainer;

public:
    DataBlock(DataBlockType const blockType, unsigned int const blockNumber, std::string const& fileDumpPath)
        : m_blockType(blockType)
        , m_blockId(blockNumber)
        , m_fileDumpPath(fileDumpPath)
        , m_numberOfObjects(0)
        , m_lowestValue{}
    {
        switch(blockType)
        {
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
    DataBlockType getBlockType() const
    {
        return m_blockType;
    }
    unsigned int getBlockId() const
    {
        return m_blockId;
    }
    unsigned int getNumberOfObjects() const
    {
        return m_numberOfObjects;
    }
    unsigned int getNumberOfObjectsInMemory() const
    {
        unsigned int numberOfObjectsInMemory(0);
        if(m_memoryBlockHandler)
        {
            numberOfObjectsInMemory = m_memoryBlockHandler.getConstReference().getContainerConstReference().size();
        }
        return numberOfObjectsInMemory;
    }
    ObjectToSort getLowestObject() const
    {
        return m_lowestValue;
    }
    bool isFileStreamOpened() const
    {
        bool isOpened = false;
        if(m_blockFileHandler)
        {
            isOpened = m_blockFileHandler.getReference().isFileStreamOpened();
        }
        return isOpened;
    }
    void add(ObjectToSort const& objectToSort)
    {
        switch(m_blockType)
        {
        case DataBlockType::Empty:
            createMemoryHandlerIfNeeded();
            m_memoryBlockHandler.getReference().add(objectToSort);
            m_blockType = DataBlockType::Memory;
            break;
        case DataBlockType::File:
            m_blockFileHandler.getReference().openFileIfNeeded(m_fileDumpPath);
            m_blockFileHandler.getReference().add(objectToSort);
            break;
        case DataBlockType::Memory:
            m_memoryBlockHandler.getReference().add(objectToSort);
            break;
        }
        setLowestObjectIfNeeded(objectToSort);
        m_numberOfObjects++;
    }
    void addAtTheStart(ObjectToSort const& objectToSort)
    {
        switchToMemoryMode();
        m_memoryBlockHandler.getReference().addAtTheStart(objectToSort);
        setLowestObjectIfNeeded(objectToSort);
        m_numberOfObjects++;
    }
    void sortThenDoFunctionThenRelease(std::function<void(ObjectToSort const&)> doFunctionForAllObjects)
    {
        switchToMemoryMode();
        MemoryContainer & contents(m_memoryBlockHandler.getReference().getContainerReference());
        std::stable_sort(contents.begin(), contents.end());
        for(ObjectToSort const& objectToSort : contents)
        {
            doFunctionForAllObjects(objectToSort);
        }
        clearAll();
    }
    void nthElementThenDoFunctionThenRelease(Indexes const& indexes, std::function<void(ObjectToSort const&)> doFunctionForAllObjects)
    {
        switchToMemoryMode();
        MemoryContainer & contents(m_memoryBlockHandler.getReference().getContainerReference());
        typename MemoryContainer::iterator iteratorForStart = contents.begin();
        for(unsigned int const& index : indexes)
        {
            typename MemoryContainer::iterator iteratorForNext = contents.begin()+index;
            std::nth_element(iteratorForStart, iteratorForNext, contents.end());
            iteratorForStart = iteratorForNext;
        }
        for(ObjectToSort const& objectToSort : contents)
        {
            doFunctionForAllObjects(objectToSort);
        }
        clearAll();
    }
    void switchToFileMode()
    {
        createFileHandlerIfNeeded();
        if(m_memoryBlockHandler)
        {
            MemoryContainer const & contents(m_memoryBlockHandler.getReference().getContainerReference());
            m_blockFileHandler.getReference().openFileIfNeeded(m_fileDumpPath);
            std::ofstream & fileDump = m_blockFileHandler.getReference().getFileDumpStreamReference();
            containerHelper::saveContentsOfContainerToFile(fileDump, contents);
        }
        m_memoryBlockHandler.clear();
        m_blockType = DataBlockType::File;
    }
    void switchToMemoryMode()
    {
        createMemoryHandlerIfNeeded();
        if(m_blockFileHandler)
        {
            m_blockFileHandler.getReference().releaseFileStream();
            MemoryContainer & contents(m_memoryBlockHandler.getReference().getContainerReference());
            std::ifstream inputFileStream(m_fileDumpPath);
            containerHelper::retrieveContentsOfContainerFromFile(inputFileStream, contents);
            assert(contents.size() == m_numberOfObjects);
        }
        m_blockFileHandler.clear();
        m_blockType = DataBlockType::Memory;
    }
    void releaseFileStream()
    {
        m_blockFileHandler.getReference().releaseFileStream();
    }

private:
    void createMemoryHandlerIfNeeded()
    {
        if(!m_memoryBlockHandler)
        {
            m_memoryBlockHandler.createObjectUsingDefaultConstructor();
        }
    }
    void createFileHandlerIfNeeded()
    {
        if(!m_blockFileHandler)
        {
            m_blockFileHandler.createObjectUsingDefaultConstructor();
        }
    }
    void clearAll()
    {
        m_memoryBlockHandler.clear();
        m_blockFileHandler.clear();
        m_blockType = DataBlockType::Empty;
        m_numberOfObjects = 0;
    }
    void setLowestObjectIfNeeded(ObjectToSort const& objectToSort)
    {
        if(objectToSort < m_lowestValue || m_numberOfObjects == 0)
        {
            m_lowestValue = objectToSort;
        }
    }
    DataBlockType m_blockType;
    unsigned int const m_blockId;
    std::string  const m_fileDumpPath;
    unsigned int m_numberOfObjects;
    ObjectToSort m_lowestValue;
    AlbaOptional<DataBlockMemoryHandler<ObjectToSort>> m_memoryBlockHandler;
    AlbaOptional<DataBlockFileHandler<ObjectToSort>> m_blockFileHandler;
};

}//namespace alba
