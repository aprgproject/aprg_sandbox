#include "ChessEngineHandler.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;

#define MAXBUF 2000
#define MAXHALFBUF 1000

namespace alba
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

DWORD WINAPI engineToGuiCallbackFunction(LPVOID lpParam)
{
    PointerToCallBackData pointerToCallBackData = (PointerToCallBackData)lpParam;
    ChessEngineHandler* chessEngineHandlerPointer = reinterpret_cast<ChessEngineHandler*>(pointerToCallBackData->epointer);
    chessEngineHandlerPointer->startMonitoringEngineOutput();
    return 0;
}
}

ChessEngineHandler::ChessEngineHandler(
        std::string const& enginePath)
{
    SECURITY_DESCRIPTOR sd; //security information for pipes
    static SECURITY_ATTRIBUTES securityAttributes;
    static STARTUPINFO startupInfo;
    static PROCESS_INFORMATION processInfo;

    if (IsWinNT())
    {
        InitializeSecurityDescriptor(&sd,SECURITY_DESCRIPTOR_REVISION);
        SetSecurityDescriptorDacl(&sd, 1, NULL, 0);
        securityAttributes.lpSecurityDescriptor = &sd;
    }
    else securityAttributes.lpSecurityDescriptor = NULL;

    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.bInheritHandle = 1; //allow inheritable handles

    if (!CreatePipe(&(m_inputStreamOnEngineThread), &(m_inputStreamOnHandler), &securityAttributes, 0))
    {
        log("Cannot Create Pipe");
    }

    if (!CreatePipe(&(m_outputStreamOnHandler), &(m_outputStreamOnEngineThread), &securityAttributes, 0))
    {
        log("Cannot Create Pipe");
    }
    GetStartupInfo(&startupInfo); //set startupinfo for the spawned process
    startupInfo.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
    startupInfo.wShowWindow = SW_SHOWDEFAULT;//SW_HIDE;
    startupInfo.hStdOutput  = m_outputStreamOnEngineThread;
    startupInfo.hStdError   = m_outputStreamOnEngineThread;
    startupInfo.hStdInput   = m_inputStreamOnEngineThread;

    //spawn the child process
    if (!CreateProcess(enginePath.c_str(),NULL,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&startupInfo,&processInfo))
    {
        log("Cannot Create Process");
    }
    PointerToCallBackData pData = new CallBackData();
    pData->epointer = this;
    m_engineThread = CreateThread(NULL, 0, engineToGuiCallbackFunction, pData, 0, &(m_threadId));
}

ChessEngineHandler::~ChessEngineHandler()
{
    sendToEngine("exit\n");
    CloseHandle(m_engineThread);
    CloseHandle(m_inputStreamOnEngineThread);
    CloseHandle(m_outputStreamOnEngineThread);
    CloseHandle(m_inputStreamOnHandler);
    CloseHandle(m_outputStreamOnHandler);
    m_logFileStream.getReference().close();
}

HANDLE & ChessEngineHandler::getGuiStdout()
{
    return m_outputStreamOnHandler;
}

void ChessEngineHandler::sendToEngine(std::string const& stringToEngine)
{
    unsigned long bytesWritten(0U);
    char mbuf[MAXBUF];
    string remainingString(stringToEngine);
    long remainingLength=0;
    do
    {
        remainingString += "\n";
        remainingLength = remainingString.length();
        strncpy(mbuf, remainingString.c_str(), MAXBUF-1);
        WriteFile(m_inputStreamOnHandler, mbuf, remainingLength, &bytesWritten, NULL);
        FlushFileBuffers(m_inputStreamOnHandler);
        remainingLength = remainingLength-bytesWritten;
        if(remainingLength>0)
        {
            remainingString.substr(bytesWritten, remainingLength);
        }
    }
    while(remainingLength>0);
    log(string("To engine: ") + stringToEngine);
}

void ChessEngineHandler::processFromEngine(std::string const& stringFromEngine)
{
    log(string("From engine: ") + stringFromEngine);
}

void ChessEngineHandler::startMonitoringEngineOutput()
{
    unsigned long bytesRead; //bytes read
    unsigned long bytesAvailable; //bytes available
    char mbuf[MAXBUF];
    char sbuf[MAXHALFBUF];
    unsigned int i(0U), j(0U), remainingSize(0U);
    mbuf[0]='\0';
    sbuf[0]='\0';
    string stringOutput;
    remainingSize=0;
    while(1)
    {
        PeekNamedPipe(m_outputStreamOnHandler, sbuf, MAXHALFBUF-1, &bytesRead, &bytesAvailable, NULL);
        if(bytesRead > 0)
        {
            ReadFile(m_outputStreamOnHandler, sbuf, MAXHALFBUF-1, &bytesRead, NULL);
            strncat(mbuf, sbuf, MAXBUF);
            j=0;
            remainingSize = remainingSize+bytesRead;
            for(i=0; i<remainingSize; )
            {
                if(mbuf[i]=='\r' || mbuf[i]=='\n')
                {
                    sbuf[j] = '\0';
                    j=0;
                    stringOutput = sbuf;
                    processFromEngine(stringOutput);
                    stringOutput += "\n";
#ifndef APRG_TEST_MODE_ON
    cout << stringOutput;
#endif
                    for(; i<remainingSize && isWhiteSpace(mbuf[i]); i++);
                }
                else
                {
                    sbuf[j++]=mbuf[i++];
                }
            }
            sbuf[j] = '\0';
            strncpy(mbuf, sbuf, MAXBUF);
            remainingSize = remainingSize-i;
            /*(y=0;
            for( ;x<isize; ){
                mbuf[y++] = mbuf[x++];
            }
            mbuf[y] = '\0';
            */
            strncpy(mbuf, sbuf, MAXBUF);
            //printf("mbuf: [%s]\n",mbuf);
            //printf("sbuf: [%s]\n",sbuf);
        }
        Sleep(1);
    }
}

void ChessEngineHandler::setLogFile(std::string const& logFilePath)
{
    m_logFileStream.createObjectUsingDefaultConstructor();
    m_logFileStream.getReference().open(logFilePath);

    if(!m_logFileStream.getReference().is_open())
    {
        log(string("Cannot open log file") + logFilePath);
    }
}

void ChessEngineHandler::log(std::string const& logString)
{
    if(m_logFileStream)
    {
        m_logFileStream.getReference() << logString << endl;
    }
#ifdef APRG_TEST_MODE_ON
    cout << logString << endl;
#endif
}

}
