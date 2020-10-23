#pragma once

#include <string>

namespace DesignDocumentCreator
{

enum class ComponentName
{
    EMPTY,
    SampleComponent
#include <FeatureSpecificFiles/ComponentName.hpp>

};

}
