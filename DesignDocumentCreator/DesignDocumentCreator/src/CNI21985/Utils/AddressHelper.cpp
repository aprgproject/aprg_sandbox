#include "AddressHelper.hpp"

namespace DesignDocumentCreator
{

TAaSysComSicad AddressHelper::getAddress(ComponentName const componentName)
{
    //this is fake, use framework function
    TAaSysComSicad result=0;
    if(componentName == ComponentName::TupcTbm)
    {
        TTask const TASK_TUPC_TBM = 0x1000;
        result = createSicad(0x100, TASK_TUPC_TBM);
    }
    else if(componentName == ComponentName::TupcCm)
    {
        TTask const TASK_TUPC_CM = 0x2000;
        result = createSicad(0x200, TASK_TUPC_CM);
    }
    else if(componentName == ComponentName::Oam)
    {
        TTask const TASK_OAM = 0x3000;
        result = createSicad(0x300, TASK_OAM);
    }
    return result;
}

TTask AddressHelper::getTask(ComponentName const componentName)
{
    //this is fake, use framework function
    TTask result=0;
    if(componentName == ComponentName::TupcTbm)
    {
        TTask const TASK_TUPC_TBM = 0x1000;
        result = TASK_TUPC_TBM;
    }
    else if(componentName == ComponentName::TupcCm)
    {
        TTask const TASK_TUPC_CM = 0x2000;
        result = TASK_TUPC_CM;
    }
    else if(componentName == ComponentName::Oam)
    {
        TTask const TASK_OAM = 0x3000;
        result = TASK_OAM;
    }
    return result;
}

AddressHelper::TAaSysComNids AddressHelper::getRlhNids(STCWamAddressIndNew const&)
{
    //this is fake, use framework function
    return TAaSysComNids{0x120d};
}

TAaSysComSicad AddressHelper::createSicad(TAaSysComNid const nid, TTask const taskId)
{
    //this is fake, use framework function
    return nid<<16 | taskId;
}

TAaSysComSicad AddressHelper::getNid(TAaSysComSicad const sicad)
{
    //this is fake, use framework function
    return sicad>>16;
}


}
