#pragma once

#include <Common/Components/Components.hpp>
#include <Common/Uml/UmlLogger.hpp>

#include <optional>

namespace DesignDocumentCreator {

class Environment {
private:
    Environment();

public:
    struct ResetableMembers {
        Components components;
        UmlLogger umlLogger;
    };
    static Environment& getInstance();
    Environment(Environment const&) = delete;
    void operator=(Environment const&) = delete;
    void clear();
    void execute();
    Components& getComponentsReference();
    UmlLogger& getUmlLogger();
    Component* getComponentPointer(ComponentName const componentName);
    void send(GenericMessage const& message);
    void send(ComponentName const sender, ComponentName const receiver, GenericMessage const& message);

private:
    std::optional<ResetableMembers> m_resetableMembers;
    void performSend(GenericMessage const& messageToRoute);
};

}  // namespace DesignDocumentCreator
