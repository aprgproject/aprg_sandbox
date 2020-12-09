#pragma once

#include <Common/Components/ComponentName.hpp>

#include <FeatureSpecificFiles/Sacks.hpp>
#include <IfAaSysCom_Defs.h>
#include <TAaSysComSicad.h>

namespace DesignDocumentCreator
{

namespace AddressHelper
{
    using TAaSysComNids = std::vector<TAaSysComNid>;
    TAaSysComSicad getAddress(ComponentName const componentName);
    TTask getTask(ComponentName const componentName);
    TAaSysComNids getRlhNids(STCWamAddressIndNew const& wamAddressInd);
    TAaSysComSicad createSicad(TAaSysComNid const nid, TTask const taskId);
    TAaSysComSicad getNid(TAaSysComSicad const sicad);
}

}
