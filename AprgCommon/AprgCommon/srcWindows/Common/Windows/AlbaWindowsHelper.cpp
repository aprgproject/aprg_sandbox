#include "AlbaWindowsHelper.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <windows.h>

#include <sstream>
#include <string>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

string AlbaWindowsHelper::getLastFormattedErrorMessage()
{
    stringstream lastErrorStream;
    unsigned int errorCode = GetLastError();
    lastErrorStream<< "No message from windows. Error code: " << errorCode;
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
            string errorMessageFromWindows(getStringWithoutRedundantWhiteSpace(string(lpMessageString, lpMessageString+bufferLength)));
            LocalFree(lpMessageBuffer);
            lastErrorStream.str(string());
            lastErrorStream<<"Error from windows: ["<<errorMessageFromWindows<<"] ErrorCode:["<<errorCode<<"]"<<endl;
        }
    }
    return lastErrorStream.str();
}

}//namespace alba
