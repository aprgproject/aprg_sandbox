#pragma once

#include <cassert>
#include <memory>

namespace alba{

template <typename ContentType> class AlbaOptional
{
public:
    AlbaOptional()
        : m_hasContent(false)
    {}

    AlbaOptional(ContentType content)
        : m_hasContent(true)
        , m_contentPointer(new ContentType(content))
    {}

    AlbaOptional(ContentType & content)
        : m_hasContent(true)
        , m_contentPointer(new ContentType(content))
    {}

    AlbaOptional(AlbaOptional<ContentType> const& albaOptional)
        : m_hasContent(albaOptional.m_hasContent)
        , m_contentPointer()
    {
        if(m_hasContent)
        {
            m_contentPointer.reset(new ContentType(albaOptional.get()));
        }
    }

    void operator=(AlbaOptional<ContentType> const& albaOptional)
    {
        m_hasContent = albaOptional.m_hasContent;
        if(m_hasContent)
        {
            m_contentPointer.reset(new ContentType(albaOptional.get()));
        }
    }

    operator bool() const
    {
        return m_hasContent;
    }

    operator ContentType() const
    {
        assert(m_hasContent);
        return *(m_contentPointer.get());
    }

    void createObjectUsingDefaultConstructor()
    {
        m_hasContent = true;
        m_contentPointer.reset(new ContentType);
    }

    void setValue(ContentType content)
    {
        m_hasContent = true;
        m_contentPointer.reset(new ContentType(content));
    }

    void setReference(ContentType & content)
    {
        m_hasContent = true;
        m_contentPointer.reset(new ContentType(content));
    }

    void clear()
    {
        m_hasContent = false;
        m_contentPointer.reset();
    }

    bool hasContent() const
    {
        return m_hasContent;
    }

    ContentType get() const
    {
        assert(m_hasContent);
        return *(m_contentPointer.get());
    }

    ContentType & getReference() const
    {
        assert(m_hasContent);
        return *(m_contentPointer.get());
    }

private:
    bool m_hasContent;
    std::unique_ptr<ContentType> m_contentPointer;
};

template <typename ContentType> class AlbaOptional<ContentType &>
{
public:

    AlbaOptional()
        : m_hasContent(false)
        , m_contentPointer(nullptr)
    {}

    AlbaOptional(ContentType & content)
        : m_hasContent(true)
        , m_contentPointer(&content)
    {}

    AlbaOptional(AlbaOptional<ContentType &> const& albaOptional)
        : m_hasContent(albaOptional.m_hasContent)
        , m_contentPointer(albaOptional.m_contentPointer)
    {}

    void operator=(AlbaOptional<ContentType &> const& albaOptional)
    {
        m_hasContent = albaOptional.m_hasContent;
        m_contentPointer = albaOptional.m_contentPointer;
    }

    void setValue(ContentType content)
    {
        if(m_hasContent)
        {
            *m_contentPointer = content;
        }
    }

    void setReference(ContentType & content)
    {
        m_hasContent = true;
        m_contentPointer = &content;
    }

    void clear()
    {
        m_hasContent = false;
        m_contentPointer = nullptr;
    }

    bool hasContent() const
    {
        return m_hasContent;
    }

    ContentType & get() const
    {
        if(m_hasContent)
        {
            return *m_contentPointer;
        }
        return m_empty;
    }

    operator bool() const
    {
        return m_hasContent;
    }

    operator ContentType &() const
    {
        if(m_hasContent)
        {
            return *m_contentPointer;
        }
        return m_empty;
    }

private:
    bool m_hasContent;
    ContentType * m_contentPointer;
    static ContentType m_empty; //think of how to remove this
};

template <typename ContentType> ContentType AlbaOptional<ContentType &>::m_empty;
}//namespace alba
