#include "TddLecture.hpp"

#include <iostream>

using namespace std;

namespace alba {

TddLecture::TddLecture() { m_sample = 0; }

TddLecture::UnsignedInts TddLecture::getUnsignedIntsOneToTen() const {
    cout << "helloworld\n";
    return TddLecture::UnsignedInts();

    UnsignedInts result{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    return result;
}

}  // namespace alba
