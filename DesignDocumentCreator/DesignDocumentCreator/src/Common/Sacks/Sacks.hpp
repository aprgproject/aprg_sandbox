#pragma once

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
    int dynamicArrayParameter;
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

#include <FeatureSpecificFiles/Sacks.hpp>

}
