#include "OtherEvent.hpp"

namespace DesignDocumentCreator {

OtherEvent::OtherEvent() : m_type(OtherEventType::Empty) {}

OtherEvent::OtherEvent(OtherEventType const timerType) : m_type(timerType) {}

OtherEventType OtherEvent::getType() const { return m_type; }

}  // namespace DesignDocumentCreator
