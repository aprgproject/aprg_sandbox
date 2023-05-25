#pragma once

namespace alba {

namespace algorithm {

template <typename Object>
class BaseQueue {
public:
    virtual ~BaseQueue() = default;  // virtual destructor because of virtual functions (vtable exists)

    virtual bool isEmpty() const = 0;
    virtual int getSize() const = 0;
    virtual void enqueue(Object const& object) = 0;  // Add item to the end of the list
    virtual Object dequeue() = 0;                    // Remove item from the beginning of the list
};

}  // namespace algorithm

}  // namespace alba
