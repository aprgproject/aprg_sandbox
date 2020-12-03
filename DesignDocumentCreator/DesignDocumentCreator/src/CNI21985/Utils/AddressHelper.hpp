#pragma once

#include <Common/Components/ComponentName.hpp>
#include <TAaSysComSicad.h>

namespace DesignDocumentCreator
{

namespace AddressHelper
{
   TAaSysComSicad getAddress(ComponentName const componentName);
}

}
