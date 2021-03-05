#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <SnapshotStatistics.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(SnapshotStatistics, DISABLED_SnapshotFilesRel2)
{
    cout<<PATH_OF_7Z_EXECUTABLE<<endl;
    cout<<PATH_OF_7Z_TEMP_FILE<<endl;

    SnapshotStatistics statistics;
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 1\Snapshot1_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1810.zip)");
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 2\Snapshot2_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1841.zip)");
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 3\Snapshot3_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1911.zip)");
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 4\Snapshot4_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1941.zip)");
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 5\Snapshot5_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-2011.zip)");

    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\BASEBAND RESET\Snapshot_baseband reset_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\CELL BLOCK_UNBLOCK\Snapshot_cell block unblock_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\CELL LOCK_UNLOCK\Snapshot_cell lock_unlock_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\DSP CRASH\Snapshot_dspcrash_0x1431_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\ESM HOT REMOVE_INSERT\Snapshot_esm hotremoveinsert_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\LINK BREAK\Snapshot_linkbreak_WBTS-399_WBTS00_0000_3215_00_WBTS399_20181113-1610.zip)");
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\RADIO MODULE BLOCK_UNBLOCK\Snapshot_rf block_unblock_WBTS-399_WBTS00_0000_3215_00_WBTS399_20181113-1426.zip)");
    statistics.fetchFileSizesForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\RADIO MODULE HOT REMOVE_INSERT\Snapshot_rf hotremove_insert_WBTS-399_WBTS00_0000_3215_00.zip)");

    AlbaLocalPathHandler localPathHandler(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_1_RESULTS)");
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
    statistics.saveFileListForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\results\outputFileSizes.csv)");

    statistics.fetchStatisticsForSnapshot();
    statistics.saveStatisticsToFile(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\results\outputFileSizesStatistics.csv)");
}

TEST(SnapshotStatistics, DISABLED_RomUsageRel2)
{
    SnapshotStatistics statistics;
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 1\s1_rom.txt)", "Snapshot1_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1810");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 2\s2_rom.txt)", "Snapshot2_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1841");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 3\s3_rom.txt)", "Snapshot3_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1911");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 4\s4_rom.txt)", "Snapshot4_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1941");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 5\s5_rom.txt)", "Snapshot5_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-2011");

    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\BASEBAND RESET\rom.txt)", "Snapshot_baseband reset_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\CELL BLOCK_UNBLOCK\rom.txt)", "Snapshot_cell block unblock_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\CELL LOCK_UNLOCK\rom.txt)", "Snapshot_cell lock_unlock_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\DSP CRASH\rom.txt)", "Snapshot_dspcrash_0x1431_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\ESM HOT REMOVE_INSERT\rom.txt)", "Snapshot_esm hotremoveinsert_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\LINK BREAK\rom.txt)", "Snapshot_linkbreak_WBTS-399_WBTS00_0000_3215_00_WBTS399_20181113-1610.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\RADIO MODULE BLOCK_UNBLOCK\rom.txt)", "Snapshot_rf block_unblock_WBTS-399_WBTS00_0000_3215_00_WBTS399_20181113-1426.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\RADIO MODULE HOT REMOVE_INSERT\rom.txt)", "Snapshot_rf hotremove_insert_WBTS-399_WBTS00_0000_3215_00.zip)");

    statistics.saveSizesForMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\results\outputRomSizes.csv)");

    statistics.fetchStatisticsForMemory();
    statistics.saveStatisticsToFile(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\results\outputRomStatistics.csv)");
}

TEST(SnapshotStatistics, DISABLED_RamUsageRel2)
{
    SnapshotStatistics statistics;
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 1\s1_ram.txt)", "Snapshot1_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1810");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 2\s2_ram.txt)", "Snapshot2_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1841");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 3\s3_ram.txt)", "Snapshot3_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1911");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 4\s4_ram.txt)", "Snapshot4_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-1941");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_2_RESULTS\SNAPSHOT 5\s5_ram.txt)", "Snapshot5_WBTS-399_WBTS00_0000_3212_00_WBTS399_20181107-2011");

    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\BASEBAND RESET\ram.txt)", "Snapshot_baseband reset_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\CELL BLOCK_UNBLOCK\ram.txt)", "Snapshot_cell block unblock_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\CELL LOCK_UNLOCK\ram.txt)", "Snapshot_cell lock_unlock_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\DSP CRASH\ram.txt)", "Snapshot_dspcrash_0x1431_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\ESM HOT REMOVE_INSERT\ram.txt)", "Snapshot_esm hotremoveinsert_WBTS-399_WBTS00_0000_3215_00.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\LINK BREAK\ram.txt)", "Snapshot_linkbreak_WBTS-399_WBTS00_0000_3215_00_WBTS399_20181113-1610.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\RADIO MODULE BLOCK_UNBLOCK\ram.txt)", "Snapshot_rf block_unblock_WBTS-399_WBTS00_0000_3215_00_WBTS399_20181113-1426.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\AP_3_RESULTS\RADIO MODULE HOT REMOVE_INSERT\ram.txt)", "Snapshot_rf hotremove_insert_WBTS-399_WBTS00_0000_3215_00.zip)");

    statistics.saveSizesForMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\results\outputRamSizes.csv)");

    statistics.fetchStatisticsForMemory();
    statistics.saveStatisticsToFile(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL2\results\outputRamStatistics.csv)");
}

