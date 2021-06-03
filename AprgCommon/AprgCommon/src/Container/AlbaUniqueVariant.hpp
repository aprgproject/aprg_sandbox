#pragma once

#include <Types/AlbaTypeId.hpp>

#include <type_traits>

namespace alba
{

namespace detail
{

// Purpose: Search type from list of types which have biggest size
template <class MaxType, class... Types>
struct MaxSizeTypeImpl;

template <class MaxType, class Type, class... Types>
struct MaxSizeTypeImpl<MaxType, Type, Types...>
{
    typedef typename std::conditional<
        (sizeof(MaxType) > sizeof(Type)),
        typename MaxSizeTypeImpl<MaxType, Types...>::type,
        typename MaxSizeTypeImpl<Type, Types...>::type
    >::type type;
};

template <class MaxType>
struct MaxSizeTypeImpl<MaxType>
{
    typedef MaxType type;
};

template <class... Types>
struct MaxSizeType
{
    typedef typename MaxSizeTypeImpl<char, Types...>::type type;
};

// Purpose: Checks if all types derive from base type
template <class Base, class... Types>
struct CheckIfDerive;

template <class Base, class Derived, class... Types>
struct CheckIfDerive<Base, Derived, Types...>
{
    static_assert(std::is_base_of<Base, Derived>::value,
                  "Class in UniqueVariant does not derive from VariantDataType");
    typedef CheckIfDerive<Base, Types...> next;
};

template <class Base>
struct CheckIfDerive<Base>
{
    typedef void next;
};

// Purpose: Checks if type is in types list
template <class Type, class... Types>
struct CheckIfInList;

template <class Type, class Head, class... Types>
struct CheckIfInList<Type, Head, Types...>
{
    typedef typename std::conditional<
        std::is_same<Type, Head>::value,
        std::integral_constant<bool, true>,
        typename CheckIfInList<Type, Types...>::type
    >::type type;
};

template <class Type>
struct CheckIfInList<Type>
{
    typedef std::integral_constant<bool, false> type;
};

} // namespace detail

// Purpose: Variant type base class
class VariantDataType
{
public:
    VariantDataType() = default;
    VariantDataType(VariantDataType const& v) = delete;
    VariantDataType& operator=(VariantDataType const& v) = delete;
    virtual ~VariantDataType(){}
};

// Purpose: A compile-time checking unique variant class
template <class... Types>
class UniqueVariant
{

typedef typename detail::CheckIfDerive<VariantDataType, Types...>::next CheckIfAllClassesDerive;
typedef typename detail::MaxSizeType<Types...>::type MaxSizeClass;

public:
    UniqueVariant<Types...>()
        : m_ptr(nullptr)
        , m_typeId(0)
    {
        allocate();
    }

    template <class T>
    T & acquire()
    {
        static_assert(detail::CheckIfInList<T, Types...>::type::value,
                      "Aquiring type from unique variant that doesn't exists");
        constructIfNeeded<T>();
        return getValue<T>();
    }

    void clear()
    {
        if (m_typeId)
        {
            m_ptr->~VariantDataType();
        }
        m_typeId = 0;
    }

    ~UniqueVariant()
    {
        if (m_typeId)
        {
            delete m_ptr;
        }
        else
        {
            ::operator delete (m_ptr);
        }
    }

private:
    void allocate()
    {
        delete m_ptr;
        m_ptr = static_cast<VariantDataType*> (::operator new (sizeof(MaxSizeClass)));
    }

    template <class T>
    void constructIfNeeded()
    {
        if (!m_typeId)
        {
            placementNew<T>();
        }
        else if (m_typeId != GetTypeId<T>())
        {
            m_ptr->~VariantDataType();
            placementNew<T>();
        }
    }

    template <class T>
    void placementNew()
    {
        updateTypeId<T>();
        m_ptr = static_cast<VariantDataType*>(new (m_ptr) T);
    }

    template <class T>
    void updateTypeId()
    {
        m_typeId = GetTypeId<T>();
    }

    template <class T>
    T & getValue()
    {
        return *static_cast<T*>(m_ptr);
    }

    VariantDataType * m_ptr;
    TypeId m_typeId;
};

} // namespace alba
