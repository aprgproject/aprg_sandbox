#pragma once

#include <functional>

namespace alba {

namespace algorithm {

template <typename Object>
class BaseBag  // Bag data stucture just collects data and can traverse the data (order does not matter)
{
public:
    using TraverseFunction = std::function<void(Object const& object)>;

    virtual ~BaseBag() = default;  // virtual destructor because of virtual functions (vtable exists)

    virtual bool isEmpty() const = 0;
    virtual unsigned int getSize() const = 0;
    virtual void add(Object const& object) = 0;
    virtual void traverse(TraverseFunction const& traverseFunction) = 0;
};

}  // namespace algorithm

}  // namespace alba
