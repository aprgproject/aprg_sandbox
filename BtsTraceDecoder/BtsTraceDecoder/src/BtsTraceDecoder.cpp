#include "BtsTraceDecoder.hpp"

#include <iostream>

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>

using namespace std;
using namespace alba::stringHelper;

namespace alba
{

BtsTraceDecoder::BtsTraceDecoder()
{}

void BtsTraceDecoder::saveSymbolTableFromObjdump(std::string const& symbolTableFilePath)
{
    saveSymbolTable(symbolTableFilePath, SymbolTableFileType::SymbolTableFromObjdump);
}

void BtsTraceDecoder::saveSymbolTableFromMappedFile(std::string const& symbolTableFilePath)
{
    saveSymbolTable(symbolTableFilePath, SymbolTableFileType::MappedFile);
}

void BtsTraceDecoder::processInputTraceFile(std::string const& inputTraceFilePath)
{
    ifstream traceFile(AlbaWindowsPathHandler(inputTraceFilePath).getFullPath());
    if(traceFile.is_open())
    {
        AlbaFileReader traceFileReader(traceFile);
        while(traceFileReader.isNotFinished())
        {
            string lineInTraceFile(traceFileReader.simpleGetLine());
            unsigned int traceAddressValue = convertHexStringToNumber<unsigned int>(getStringInBetweenTwoStrings(lineInTraceFile, "[", "]"));
            if(traceAddressValue != 0)
            {
                cout<<"TraceAddressValue: [0x"<<std::hex<<traceAddressValue<<"] NearestSymbol: ["<<getNearestLowerSymbol(traceAddressValue)<<"]"<<endl;
            }
        }
    }
}

std::string BtsTraceDecoder::getNearestLowerSymbol(int const address, int const offset)
{
    BtsTraceDecoder::SymbolMapType::iterator symbolIterator = m_symbolMap.lower_bound(address+offset);
    return symbolIterator->second;
}

void BtsTraceDecoder::saveSymbolTable(std::string const& symbolTableFilePath, SymbolTableFileType const filetype)
{
    ifstream symbolTableFileStream(AlbaWindowsPathHandler(symbolTableFilePath).getFullPath());
    if(symbolTableFileStream.is_open())
    {
        cout<<"Symbol table file is opened"<<endl;
        AlbaFileReader symbolTableFileReader(symbolTableFileStream);
        while(symbolTableFileReader.isNotFinished())
        {
            string lineInFile(symbolTableFileReader.getLineAndIgnoreWhiteSpaces());
            saveLineInSymbolMapIfValid(getAddressFromLineInFile(lineInFile, filetype), lineInFile);
        }
    }
    else
    {
        cout<<"Symbol table file is not opened"<<endl;
    }
}

int BtsTraceDecoder::getAddressFromLineInFile(string const& lineInFile, SymbolTableFileType const filetype) const
{
    int address = 0;
    if(filetype == SymbolTableFileType::SymbolTableFromObjdump)
    {
        address = convertHexStringToNumber<int>(getStringBeforeThisString(lineInFile, " "));
    }
    else if(filetype == SymbolTableFileType::MappedFile)
    {
        address = convertHexStringToNumber<int>(getStringInBetweenTwoStrings(lineInFile, "0x", " "));
    }
    return address;
}

void BtsTraceDecoder::saveLineInSymbolMapIfValid(int const address, std::string const& lineInFile)
{
    cout<<address<<lineInFile<<endl;
    if(address!=0)
    {
        m_symbolMap.emplace(address, lineInFile);
    }
}

}