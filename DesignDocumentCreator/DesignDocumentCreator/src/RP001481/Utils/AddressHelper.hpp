#pragma once

#include <Common/Components/ComponentName.hpp>
#include <TAaSysComSicad.h>

namespace DesignDocumentCreator
{

namespace AddressHelper
{
   TAaSysComSicad getAddress(ComponentName const componentName);
   //unsigned int calculatePowerGroup(TAaSysComNid nidAddress); //from TOAM's code, this should be specified in specification as well.
}

}
