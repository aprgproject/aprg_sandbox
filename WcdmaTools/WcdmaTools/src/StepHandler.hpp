#pragma once

#include <WcdmaToolsConfiguration.hpp>

namespace wcdmaToolsGui {

class StepHandler {
public:
    StepHandler();
    void execute(WcdmaToolsConfiguration const& configuration) const;

private:
    std::string executeExtractStep(WcdmaToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string executeCombineAndSortStep(
        WcdmaToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string executeGrepStep(WcdmaToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string executeCropStep(WcdmaToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string getTempFileFor7zBasedOnLogSorter(WcdmaToolsConfiguration const& configuration) const;
};

}  // namespace wcdmaToolsGui
