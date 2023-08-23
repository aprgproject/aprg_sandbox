#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace alba {

class RttAnalyzer2 {
public:
    RttAnalyzer2(std::string const& outputFilePath);
    void processFile(std::string const& file);
    void processLine(std::ofstream& outputFile, std::string const& line);

    void saveTitle2();
    void processFile2(std::string const& file);
    void processLine2(std::string const& fileName, std::string const& line);

    void processFile3(std::string const& file);
    void processLine3(std::ofstream& outputFile, std::string const& line);

private:
    std::ofstream m_outputLogStream;
};

}  // namespace alba
