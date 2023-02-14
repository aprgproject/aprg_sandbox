#pragma once

#include <cstdint>
#include <memory>

namespace alba
{
typedef uintptr_t TypeId;

namespace detail{

// generates unique integer type id, as an address of static method
template <class T>
class TypeIdGenerator
{
public:
    static TypeId GetTypeId()
    {
        return reinterpret_cast<TypeId>(std::addressof(GetTypeId));
    }
};
} // namespace details

template <class T>TypeId GetTypeId()
{
    return detail::TypeIdGenerator<T>::GetTypeId();
}

} // namespace alba
