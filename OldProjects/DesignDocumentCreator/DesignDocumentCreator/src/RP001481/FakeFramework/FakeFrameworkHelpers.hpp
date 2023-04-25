#pragma once

#include <Common/Components/ComponentName.hpp>
#include <IfAaSysCom_Defs.h>
#include <TAaSysComSicad.h>

namespace DesignDocumentCreator {

namespace FakeFrameworkHelpers {
TAaSysComNid const INVALID_DSP_ADDRESS = 0xFFFF;
TAaSysComSicad getAddress(ComponentName const componentName);
// unsigned int calculatePowerGroup(TAaSysComNid nidAddress); //from TOAM's code, this should be specified in
// specification as well.
}  // namespace FakeFrameworkHelpers

}  // namespace DesignDocumentCreator
