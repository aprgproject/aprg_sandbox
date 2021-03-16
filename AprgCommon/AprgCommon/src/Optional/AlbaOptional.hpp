#pragma once

#include <cassert>
#include <memory>

namespace alba
{

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

    AlbaOptional(ContentType& content)
        : m_hasContent(true)
        , m_contentPointer(new ContentType(content))
    {}

    AlbaOptional(AlbaOptional<ContentType> const& optional)
        : m_hasContent(optional.m_hasContent)
        , m_contentPointer(nullptr)
    {
        if(m_hasContent)
        {
            m_contentPointer.reset(new ContentType(optional.get()));
        }
    }

    AlbaOptional(AlbaOptional<ContentType>&& optional)
        : m_hasContent(optional.m_hasContent)
        , m_contentPointer(nullptr)
    {
        if(m_hasContent)
        {
            m_contentPointer = std::move(optional.m_contentPointer);
            optional.m_hasContent = false;
        }
    }

    void operator=(AlbaOptional<ContentType> const& optional)
    {
        m_hasContent = optional.m_hasContent;
        if(m_hasContent)
        {
            m_contentPointer.reset(new ContentType(optional.get()));
        }
    }

    void operator=(AlbaOptional<ContentType>&& optional)
    {
        m_hasContent = optional.m_hasContent;
        if(m_hasContent)
        {
            m_contentPointer = std::move(optional.m_contentPointer);
            optional.m_hasContent = false;
        }
    }

    operator bool() const
    {
        return m_hasContent;
    }

    operator ContentType() const
    {
        assert(m_hasContent); //we will not allow mistakes
        if(m_hasContent)
        {
            return *(m_contentPointer.get());
        }
        else
        {
            return ContentType();
        }
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

    void setReference(ContentType& content)
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
        assert(m_hasContent); //we will not allow mistakes
        if(m_hasContent)
        {
            return *(m_contentPointer.get());
        }
        else
        {
            return ContentType();
        }
    }

    ContentType& getReference()
    {
        assert(m_hasContent); //we will not allow mistakes
        return *(m_contentPointer.get());
    }

    ContentType const& getConstReference() const
    {
        assert(m_hasContent); //we will not allow mistakes
        return *(m_contentPointer.get());
    }

private:
    bool m_hasContent;
    std::unique_ptr<ContentType> m_contentPointer;
};

template <typename ContentType> class AlbaOptional<ContentType &>
{
public:

//#warning Please make sure that object still exists in the life time of an optional reference object

    AlbaOptional()
        : m_hasContent(false)
        , m_contentPointer(nullptr)
    {}

    AlbaOptional(ContentType & content)
        : m_hasContent(true)
        , m_contentPointer(&content)
    {}

    AlbaOptional(AlbaOptional<ContentType&> const& optional)
        : m_hasContent(optional.m_hasContent)
        , m_contentPointer(optional.m_contentPointer)
    {}

    void operator=(AlbaOptional<ContentType&> const& optional)
    {
        m_hasContent = optional.m_hasContent;
        m_contentPointer = optional.m_contentPointer;
    }

    void setValue(ContentType content)
    {
        if(m_hasContent && isContentPointerValid())
        {
            *m_contentPointer = content;
        }
    }

    void setReference(ContentType& content)
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

    ContentType& get() const
    {
        if(m_hasContent && isContentPointerValid())
        {
            return *m_contentPointer;
        }
        return m_empty;
    }

    operator bool() const
    {
        return m_hasContent;
    }

    operator ContentType&() const
    {
        if(m_hasContent && isContentPointerValid())
        {
            return *m_contentPointer;
        }
        return m_empty;
    }

private:
    inline bool isContentPointerValid() const
    {
        return m_contentPointer != nullptr;
    }

    bool m_hasContent;
    ContentType* m_contentPointer;
    static ContentType m_empty; //think of how to remove this
};

template <typename ContentType> ContentType AlbaOptional<ContentType&>::m_empty;
} // namespace alba