TEST(SnapshotStatistics, DISABLED_SnapshotFilesRel3)
{
    cout<<PATH_OF_7Z_EXECUTABLE<<endl;
    cout<<PATH_OF_7Z_TEMP_FILE<<endl;

    SnapshotStatistics statistics;
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP2_REL3\Snapshot1_WBTS-669_WBTS18_2000_0449_07_WBTS669ALDLOGS_20181205-1803.zip)");
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP2_REL3\Snapshot2_WBTS-669_WBTS18_2000_0449_07_WBTS669ALDLOGS_20181205-1803.zip)");
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP2_REL3\Snapshot3_WBTS-669_WBTS18_2000_0449_07_WBTS669ALDLOGS_20181205-1803.zip)");
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP2_REL3\Snapshot4_WBTS-669_WBTS18_2000_0449_07_WBTS669ALDLOGS_20181205-1803.zip)");
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP2_REL3\Snapshot5_WBTS-669_WBTS18_2000_0449_07_WBTS669ALDLOGS_20181205-1803.zip)");

    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\BB RESET_REL3\Snapshot_baseband reset rel3_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\CELL BLOCK UNBLOCK\Snapshot_cell block unblock_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\CELL LOCK UNLOCK\Snapshot_cell lock unlock_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\ESM HOT REMOVE\Snapshot_esm hot remove insert_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\LINK BREAK\Snapshot_link break_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\NYQUIST CRASH\Snapshot_nyquist crash_WBTS-669_WBTS18_2000_0449_0.zip)");
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\RF BLOCK UNBLOCK\Snapshot_rf block unblock_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\RF HOT INSERT REMOVE\Snapshot_rf hot remove insert_WBTS-669_WBTS18_2000_0449_07.zip)");

    statistics.saveFileListForSnapshot(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\results\outputFileSizes.csv)");

    statistics.fetchStatisticsForSnapshot();
    statistics.saveStatisticsToFile(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\results\outputFileSizesStatistics.csv)");
}

TEST(SnapshotStatistics, DISABLED_RomUsageRel3)
{
    SnapshotStatistics statistics;

    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\BB RESET_REL3\rom.txt)", "Snapshot_baseband reset rel3_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\CELL BLOCK UNBLOCK\rom.txt)", "Snapshot_cell block unblock_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\CELL LOCK UNLOCK\rom.txt)", "Snapshot_cell lock unlock_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\ESM HOT REMOVE\rom.txt)", "Snapshot_esm hot remove insert_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\LINK BREAK\rom.txt)", "Snapshot_link break_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\NYQUIST CRASH\rom.txt)", "Snapshot_nyquist crash_WBTS-669_WBTS18_2000_0449_0.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\RF BLOCK UNBLOCK\rom.txt)", "Snapshot_rf block unblock_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\RF HOT INSERT REMOVE\rom.txt)", "Snapshot_rf hot remove insert_WBTS-669_WBTS18_2000_0449_07.zip)");

    statistics.saveSizesForMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\results\outputRomSizes.csv)");

    statistics.fetchStatisticsForMemory();
    statistics.saveStatisticsToFile(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\results\outputRomStatistics.csv)");
}

TEST(SnapshotStatistics, RamUsageRel3)
{
    SnapshotStatistics statistics;

    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\BB RESET_REL3\ram.txt)", "Snapshot_baseband reset rel3_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\CELL BLOCK UNBLOCK\ram.txt)", "Snapshot_cell block unblock_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\CELL LOCK UNLOCK\ram.txt)", "Snapshot_cell lock unlock_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\ESM HOT REMOVE\ram.txt)", "Snapshot_esm hot remove insert_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\LINK BREAK\ram.txt)", "Snapshot_link break_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\NYQUIST CRASH\ram.txt)", "Snapshot_nyquist crash_WBTS-669_WBTS18_2000_0449_0.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\RF BLOCK UNBLOCK\ram.txt)", "Snapshot_rf block unblock_WBTS-669_WBTS18_2000_0449_07.zip)");
    statistics.processMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\AP3_REL3\RF HOT INSERT REMOVE\ram.txt)", "Snapshot_rf hot remove insert_WBTS-669_WBTS18_2000_0449_07.zip)");

    statistics.saveSizesForMemory(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\results\outputRamSizes.csv)");

    statistics.fetchStatisticsForMemory();
    statistics.saveStatisticsToFile(R"(C:\Work\CP\Features\CNI-31516\LogsForStatistics\CNI 31516_AP_REL3\results\outputRamStatistics.csv)");
}


