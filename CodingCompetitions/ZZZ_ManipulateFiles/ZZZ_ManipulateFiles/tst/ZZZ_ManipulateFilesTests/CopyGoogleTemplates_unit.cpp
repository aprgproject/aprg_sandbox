#include <ZZZ_ManipulateFiles/CopyGoogleTemplates.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(CopyGoogleTemplatesTest, Test1) {
    CopyGoogleTemplates entity;

    string destinationPath = APRG_DIR R"(\CodingCompetitions\GoogleKickStart\GoogleKickStart\tst\2021\RoundF)";
    CopyGoogleTemplates::StringPairs replacePairs{
        {"ContestName_Year_Round_", "KickStart_2021_RoundF_"},
        {"P1_SampleProblem", "P1_TrashBins"},
        {"P2_SampleProblem", "P2_Festival"},
        {"P3_SampleProblem", "P3_StarTrappers"},
        {"P4_SampleProblem", "P4_GraphTravel"}};
    entity.copyTemplatesForOneRound(destinationPath, replacePairs);
}

}  // namespace alba
