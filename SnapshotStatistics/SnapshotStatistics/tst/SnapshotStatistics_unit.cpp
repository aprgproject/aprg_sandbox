#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <SnapshotStatistics.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(SnapshotStatistics, DISABLED_SnapshotFiles)
{
    cout<<PATH_OF_7Z_EXECUTABLE<<endl;
    cout<<PATH_OF_7Z_TEMP_FILE<<endl;

    SnapshotStatistics statistics;
    statistics.fetchFileSizesForSnapshot(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 1\Snapshot1_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1810.zip)");
    statistics.fetchFileSizesForSnapshot(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 2\Snapshot2_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1841.zip)");
    statistics.fetchFileSizesForSnapshot(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 3\Snapshot3_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1911.zip)");
    statistics.fetchFileSizesForSnapshot(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 4\Snapshot4_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1941.zip)");
    statistics.fetchFileSizesForSnapshot(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 5\Snapshot5_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-2011.zip)");

    AlbaLocalPathHandler localPathHandler(R"(D:\ZZZ_Logs\CNI-31516\AP_1_RESULTS)");
    ListOfPaths listOfFiles;
    ListOfPaths listOfDirectories;
    localPathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& filePath : listOfFiles)
    {
        AlbaLocalPathHandler localPathHandler(filePath);
        if(localPathHandler.getExtension() == "zip")
        {
            statistics.fetchFileSizesForSnapshot(localPathHandler.getFullPath());
        }
    }
    statistics.saveFileListForSnapshot(R"(D:\ZZZ_Logs\CNI-31516\TEST\outputFileSize.csv)");

    statistics.fetchStatisticsForSnapshot();
    statistics.saveStatisticsForSnapshot(R"(D:\ZZZ_Logs\CNI-31516\TEST\outputStatistics.csv)");
}

TEST(SnapshotStatistics, RomUsage)
{
    SnapshotStatistics statistics;
    statistics.processMemory(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 1\s1_rom.txt)", "Snapshot1_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1810");
    statistics.processMemory(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 2\s2_rom.txt)", "Snapshot2_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1841");
    statistics.processMemory(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 3\s3_rom.txt)", "Snapshot3_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1911");
    statistics.processMemory(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 4\s4_rom.txt)", "Snapshot4_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1941");
    statistics.processMemory(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 5\s5_rom.txt)", "Snapshot5_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-2011");
    statistics.saveStatisticsForMemory(R"(D:\ZZZ_Logs\CNI-31516\TEST\outputRom.csv)");
}

TEST(SnapshotStatistics, RamUsage)
{
    SnapshotStatistics statistics;
    statistics.processMemory(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 1\s1_ram.txt)", "Snapshot1_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1810");
    statistics.processMemory(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 2\s2_ram.txt)", "Snapshot2_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1841");
    statistics.processMemory(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 3\s3_ram.txt)", "Snapshot3_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1911");
    statistics.processMemory(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 4\s4_ram.txt)", "Snapshot4_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1941");
    statistics.processMemory(R"(D:\ZZZ_Logs\CNI-31516\AP_2_RESULTS\SNAPSHOT 5\s5_ram.txt)", "Snapshot5_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-2011");
    statistics.saveStatisticsForMemory(R"(D:\ZZZ_Logs\CNI-31516\TEST\outputRam.csv)");
}
