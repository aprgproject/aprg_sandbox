#pragma once

namespace DesignDocumentCreator
{

/* Global type defintions */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;     /* int == long */
typedef signed char    i8;
typedef signed short   i16;
typedef signed int     i32;     /* int == long */
typedef float          r32;     /* Do not use this in DSP */
typedef double         r64;     /* Do not use this in DSP */
typedef long double    r128;    /* Do not use this in DSP */
typedef unsigned char  *pu8;
typedef u8             *pu8h;
typedef unsigned short *pu16;
typedef unsigned int   *pu32;
typedef signed char    *pi8;
typedef signed short   *pi16;
typedef signed int     *pi32;

typedef unsigned long long u64;
typedef signed long long i64;

struct SampleSack
{
    int sampleParameter;
};

#include <EditableFiles/EditSacksIncludes.hpp>

}
