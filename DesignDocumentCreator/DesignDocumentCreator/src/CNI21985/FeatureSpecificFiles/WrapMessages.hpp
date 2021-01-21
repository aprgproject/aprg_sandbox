#pragma once

#include <Common/Messages/MessageWrapper.hpp>

#include <FeatureSpecificFiles/Sacks.hpp>
#include <oam_tcom.h>
#include <STransportBearerRegisterMsg.h>
#include <STransportBearerRegisterResponseMsg.h>
#include <STransportBearerUnregisterMsg.h>
#include <STransportBearerUnregisterResponseMsg.h>
#include <STransportBearerReallocationPrepareReq.h>
#include <STransportBearerReallocationPrepareResp.h>
#include <STransportBearerReallocationCommitReq.h>
#include <STransportBearerReallocationCommitResp.h>
#include <STransportBearerReallocationCleanupReq.h>
#include <STransportBearerReallocationCleanupResp.h>
#include <STransportBearerReallocationCancelReq.h>
#include <STransportBearerReallocationCancelResp.h>
#include <STransportBearerModificationCancelReq.h>
#include <STransportBearerModificationCancelResp.h>
#include <STransportBearerModificationCommitReq.h>
#include <STransportBearerModificationCommitResp.h>
#include <STransportBearerModificationPrepareReq.h>
#include <STransportBearerModificationPrepareResp.h>
#include <STransportBearerSetupMsg.h>
#include <STransportBearerReleaseMsg.h>
#include <TUP_TransportConnectionSetupReq.h>
#include <TUP_TransportConnectionSetupResp.h>
#include <TUP_TransportConnectionReleaseReq.h>
#include <TUP_TransportConnectionReleaseResp.h>
#include <TUP_TransportConnectionTransferReq.h>
#include <TUP_TransportConnectionTransferResp.h>

namespace DesignDocumentCreator
{

WRAP_STATIC_MESSAGE(MessageName::OAM_ATM_HW_CONFIGURATION_MSG, SAtmHwConfigurationMsgFake)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TUP_CmConfigurationCmd_Msg, TUP_CmConfigurationCmd, SFspInformation)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG, STransportBearerRegisterMsg, STransportBearerLocationData)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TC_TRANSPORT_BEARER_REGISTER_RESP_MSG, STransportBearerRegisterResponseMsg, STransportBearerSignallingData)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TC_TRANSPORT_BEARER_UNREGISTER_MSG, STransportBearerUnregisterMsg, TTransportBearerId)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_UNREGISTER_RESP_MSG, STransportBearerUnregisterResponseMsg)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TC_TRANSPORT_BEARER_REALLOCATION_PREPARE_REQ_MSG, STransportBearerReallocationPrepareReq, STransportBearerReallocationData)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_REALLOCATION_PREPARE_RESP_MSG, STransportBearerReallocationPrepareResp)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_REALLOCATION_COMMIT_REQ_MSG, STransportBearerReallocationCommitReq)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_REALLOCATION_COMMIT_RESP_MSG, STransportBearerReallocationCommitResp)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_REALLOCATION_CLEANUP_REQ_MSG, STransportBearerReallocationCleanupReq)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_REALLOCATION_CLEANUP_RESP_MSG, STransportBearerReallocationCleanupResp)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_REALLOCATION_CANCEL_REQ_MSG, STransportBearerReallocationCancelReq)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_REALLOCATION_CANCEL_RESP_MSG, STransportBearerReallocationCancelResp)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_MODIFICATION_CANCEL_REQ_MSG, STransportBearerModificationCancelReq)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_MODIFICATION_CANCEL_RESP_MSG, STransportBearerModificationCancelResp)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_MSG, STransportBearerModificationCommitReq)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_RESP_MSG, STransportBearerModificationCommitResp)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_REQ_MSG, STransportBearerModificationPrepareReq, STransportBearerModificationData)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_RESP_MSG, STransportBearerModificationPrepareResp)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_SETUP_MSG, STransportBearerSetupMsg)
WRAP_STATIC_MESSAGE(MessageName::TC_TRANSPORT_BEARER_RELEASE_MSG, STransportBearerReleaseMsg)
WRAP_STATIC_MESSAGE(MessageName::TUP_TRANSPORT_CONNECTION_SETUP_REQ_MSG, TUP_TransportConnectionSetupReq)
WRAP_STATIC_MESSAGE(MessageName::TUP_TRANSPORT_CONNECTION_SETUP_RESP_MSG, TUP_TransportConnectionSetupResp)
WRAP_STATIC_MESSAGE(MessageName::TUP_TRANSPORT_CONNECTION_RELEASE_REQ_MSG, TUP_TransportConnectionReleaseReq)
WRAP_STATIC_MESSAGE(MessageName::TUP_TRANSPORT_CONNECTION_RELEASE_RESP_MSG, TUP_TransportConnectionReleaseResp)
WRAP_STATIC_MESSAGE(MessageName::TUP_TRANSPORT_CONNECTION_TRANSFER_REQ_MSG, TUP_TransportConnectionTransferReq)
WRAP_STATIC_MESSAGE(MessageName::TUP_TRANSPORT_CONNECTION_TRANSFER_RESP_MSG, TUP_TransportConnectionTransferResp)
WRAP_STATIC_MESSAGE(MessageName::TC_HW_CONFIGURATION_MSG, SHwConfigurationMsg)
WRAP_STATIC_MESSAGE(MessageName::TC_HW_CONFIGURATION_RESP_MSG, SHwConfigurationResponseMsg)
WRAP_STATIC_MESSAGE(MessageName::TC_HW_CONFIGURATION_CHANGE_MSG, SHwConfigurationChangeMsg)
WRAP_STATIC_MESSAGE(MessageName::TC_TCOM_DEPLOYMENT_IND_MSG, STcomDeploymentIndMsg)
WRAP_STATIC_MESSAGE(MessageName::TC_LINK_STATES_MSG, SLinkStatesMsg)
WRAP_STATIC_MESSAGE(MessageName::TC_LINK_STATES_RESP_MSG, SLinkStatesResponseMsg)
WRAP_STATIC_MESSAGE(MessageName::TUPC_TBM_CONFIGURATION_MSG, STupcTbmConfigurationMsg)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TUP_CM_BEARERS_SETUP_REQ_MSG, SCmBearersSetupReqMsg, SCmBearersSetupReqDynamicPart)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TUP_CM_BEARERS_SETUP_RESP_MSG, SCmBearersSetupRespMsg, SCmBearersSetupRespDynamicPart)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TUP_CM_BEARERS_RELEASE_REQ_MSG, SCmBearersReleaseReqMsg, SCmBearersReleaseReqDynamicPart)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TUP_CM_BEARERS_RELEASE_RESP_MSG, SCmBearersReleaseRespMsg, SCmBearersReleaseRespDynamicPart)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TUP_CM_BEARERS_MODIFY_REQ_MSG, SCmBearersModifyReqMsg, SCmBearersModifyReqDynamicPart)
WRAP_STATIC_MESSAGE(MessageName::TUP_CM_BEARERS_MODIFY_RESP_MSG, SCmBearersModifyRespMsg)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::TUP_CM_BEARERS_UPDATE_IND_MSG, SCmBearersUpdateIndMsg, SCmBearersUpdateIndDynamicPart)


}
