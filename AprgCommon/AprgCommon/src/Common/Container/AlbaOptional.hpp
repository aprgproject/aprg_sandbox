
#pragma once

#include <cassert>
#include <memory>
#include <ostream>

namespace alba {

template <typename ContentType>
// class [[deprecated("Use std::optional instead! (needs c++17)")]] AlbaOptional // lets remove [[deprecated]] to avoid
// unnecessary warnings
class AlbaOptional {
    // This requires copy constructor and default constructor on ContentType
public:
    AlbaOptional() = default;

    AlbaOptional(ContentType content) : m_contentPointer(std::make_unique<ContentType>(content)) {}

    AlbaOptional(ContentType& content) : m_contentPointer(std::make_unique<ContentType>(content)) {}

    AlbaOptional(AlbaOptional const& optional) {
        if (optional.m_contentPointer) {
            m_contentPointer = std::make_unique<ContentType>(*(optional.m_contentPointer));
        }
    }

    AlbaOptional(AlbaOptional&& optional) : m_contentPointer(std::move(optional.m_contentPointer)) {}

    AlbaOptional& operator=(AlbaOptional const& optional) {
        if (optional.m_contentPointer) {
            m_contentPointer = std::make_unique<ContentType>(*(optional.m_contentPointer));
        }
        return *this;
    }

    AlbaOptional& operator=(AlbaOptional&& optional) {
        m_contentPointer = std::move(optional.m_contentPointer);
        return *this;
    }

    explicit operator bool() const { return hasContent(); }

    operator ContentType() const { return get(); }

    void createObjectUsingDefaultConstructor() { m_contentPointer = std::make_unique<ContentType>(); }

    void setValue(ContentType content) {
        if (m_contentPointer) {
            *m_contentPointer = content;
        } else {
            m_contentPointer = std::make_unique<ContentType>(content);
        }
    }

    void setConstReference(ContentType const& content) {
        if (m_contentPointer) {
            *m_contentPointer = content;
        } else {
            m_contentPointer = std::make_unique<ContentType>(content);
        }
    }

    void clear() { m_contentPointer.reset(); }

    bool hasContent() const { return static_cast<bool>(m_contentPointer); }

    ContentType get() const {
        assert(m_contentPointer);  // not allowing any mistakes
        if (m_contentPointer) {
            return *(m_contentPointer);
        } else {
            return ContentType();
        }
    }

    ContentType& getReference() {
        assert(m_contentPointer);  // not allowing any mistakes
        return *(m_contentPointer);
    }

    ContentType const& getConstReference() const {
        assert(m_contentPointer);  // not allowing any mistakes
        return *(m_contentPointer);
    }

private:
    friend std::ostream& operator<<(std::ostream& out, AlbaOptional const& optional) {
        out << "hasContent: " << optional.hasContent();
        if (optional.hasContent()) {
            out << " value: " << optional.getConstReference();
        }
        return out;
    }

    std::unique_ptr<ContentType> m_contentPointer;
};

template <typename ContentType>
// class [[deprecated("Check if std::reference_wrapper can be used instead.")]] AlbaOptional
// lets remove [[deprecated]] to avoid unnecessary warnings
class AlbaOptional<ContentType&> {
public:
    //#warning Please make sure that object still exists in the life time of an optional reference object

    AlbaOptional() : m_hasContent(false), m_contentPointer(nullptr) {}

    AlbaOptional(ContentType& content)
        : m_hasContent(true),
          m_contentPointer(std::addressof(content))  // std::addressof should be used because & might be overloaded
    {}

    AlbaOptional(AlbaOptional<ContentType&> const& optional)
        : m_hasContent(optional.m_hasContent), m_contentPointer(optional.m_contentPointer) {}

    AlbaOptional& operator=(AlbaOptional<ContentType&> const& optional) {
        m_hasContent = optional.m_hasContent;
        m_contentPointer = optional.m_contentPointer;
        return *this;
    }

    void setValue(ContentType content) {
        if (m_hasContent && isContentPointerValid()) {
            *m_contentPointer = content;
        }
    }

    void setReference(ContentType& content) {
        m_hasContent = true;
        m_contentPointer = std::addressof(content);
    }

    void clear() {
        m_hasContent = false;
        m_contentPointer = nullptr;
    }

    bool hasContent() const { return m_hasContent; }

    ContentType& get() const {
        if (m_hasContent && isContentPointerValid()) {
            return *m_contentPointer;
        }
        return m_empty;
    }

    explicit operator bool() const { return m_hasContent; }

    operator ContentType&() const {
        if (m_hasContent && isContentPointerValid()) {
            return *m_contentPointer;
        }
        return m_empty;
    }

private:
    inline bool isContentPointerValid() const { return m_contentPointer != nullptr; }

    bool m_hasContent;
    ContentType* m_contentPointer;
    static ContentType m_empty;  // think of how to remove this

    friend std::ostream& operator<<(std::ostream& out, AlbaOptional<ContentType&> const& optional) {
        out << "hasContent: " << optional.m_hasContent;
        if (optional.m_hasContent) {
            out << " value: " << optional.get();
        }
        return out;
    }
};

template <typename ContentType>
ContentType AlbaOptional<ContentType&>::m_empty;
}  // namespace alba
