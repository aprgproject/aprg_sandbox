#include <BtsTraceDecoder.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(SymbolMapTest, DISABLED_InputTraceFileIsProcessedByTraceDecoder)
{
    BtsTraceDecoder traceDecoder;
    traceDecoder.saveSymbolTableFromObjdump(R"(C:\APRG\symbols.txt)");
    cout<<traceDecoder.getNearestLowerSymbol(0x08a0c623)<<"\n";
}

TEST(FileTest, DISABLED_InputTraceFileIsProcessedByTraceDecoderWithSymbolTableFromObjdump){
    BtsTraceDecoder traceDecoder;
    traceDecoder.saveSymbolTableFromObjdump(R"(C:\APRG\symbols.txt)");
    traceDecoder.processInputTraceFile(R"(C:\APRG\input.txt)");}

TEST(FileTest, DISABLED_InputTraceFileIsProcessedByTraceDecoderWithSymbolTableFromMappedFile)
{
    BtsTraceDecoder traceDecoder;
    traceDecoder.saveSymbolTableFromMappedFile(R"(C:\APRG\tcomr3.map)");
    traceDecoder.processInputTraceFile(R"(C:\APRG\input.txt)");
}

}
