#include "AddressHelper.hpp"

namespace DesignDocumentCreator
{

TAaSysComSicad AddressHelper::getAddress(ComponentName const componentName)
{
    TAaSysComSicad result=0x00000000;
    if(componentName == ComponentName::Oam)
    {
        result = 0x10110001;
    }
    return result;
}

}
