#pragma once

#include <BtsLogPrint.hpp>
#include <fstream>

using std::ifstream;

namespace tcomToolsBackend
{

class BtsPrintReaderWithRollback
{
public:
    bool isGood() const;
    BtsLogPrint getPrint();
    void rollBackGetPrint();
    void openIfNeeded(string const& filePath);
private:
    bool m_isGood;
    bool m_isPreviousPrintValid;
    BtsLogPrint m_previousPrint;
    ifstream m_inputStream;
};

}
