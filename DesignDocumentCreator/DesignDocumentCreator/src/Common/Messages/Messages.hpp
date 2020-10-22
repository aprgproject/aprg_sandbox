#pragma once

#include <Common/Messages/GenericMessage.hpp>
#include <Common/Messages/MessageConverters.hpp>
#include <Common/Messages/MessageWrapper.hpp>
#include <Common/Messages/SpecificMessage.hpp>
#include <Common/Sacks/Sacks.hpp>

namespace DesignDocumentCreator
{

WRAP_MESSAGE(MessageName::MESSAGE_SAMPLE, SampleSack)
#include <EditableFiles/EditWrapMessage.hpp>

}
