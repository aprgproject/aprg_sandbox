#pragma once

#include <map>
#include <string>

#include <SymbolTableFileType.hpp>

namespace alba
{

class BtsTraceDecoder
{
public:
    using SymbolMapType = std::map<unsigned int, std::string>;
    BtsTraceDecoder();
    void saveSymbolTableFromObjdump(std::string const& symbolTableFilePath);
    void saveSymbolTableFromMappedFile(std::string const& symbolTableFilePath);
    void processInputTraceFile(std::string const& inputTraceFilePath);
    std::string getNearestLowerSymbol(int const address, int const offset = 0);
private:
    void saveSymbolTable(std::string const& symbolTableFilePath, SymbolTableFileType const filetype);
    int getAddressFromLineInFile(std::string const& lineInFile, SymbolTableFileType const filetype) const;
    void saveLineInSymbolMapIfValid(int const address, std::string const& lineInFile);
    SymbolMapType m_symbolMap;
};

}
