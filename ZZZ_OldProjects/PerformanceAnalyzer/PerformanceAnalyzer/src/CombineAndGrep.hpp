#pragma once

#include <fstream>
#include <string>

namespace alba {

struct CombineAndGrep {
    CombineAndGrep(std::string const& outputFilePath, std::string const& grepString);
    void processDirectory(std::string const& inputDirectoryPath);
    void processFile(std::string const& inputFilePath);

private:
    std::ofstream m_outputFileStream;
    std::string m_grepString;
};

}  // namespace alba
