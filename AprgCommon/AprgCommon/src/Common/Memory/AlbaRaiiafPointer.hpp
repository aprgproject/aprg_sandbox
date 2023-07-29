#pragma once

#include <cassert>
#include <functional>

namespace alba {

// RAIIAF
// Resource Aquisition Is In A Function
// anti RAII :(

template <typename ContentType>
class AlbaRaiiafPointer {
public:
    // rule of five or six
    AlbaRaiiafPointer() : m_voidPointer(nullptr) {}

    ~AlbaRaiiafPointer() {
        assert(!hasContent());
        // deAllocate(); // this is Raiiaf so we dont delete here
    }

    AlbaRaiiafPointer(AlbaRaiiafPointer const &) = delete;
    AlbaRaiiafPointer &operator=(AlbaRaiiafPointer const &) = delete;
    AlbaRaiiafPointer(AlbaRaiiafPointer &&) = delete;
    AlbaRaiiafPointer &operator=(AlbaRaiiafPointer &&) = delete;

    ContentType get() { return *(static_cast<ContentType *>(m_voidPointer)); }

    ContentType &getReference() { return *(static_cast<ContentType *>(m_voidPointer)); }

    void deAllocate() {
        // Even if it is safe to delete a pointer with nullptr, lets not just do it to remove potential overhead.
        if (hasContent()) {
            delete (static_cast<ContentType *>(m_voidPointer));
            m_voidPointer = nullptr;
        }
    }

    void setAndAllocateNewContent(ContentType const &reference) {
        assert(!hasContent());
        m_voidPointer = new ContentType(reference);
    }

private:
    bool hasContent() const { return m_voidPointer != nullptr; }
    void *m_voidPointer;
};

}  // namespace alba
