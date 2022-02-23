#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

namespace alba
{

class FileDestructor
{
public:
    FileDestructor();
    void destroy() const;
    void destroy(std::string const& path) const;
    void renameDirectoriesUnderneath(std::string const& directoryPath) const;
    void destroyFilesAndDirectories(std::string const& filePath) const;
    void renameDirectory(std::string const& directoryPath) const;
    void destroyFile(std::string const& filePath) const;

private:
    AlbaLocalPathHandler m_pathToDestroy;
};

}
