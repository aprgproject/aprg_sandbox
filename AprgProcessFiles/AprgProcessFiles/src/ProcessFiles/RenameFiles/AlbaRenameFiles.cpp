#include "AlbaRenameFiles.hpp"

#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaRenameFiles::AlbaRenameFiles(string const& directoryPath) : m_directoryPathHandler(directoryPath) {}

void AlbaRenameFiles::renameWithIncreasingNumbers(
    string const& prefix, unsigned int const startingNumber, unsigned int const fieldWidth) const {
    StringConverterWithFormatting converter(fieldWidth, '0');

    ListOfPaths listOfFiles;
    ListOfPaths listOfDirectories;
    m_directoryPathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);

    unsigned int count = startingNumber;
    for (string const& file : listOfFiles) {
        AlbaLocalPathHandler filePathHandler(file);
        filePathHandler.renameFile(
            prefix + converter.convertToString(count++) + string(".") + filePathHandler.getExtension());
    }
}

}  // namespace alba
