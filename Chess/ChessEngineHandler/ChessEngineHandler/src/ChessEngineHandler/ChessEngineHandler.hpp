#pragma once

#include <Common/Optional/AlbaOptional.hpp>

#include <fstream>
#include <string>
#include <windows.h>

namespace alba
{

class ChessEngineHandler
{
public:

    ChessEngineHandler(std::string const& enginePath);
    ~ChessEngineHandler();

    HANDLE & getGuiStdout();

    void sendToEngine(std::string const& stringToEngine);
    void processFromEngine(std::string const& stringFromEngine);
    void startMonitoringEngineOutput();

    void setLogFile(std::string const& logFilePath);

private:
    void log(std::string const& logString);
    HANDLE m_engineThread;
    DWORD m_threadId;
    HANDLE m_inputStreamOnEngineThread, m_outputStreamOnEngineThread;
    HANDLE m_inputStreamOnHandler, m_outputStreamOnHandler;
    AlbaOptional<std::ofstream> m_logFileStream;
};

}