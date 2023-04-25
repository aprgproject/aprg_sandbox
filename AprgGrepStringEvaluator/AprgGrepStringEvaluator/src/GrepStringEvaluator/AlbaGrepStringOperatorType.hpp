#pragma once

#include <string>

namespace alba {

enum class AlbaGrepStringOperatorType {
    Unknown,
    AndOperator,
    ClosingParenthesis,
    NotOperator,
    IgnoreOperator,
    OpeningParenthesis,
    OrOperator,
    XorOperator,
    XnorOperator,
};

}
