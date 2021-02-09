#pragma once

#include <User/AlbaLocalUserAutomation.hpp>

#include <fstream>
#include <string>
#include <vector>

using Frequencies = std::vector<int>;

namespace alba
{

class FesterRobot
{
public:
    FesterRobot(std::string const& outputPath);
    void run();

private:
    void exitIfSpecialKeyIsPressed();
    void updateExcelFile(unsigned int freqUsageBits);
    void setupFesterEnvironmentInMatlab();
    void editCellInExcelWithNewFrequencies(MousePosition const& excelCellPosition);
    void runFesterFunctionInMatlab();
    bool isRunningInClipboardData(std::string const& clipboardData) const;
    bool isRunningFinishedInClipboardData(std::string const& clipboardData) const;
    std::string getClipboardFormattedData() const;
    void saveDataToOutputFile(std::string const& clipboardData);
    std::string getFrequenciesStringForExcel() const;
    void updateFrequenciesBasedFreqUsageBits(unsigned int freqUsageBits);
    std::ofstream m_outputStream;
    Frequencies m_frequencies;
    AlbaWindowsUserAutomation m_userAutomation;
    bool m_retryCurrentFrequencies;
};

}
