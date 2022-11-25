#pragma once

#include <cassert>
#include <memory>
#include <ostream>

namespace alba
{

template <typename ContentType> class AlbaOptional
{
    // This requires copy constructor and default constructor on ContentType
public:

    AlbaOptional() = default;

    AlbaOptional(ContentType content)
        : m_contentPointer(std::make_unique<ContentType>(content))
    {}

    AlbaOptional(ContentType& content)
        : m_contentPointer(std::make_unique<ContentType>(content))
    {}

    AlbaOptional(AlbaOptional<ContentType> const& optional)
    {
        if(optional.m_contentPointer)
        {
            m_contentPointer = std::make_unique<ContentType>(*(optional.m_contentPointer));
        }
    }

    AlbaOptional(AlbaOptional<ContentType>&& optional)
        : m_contentPointer(std::move(optional.m_contentPointer))
    {}

    void operator=(AlbaOptional<ContentType> const& optional)
    {
        if(optional.m_contentPointer)
        {
            m_contentPointer = std::make_unique<ContentType>(*(optional.m_contentPointer));
        }
    }

    void operator=(AlbaOptional<ContentType>&& optional)
    {
        m_contentPointer = std::move(optional.m_contentPointer);
    }

    operator bool() const
    {
        return hasContent();
    }

    operator ContentType() const
    {
        return get();
    }

    void createObjectUsingDefaultConstructor()
    {
        m_contentPointer = std::make_unique<ContentType>();
    }

    void setValue(ContentType content)
    {
        if(m_contentPointer)
        {
            *m_contentPointer = content;
        }
        else
        {
            m_contentPointer = std::make_unique<ContentType>(content);
        }
    }

    void setConstReference(ContentType const& content)
    {
        if(m_contentPointer)
        {
            *m_contentPointer = content;
        }
        else
        {
            m_contentPointer = std::make_unique<ContentType>(content);
        }
    }

    void clear()
    {
        m_contentPointer.reset();
    }

    bool hasContent() const
    {
        return static_cast<bool>(m_contentPointer);
    }

    ContentType get() const
    {
        assert(m_contentPointer); //we will not allow mistakes
        if(m_contentPointer)
        {
            return *(m_contentPointer);
        }
        else
        {
            return ContentType();
        }
    }

    ContentType& getReference()
    {
        assert(m_contentPointer); //we will not allow mistakes
        return *(m_contentPointer);
    }

    ContentType const& getConstReference() const
    {
        assert(m_contentPointer); //we will not allow mistakes
        return *(m_contentPointer);
    }

private:

    friend std::ostream & operator<<(std::ostream & out, AlbaOptional<ContentType> const& optional)
    {
        out << "hasContent: " << optional.hasContent();        if(optional.hasContent())
        {
            out << " value: " << optional.getConstReference();
        }
        return out;
    }

    std::unique_ptr<ContentType> m_contentPointer;
};
template <typename ContentType> class AlbaOptional<ContentType &>
{
public:

//#warning Please make sure that object still exists in the life time of an optional reference object


    AlbaOptional()
        : m_hasContent(false)
        , m_contentPointer(nullptr)    {}

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
    {        return m_contentPointer != nullptr;
    }

    bool m_hasContent;
    ContentType* m_contentPointer;
    static ContentType m_empty; //think of how to remove this


    friend std::ostream & operator<<(std::ostream & out, AlbaOptional<ContentType&> const& optional)
    {
        out << "hasContent: " << optional.m_hasContent;
        if(optional.m_hasContent)
        {
            out << " value: " << optional.get();
        }
        return out;
    }
};

template <typename ContentType> ContentType AlbaOptional<ContentType&>::m_empty;} // namespace alba
