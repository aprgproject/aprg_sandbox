#pragma once

#include <FileExtractor/AprgFileExtractor.hpp>
#include <FileGroup.hpp>

#include <map>#include <set>
#include <vector>

namespace alba{

class SnapshotStatistics
{
public:
    SnapshotStatistics();
    using SnapshotNameToFileSizeMap = std::map<std::string, double>;
    using SnapshotNameToFileSizePair = std::pair<std::string, double>;
    using SampleSizes = std::vector<double>;
    using FileNameToSnapshotNameToFileSizeMap = std::map<std::string, SnapshotNameToFileSizeMap>;
    using FileNameToSnapshotNameToFileSizePair = std::pair<std::string, SnapshotNameToFileSizeMap>;
    using WildcardNameToSampleSizesMap = std::map<std::string, SampleSizes>;
    using WildcardNameToSampleSizesPair = std::pair<std::string, SampleSizes>;

    void addFileSizeForSnapshot(std::string const& fileName, std::string const& snapshotName, double const fileSize);
    std::string getSnapshotDirectory(std::string const& snapshotPath) const;
    void extractFilesInSnapshot(std::string const& snapshotPath);
    void fetchFileSizesForSnapshot(std::string const& snapshotPath);
    void saveFileListForSnapshot(std::string const& outputPath);
    void fetchStatisticsForSnapshot();
    void fetchStatisticsForMemory();
    void saveStatisticsToFile(std::string const& outputPath);
    std::string getWildcardNameIfFileGroupsIsFound(std::string const& fileName) const;
    void processSnapshot(std::string const& snapshotPath);

    void processMemory(std::string const& ramFilePath, std::string const& snapshotName);
    double convertFileSizeToDouble(std::string const& fileSizeInString) const;
    void addStatisticForMemory(std::string const& fileName, std::string const& snapshotName, double const fileSize);
    void saveSizesForMemory(std::string const& outputPath);

    void initializeFileGroups();

private:
    AprgFileExtractor m_fileExtractor;
    FileNameToSnapshotNameToFileSizeMap m_fileNameToSnapshotNameToFileSize;
    FileNameToSnapshotNameToFileSizeMap m_fileNameToSnapshotNameToMemorySize;
    std::set<std::string> m_snapshotNames;
    std::vector<FileGroup> m_fileGroups;
    WildcardNameToSampleSizesMap m_wildcardNameToSampleSizesMap;
};

}
