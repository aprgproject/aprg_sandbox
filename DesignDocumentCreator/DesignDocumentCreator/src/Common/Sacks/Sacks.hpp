#pragma once

#include <FeatureSpecificFiles/Sacks.hpp>

namespace DesignDocumentCreator
{

struct StaticPartSack
{
    int sampleStaticParameter;
};

struct DynamicArrayPartSack
{
    int dynamicArrayParameter;
};

struct DynamicPlaceHolderSack
{
    int dynamicPlaceHolderParameter;
};

struct DynamicPolymorphicPartSack
{
    int dynamicPolymorphicParameter;
};

struct StaticMessageSack
{
    int sampleParameter;
};

struct DynamicArrayMessageSack
{
    StaticPartSack staticPart;
    DynamicArrayPartSack dynamicPart[1];
};

struct DynamicPolymorphicMessageSack
{
    StaticPartSack staticPart;
    DynamicPlaceHolderSack dynamicPart;
};

struct SampleActualDynamicArrayMessageSack
{
    StaticPartSack staticPart;
    DynamicArrayPartSack dynamicPart[10];
};

struct SampleActualDynamicPolymorphicMessageSack
{
    StaticPartSack staticPart;
    DynamicPolymorphicPartSack dynamicPart;
};

}
