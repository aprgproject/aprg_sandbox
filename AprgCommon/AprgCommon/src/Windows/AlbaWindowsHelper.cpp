#include "AlbaWindowsHelper.hpp"

#include <windows.h>

#include <sstream>
#include <string>

using namespace std;

namespace alba
{

string AlbaWindowsHelper::getLastFormattedErrorMessage()
{
    stringstream lastError;
    unsigned int errorCode = GetLastError();
    lastError<< "No message from windows. Error code: " << errorCode;
    if (errorCode)
    {
        LPVOID lpMessageBuffer;
        DWORD bufferLength = FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    errorCode,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    (LPTSTR) &lpMessageBuffer,
                    0, NULL );
        if(bufferLength)
        {
            LPCSTR lpMessageString = (LPCSTR)lpMessageBuffer;
            std::string errorMessageFromWindows(lpMessageString, lpMessageString+bufferLength);
            LocalFree(lpMessageBuffer);
            lastError<<"Error from windows: ["<<errorMessageFromWindows<<"] ErrorCode:["<<errorCode<<"]"<<endl;
        }
    }
    return lastError.str();
}

}//namespace alba
