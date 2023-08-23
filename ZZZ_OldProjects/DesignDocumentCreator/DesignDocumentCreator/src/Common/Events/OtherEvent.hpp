#pragma once

#include <Common/Events/OtherEventType.hpp>

namespace DesignDocumentCreator {

class OtherEvent {
public:
    OtherEvent();
    OtherEvent(OtherEventType const timerType);
    OtherEventType getType() const;

private:
    OtherEventType m_type;
};

}  // namespace DesignDocumentCreator
