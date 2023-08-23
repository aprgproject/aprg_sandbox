#include "FakeFrameworkHelpers.hpp"

namespace DesignDocumentCreator {

// this are FAKES, use framework function

TAaSysComSicad FakeFrameworkHelpers::getAddress(ComponentName const componentName) {
    TAaSysComSicad result = 0;
    if (componentName == ComponentName::TupcTbm) {
        TTask const TASK_TUPC_TBM = 0x1000;
        result = createSicad(0x100, TASK_TUPC_TBM);
    } else if (componentName == ComponentName::TupcCm) {
        TTask const TASK_TUPC_CM = 0x2000;
        result = createSicad(0x200, TASK_TUPC_CM);
    } else if (componentName == ComponentName::Oam) {
        TTask const TASK_OAM = 0x3000;
        result = createSicad(0x300, TASK_OAM);
    }
    return result;
}

TTask FakeFrameworkHelpers::getTask(ComponentName const componentName) {
    TTask result = 0;
    if (componentName == ComponentName::TupcTbm) {
        TTask const TASK_TUPC_TBM = 0x1000;
        result = TASK_TUPC_TBM;
    } else if (componentName == ComponentName::TupcCm) {
        TTask const TASK_TUPC_CM = 0x2000;
        result = TASK_TUPC_CM;
    } else if (componentName == ComponentName::Oam) {
        TTask const TASK_OAM = 0x3000;
        result = TASK_OAM;
    }
    return result;
}

FakeFrameworkHelpers::TAaSysComNids FakeFrameworkHelpers::getRlhNids(STCWamAddressIndNew const&) {
    return TAaSysComNids{0x120d};
}

TAaSysComSicad FakeFrameworkHelpers::createSicad(TAaSysComNid const nid, TTask const taskId) {
    return nid << 16 | taskId;
}

TAaSysComSicad FakeFrameworkHelpers::getNid(TAaSysComSicad const sicad) { return sicad >> 16; }

}  // namespace DesignDocumentCreator
