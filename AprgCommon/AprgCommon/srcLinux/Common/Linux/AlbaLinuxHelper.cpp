#include "AlbaLinuxHelper.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <cstring>
#include <string>

using namespace std;

namespace alba::AlbaLinuxHelper {

string getErrorMessage(int const localErrnoCopy) {
    constexpr size_t MAX_ERROR_CHAR_STRING = 256;
    array<char, MAX_ERROR_CHAR_STRING> characterBuffer{};
    auto str = strerror_r(localErrnoCopy, begin(characterBuffer), MAX_ERROR_CHAR_STRING);
    return string(str);
}

}  // namespace alba
