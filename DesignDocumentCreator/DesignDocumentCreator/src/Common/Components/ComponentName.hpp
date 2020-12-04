#pragma once

#include <vector>

namespace DesignDocumentCreator
{

enum class ComponentName
{
    Empty,
    SampleComponent
#define COMPONENT_NAME_MACRO(COMPONENT_NAME) ,COMPONENT_NAME
    #include <FeatureSpecificFiles/ComponentNameMacro.hpp>
#undef COMPONENT_NAME_MACRO

};
using ComponentNames = std::vector<ComponentName>;

}
