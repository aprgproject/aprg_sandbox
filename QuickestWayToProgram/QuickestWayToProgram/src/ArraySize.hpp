/*
 * Get the size of Array
 */
#ifndef ARRAY_SIZE_HPP
#define ARRAY_SIZE_HPP

#include <stddef.h>

template <typename Element, size_t n>
constexpr size_t arraySize(Element(&)[n])
{
    return n;
}

#endif


