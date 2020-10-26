#pragma once

#include <set>
#include <string>
#include <vector>

namespace alba
{

class CPlusPlusFileFixer
{
public:
    void processDirectory(std::string const& path);
    void processFile(std::string const& path);

private:
    void clear();
    void checkFile(std::string const& path);
    void fix(std::string const& path);
    void writeFile(std::string const& path);
    bool isCPlusPlusHeader(std::string const& header) const;
    bool isOtherLibraryHeaders(std::string const& headerFoundInFile) const;
    bool isMainHeader(std::string const& headerFoundInFile, std::string const& filePath) const;

    std::vector<std::string> m_linesAfterTheHeader;
    std::vector<std::string> m_headerListFromAngleBrackets;
    std::set<std::string> m_headerListFromQuotation;
    bool m_isPragmaOnceFound;
};

}
