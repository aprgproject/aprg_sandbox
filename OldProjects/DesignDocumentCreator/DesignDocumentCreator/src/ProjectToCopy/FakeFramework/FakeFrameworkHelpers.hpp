#pragma once

#include <Common/Components/ComponentName.hpp>
#include <TAaSysComSicad.h>

namespace DesignDocumentCreator {

namespace FakeFrameworkHelpers {
TAaSysComSicad getAddress(ComponentName const componentName);
}

}  // namespace DesignDocumentCreator
