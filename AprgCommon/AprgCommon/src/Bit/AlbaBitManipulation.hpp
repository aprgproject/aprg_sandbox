#pragma once

#include <cassert>

namespace alba
{

template <typename DataTypeToManipulate>
class AlbaBitManipulation
{

public:
    AlbaBitManipulation() = delete;

    template <typename ArgumentType, typename... Arguments>
    static constexpr DataTypeToManipulate concatenateBytes(ArgumentType const currentByte, Arguments const... arguments)
    {
        static_assert(sizeof(ArgumentType) == 1, "concatenateBytes: ArgumentType size is greater than a byte");
        static_assert(sizeof(DataTypeToManipulate) > sizeof...(Arguments), "concatenateBytes: DataTypeToManipulate size is greater than Arguments size");
        return (currentByte << (sizeof...(Arguments) * byteSizeInBits)) | concatenateBytes(arguments...);
    }

    template <unsigned char position>
    static constexpr unsigned char getByteAtLeastSignificantPosition(DataTypeToManipulate const value)
    {
        static_assert(sizeof(DataTypeToManipulate) > position, "getByteAtLeastSignificantPosition: position is greater than DataTypeToManipulate size");
        return value >> (position * byteSizeInBits);
    }

    static unsigned char const byteSizeInBits = 8;

private:
    template <typename ArgumentType>
    static constexpr DataTypeToManipulate concatenateBytes(ArgumentType arg)
    {
        static_assert(sizeof(ArgumentType) == 1, "concatenateBytes: ArgumentType size is greater than a byte");
        return arg;
    }

};

}



