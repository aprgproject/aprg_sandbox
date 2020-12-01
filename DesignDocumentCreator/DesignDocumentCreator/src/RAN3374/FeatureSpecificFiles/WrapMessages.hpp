#include <Common/Messages/MessageWrapper.hpp>
#include <AntennaCarrierAPI.h>
#include <BB_2_ConfigDataReq.h>
#include <oam_tcom.h>

namespace DesignDocumentCreator
{
WRAP_STATIC_MESSAGE(MessageName::TC_LTX_TELECOM_MSG, AntennaCarrier_PowerEventInd)
WRAP_STATIC_MESSAGE(MessageName::BB_RAKE_POWER_REPORT, BB_2_ConfigDataReq)
WRAP_STATIC_MESSAGE(MessageName::TC_HW_CONFIGURATION_MSG, SHwConfigurationMsg)
}
