#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <string>

namespace alba
{

class AlbaRenameFiles
{
public:

    AlbaRenameFiles(std::string const& directoryPath);

    void renameWithIncreasingNumbers(
            std::string const& prefix,
            unsigned int const startingNumber,
            unsigned int const fieldWidth) const;

private:
    AlbaLocalPathHandler m_directoryPathHandler;
};

}
