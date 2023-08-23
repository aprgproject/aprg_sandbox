#include "FakeFrameworkHelpers.hpp"

namespace DesignDocumentCreator {

TAaSysComSicad FakeFrameworkHelpers::getAddress(ComponentName const componentName) {
    TAaSysComSicad result = 0x00000000;
    // if(componentName == ComponentName::Oam)
    //{
    // result = 0x10110001;
    //}
    return result;
}

}  // namespace DesignDocumentCreator
