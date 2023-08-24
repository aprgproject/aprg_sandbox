#include "FileUtilities.hpp"

#include <fstream>

using namespace std;

namespace alba {

void clearContentsOfFile(string_view path) {
    ofstream fileStream(path.data());
    fileStream.close();
}

}  // namespace alba
