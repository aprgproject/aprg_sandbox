#pragma once

#include <Common/Messages/GenericMessage.hpp>
#include <SLrmConfigurationDataInd.h>

namespace DesignDocumentCreator {

namespace MessageFactory {
GenericMessage createLrmConfigurationDataForMoreThan2K2sWithNbic();
void saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbic(SLrmConfigurationDataInd& payload);
void saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbicWith2Fsps(SLrmConfigurationDataInd& payload);
void saveLrmConfigurationDataPayloadForMoreThan2K2sWithNbicWithWrongPowerGroup(SLrmConfigurationDataInd& payload);
void saveLrmConfigurationDataPayloadForPrioritizationNumberMcdCcdDInFspForMcdCcdD(SLrmConfigurationDataInd& payload);
void saveLrmConfigurationDataPayloadForPrioritizationNumberK2sForMcdCcdD(SLrmConfigurationDataInd& payload);
}  // namespace MessageFactory

}  // namespace DesignDocumentCreator
