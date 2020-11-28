#pragma once

#include <string>

namespace DesignDocumentCreator
{

enum class ComponentName
{
    EMPTY,
    SampleComponent

#define COMPONENT_NAME_MACRO(COMPONENT_NAME) ,COMPONENT_NAME
    #include <FeatureSpecificFiles/ComponentNameMacro.hpp>
#undef COMPONENT_NAME_MACRO

};

}