#include "SnapshotStatistics.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <fstream>
#include <iostream>

using namespace std;

namespace alba {

namespace ProgressCounters {
int numberOfFilesToBeAnalyzedForExtraction;
int numberOfFilesAnalyzedForExtraction;
}  // namespace ProgressCounters

SnapshotStatistics::SnapshotStatistics() : m_fileExtractor("[.]") { initializeFileGroups(); }

void SnapshotStatistics::addFileSizeForSnapshot(
    string const& fileName, string const& snapshotName, double const fileSize) {
    string fileNameWithoutWhiteSpace(stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(fileName));
    m_fileNameToSnapshotNameToFileSize[fileNameWithoutWhiteSpace][snapshotName] = fileSize;
    m_snapshotNames.emplace(snapshotName);
}

string SnapshotStatistics::getSnapshotDirectory(string const& snapshotPath) const {
    AlbaLocalPathHandler snapshotPathHandler(snapshotPath);
    return snapshotPathHandler.getDirectory() + R"(\)" + snapshotPathHandler.getFilenameOnly();
}

void SnapshotStatistics::extractFilesInSnapshot(string const& snapshotPath) {
    cout << "processFileOrDirectory snapshotPath: " << snapshotPath << "\n";
    AlbaLocalPathHandler snapshotPathHandler(snapshotPath);
    m_fileExtractor.extractOnceForAllFiles(snapshotPathHandler.getFullPath());
    snapshotPathHandler.input(getSnapshotDirectory(snapshotPathHandler.getFullPath()) + R"(\BTSLogFiles.zip)");
    m_fileExtractor.extractOnceForAllFiles(snapshotPathHandler.getFullPath());
}

void SnapshotStatistics::fetchFileSizesForSnapshot(string const& snapshotPath) {
    // cout<<"fetchStatistics snapshotPath: "<<snapshotPath<<"\n";
    AlbaLocalPathHandler snapshotDirectoryPathHandler(getSnapshotDirectory(snapshotPath));
    ListOfPaths listOfFiles;
    ListOfPaths listOfDirectories;
    snapshotDirectoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (string const& filePath : listOfFiles) {
        AlbaLocalPathHandler filePathHandler(filePath);
        addFileSizeForSnapshot(
            filePathHandler.getFile(), snapshotDirectoryPathHandler.getImmediateDirectoryName(),
            filePathHandler.getFileSizeEstimate());
    }
}

void SnapshotStatistics::saveFileListForSnapshot(string const& outputPath) {
    ofstream outputStream(outputPath);
    outputStream.precision(20);
    outputStream << ",Sizes (in bytes)\n";
    for (string const& snapshotName : m_snapshotNames) {
        outputStream << "," << snapshotName;
    }
    outputStream << "\n";
    for (auto const& firstPair : m_fileNameToSnapshotNameToFileSize) {
        outputStream << firstPair.first;
        for (string const& snapshotName : m_snapshotNames) {
            SnapshotNameToFileSizeMap const& snapshotNameToFileSize(firstPair.second);            if (snapshotNameToFileSize.find(snapshotName) != snapshotNameToFileSize.end()) {
                outputStream << "," << snapshotNameToFileSize.at(snapshotName);
            } else {
                outputStream << ",";            }
        }
        outputStream << "\n";
    }
}

void SnapshotStatistics::fetchStatisticsForSnapshot() {
    for (auto const& firstPair : m_fileNameToSnapshotNameToFileSize) {
        for (auto const& secondPair : firstPair.second) {
            string wildcardName(getWildcardNameIfFileGroupsIsFound(firstPair.first));
            if (wildcardName.empty()) {
                wildcardName = firstPair.first;            }
            m_wildcardNameToSampleSizesMap[wildcardName].emplace_back(secondPair.second);
        }
    }
}

void SnapshotStatistics::fetchStatisticsForMemory() {
    for (auto const& firstPair : m_fileNameToSnapshotNameToMemorySize) {
        for (auto const& secondPair : firstPair.second) {
            string wildcardName(getWildcardNameIfFileGroupsIsFound(firstPair.first));
            if (wildcardName.empty()) {
                wildcardName = firstPair.first;            }
            m_wildcardNameToSampleSizesMap[wildcardName].emplace_back(secondPair.second);
        }
    }}

void SnapshotStatistics::saveStatisticsToFile(string const& outputPath) {
    ofstream outputStream(outputPath);
    outputStream.precision(20);
    outputStream << ",Samples of sizes (in bytes)\n";
    for (auto const& firstPair : m_wildcardNameToSampleSizesMap) {
        outputStream << firstPair.first;
        for (double const& size : firstPair.second) {
            outputStream << "," << size;        }
        outputStream << "\n";
    }
}
string SnapshotStatistics::getWildcardNameIfFileGroupsIsFound(string const& fileName) const {
    for (FileGroup const& fileGroup : m_fileGroups) {
        if (fileGroup.isInFileGroup(fileName)) {
            return fileGroup.getWildcardName();
        }
    }
    return "";
}

void SnapshotStatistics::processSnapshot(string const& snapshotPath) {
    extractFilesInSnapshot(snapshotPath);
    fetchFileSizesForSnapshot(snapshotPath);
}

void SnapshotStatistics::processMemory(string const& memoryFilePath, string const& snapshotName) {
    ifstream memoryFileStream(memoryFilePath);
    AlbaFileReader memoryFileReader(memoryFileStream);
    while (memoryFileReader.isNotFinished()) {
        string lineInFile(memoryFileReader.getLineAndIgnoreWhiteSpaces());
        string relativeFilePath;
        string fileSizeInString;
        double fileSizeInBytes = 0;
        if (stringHelper::isStringFoundCaseSensitive(lineInFile, "./")) {
            relativeFilePath = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(
                stringHelper::getStringAfterThisString(lineInFile, "./"));
            fileSizeInString = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(
                stringHelper::getStringBeforeThisString(lineInFile, "./"));
            fileSizeInBytes = convertFileSizeToDouble(fileSizeInString);
            addStatisticForMemory(relativeFilePath, snapshotName, fileSizeInBytes);
        } else if (stringHelper::isStringFoundCaseSensitive(lineInFile, " .")) {
            relativeFilePath = "***TotalSize***";
            fileSizeInString = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(
                stringHelper::getStringBeforeThisString(lineInFile, " ."));            fileSizeInBytes = convertFileSizeToDouble(fileSizeInString);
            addStatisticForMemory(relativeFilePath, snapshotName, fileSizeInBytes);
        }
    }}

double SnapshotStatistics::convertFileSizeToDouble(string const& fileSizeInString) const {
    double fileSizeInBytes(stringHelper::convertStringToNumber<double>(fileSizeInString));
    if (stringHelper::isStringFoundCaseSensitive(fileSizeInString, "K")) {
        fileSizeInBytes *= 1000;
    } else if (stringHelper::isStringFoundCaseSensitive(fileSizeInString, "M")) {
        fileSizeInBytes *= 1000000;
    }
    return fileSizeInBytes;}

void SnapshotStatistics::addStatisticForMemory(
    string const& fileName, string const& snapshotName, double const fileSize) {    string fileNameWithoutWhiteSpace(stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(fileName));
    m_fileNameToSnapshotNameToMemorySize[fileNameWithoutWhiteSpace][snapshotName] = fileSize;
    m_snapshotNames.emplace(snapshotName);
}

void SnapshotStatistics::saveSizesForMemory(string const& outputPath) {
    ofstream outputStream(outputPath);
    outputStream.precision(20);
    outputStream << ",Sizes (in bytes)\n";
    for (string const& snapshotName : m_snapshotNames) {
        outputStream << "," << snapshotName;
    }
    outputStream << "\n";
    for (auto const& firstPair : m_fileNameToSnapshotNameToMemorySize) {
        outputStream << firstPair.first;
        for (string const& snapshotName : m_snapshotNames) {
            SnapshotNameToFileSizeMap const& snapshotNameToFileSize(firstPair.second);            if (snapshotNameToFileSize.find(snapshotName) != snapshotNameToFileSize.end()) {
                outputStream << "," << snapshotNameToFileSize.at(snapshotName);
            } else {
                outputStream << ",";            }
        }
        outputStream << "\n";
    }
}

void SnapshotStatistics::initializeFileGroups() {
    m_fileGroups.emplace_back("CommissioningBefore_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "CommissioningBefore_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("1 AMR_CALL_*.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "1 AMR_CALL_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("1 AMR_CALL_*.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "1 AMR_CALL_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("1PS_ Ftp_*.dat", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "1PS_ Ftp_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".dat");
    });
    m_fileGroups.emplace_back("1PS_ Ftp_*.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "1PS_ Ftp_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("1 PSD_ FTP_*.dat", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "1 PSD_ FTP_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".dat");
    });
    m_fileGroups.emplace_back("1 PSD_ FTP_*.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "1 PSD_ FTP_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("ALMessageTrace*.txt*", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "ALMessageTrace") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("*EXTMEMDUMP.BIN.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "EXTMEMDUMP.BIN.xz");
    });
    m_fileGroups.emplace_back("*ALMessageTrace.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "ALMessageTrace.txt");
    });
    m_fileGroups.emplace_back("*AaConfigRadMasterHistory.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "AaConfigRadMasterHistory.log.xz");
    });
    m_fileGroups.emplace_back("*AaShellradCommandHistory.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "AaShellradCommandHistory.log.xz");
    });
    m_fileGroups.emplace_back("*AaTestPortClientHistory.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "AaTestPortClientHistory.log.xz");
    });
    m_fileGroups.emplace_back("*BlackBox.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "BlackBox.xml");
    });
    m_fileGroups.emplace_back("*CUTool.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "CUTool.log.xz");
    });
    m_fileGroups.emplace_back("*DMEASREL3.BIN.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "DMEASREL3.BIN.xz");
    });
    m_fileGroups.emplace_back("*Dbdump.xml.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Dbdump.xml.xz");
    });
    m_fileGroups.emplace_back("*Decoder_BLER_Debug.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Decoder_BLER_Debug.bin.xz");
    });
    m_fileGroups.emplace_back("*EncDchTrace.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "EncDchTrace.bin.xz");
    });
    m_fileGroups.emplace_back("*FSP*_DSP*.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "_FSP") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_DSP") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".zip");
    });
    m_fileGroups.emplace_back("*FileDirectory.xml.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "FileDirectory.xml.xz");
    });
    m_fileGroups.emplace_back("*FileDirectory.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "FileDirectory.xml");
    });
    m_fileGroups.emplace_back("*FpTtiTrace.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "FpTtiTrace.bin.xz");
    });
    m_fileGroups.emplace_back("*FrequencyHistory.xml.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "FrequencyHistory.xml.xz");
    });
    m_fileGroups.emplace_back("*HWF.xml.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "HWF.xml.xz");
    });
    m_fileGroups.emplace_back("*HWdb.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "HWdb.bin.xz");
    });
    m_fileGroups.emplace_back("*HsTupTtiTrace.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "HsTupTtiTrace.bin.xz");
    });
    m_fileGroups.emplace_back("*HsupaL2MasterCellTrace*.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "HsupaL2MasterCellTrace") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".bin.xz");
    });
    m_fileGroups.emplace_back("*HsupaL2MasterDspRmTrace*.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "HsupaL2MasterDspRmTrace") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".bin.xz");
    });
    m_fileGroups.emplace_back("*HsupaL2MasterUserTrace*.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "HsupaL2MasterUserTrace") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".bin.xz");
    });
    m_fileGroups.emplace_back("*KpiLog.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "KpiLog.bin.xz");
    });
    m_fileGroups.emplace_back("*KpiLogStringFormat.ini.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "KpiLogStringFormat.ini.xz");
    });
    m_fileGroups.emplace_back("*L1TraNonHsTrace.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "L1TraNonHsTrace.bin.xz");
    });
    m_fileGroups.emplace_back("*MacHsTrace.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "MacHsTrace.bin.xz");
    });
    m_fileGroups.emplace_back("*MemoryConsumption_LastDay.csv", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "MemoryConsumption_LastDay.csv");
    });
    m_fileGroups.emplace_back("*MemoryConsumption_LastFourHours.csv", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "MemoryConsumption_LastFourHours.csv");
    });
    m_fileGroups.emplace_back("*MemoryConsumption_LastMonth.csv", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "MemoryConsumption_LastMonth.csv");
    });
    m_fileGroups.emplace_back("*NonDefaultRadMasterParams.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "NonDefaultRadMasterParams.log.xz");
    });
    m_fileGroups.emplace_back("*OPTRt.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "OPTRt.log.xz");
    });
    m_fileGroups.emplace_back("*PsStats.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "PsStats.bin.xz");
    });
    m_fileGroups.emplace_back("RD.BTS*.WCDM.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "RD.BTS") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".WCDM.xml");
    });
    m_fileGroups.emplace_back("RLH.BIN.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "RLH.BIN.xz");
    });
    m_fileGroups.emplace_back("*RachRtlog.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "RachRtlog.bin.xz");
    });
    m_fileGroups.emplace_back("*RakeL2TtiTrace.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "RakeL2TtiTrace.bin.xz");
    });
    m_fileGroups.emplace_back("*RakeRtlog.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "RakeRtlog.bin.xz");
    });
    m_fileGroups.emplace_back("*RawAlarmHistory.txt.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "RawAlarmHistory.txt.xz");
    });
    m_fileGroups.emplace_back("*RawAlarmHistory.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "RawAlarmHistory.txt");
    });
    m_fileGroups.emplace_back("*Rp3Configuration.xml.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Rp3Configuration.xml.xz");
    });
    m_fileGroups.emplace_back("*SCFBackup.xml.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "SCFBackup.xml.xz");
    });
    m_fileGroups.emplace_back("*SCFC_*.xml.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "SCFC_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml.xz");
    });
    m_fileGroups.emplace_back("*SOAPMessageTrace.xml.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "SOAPMessageTrace.xml.xz");
    });
    m_fileGroups.emplace_back("*SWDLreport.txt.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "SWDLreport.txt.xz");
    });
    m_fileGroups.emplace_back("*TCOM_LRM_dump.txt.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "TCOM_LRM_dump.txt.xz");
    });
    m_fileGroups.emplace_back("*TuningHistory.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "TuningHistory.log.xz");
    });
    m_fileGroups.emplace_back("*TxTrace.bin.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "TxTrace.bin.xz");
    });
    m_fileGroups.emplace_back("*VSWRmeas.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "VSWRmeas.txt");
    });
    m_fileGroups.emplace_back("*WBTSHWData.xml.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "WBTSHWData.xml.xz");
    });
    m_fileGroups.emplace_back("*asnDump.bin*", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "asnDump.bin");
    });
    m_fileGroups.emplace_back("*blackbox.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "blackbox.xz");
    });
    m_fileGroups.emplace_back("*blackbox_alarms.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "blackbox_alarms.xz");
    });
    m_fileGroups.emplace_back("*blackbox_sfp.csv.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "blackbox_sfp.csv.xz");
    });
    m_fileGroups.emplace_back("*blackbox_temperature.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "blackbox_temperature.xz");
    });
    m_fileGroups.emplace_back("*eventlog.bin", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "eventlog.bin");
    });
    m_fileGroups.emplace_back("*fault_history_log.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "fault_history_log.txt");
    });
    m_fileGroups.emplace_back("*fddcctrl.bin", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "fddcctrl.bin");
    });
    m_fileGroups.emplace_back("*fdpp.bin", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "fdpp.bin");
    });
    m_fileGroups.emplace_back("*frozenFrame.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "frozenFrame.log");
    });
    m_fileGroups.emplace_back("*im_dump.xml.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "im_dump.xml.xz");
    });
    m_fileGroups.emplace_back("*irq_stats.txt.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "irq_stats.txt.xz");
    });
    m_fileGroups.emplace_back("*linux_logs.tar", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "linux_logs.tar");
    });
    m_fileGroups.emplace_back("*memdump_HwapiExe_*.txt.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "memdump_HwapiExe_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt.xz");
    });
    m_fileGroups.emplace_back("*metadata.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "metadata.txt");
    });
    m_fileGroups.emplace_back("*muksu_scan_*.txt.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "muksu_scan_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt.xz");
    });
    m_fileGroups.emplace_back("*ntp.conf.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "ntp.conf.zip");
    });
    m_fileGroups.emplace_back("*pmGeneration.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pmGeneration.log.xz");
    });
    m_fileGroups.emplace_back("*pm_*_frozenFrame.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_frozenFrame.log");
    });
    m_fileGroups.emplace_back("*pm_*_kernel.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_kernel.log");
    });
    m_fileGroups.emplace_back("*pm_*_message.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_message.log");
    });
    m_fileGroups.emplace_back("*pm_*_process.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_process.log");
    });
    m_fileGroups.emplace_back("*pm_*_scheduler.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_scheduler.log");
    });
    m_fileGroups.emplace_back("*pm_*_sysinfo.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_sysinfo.log");
    });
    m_fileGroups.emplace_back("*pm_*_syslog.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_syslog.log");
    });
    m_fileGroups.emplace_back("*pm_*_system.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_system.log");
    });
    m_fileGroups.emplace_back("*pm_*_collect.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_collect.log");
    });
    m_fileGroups.emplace_back("*pm_*_frozenFrame.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_frozenFrame.zip");
    });
    m_fileGroups.emplace_back("*pm_*_kernel.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_kernel.zip");
    });
    m_fileGroups.emplace_back("*pm_*_message.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_message.zip");
    });
    m_fileGroups.emplace_back("*pm_*_process.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_process.zip");
    });
    m_fileGroups.emplace_back("*pm_*_scheduler.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_scheduler.zip");
    });
    m_fileGroups.emplace_back("*pm_*_sysinfo.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_sysinfo.zip");
    });
    m_fileGroups.emplace_back("*pm_*_syslog.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_syslog.zip");
    });
    m_fileGroups.emplace_back("*pm_*_system.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_system.zip");
    });
    m_fileGroups.emplace_back("*pm_*_collect.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "pm_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, "_collect.zip");
    });
    m_fileGroups.emplace_back("*postmortem*.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "postmortem") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("*runtime.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime.log.xz");
    });
    m_fileGroups.emplace_back("*runtime.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime.txt");
    });
    m_fileGroups.emplace_back("*runtime.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime.zip");
    });
    m_fileGroups.emplace_back("*runtime_AaSysInfoOverload.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_AaSysInfoOverload.log.xz");
    });
    m_fileGroups.emplace_back("*runtime_HWAPI_DBG_AdetS.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_HWAPI_DBG_AdetS.log.xz");
    });
    m_fileGroups.emplace_back("*runtime_HWAPI_DBG_ClockS.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_HWAPI_DBG_ClockS.log.xz");
    });
    m_fileGroups.emplace_back("*runtime_HWAPI_DBG_GnssS.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_HWAPI_DBG_GnssS.log.xz");
    });
    m_fileGroups.emplace_back("*runtime_HWAPI_DBG_OptS.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_HWAPI_DBG_OptS.log.xz");
    });
    m_fileGroups.emplace_back("*runtime_HWAPI_DBG_SumS.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_HWAPI_DBG_SumS.log.xz");
    });
    m_fileGroups.emplace_back("*runtime_HWAPI_DBG_SyncS.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_HWAPI_DBG_SyncS.log.xz");
    });
    m_fileGroups.emplace_back("*runtime_HWAPI_DBG_TimeS.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_HWAPI_DBG_TimeS.log.xz");
    });
    m_fileGroups.emplace_back("*runtime_cpidInfo.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_cpidInfo.log.xz");
    });
    m_fileGroups.emplace_back("*runtime_dropInfo.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_dropInfo.log.xz");
    });
    m_fileGroups.emplace_back("*runtime_routeInfo.log.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_routeInfo.log.xz");
    });
    m_fileGroups.emplace_back("*runtime_sysinfo.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "runtime_sysinfo.zip");
    });
    m_fileGroups.emplace_back("*siteconf.xml.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "siteconf.xml.xz");
    });
    m_fileGroups.emplace_back("*startup.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "startup.txt");
    });
    m_fileGroups.emplace_back("*startup.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "startup.zip");
    });
    m_fileGroups.emplace_back("*statistic.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "statistic.log");
    });
    m_fileGroups.emplace_back("*tcomBinaryLogger.py.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "tcomBinaryLogger.py.xz");
    });
    m_fileGroups.emplace_back("*xohDump.bin", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "xohDump.bin");
    });
    m_fileGroups.emplace_back("Before_SW_upload_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Before_SW_upload_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("CCS.boot*.gz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "CCS.boot") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".gz");
    });
    m_fileGroups.emplace_back("CCS*.gz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "CCS") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".gz");
    });
    m_fileGroups.emplace_back("CDNL_BTSC_*.gz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "CDNL_BTSC_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".gz");
    });
    m_fileGroups.emplace_back("CLLog*.bk", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "CLLog") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".bk");
    });
    m_fileGroups.emplace_back("CUTool*.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "CUTool") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".log");
    });
    m_fileGroups.emplace_back("CUPL_BTSC_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "CUPL_BTSC_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("CommissioningBefore_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "CommissioningBefore_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("Execute_Comm_Comm_file_selected_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Execute_Comm_Comm_file_selected_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Execute_Comm_Detecting_SEM_window*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Execute_Comm_Detecting_SEM_window") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Execute_Comm_Detection_SEM_window_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Execute_Comm_Detection_SEM_window_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Execute_Comm_Open_comm_file_window_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Execute_Comm_Open_comm_file_window_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Execute_Comm_SWDL_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Execute_Comm_SWDL_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Execute_Comm_TRS_check_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Execute_Comm_TRS_check_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Execute_Comm_parms_sent_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Execute_Comm_parms_sent_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Execute_Comm_restart_option_marked_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Execute_Comm_restart_option_marked_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Execute_Comm_saving_params_before_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Execute_Comm_saving_params_before_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Execute_Comm_select_planned_type_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Execute_Comm_select_planned_type_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Execute_Comm_parms_sent_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Execute_Comm_parms_sent_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("FR1_*.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "FR1_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("FeatureDefinitions_*.lua", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "FeatureDefinitions_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".lua");
    });
    m_fileGroups.emplace_back("FlexiBTSProperties_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "FR1_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("FlexiOAMThread*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "FlexiOAMThread") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("FlexiSiteEM_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "FlexiSiteEM_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("METAFlexi_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "METAFlexi_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("Mondatory_missing_alarms_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Mondatory_missing_alarms_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("OamServicesConfig*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "OamServicesConfig") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("PM.BTS-*.WCDM.xml.gz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "PM.BTS-") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".WCDM.xml.gz");
    });
    m_fileGroups.emplace_back("PM.BTS-*.WCDM.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "PM.BTS-") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".WCDM.xml");
    });
    m_fileGroups.emplace_back("RD.BTS-*.WCDM.xml.gz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "RD.BTS-") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".WCDM.xml.gz");
    });
    m_fileGroups.emplace_back("RNC_alarms_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "RNC_alarms_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("RNC_alarms_*.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "RNC_alarms_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("SCFC*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "SCFC") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("SCFD*.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "SCFD") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("SCF*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "SCF") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("SM_Alarms_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "SM_Alarms_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("SW_upload_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "SW_upload_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("SiteManager.bk*.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "SiteManager.bk") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".zip");
    });
    m_fileGroups.emplace_back("Snapshot*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Snapshot") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Snapshot*.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Snapshot") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".zip");
    });
    m_fileGroups.emplace_back("*_Alarms_all*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "_Alarms_all") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("*_Alarms_mandatory_missing*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "_Alarms_mandatory_missing") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("*_Alarms_unexpected*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "_Alarms_unexpected") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("Step*.log", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Step") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".log");
    });
    m_fileGroups.emplace_back("TargetBD_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "TargetBD_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("Test*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Test") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("Test*.zip", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Test") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".zip");
    });
    m_fileGroups.emplace_back("Tsharks_*.pcap", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Tsharks_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".pcap");
    });
    m_fileGroups.emplace_back("UDP_*.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "UDP_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("Unexpected_UDP_alarms_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Unexpected_UDP_alarms_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("Unwanted_UDP_alarms_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "Unwanted_UDP_alarms_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("VSWRmeas*.txt*", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "VSWRmeas") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("all_UDP_alarms_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "all_UDP_alarms_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("cells*.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "cells") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("*eventlog.bin*", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "eventlog.bin");
    });
    m_fileGroups.emplace_back("*extended_FTMLog_*.tgz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "extended_FTMLog_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".tgz");
    });
    m_fileGroups.emplace_back("*fddcctrl.bin*", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "fddcctrl.bin");
    });
    m_fileGroups.emplace_back("*fdpp.bin*", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "fdpp.bin");
    });
    m_fileGroups.emplace_back("loggingDB*.h2.db", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "loggingDB") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".h2.db");
    });
    m_fileGroups.emplace_back("loggingDB*.trace.db", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "loggingDB") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".trace.db");
    });
    m_fileGroups.emplace_back("messages*.gz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "messages") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".gz");
    });
    m_fileGroups.emplace_back("muksu_scan_*.txt", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "muksu_scan_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txt");
    });
    m_fileGroups.emplace_back("problem_bts_onAir*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "problem_bts_onAir") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("procdump*.xz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "procdump") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xz");
    });
    m_fileGroups.emplace_back("siteconf_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "siteconf_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("xohDump*.bin", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "xohDump") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".bin");
    });
    m_fileGroups.emplace_back("commissioning_*.jpg", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "commissioning_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".jpg");
    });
    m_fileGroups.emplace_back("CDNL_BTSC_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "CDNL_BTSC_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("FlexiBTSProperties_*.xml", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "FlexiBTSProperties_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".xml");
    });
    m_fileGroups.emplace_back("*FCMD-ROM-BW_*.BIN", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "FCMD-ROM-BW_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".BIN");
    });
    m_fileGroups.emplace_back("*TCOM_*.txz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "TCOM_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".txz");
    });
    m_fileGroups.emplace_back("*TUPC_*.tgz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "TUPC_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".tgz");
    });
    m_fileGroups.emplace_back("*fmRules_*.tgz", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "fmRules_") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".tgz");
    });
    m_fileGroups.emplace_back("licences/*.XML", [](string const& fileName) -> bool {
        return stringHelper::isStringFoundCaseSensitive(fileName, "licences/") &&
               stringHelper::isStringFoundCaseSensitive(fileName, ".XML");
    });
}
}  // namespace alba