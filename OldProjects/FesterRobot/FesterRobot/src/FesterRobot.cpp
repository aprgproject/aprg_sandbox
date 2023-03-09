#include "FesterRobot.hpp"

#include <Common/String/AlbaStringHelper.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <iostream>
#include <sstream>

#define POLLING_DELAY_TO_WAIT_FOR_START 1000
#define EXCEL_CELL_COORDINATES1 1256,437
#define EXCEL_CELL_COORDINATES2 1256,466
#define MATLAB_COMMAND_WINDOW_COORDINATES 190,160
#define MATLAB_TITLE_BAR_COORDINATES 375,14
#define ORIGIN 0,0

using namespace std;

namespace alba
{


FesterRobot::FesterRobot(string const& outputPath)
    : m_outputStream(outputPath)
    , m_retryCurrentFrequencies(false)
{}

void FesterRobot::run()
{
    cout<<"Press the key 'ctrl' to start.\n";
    while(1)
    {
        exitIfSpecialKeyIsPressed();
        if(m_userAutomation.isLetterPressed(VK_CONTROL))
        {
            cout<<"Starting robot duties.\n";
            setupFesterEnvironmentInMatlab();

            for(int filterBitInteger=63; filterBitInteger>0; )
            {
                updateExcelFile(static_cast<unsigned int>(filterBitInteger));
                m_outputStream<<"FREQUENCIES BIT: ["<<std::hex<<filterBitInteger<<std::dec<<"]\n";
                runFesterFunctionInMatlab();
                if(!m_retryCurrentFrequencies)
                {
                    filterBitInteger--;
                }
            }
            break;
        }
        m_userAutomation.sleep(POLLING_DELAY_TO_WAIT_FOR_START);
    }
    m_userAutomation.setMousePosition(MousePosition(ORIGIN));
}

void FesterRobot::exitIfSpecialKeyIsPressed()
{
    if(m_userAutomation.isLetterPressed(VK_MENU))
    {
        m_userAutomation.setMousePosition(MousePosition(ORIGIN));
        exit(0);
    }
}

void FesterRobot::setupFesterEnvironmentInMatlab()
{
    m_userAutomation.doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
    m_userAutomation.doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
    m_userAutomation.setStringToClipboard("clc");
    m_userAutomation.typeControlAndLetterSimultaneously('V');
    m_userAutomation.typeCharacter(VK_RETURN);
    m_userAutomation.setStringToClipboard(R"(run('C:\Users\malba\Desktop\DSS\Fester\Fester_scp.m'))");
    m_userAutomation.typeControlAndLetterSimultaneously('V');
    m_userAutomation.typeCharacter(VK_RETURN);
    m_userAutomation.setStringToClipboard(R"(format long g)");
    m_userAutomation.typeControlAndLetterSimultaneously('V');
    m_userAutomation.typeCharacter(VK_RETURN);
}

void FesterRobot::updateExcelFile(unsigned int freqUsageBits)
{
    updateFrequenciesBasedFreqUsageBits(freqUsageBits);
    editCellInExcelWithNewFrequencies(MousePosition(EXCEL_CELL_COORDINATES1));
    editCellInExcelWithNewFrequencies(MousePosition(EXCEL_CELL_COORDINATES2));
    m_userAutomation.typeControlAndLetterSimultaneously('S');
}

void FesterRobot::editCellInExcelWithNewFrequencies(MousePosition const& excelCellPosition)
{
    m_userAutomation.doLeftClickAt(excelCellPosition);
    m_userAutomation.doLeftClickAt(excelCellPosition);
    m_userAutomation.typeCharacter(VK_DELETE);
    m_userAutomation.doDoubleLeftClickAt(excelCellPosition);
    m_userAutomation.setStringToClipboard(getFrequenciesStringForExcel());
    m_userAutomation.typeControlAndLetterSimultaneously('V');
}

void FesterRobot::runFesterFunctionInMatlab()
{
    m_userAutomation.doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
    m_userAutomation.setStringToClipboard("clc");
    m_userAutomation.typeControlAndLetterSimultaneously('V');
    m_userAutomation.typeCharacter(VK_RETURN);
    m_userAutomation.setStringToClipboard(R"(fester('perf_rake_ilpc_gsm:1M_FixedGsm','300a');)");
    m_userAutomation.typeControlAndLetterSimultaneously('V');
    m_userAutomation.typeCharacter(VK_RETURN);
    bool isRunning(true);
    bool isRunningFinished(false);
    string clipboardData;
    while(isRunning && !isRunningFinished)
    {
        exitIfSpecialKeyIsPressed();
        m_userAutomation.sleep(2000);
        m_userAutomation.doLeftClickAt(MousePosition(MATLAB_COMMAND_WINDOW_COORDINATES));
        m_userAutomation.typeControlAndLetterSimultaneously('A');
        m_userAutomation.typeControlAndLetterSimultaneously('C');
        clipboardData = getClipboardFormattedData();
        isRunning = isRunningInClipboardData(clipboardData);
        isRunningFinished = isRunningFinishedInClipboardData(clipboardData);
        m_userAutomation.doLeftClickAt(MousePosition(MATLAB_TITLE_BAR_COORDINATES));
    }
    m_retryCurrentFrequencies=!isRunning;
    saveDataToOutputFile(clipboardData);
}

bool FesterRobot::isRunningInClipboardData(string const& clipboardData) const
{
    return stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(clipboardData, "running iteration");
}


bool FesterRobot::isRunningFinishedInClipboardData(string const& clipboardData) const
{
    string freqBandStringInLog(
                stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(
                    stringHelper::getStringWithoutRedundantWhiteSpace(
                        stringHelper::getStringAfterThisString(
                            stringHelper::getStringInBetweenTwoStrings(clipboardData, "freqBand", "filCoef"), "="))));
    string frequenciesStringForExcel(getFrequenciesStringForExcel());
    cout<<"freqBandStringInLog: ["<<freqBandStringInLog<<"]\n";
    cout<<"frequenciesStringForExcel: ["<<frequenciesStringForExcel<<"]\n";
    return freqBandStringInLog == frequenciesStringForExcel;
}

string FesterRobot::getClipboardFormattedData() const
{
    string clipboardData(m_userAutomation.getStringFromClipboard());
    stringHelper::transformReplaceStringIfFound(clipboardData, "\r", "");
    return clipboardData;
}

void FesterRobot::saveDataToOutputFile(string const& clipboardData)
{
    m_outputStream<<"FREQUENCIES: ["<<getFrequenciesStringForExcel()<<"]\n";
    m_outputStream<<clipboardData<<"\n";
}

string FesterRobot::getFrequenciesStringForExcel() const
{
    stringstream frequencyStream;
    for(int frequency : m_frequencies)
    {
        frequencyStream << frequency << " ";
    }
    string frequencyString(frequencyStream.str());
    if(!frequencyString.empty())
    {
        frequencyString = frequencyString.substr(0, frequencyString.length()-1);
    }
    return frequencyString;
}

void FesterRobot::updateFrequenciesBasedFreqUsageBits(unsigned int freqUsageBits)
{
    m_frequencies.clear();
    if(freqUsageBits & 0x1)
    {
        m_frequencies.emplace_back(-1800);
    }
    if(freqUsageBits & 0x2)
    {
        m_frequencies.emplace_back(-1600);
    }
    if(freqUsageBits & 0x4)
    {
        m_frequencies.emplace_back(-1400);
    }
    if(freqUsageBits & 0x8)
    {
        m_frequencies.emplace_back(1400);
    }
    if(freqUsageBits & 0x16)
    {
        m_frequencies.emplace_back(1600);
    }
    if(freqUsageBits & 0x32)
    {
        m_frequencies.emplace_back(1800);
    }
}

}
