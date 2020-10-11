#pragma once

#include <TcomToolsConfiguration.hpp>

namespace tcomToolsGui
{

class StepHandler
{
public:
    StepHandler(TcomToolsConfiguration & configuration);
    void execute() const;
private:
    void executeExtractStep(alba::AlbaWindowsPathHandler & currentPathHandler) const;
    void executeCombineAndSortStep(alba::AlbaWindowsPathHandler & currentPathHandler) const;    void executeGrep(alba::AlbaWindowsPathHandler & currentPathHandler) const;
    TcomToolsConfiguration & m_configuration;
};
}
