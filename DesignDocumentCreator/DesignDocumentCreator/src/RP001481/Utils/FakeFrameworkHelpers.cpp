#include "FakeFrameworkHelpers.hpp"

namespace DesignDocumentCreator
{

TAaSysComSicad FakeFrameworkHelpers::getAddress(ComponentName const componentName)
{
    TAaSysComSicad result=0x00000000;
    //if(componentName == ComponentName::Oam)
    //{
        //result = 0x10110001;
    //}
    return result;
}

/*unsigned int FakeFrameworkHelpers::calculatePowerGroup(TAaSysComNid nidAddress) //from TOAM's code
{
    //old algorithm
    unsigned int BoardIndex = (nidAddress>>8) & 0xF;
    unsigned int CpuIndex = (nidAddress>>4) & 0xF;
    return ((BoardIndex - 2) * 2) + (CpuIndex / 5) + 1;
}
*/

}
