#include "ChessEngineHandler.hpp"

#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Windows/AlbaWindowsHelper.hpp>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;

#define MAX_BUFFER_SIZE 2000

namespace alba
{

namespace chess
{

namespace
{

typedef struct _mydata
{
    ChessEngineHandler* epointer;
} CallBackData, *PointerToCallBackData;

int IsWinNT()
{
    OSVERSIONINFO osv;
    osv.dwOSVersionInfoSize = sizeof(osv);
    GetVersionEx(&osv);
    return (osv.dwPlatformId == VER_PLATFORM_WIN32_NT);
}

DWORD WINAPI engineMonitoringCallbackFunction(LPVOID lpParam)
{
    PointerToCallBackData pointerToCallBackData = (PointerToCallBackData)lpParam;
    ChessEngineHandler* chessEngineHandlerPointer = reinterpret_cast<ChessEngineHandler*>(pointerToCallBackData->epointer);
    chessEngineHandlerPointer->startMonitoringEngineOutput();
    return 0;
}
}

ChessEngineHandler::ChessEngineHandler(string const& enginePath)
    : m_enginePath(enginePath)
{
    initializeEngine();
}

ChessEngineHandler::~ChessEngineHandler()
{
    shutdownEngine();
    m_logFileStreamOptional.getReference().close();
}

void ChessEngineHandler::reset()
{
    log(LogType::HandlerStatus, "Resetting engine");
    shutdownEngine();
    initializeEngine();
}

void ChessEngineHandler::sendStringToEngine(string const& stringToEngine)
{
    unsigned long bytesWritten(0U);
    string stringToWrite(stringToEngine);
    stringToWrite += "\n";
    long remainingLength=stringToWrite.length();
    bool isSuccessful(true);
    do
    {
        isSuccessful = WriteFile(m_inputStreamOnHandler, stringToWrite.c_str(), remainingLength, &bytesWritten, NULL);
        if(isSuccessful)
        {
            remainingLength = remainingLength-bytesWritten;
            if(remainingLength>0)
            {
                stringToWrite = stringToWrite.substr(bytesWritten, remainingLength);
            }
        }
        else
        {
            cout << "Error on sendStringToEngine: " << AlbaWindowsHelper::getLastFormattedErrorMessage() << endl;
        }
    }
    while(isSuccessful && remainingLength>0);
    log(LogType::ToEngine, stringToEngine);
}

void ChessEngineHandler::processStringFromEngine(string const& stringFromEngine)
{
    log(LogType::FromEngine, stringFromEngine);
    if(m_additionalStepsInProcessingAStringFromEngine)
    {
        m_additionalStepsInProcessingAStringFromEngine.getConstReference()(stringFromEngine);
    }
}

void ChessEngineHandler::startMonitoringEngineOutput()
{
    unsigned long bytesRead; //bytes read
    unsigned long bytesAvailable; //bytes available
    char buffer[MAX_BUFFER_SIZE];
    string stringBuffer;
    while(1)
    {
        PeekNamedPipe(m_outputStreamOnHandler, buffer, MAX_BUFFER_SIZE, NULL, &bytesAvailable, NULL);
        if(bytesAvailable > 0)
        {
            ReadFile(m_outputStreamOnHandler, buffer, MAX_BUFFER_SIZE, &bytesRead, NULL);
            stringBuffer.reserve(stringBuffer.size() + bytesRead);
            copy(begin(buffer), begin(buffer)+bytesRead, back_inserter(stringBuffer));

            unsigned int currentIndex(0U);
            bool shouldContinue(true);
            while(shouldContinue)
            {
                unsigned int startIndex = currentIndex;
                unsigned int newLineIndex = stringBuffer.find_first_of("\r\n", startIndex);
                if(isNotNpos(static_cast<int>(newLineIndex)))
                {
                    string oneLine(stringBuffer.substr(startIndex, newLineIndex-startIndex));
                    if(!oneLine.empty())
                    {
                        processStringFromEngine(oneLine);
                    }
                    currentIndex = newLineIndex+1;
                }
                else
                {
                    if(currentIndex > 0)
                    {
                        stringBuffer = stringBuffer.substr(currentIndex);
                    }
                    shouldContinue = false;
                }
            }
        }
        else if(!stringBuffer.empty())
        {
            processStringFromEngine(stringBuffer);
            stringBuffer.clear();
        }
        Sleep(1);
    }
}

void ChessEngineHandler::setLogFile(string const& logFilePath)
{
    m_logFileStreamOptional.createObjectUsingDefaultConstructor();
    m_logFileStreamOptional.getReference().open(logFilePath);

    if(!m_logFileStreamOptional.getReference().is_open())
    {
        log(LogType::HandlerStatus, string("Cannot open log file") + logFilePath);
    }
}

void ChessEngineHandler::setAdditionalStepsInProcessingAStringFromEngine(
        ProcessAStringFunction const& additionalSteps)
{
    m_additionalStepsInProcessingAStringFromEngine.setConstReference(additionalSteps);
}

void ChessEngineHandler::initializeEngine()
{
    SECURITY_DESCRIPTOR securityDescriptor; //security information for pipes
    SECURITY_ATTRIBUTES securityAttributes;

    if (IsWinNT())
    {
        InitializeSecurityDescriptor(&securityDescriptor, SECURITY_DESCRIPTOR_REVISION);
        SetSecurityDescriptorDacl(&securityDescriptor, 1, NULL, 0);
        securityAttributes.lpSecurityDescriptor = &securityDescriptor;
    }
    else securityAttributes.lpSecurityDescriptor = NULL;

    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.bInheritHandle = 1; //allow inheritable handles

    if (!CreatePipe(&(m_inputStreamOnEngineThread), &(m_inputStreamOnHandler), &securityAttributes, 0))
    {
        log(LogType::HandlerStatus, "Cannot Create Pipe");
    }

    if (!CreatePipe(&(m_outputStreamOnHandler), &(m_outputStreamOnEngineThread), &securityAttributes, 0))
    {
        log(LogType::HandlerStatus, "Cannot Create Pipe");
    }
    GetStartupInfo(&m_startupInfo); //set startupinfo for the spawned process
    m_startupInfo.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
    m_startupInfo.wShowWindow = SW_HIDE;//SW_SHOWDEFAULT;//
    m_startupInfo.hStdOutput  = m_outputStreamOnEngineThread;
    m_startupInfo.hStdError   = m_outputStreamOnEngineThread;
    m_startupInfo.hStdInput   = m_inputStreamOnEngineThread;

    //spawn the child process
    if (!CreateProcess(m_enginePath.c_str(),NULL,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&m_startupInfo,&m_processInfo))
    {
        log(LogType::HandlerStatus, "Cannot Create Process");
    }
    PointerToCallBackData pData = new CallBackData();
    pData->epointer = this;
    m_engineMonitoringThread = CreateThread(NULL, 0, engineMonitoringCallbackFunction, pData, 0, &(m_threadId));
}

void ChessEngineHandler::shutdownEngine()
{
    sendStringToEngine("quit\n");
    WaitForSingleObject(m_engineMonitoringThread, 1);
    CloseHandle(m_engineMonitoringThread);
    TerminateProcess(m_processInfo.hProcess, 0);
    CloseHandle(m_inputStreamOnEngineThread);
    CloseHandle(m_outputStreamOnEngineThread);
    CloseHandle(m_inputStreamOnHandler);
    CloseHandle(m_outputStreamOnHandler);
}

void ChessEngineHandler::log(LogType const logtype, string const& logString)
{
    if(m_logFileStreamOptional)
    {
        m_logFileStreamOptional.getReference() << getLogHeader(logtype) << logString << endl;
    }
#ifdef APRG_TEST_MODE_ON
    //cout << getLogHeader(logtype) << logString << endl;
#else
    if(LogType::FromEngine == logtype)
    {
        cout << logString << endl;
    }
#endif
}

string ChessEngineHandler::getLogHeader(LogType const logtype) const
{
    string result;
    switch(logtype)
    {
    case LogType::FromEngine:
    {
        result="From engine: ";
        break;
    }
    case LogType::ToEngine:
    {
        result="To engine: ";
        break;
    }
    case LogType::HandlerStatus:
    {
        result="HandlerStatus: ";
        break;
    }
    }
    return result;
}

}

}
