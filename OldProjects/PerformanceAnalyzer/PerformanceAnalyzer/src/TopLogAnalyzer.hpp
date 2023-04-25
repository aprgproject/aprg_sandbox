#pragma once

#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaDateTime.hpp>
#include <Statistics/DataCollection.hpp>

#include <map>
#include <string>
#include <vector>

namespace alba {

enum class TopLogAnalyzerState { BeforeColumnHeaders, AfterColumnHeaders };

class TopLogAnalyzer {
public:
    struct CpuMemLoad {
        double cpuLoad;
        double memLoad;
    };

    struct DataEntry {
        using ProcessToCpuMemMap = std::map<std::string, CpuMemLoad>;
        using ProcessToCpuMemPair = std::pair<std::string, CpuMemLoad>;
        AlbaDateTime timeInTop;
        double totalCpuFromTop;
        ProcessToCpuMemMap processToCpuMemMap;
        void clear();
        bool isEmpty() const;
    };

    struct ColumnHeaders {
        unsigned int size;
        unsigned int cpuIndex;
        unsigned int memIndex;
        void clear();
        void set(unsigned int const sizeFromTop, double const cpuIndexFromTop, double const memIndexFromTop);
    };

    struct CpuMemCollection {
        DataCollection<double> mem;
        DataCollection<double> cpu;
    };

    TopLogAnalyzer();
    void clear();
    void processTopLog(std::string const& pathOfBtsLog);

private:
    void readTopLogsAndSaveToDatabase(std::string const& pathOfTopLog);
    void generateCpuReport(std::string const& pathOfTopLog);
    stringHelper::strings getProcessNamesForCpuReport();
    void putHeadersInCpuReport(
        stringHelper::strings const& processNamesInReport, std::ofstream& cpuReportFileStream) const;
    void putEntriesInCpuReport(
        stringHelper::strings const& processNamesInReport, std::ofstream& cpuReportFileStream) const;
    void generateMemReport(std::string const& pathOfTopLog);
    stringHelper::strings getProcessNamesForMemReport();
    void putHeadersInMemReport(
        stringHelper::strings const& processNamesInReport, std::ofstream& cpuReportFileStream) const;
    void putEntriesInMemReport(
        stringHelper::strings const& processNamesInReport, std::ofstream& cpuReportFileStream) const;
    bool isTopCommandFirstLine(std::string const& lineInLogs) const;
    bool isTopCommandHeaderLine(std::string const& lineInLogs) const;
    void saveAndClearCurrentEntry(DataEntry& currentEntry);
    void saveTimeFromTop(std::string const& lineInLogs, DataEntry& currentEntry) const;
    void saveDataFromHeaders(std::string const& lineInLogs);
    void saveOverallCpuData(std::string const& lineInLogs, DataEntry& currentEntry) const;
    void saveCpuAndMem(std::string const& lineInLogs, DataEntry& currentEntry);
    TopLogAnalyzerState m_state;
    ColumnHeaders m_columnHeaders;
    std::vector<DataEntry> m_dataEntries;
    std::map<std::string, CpuMemCollection> m_processToCpuMemCollectionMap;
};

}  // namespace alba
