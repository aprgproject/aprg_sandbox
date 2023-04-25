#pragma once

#include <WcdmaToolsBackend/BtsLogPrint.hpp>

#include <fstream>

namespace wcdmaToolsBackend {

class BtsPrintReaderWithRollback {
public:
    BtsPrintReaderWithRollback();
    void clear();
    bool isGood() const;
    BtsLogPrint getPrint();
    void rollBackPrint();
    void openIfNeeded(std::string const& filePath);
    double getCurrentLocation();

private:
    bool m_isRollbackActivated;
    BtsLogPrint m_previousPrint;
    std::ifstream m_inputStream;
};

}  // namespace wcdmaToolsBackend
