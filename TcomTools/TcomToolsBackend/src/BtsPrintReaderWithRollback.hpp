#pragma once

#include <BtsLogPrint.hpp>

#include <fstream>

namespace tcomToolsBackend
{

class BtsPrintReaderWithRollback
{
public:
    bool isGood() const;
    BtsLogPrint getPrint();
    void rollBackGetPrint();
    void openIfNeeded(std::string const& filePath);
    double getCurrentLocation();
private:
    bool m_isGood;
    bool m_isPreviousPrintValid;
    BtsLogPrint m_previousPrint;
    std::ifstream m_inputStream;
};

}
