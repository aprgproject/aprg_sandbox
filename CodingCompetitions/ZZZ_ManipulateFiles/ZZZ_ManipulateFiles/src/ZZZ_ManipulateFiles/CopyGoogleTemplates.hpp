#pragma once

#include <string>
#include <vector>

namespace alba
{

class CopyGoogleTemplates
{
public:

    using StringPair=std::pair<std::string, std::string>;
    using StringPairs=std::vector<StringPair>;

    void copyTemplatesForOneRound(
            std::string const& destinationPath,
            StringPairs const& replacePairs) const;
    void replaceStringWithStringOnFile(
            std::string const& inputFilePath,
            std::string const& outputFilePath,
            StringPairs const& replacePairs) const;

private:
    std::string const m_googleTemplatesPath{APRG_DIR R"(\CodingCompetitions\ZZZ_templates\GoogleProblems\)"};
};

}
