#pragma once

#include <Common/Optional/AlbaOptional.hpp>

#include <fstream>
#include <string>
#include <windows.h>

namespace alba
{

namespace chess
{

class ChessEngineHandler
{
public:
    enum class LogType
    {
        FromEngine,
        ToEngine,
        HandlerStatus
    };
    using ProcessAStringFunction = std::function<void(std::string const&)> ;

    ChessEngineHandler(std::string const& enginePath);
    ~ChessEngineHandler();

    void sendStringToEngine(std::string const& stringToEngine);
    void processStringFromEngine(std::string const& stringFromEngine);
    void startMonitoringEngineOutput();

    void setLogFile(std::string const& logFilePath);
    void setAdditionalStepsInProcessingAStringFromEngine(ProcessAStringFunction const& additionalSteps);

private:
    void log(LogType const logtype, std::string const& logString);
    std::string getLogHeader(LogType const logtype) const;
    HANDLE m_engineThread;
    DWORD m_threadId;
    HANDLE m_inputStreamOnEngineThread, m_outputStreamOnEngineThread;
    HANDLE m_inputStreamOnHandler, m_outputStreamOnHandler;
    AlbaOptional<std::ofstream> m_logFileStreamOptional;
    AlbaOptional<ProcessAStringFunction> m_additionalStepsInProcessingAStringFromEngine;
};
}

}