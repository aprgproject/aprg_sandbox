#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>
#include <Common/Types/AlbaTypeId.hpp>

namespace alba {

namespace detail {

// Purpose: Search type from list of types which have biggest size
template <class MaxType, class... Types>
struct MaxSizeTypeImpl;

template <class MaxType, class Type, class... Types>
struct MaxSizeTypeImpl<MaxType, Type, Types...> {
    using type = typeHelper::ConditionalType<
        (sizeof(MaxType) > sizeof(Type)), typename MaxSizeTypeImpl<MaxType, Types...>::type,
        typename MaxSizeTypeImpl<Type, Types...>::type>;
};

template <class MaxType>
struct MaxSizeTypeImpl<MaxType> {
    using type = MaxType;
};

template <class... Types>
struct MaxSizeType {
    using type = typename MaxSizeTypeImpl<char, Types...>::type;
};

// Purpose: Checks if all types derive from base type
template <class Base, class... Types>
struct CheckIfDerive;

template <class Base, class Derived, class... Types>
struct CheckIfDerive<Base, Derived, Types...> {
    static_assert(typeHelper::isBaseOf<Base, Derived>(), "Class in UniqueVariant does not derive from VariantDataType");
    using next = CheckIfDerive<Base, Types...>;
};

template <class Base>
struct CheckIfDerive<Base> {
    using next = void;
};

// Purpose: Checks if type is in types list
template <class Type, class... Types>
struct CheckIfInList;

template <class Type, class Head, class... Types>
struct CheckIfInList<Type, Head, Types...> {
    using type = typeHelper::ConditionalType<
        typeHelper::areSameTypes<Type, Head>(), std::integral_constant<bool, true>,
        typename CheckIfInList<Type, Types...>::type>;
};

template <class Type>
struct CheckIfInList<Type> {
    using type = std::integral_constant<bool, false>;
};

}  // namespace detail

// Purpose: Variant type base class
class VariantDataType {
public:
    // rule of five or six
    VariantDataType() = default;
    virtual ~VariantDataType() = default;  // virtual destructor because derived classes need this
    VariantDataType(VariantDataType const &) = delete;
    VariantDataType &operator=(VariantDataType const &) = delete;
    VariantDataType(VariantDataType &&) = delete;
    VariantDataType &operator=(VariantDataType &&) = delete;
};

// Purpose: A compile-time checking unique variant class
template <class... Types>
// class [[deprecated("Use std::variant instead! (needs c++17)")]] UniqueVariant // lets remove [[deprecated]] to avoid
// unnecessary warnings
class UniqueVariant {
    using CheckIfAllClassesDerive = typename detail::CheckIfDerive<VariantDataType, Types...>::next;
    using MaxSizeClass = typename detail::MaxSizeType<Types...>::type;

public:
    UniqueVariant<Types...>() : m_ptr(nullptr), m_typeId(0) { allocate(); }

    template <class T>
    T &acquire() {
        static_assert(
            detail::CheckIfInList<T, Types...>::type::value, "Aquiring type from unique variant that doesn't exists");
        constructIfNeeded<T>();
        return getValue<T>();
    }

    void clear() {
        if (m_typeId) {
            m_ptr->~VariantDataType();
        }
        m_typeId = 0;
    }

    ~UniqueVariant() {
        if (m_typeId) {
            delete m_ptr;
        } else {
            ::operator delete(m_ptr);
        }
    }

private:
    void allocate() {
        delete m_ptr;
        m_ptr = static_cast<VariantDataType *>(::operator new(sizeof(MaxSizeClass)));
    }

    template <class T>
    void constructIfNeeded() {
        if (!m_typeId) {
            placementNew<T>();
        } else if (m_typeId != GetTypeId<T>()) {
            m_ptr->~VariantDataType();
            placementNew<T>();
        }
    }

    template <class T>
    void placementNew() {
        updateTypeId<T>();
        m_ptr = static_cast<VariantDataType *>(new (m_ptr) T);
    }

    template <class T>
    void updateTypeId() {
        m_typeId = GetTypeId<T>();
    }

    template <class T>
    T &getValue() {
        return *static_cast<T *>(m_ptr);
    }

    VariantDataType *m_ptr;
    TypeId m_typeId;
};

}  // namespace alba
